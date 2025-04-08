#include <iostream>
#include <gtkmm/application.h>
#include "ventana_main.hpp"
#include "../fsys.hpp"

std::string deposito, HOME;
std::filesystem::path VentanaMain::path_store = deposito;

int main(int argc, char *argv[])
{
    try
    {
        Confirguracion(deposito, HOME);
    }
    catch (const char*&  err)
    {
        std::cerr << err;
        exit (-1);
    }

    // Ruta al depósito
    std::cout << "Deposito: " << deposito << std::endl;
    VentanaMain::path_store = deposito;

    auto app = Gtk::Application::create("pacomun.gtkmm.password");

    // Muestra la ventana y retorna cuando se cierra.
    return app->make_window_and_run<VentanaMain>(argc, argv);
}
