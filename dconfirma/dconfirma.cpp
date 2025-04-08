// dconfirma.cpp 
#include <iostream>
#include "dconfirma.hpp"
using namespace std;

Dconfirma* Dconfirma::m_pDconfirma;

Dconfirma::Dconfirma(const Glib::ustring& titulo,
        const Glib::ustring& mensaje)
    : m_Grid(),
    m_Label_Titulo(titulo),
    m_Label_mensaje(mensaje),
    m_Button_Ok("Aceptar"),
    m_Button_Cancel("Cancelar"),
    m_ButtonBox(Gtk::Orientation::HORIZONTAL)
{
    set_title("ATENCION");
    // set_default_size(500, 200);
    set_child(m_Grid);

    // Imagen
    auto m_pixbuf = Gdk::Pixbuf::create_from_file("/usr/share/pixmaps/gtkmm_password/g1.png");
    auto m_imagen = Gtk::Image(m_pixbuf);

    m_Label_Titulo.set_use_markup(true);
    m_Label_mensaje.set_use_markup(true);

    m_Grid.set_row_spacing(5);
    m_Grid.set_column_spacing(10);
    m_Grid.set_margin(8);
    m_imagen.set_pixel_size(48);
    m_imagen.set_halign(Gtk::Align::START);
    m_Grid.attach(m_imagen,1,1,1,2);
    m_Grid.attach(m_Label_Titulo,2,1,1,1);
    m_Grid.attach(m_Label_mensaje,2,2,1,1);

    m_ButtonBox.set_expand(); m_ButtonBox.set_halign(Gtk::Align::CENTER);
    m_ButtonBox.set_valign(Gtk::Align::END);
    m_ButtonBox.set_spacing(5);
    m_ButtonBox.append(m_Button_Cancel);
    m_ButtonBox.append(m_Button_Ok);
    m_ButtonBox.set_halign(Gtk::Align::CENTER);
    m_Grid.attach(m_ButtonBox,0,3,3,1);

}

Dconfirma::~Dconfirma()
{
    std::cout << "Llamada al destructor\n";
}

Glib::RefPtr<Dconfirma> Dconfirma::create(const Glib::ustring& titulo,
        const Glib::ustring& mensaje)
{
    m_pDconfirma = new Dconfirma(titulo, mensaje);
    auto refptr =  Glib::make_refptr_for_instance(m_pDconfirma);
    return refptr;
}

void Dconfirma::buttons_clicked_connect(const sigc::slot<void(const Glib::ustring&)>& slot)
{
    m_Button_Ok.signal_clicked().connect(sigc::bind(slot, "OK"));
    m_Button_Cancel.signal_clicked().connect(sigc::bind(slot, "Cancel"));
}

void Dconfirma::set_label_titulo(std::string& titulo)
{
    m_Label_Titulo.set_text(titulo);
    m_Label_Titulo.set_use_markup();
}

void Dconfirma::set_label_mensaje(std::string& mensaje)
{
    m_Label_mensaje.set_text(mensaje);
    m_Label_mensaje.set_use_markup();
}
// Control

// class ExampleWindow : public Gtk::Window
// {
//     public:
//         ExampleWindow();
//         ~ExampleWindow() override;

//     protected:
//         void on_button_clicled();
//         void  on_respuesta_dialogo(const Glib::ustring& res);
//         void on_dialogo_hidden();

//         Gtk::Button m_Button;

//         // Dconfirma m_Dconfirma;
//         Glib::RefPtr<Dconfirma> m_refDconfirma;
// };

// ExampleWindow::ExampleWindow()
//     : m_Button("Dialogo")
//     // m_Dconfirma("<b>Atención</b>", "Se borrará el archivo: <tt>archivo</tt>")
// {
//     set_default_size(400, 300);
//     set_child(m_Button);

//     m_Button.signal_clicked().connect(sigc::mem_fun(*this,
//                 &ExampleWindow::on_button_clicled));
//     m_refDconfirma = Dconfirma::create("<b>Atención</b>",
//             "Se borrará el archivo: <tt>archivo</tt>");

//     m_refDconfirma->set_transient_for(*this);
//     m_refDconfirma->set_modal();
//     m_refDconfirma->set_hide_on_close();
//     m_refDconfirma->buttons_clicked_connect(sigc::mem_fun(*this,
//                 &ExampleWindow::on_respuesta_dialogo));
//     m_refDconfirma->signal_hide().connect(sigc::mem_fun(*this,
//                 &ExampleWindow::on_dialogo_hidden));

    // m_Dconfirma.set_transient_for(*this);
    // m_Dconfirma.set_modal();
    // m_Dconfirma.set_hide_on_close();
    // m_Dconfirma.buttons_clicked_connect(sigc::mem_fun(*this,
    //             &ExampleWindow::on_respuesta_dialogo));
    // m_Dconfirma.signal_hide().connect(sigc::mem_fun(*this,
    //             &ExampleWindow::on_dialogo_hidden));
// }

// ExampleWindow::~ExampleWindow()
// {
// }

// void ExampleWindow::on_button_clicled()
// {
//     m_refDconfirma->set_visible(true);
//     // m_Dconfirma.set_visible(true);
// }

// void ExampleWindow::on_respuesta_dialogo(const Glib::ustring& resp)
// {
//     if (resp == "OK")
//         std::cout << "OK" << std::endl;
//     else
//         std::cout << "Cancelado" << std::endl;
//     m_refDconfirma->set_visible(false);
//     // m_Dconfirma.set_visible(false);
// }

// void ExampleWindow::on_dialogo_hidden()
// {
//     std::cout << "Se ha ocultado el dialogo." << std::endl;
// }


// int main(int argc, char *argv[])
// {
//     auto app = Gtk::Application::create("Pacomun.org");

//     return app->make_window_and_run<ExampleWindow>(argc, argv);
// }
