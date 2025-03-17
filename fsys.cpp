// Lectura de directorioo
#include <algorithm>
#include "fsys.hpp"

bool LeerDeposito(const std::string& path, listado& list)
{
    for (auto dir_entry : std::filesystem::directory_iterator{path})
    {
        if (static_cast<std::string>(dir_entry.path().filename())[0] != '.')
        {
            if (dir_entry.is_directory())
               list.carpetas.push_back(dir_entry);
            else
                list.archivos.push_back(dir_entry);
        }
    }
    // Ordenar los vectores.
    
    std::sort(list.archivos.begin(), list.archivos.end());
    std::sort(list.carpetas.begin(), list.carpetas.end());
    return true;
}

