// ventana_main.cpp 
#include <iostream>
#include "ventana_main.hpp"


// Constructor de VentanaMain
VentanaMain::VentanaMain()
    : m_VBox(Gtk::Orientation::VERTICAL),
    m_Button_Quit("Salir")
{
    // Título de la ventana y tamaño por defecto.
    set_title("Gtkmm Password");
    set_default_size(800, 600);

    // Colocamos el margen y añadimos la caja vertical.
    m_VBox.set_margin(5);
    set_child(m_VBox);

    // Añadimos el TreeView con el ScrolledWindow y el botón debajo.
    m_ScrolledWindown.set_child(m_TreeView);

    // Sólo muestra la barra si es necesario
    m_ScrolledWindown.set_policy(
            Gtk::PolicyType::AUTOMATIC,
            Gtk::PolicyType::AUTOMATIC);
    m_ScrolledWindown.set_expand(true);

    m_VBox.append(m_ScrolledWindown);
    m_VBox.append(m_ButtonBox);

    m_ButtonBox.append(m_Button_Quit);
    m_ButtonBox.set_margin(5);
    m_Button_Quit.set_expand(false);
    m_Button_Quit.set_halign(Gtk::Align::END);
    m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this,
                &VentanaMain::on_button_quit));

    // Crear el modelo
    m_refTreeModel = Gtk::TreeStore::create(m_Columns);
    m_TreeView.set_model(m_refTreeModel);

    // Llenar el modelo
    try
    {
        LeerDeposito("./password-store", m_listado);
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: al lleer depósito. "<< e.what() << std::endl;
        exit(1);
    }
    int id = 0;
    for (int it = 0; it < m_listado.carpetas.size(); it++)
    {
        auto row = *(m_refTreeModel->append());
        row[m_Columns.col_id] = id;
        row[m_Columns.m_directory_entry] = m_listado.carpetas[it];
        row[m_Columns.col_name] = m_listado.carpetas[it].path().stem().c_str();
        id++;
        m_hijos.archivos.clear(); // para no acumular archivos.
        LeerDeposito(m_listado.carpetas[it].path(),m_hijos);
        for (auto i : m_hijos.archivos)
        {
            auto childrow = *(m_refTreeModel->append(row.children()));
            childrow[m_Columns.col_id] = id;
            childrow[m_Columns.col_name] = i.path().stem().c_str();
            childrow[m_Columns.m_directory_entry] = i;
            id++;
        }

    }
    for (auto i : m_listado.archivos)
    {
        auto row = *(m_refTreeModel->append());
        row[m_Columns.col_id] = id;
        row[m_Columns.m_directory_entry] = i;
        row[m_Columns.col_name] = i.path().stem().c_str();
        id++;
    }

    // Añadir las columnas al su TreeView
    // m_TreeView.append_column("ID", m_Columns.col_id);
    m_TreeView.append_column("Nombre", m_Columns.col_name);

    // Conectar señal
    m_TreeView.signal_row_activated().connect(sigc::mem_fun(*this,
                &VentanaMain::on_treeview_row_activate));
}

VentanaMain::~VentanaMain()
{
}

void VentanaMain::on_button_quit()
{
    set_visible(false);
}

void VentanaMain::on_treeview_row_activate(const Gtk::TreeModel::Path& path,
        Gtk::TreeViewColumn* /* column */)
{
    const auto iter = m_refTreeModel->get_iter(path);
    if (iter)
    {
        const auto row = *iter;
        std::cout << "Row activated: ID=" << row[m_Columns.col_id] << ", Name="
            << row[m_Columns.col_name] << std::endl;
        std::cout << row[m_Columns.m_directory_entry] << std::endl;
    }
}

