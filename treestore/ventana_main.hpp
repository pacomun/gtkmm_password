/* Ventana principal para la aplicación.
 *
 */
#ifndef VENTANA_MAIN_H
#define VENTANA_MAIN_H
#include <gtkmm.h>
#include "../fsys.hpp"
#include "../textview/textview.hpp"
#include "../mdialogo/mdialogo.hpp"
#include "../dconfirma/dconfirma.hpp"


class VentanaMain : public Gtk::Window
{
    protected:
        // Manejadores de señal
        void on_button_quit();
        void on_button_Nueva();
        void on_button_eliminar();
        void on_button_bajar();
        void on_button_subir();
        void on_treeview_row_activate(const Gtk::TreeModel::Path& path,
                Gtk::TreeViewColumn* column);
        void on_mdialogo_ok(std::string& datos, std::filesystem::directory_entry& dir_entry);
        void on_dconfirma_resp(const Glib::ustring& cad);

        // Modelo de columnas
        class ModelColumns : public Gtk::TreeModel::ColumnRecord
        {
            public:
                ModelColumns()
                { add(col_id);
                  add(col_name);
                  add(m_directory_entry);
                }

                Gtk::TreeModelColumn<int> col_id;
                Gtk::TreeModelColumn<std::filesystem::directory_entry> m_directory_entry;
                Gtk::TreeModelColumn<Glib::ustring> col_name;
        };
        
        ModelColumns m_Columns;

        // Widget hijos.
        Gtk::Box m_VBox;
        VisorTexto m_VisorTexto;
        Mdialogo m_Mdialogo;

        Gtk::ScrolledWindow m_ScrolledWindown;
        Gtk::TreeView m_TreeView;
        Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;
        Glib::RefPtr<Dconfirma> m_refDconfirma;
        Glib::RefPtr<Gtk::AlertDialog> m_refDialog;

        Gtk::Box m_ButtonBox;
        Gtk::Button m_Button_Quit;
        Gtk::Button m_Button_Nueva;
        Gtk::Button m_Button_Eliminar;
        Gtk::Button m_Button_Subir;
        Gtk::Button m_Button_Bajar;


        // Listado de carpetas y archivos.
        listado m_listado, m_hijos;
        // directory seleccionado.
        std::filesystem::directory_entry m_selected_entry;

    public:
        VentanaMain();
        virtual ~VentanaMain();
        static std::filesystem::path path_store;

    private:
        void llenar_modelo();
        void refrescar_modelo();
        Gtk::TreeModel::Path m_treemodel_path;
};

#endif /* VENTANA_MAIN_H */
