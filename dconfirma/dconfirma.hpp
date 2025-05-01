// dconfirma.hpp 
// Diálogo para respuesta a una cuestión.
#ifndef DCONFIRMA_H
#define DCONFIRMA_H
#include <gtkmm.h>


class Dconfirma : public Gtk::Window
{
    protected:
       // Widget hijos
        Gtk::Grid m_Grid;
        Gtk::Label m_Label_Titulo, m_Label_mensaje;
        Gtk::Box m_ButtonBox;
        Gtk::Button m_Button_Cancel, m_Button_Ok;

        static Dconfirma * m_pDconfirma;
 
    public:
        Dconfirma(const Glib::ustring& titulo="",
                const Glib::ustring& mensaje="");
        virtual ~Dconfirma();

        // Métodos.
        void set_label_titulo(std::string& titulo);
        void set_label_mensaje(std::string& mensaje);

        // Señal a conectar ambos botones
        void buttons_clicked_connect(const sigc::slot<void(const Glib::ustring&)>& slot);

        // Contructor para un puntero inteligente
        static Glib::RefPtr<Dconfirma> create(const Glib::ustring& titulo,
                const Glib::ustring& mensaje);
};

#endif /* DCONFIRMA_H */
