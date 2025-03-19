// Ventana con Gtk::TextView para mostrar la Clave descifrada.
#ifndef TEXTVIEW_H
#define TEXTVIEW_H
#include <gtkmm.h>

class VisorTexto : public Gtk::Window
{
    private:
        // Nanejadores de señal.
        void on_button_quit();

        // widgets hijos
        Gtk::Box m_VBox;

        Gtk::ScrolledWindow m_ScrolledWindow;
        Gtk::TextView m_TextView;

        Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;
        Gtk::Box m_ButtonBox;
        Gtk::Button m_Button_Quit;

    public:
        VisorTexto();
        virtual ~VisorTexto();
        void set_text(const Glib::ustring& salida);
};

#endif /* TEXTVIEW_H */
