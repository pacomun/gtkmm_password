// mdialogo.hpp -Objeto dialogo personalizado-
#ifndef MDIALOGO_H
#define MDIALOGO_H
#include <gtkmm.h>
#include <filesystem>
#include <vector>

class Mdialogo : public Gtk::Window
{
    protected:
        // Widget miembros
        Gtk::Grid m_Grid;
        Gtk::Label m_Label_Carpeta;
        Gtk::ComboBoxText m_ComboBoxText;
        Gtk::Label m_Label_Clave;
        Gtk::Entry m_Entry_Clave;
        Gtk::Entry m_Entry_pass;
        Gtk::Button m_Button_Gen;
        Gtk::ScrolledWindow m_ScrolledWindow;
        Gtk::TextView m_TextView;
        Gtk::Box m_ButtonBox;
        Gtk::Button m_Button_Cancel, m_Button_Ok;

    public:
        Mdialogo();
        virtual ~Mdialogo();

        // Manejadores de señal
        void on_button_cancel();
        void on_button_ok();
        void on_button_gen();

        void set_vdirectory_entry(std::vector<std::filesystem::directory_entry>& dir_entry);
        std::vector<std::filesystem::directory_entry>& get_vdirectoory_entry();

        using type_signal_ok = sigc::signal<void(std::string&, std::filesystem::directory_entry&)>; 
        type_signal_ok signal_ok();

        Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;

    private:
        std::vector<std::filesystem::directory_entry> vdirectory_entry;
        type_signal_ok m_signal_ok;
        void recuperar_datos(std::string& datos, std::filesystem::directory_entry& m_dir_entry);
};

#endif /* MDIALOGO_H */
