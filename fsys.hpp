#ifndef FSYS_HPP
#define FSYS_HPP value
#include <filesystem>
#include <vector>
#include <string>
#include <gpgme.h>
#include <toml.hpp>



/* Variables Globales */
extern std::string HOME, deposito;

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

namespace pcm {

    // Genera claves válidas
    std::string GenerarClave(
            int longitud,  // Longitud 
            bool digit=true, // Con números
            bool signos=true);  // Con siginos ortográficos.

} /* End namespace pcm */

// Función que actualiza cambios desde repositorios de claves
std::string HacerPull();

// Función que realiza commit y envía cambios al servidor
std::string HacerPush();

// Función para configurar la aplicación.
int Confirguracion(std::string& deposito, std::string& HOME);

#endif /* ifndef FSYS_HPP */
