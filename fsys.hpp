#ifndef FSYS_HPP
#define FSYS_HPP value
#include <filesystem>
#include <vector>
#include <string>


/* Estructura de datos para guardar listado de archivos y directorios */
struct listado
{
    std::vector<std::filesystem::directory_entry> carpetas;
    std::vector<std::filesystem::directory_entry> archivos;
};


/* Llena dos vectores, uno con carpetas y otro con archivos. */
bool LeerDeposito(const std::string& path, listado& list);

#endif /* ifndef FSYS_HPP */
