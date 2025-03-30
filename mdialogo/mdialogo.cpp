// mdialogo.cpp Dialogo personalizado.
#include "mdialogo.hpp" 
#include <iostream>
#include "../treestore/ventana_main.hpp"


Mdialogo::Mdialogo()
    : Gtk::Window(),
    m_Label_Carpeta("Carpeta", Gtk::Align::START),
    m_ComboBoxText(true),
    m_Label_Clave("Nombre:"),
    m_Entry_Clave(),
    m_Button_Gen("Generar"),
    m_TextView(),
    m_ButtonBox(Gtk::Orientation::HORIZONTAL),
    m_Button_Cancel("Cancelar"),
    m_Button_Ok("Ok")
{
    set_title("Dialogo personalizado");
    set_default_size(500, 350);

    set_child(m_Grid);
    m_Grid.set_row_spacing(4);
    m_Grid.set_column_spacing(4);
    m_Grid.set_expand(true);
    m_Grid.set_margin(15);
    m_Grid.set_row_spacing(8);

    m_ScrolledWindow.set_child(m_TextView);
    m_ScrolledWindow.set_expand();

    m_ButtonBox.append(m_Button_Cancel);
    m_ButtonBox.append(m_Button_Ok);
    m_ButtonBox.set_spacing(5);
    m_ButtonBox.set_halign(Gtk::Align::END);
    m_ButtonBox.set_margin(5);
    
    
    m_Grid.attach(m_Label_Carpeta, 1, 1);
    m_Grid.attach(m_ComboBoxText, 2, 1);
    m_Grid.attach(m_Label_Clave, 1, 2);
    m_Grid.attach(m_Entry_Clave, 2, 2);
    m_Grid.attach(m_Entry_pass, 2, 3);
    m_Grid.attach(m_Button_Gen, 3, 3);
    m_Grid.attach(m_ScrolledWindow, 2, 4);
    m_Grid.attach(m_ButtonBox, 1, 5, 5, 1);

    // ComboBox
    // for (auto it : vdirectory_entry)
    //     m_ComboBoxText.append(it.path().stem().c_str());

    // Conectar señales
    m_Button_Ok.signal_clicked().connect(sigc::mem_fun(*this,
                &Mdialogo::on_button_ok));
    m_Button_Cancel.signal_clicked().connect(sigc::mem_fun(*this,
                &Mdialogo::on_button_cancel));
    m_Button_Gen.signal_clicked().connect(sigc::mem_fun(*this,
                &Mdialogo::on_button_gen));
}

Mdialogo::~Mdialogo()
{
}

void Mdialogo::on_button_ok()
{
    std::string datos;
    std::filesystem::directory_entry m_dir_entry;
    recuperar_datos(datos, m_dir_entry);
    m_signal_ok.emit(datos, m_dir_entry);
    std::cout << "Pulsado botón OK\n";
    set_visible(false);
}

void Mdialogo::on_button_cancel()
{
    std::cout << "Pulsado botón Cancel\n";
    set_visible(false);
}

void Mdialogo::on_button_gen()
{
    std::cout << "Pulsado botón gen\n";
    set_visible(false);
}

void Mdialogo::set_vdirectory_entry(std::vector<std::filesystem::directory_entry>& dir_entry)
{
    m_ComboBoxText.remove_all();
    vdirectory_entry = dir_entry;
    for (auto it : dir_entry)
    {
        m_ComboBoxText.append( it.path().stem().c_str());
    }
}

std::vector<std::filesystem::directory_entry>& Mdialogo::get_vdirectoory_entry()
{
    return vdirectory_entry;
}

Mdialogo::type_signal_ok Mdialogo::signal_ok()
{
    return m_signal_ok;
}

void Mdialogo::recuperar_datos(std::string& datos, std::filesystem::directory_entry& dir_entry)
{
    // Cargar cadena datos.
    m_refTextBuffer = m_TextView.get_buffer();

    datos = m_Entry_pass.get_text() + "\n" + m_refTextBuffer->get_text();

    std::filesystem::path clave_tmp;
    clave_tmp = VentanaMain::path_store;
    for(auto it : vdirectory_entry)
    {
        if (it.path().stem().c_str() == m_ComboBoxText.get_entry_text())
        {
            clave_tmp = it.path();
            break;
        }
    }
    if (m_ComboBoxText.get_entry_text().empty())
        clave_tmp = clave_tmp / static_cast<std::string>(m_Entry_Clave.get_text());
    else
    {
        clave_tmp = VentanaMain::path_store / static_cast<std::string>(m_ComboBoxText.get_entry_text());
        clave_tmp = clave_tmp / static_cast<std::string>(m_Entry_Clave.get_text());
    }

    dir_entry.assign(clave_tmp);
    // Añadir extensión
    std::string tmp = dir_entry.path().string() + ".gpg";
    dir_entry.assign(tmp);
}


