// ventana_main.cpp 
#include <iostream>
#include "ventana_main.hpp"
#include "../fsys.hpp"


// Constructor de VentanaMain
VentanaMain::VentanaMain()
    : m_VBox(Gtk::Orientation::VERTICAL),
    m_VisorTexto(),
    m_Button_Quit("Salir"),
    m_Button_Nueva("Nueva Clave"),
    m_Button_Eliminar("Eliminar Clave"),
    m_Button_Subir("Subir al servidor"),
    m_Button_Bajar("Bajar del servidor")
{
    // Título de la ventana y tamaño por defecto.
    set_title("Gtkmm Password");
    set_default_size(800, 600);

    // Ventana visor de texto
    m_VisorTexto.set_default_size(500, 250);
    m_VisorTexto.set_transient_for(*this);
    m_VisorTexto.set_modal();
    m_Mdialogo.set_hide_on_close();
    m_Mdialogo.set_transient_for(*this);
    m_Mdialogo.set_modal();
    m_Mdialogo.set_hide_on_close();

    // Ventana para confirmar borrado.
    m_refDconfirma = Dconfirma::create("<b>Atención</b>", "");
    m_refDconfirma->set_transient_for(*this);
    m_refDconfirma->set_modal();
    m_refDconfirma->set_hide_on_close();


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

    // Añadir ScrolledWindow a la caja central
    m_VBox.append(m_ScrolledWindown);
    m_VBox.append(m_ButtonBox);

    // Añado los botones en su propia caja
    m_ButtonBox.set_halign(Gtk::Align::END);
    m_ButtonBox.set_margin(5);
    m_ButtonBox.append(m_Button_Subir);
    m_ButtonBox.append(m_Button_Bajar);
    m_ButtonBox.append(m_Button_Nueva);
    m_ButtonBox.append(m_Button_Eliminar);
    m_ButtonBox.append(m_Button_Quit);
    m_Button_Quit.set_expand(false);

    // Conecto señales
    m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this,
                &VentanaMain::on_button_quit));
    m_Button_Nueva.signal_clicked().connect(sigc::mem_fun(*this,
                &VentanaMain::on_button_Nueva));
    m_Button_Eliminar.signal_clicked().connect(sigc::mem_fun(*this,
                &VentanaMain::on_button_eliminar));
    m_Button_Subir.signal_clicked().connect(sigc::mem_fun(*this,
                &VentanaMain::on_button_subir));
    m_Button_Bajar.signal_clicked().connect(sigc::mem_fun(*this,
                &VentanaMain::on_button_bajar));
    m_Mdialogo.signal_ok().connect(sigc::mem_fun(*this, 
                &VentanaMain::on_mdialogo_ok));
    m_refDconfirma->buttons_clicked_connect(sigc::mem_fun(*this,
                &VentanaMain::on_dconfirma_resp));

    // Crear el modelo
    m_refTreeModel = Gtk::TreeStore::create(m_Columns);
    m_TreeView.set_model(m_refTreeModel);

    // Poner el directorio de trabajo al depósito de claves.
    std::filesystem::current_path(VentanaMain::path_store);

    // Llenar el modelo
    try
    {
        LeerDeposito(std::filesystem::current_path() , m_listado);
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << 
        e.what();
    }
   
    llenar_modelo();

    // Añadir las columnas al su TreeView
    m_TreeView.append_column("Nombre", m_Columns.col_name);

    // Conectar señal 
    m_TreeView.signal_row_activated().connect(sigc::mem_fun(*this,
                &VentanaMain::on_treeview_row_activate));

    // Crear Diálogo de alertea
    m_refDialog = Gtk::AlertDialog::create();

}

VentanaMain::~VentanaMain()
{
}

void VentanaMain::on_button_quit()
{
    set_visible(false);
}

void VentanaMain::on_button_Nueva()
{
    m_Mdialogo.set_vdirectory_entry(m_listado.carpetas);
    m_Mdialogo.set_visible(true);
}

void VentanaMain::on_button_eliminar()
{
    auto refTreeSelection = m_TreeView.get_selection();
    auto iter = refTreeSelection->get_selected();
    if (iter)
    {
        auto row = *iter;
        std::cout << "Fila seleccionada: " << row[m_Columns.m_directory_entry] << std::endl;
        m_selected_entry = row[m_Columns.m_directory_entry]; // Valor seleccionado.
        std::string mensaje = "Se borrará la clave <tt>";
        mensaje = mensaje +
            std::string{static_cast<std::filesystem::directory_entry>(row[m_Columns.m_directory_entry]).path().stem()};
        mensaje += "</tt>";

        m_refDconfirma->set_label_mensaje((mensaje));
        m_refDconfirma->set_visible(true);
    }
}

void VentanaMain::on_button_bajar()
{
    m_refDialog->set_buttons({});
    m_refDialog->set_default_button(-1);
    m_refDialog->set_message("Bajar del servidor");
    auto salida = HacerPull();
    m_refDialog->set_detail(salida);
    m_refDialog->show(*this);
}

void VentanaMain::on_button_subir()
{
    m_refDialog->set_buttons({});
    m_refDialog->set_default_button(-1);
    m_refDialog->set_message("Subir al servidor");
    auto salida = HacerPush();
    m_refDialog->set_detail(salida);
    m_refDialog->show(*this);
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
        auto m_dir_entry = static_cast<std::filesystem::directory_entry>(row[m_Columns.m_directory_entry]);
        if (!m_dir_entry.is_directory())
        {
            std::string salida;
            try
            {
            salida = DescifrarClave(m_dir_entry);
            }
            catch (const char* e )
            {
                std::cerr << "Excepción: " << e << std::endl;
                return;
            }
            m_VisorTexto.set_visible(true);
            m_VisorTexto.set_text(salida);
        }
    }
}

void VentanaMain::on_mdialogo_ok(std::string& datos, std::filesystem::directory_entry& dir_entry)
{
    std::cout << "Señal emitida: \n" << "Nueva ruta = " << dir_entry <<
       "\nContraseña = " << datos << std::endl;
    try
    {
        CifrarClave(datos, dir_entry);
    }
    catch (...)
    {
        std::cerr << "Error en cifrado: " << dir_entry << std::endl;
    }
    refrescar_modelo();
}

void VentanaMain::on_dconfirma_resp(const Glib::ustring& cad)
{
    if (cad == "OK")
    {
        std::cout << "capturado OK\n";
        m_refDconfirma->set_visible(false);
        std::cout << "Entrada de directorio seleccionada = " << m_selected_entry << std::endl;
        try
        {
            std::filesystem::remove(m_selected_entry);;
        }
        catch (std::exception& e)
        {
            m_refDialog->set_message("Error:");
            m_refDialog->set_detail(e.what());
            std::cerr << "Error: " << e.what() << std::endl;
            m_refDialog->show(*this);
            return;
        }
        std::cout << "Borrada clave " << m_selected_entry << std::endl;
        refrescar_modelo();
    }
    else
    {
        std::cout << "Se a cancelado la operación.\n";
        m_refDconfirma->set_visible(false);
    }
}

void VentanaMain::llenar_modelo()
{
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
}

void VentanaMain::refrescar_modelo()
{
    m_refTreeModel->clear();
    m_listado.carpetas.clear();
    m_listado.archivos.clear();
    LeerDeposito(std::filesystem::current_path(), m_listado);
    llenar_modelo();
}
