#include <gtkmm/application.h>
#include "ventana_main.hpp"


int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create("pacomun.gtkmm.password");

    // Muestra la ventana y retorna cuando se cierra.
    return app->make_window_and_run<VentanaMain>(argc, argv);
}
