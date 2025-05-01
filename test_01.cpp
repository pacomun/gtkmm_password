// Aplicación de control de fsys.hpp
#include <iostream>
#include <string>
#include "fsys.hpp"
using namespace std;

void ImprimirListado(listado& m_list)
{
    cout << "Archivos:\n---\n";
    for (auto it : m_list.archivos)
        cout << it << endl;
    cout << "\nCarpetas:\n---\n";
    for (auto it : m_list.carpetas)
        cout << it << endl;
}

int main(int argc, char *argv[])
{
    std::string namefile = "/home/pacomun/.password-store";
    // std::string namefile = ".";
    listado m_list;

    try
    {
        LeerDeposito(namefile, m_list);
    }
    catch (const char* e)
    {
        cerr << e;
        exit(-1);
    }

    ImprimirListado(m_list);


    // DescifrarClave(list.archivos[0]);

    return 0;
}
