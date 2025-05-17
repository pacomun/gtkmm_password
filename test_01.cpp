// Aplicación de control de fsys.hpp
#include <iostream>
#include "fsys.hpp"


int main(int argc, char *argv[])
{
    listado list;
    std::filesystem::path temp_path = std::filesystem::temp_directory_path();
    std::string namefile = "password-store";
    std::filesystem::path deposito = temp_path  /  namefile;
    std::filesystem::create_directory(deposito);
    std::cout << "Depósito temporal: " << deposito << std::endl;
    std::filesystem::path clave = deposito/ "clave.gpg";
    std::cout << "Depósito temporal: " << deposito << std::endl;
    std::filesystem::directory_entry dir_clave(clave);
    std::string cadena_a_cifrar = "Esto es una cadena cifrada...\n";
    try
    {
        CifrarClave(cadena_a_cifrar, dir_clave);
    }
    catch (const char* e)
    {
        std::cerr << e << std::endl;
    }

    LeerDeposito(deposito, list);

    for (auto it : list.carpetas)
        std::cout << it.path().filename() << std::endl;
    for (auto it : list.archivos)
        std::cout << it.path().stem() << std::endl;

    auto salida = DescifrarClave(list.archivos[0]);
    std::cout << "Salida: " << salida << std::endl;

    return 0;
}
