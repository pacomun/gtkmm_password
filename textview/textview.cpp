// textview.cpp 
#include "textview.hpp"


VisorTexto::VisorTexto()
    : m_VBox(Gtk::Orientation::VERTICAL),
    m_Button_Quit("Cerrar")
{
    set_title("Clave");
    set_default_size(600, 300);

    m_VBox.set_margin(5);
    set_child(m_VBox);

    // Añadir m_TextView, con la barra de desplazamiento
    m_TextView.set_editable(false);
    m_TextView.set_cursor_visible(false);
    m_ScrolledWindow.set_child(m_TextView);
    m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC,
            Gtk::PolicyType::AUTOMATIC);
    m_ScrolledWindow.set_expand(true);

    m_VBox.append(m_ScrolledWindow);

    // Butón cerrar.
    m_ButtonBox.set_orientation(Gtk::Orientation::HORIZONTAL);
    m_ButtonBox.append(m_Button_Quit);
    m_ButtonBox.set_halign(Gtk::Align::CENTER);
    m_ButtonBox.set_margin(5);
    m_ButtonBox.set_spacing(5);
    m_VBox.append(m_ButtonBox);

    // Conectar señales.
    m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this,
                &VisorTexto::on_button_quit));
}

VisorTexto::~VisorTexto()
{
}

void VisorTexto::on_button_quit()
{
    set_visible(false);
}

void VisorTexto::set_text(const Glib::ustring& salida)
{
    m_refTextBuffer = Gtk::TextBuffer::create();
    m_refTextBuffer->set_text(salida);
    m_TextView.set_buffer(m_refTextBuffer);
}

