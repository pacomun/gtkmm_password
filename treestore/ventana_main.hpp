/* Ventana principal para la aplicación.
 *
 */
#ifndef VENTANA_MAIN_H
#define VENTANA_MAIN_H
#include <gtkmm.h>
#include "../fsys.hpp"
#include "../textview/textview.hpp"


class VentanaMain : public Gtk::Window
{
    protected:
        // Manejadores de señal
        void on_button_quit();
        void on_treeview_row_activate(const Gtk::TreeModel::Path& path,
                Gtk::TreeViewColumn* column);

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

        Gtk::ScrolledWindow m_ScrolledWindown;
        Gtk::TreeView m_TreeView;
        Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;

        Gtk::Box m_ButtonBox;
        Gtk::Button m_Button_Quit;

        // Listado de carpetas y archivos.
        listado m_listado, m_hijos;

    public:
        VentanaMain();
        virtual ~VentanaMain();
};

#endif /* VENTANA_MAIN_H */
