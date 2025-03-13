/* Ventana principal para la aplicación.
 *
 */
#ifndef VENTANA_MAIN_H
#define VENTANA_MAIN_H
#include <gtkmm.h>

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
                { add(col_id); add(col_name); }

                Gtk::TreeModelColumn<int> col_id;
                Gtk::TreeModelColumn<Glib::ustring> col_name;
        };
        
        ModelColumns m_Columns;

        // Widget hijos.
        Gtk::Box m_VBox;

        Gtk::ScrolledWindow m_ScrolledWindown;
        Gtk::TreeView m_TreeView;
        Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;

        Gtk::Box m_ButtonBox;
        Gtk::Button m_Button_Quit;

    public:
        VentanaMain();
        virtual ~VentanaMain();
};

#endif /* VENTANA_MAIN_H */
