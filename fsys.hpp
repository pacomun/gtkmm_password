#ifndef FSYS_HPP
#define FSYS_HPP value
#include <vector>
#include <string>


/* Estructura de datos para guardar listado de archivos y directorios */
struct listado
{
    std::vector<std::string> carpetas;
    std::vector<std::string> archivos;
};

// Funcion que lee directorio, devueve vector de cadenas.
std::vector<std::string> LeerDirectorio(const std::string& path);

// Funcion que discierne entre directorio y archivo regular.
int TypeFile(const std::string& entrada);

/* Llena dos vectores, uno con carpetas y otro con archivos. */
bool LeerDeposito(const std::string& path, listado& list);

/* descifra u archivo */
std::string DescifrarClave(std::string& nombre_clave);

/* Cifrar clave recibe datos y un cadena con dir_entry */
void CifrarClave(std::string& datos, std::string& dir_entry);

#endif /* ifndef FSYS_HPP */
