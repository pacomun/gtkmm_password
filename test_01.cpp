// Aplicación de control de fsys.hpp
#include <iostream>
#include "fsys.hpp"


int main(int argc, char *argv[])
{
    std::string namefile = "./password-store";
    listado list;

    LeerDeposito(namefile, list);

    for (auto it : list.carpetas)
        std::cout << it.path().filename() << std::endl;
    for (auto it : list.archivos)
        std::cout << it.path().stem() << std::endl;

    DescifrarClave(list.archivos[0]);

    return 0;
}
