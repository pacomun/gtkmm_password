#ifndef FSYS_HPP
#define FSYS_HPP value
#include <filesystem>
#include <vector>
#include <string>
#include <gpgme.h>



/* Estructura de datos para guardar listado de archivos y directorios */
struct listado
{
    std::vector<std::filesystem::directory_entry> carpetas;
    std::vector<std::filesystem::directory_entry> archivos;
};

struct clave
{
    std::string cad_clave;
    std::string cad_auxi;
};

/* Llena dos vectores, uno con carpetas y otro con archivos. */
bool LeerDeposito(const std::filesystem::path& path, listado& list);

/* Descifrar un archivo de claves. */
std::string DescifrarClave(std::filesystem::directory_entry& nombre_clave);

// Cifrar los datos pasados en el archivo dir_entry.
// // Cifrar los datos pasados en el archivo dir_entry.
void CifrarClave(std::string& datos, std::filesystem::directory_entry& dir_entry);

#endif /* ifndef FSYS_HPP */
