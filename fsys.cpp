// Lectura de directorioo
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include "fsys.hpp"
#include "auxiliar.h"


#define SIZE 512


bool LeerDeposito(const std::filesystem::path& path, listado& list)
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


std::string DescifrarClave(std::filesystem::directory_entry& nombre_clave)
{
    char buf[SIZE];
    char *p;
    size_t read_bytes;
    bool tmp;
    std::string m_clave;
    gpgme_ctx_t ctx;
    gpgme_error_t err;
    gpgme_data_t data, cipher;

    // Iniciar el entorno GPGME
    init_gpgme(GPGME_PROTOCOL_OpenPGP);
    
    // Crear contexto
    err = gpgme_new(&ctx);
    if (err != GPG_ERR_NO_ERROR) throw "Error: en descifrado.\n";

    // Poner nuestro protocolo al contexto.
    err = gpgme_set_protocol(ctx, GPGME_PROTOCOL_OpenPGP);
    if (err != GPG_ERR_NO_ERROR) throw "Error: en descifrado.\n";

    // Crear el buffer para intercambio de datos con gpgme
    err = gpgme_data_new(&data);
    if (err != GPG_ERR_NO_ERROR) throw "Error: en descifrado.\n";

    // Lectura del archivo clave
    err = gpgme_data_new_from_file(&cipher, nombre_clave.path().c_str(), 1);
    if (err != GPG_ERR_NO_ERROR) throw "Error: en descifrado.\n";

    // Descifrar.
    err = gpgme_op_decrypt(ctx, cipher, data);
    if (err != GPG_ERR_NO_ERROR) throw "Error: en descifrado.\n";

    // Recuperar texto descifrado.
    read_bytes = gpgme_data_seek(data, 0, SEEK_SET);
    while ((read_bytes = gpgme_data_read(data, buf, SIZE)) > 0)
    {
        for (size_t i = 0; i < read_bytes; i++)
            m_clave += buf[i];
    }
    
    gpgme_release(ctx);
    gpgme_data_release(cipher);
    gpgme_data_release(data);

    return m_clave;
}

void CifrarClave(std::string& datos, std::filesystem::directory_entry& dir_entry)
{
    char buf[SIZE];
    char *p;
    size_t read_bytes;
    bool tmp;
    std::string m_clave;
    gpgme_key_t keys[2] = {0, 0};
    gpgme_ctx_t ctx;
    gpgme_error_t err;
    gpgme_data_t data, cipher;

    // Iniciar el entorno GPGME
    init_gpgme(GPGME_PROTOCOL_OpenPGP);
    
    // Crear contexto
    err = gpgme_new(&ctx);
    if (err != GPG_ERR_NO_ERROR) throw "Error: al cifrar cadena.\n";

    // Poner nuestro protocolo al contexto.
    err = gpgme_set_protocol(ctx, GPGME_PROTOCOL_OpenPGP);
    if (err != GPG_ERR_NO_ERROR) throw "Error: al cifrar cadena.\n";

    gpgme_set_armor(ctx, 1);
    
    // Cargar cadena a cifrar.º
    err = gpgme_data_new_from_mem(&data, datos.c_str(), datos.size(), 1);
    if (err != GPG_ERR_NO_ERROR) throw "Error: al cifrar cadena.\n";

    // Incializar contenedor para datos cifrados.
    err = gpgme_data_new(&cipher);
    if (err != GPG_ERR_NO_ERROR) throw "Error: al cifrar cadena.\n";

    // Leer claves pública principal.
    err = gpgme_op_keylist_start(ctx, "pacomun", 0);
    if (err != GPG_ERR_NO_ERROR) throw "Error: al cifrar cadena.\n";

    err = gpgme_op_keylist_next(ctx, keys);
    if (err != GPG_ERR_NO_ERROR) throw "Error: al cifrar cadena.\n";

    keys[1] = 0; // Termina en clave nula.

    // Cifrar datos.
    err = gpgme_op_encrypt(ctx, keys, GPGME_ENCRYPT_ALWAYS_TRUST, data, cipher);
    if (err != GPG_ERR_NO_ERROR) throw "Error: al cifrar cadena.\n";

    // Crea el directorio si es nuevo.
    // if (!std::filesystem::exists(dir_entry.path().parent_path()))
    //     std::filesystem::create_directories(dir_entry.path().parent_path());

    FILE *fd;
    fd = fopen(dir_entry.path().c_str(), "w");
    if (fd)
    {
        print_data(cipher, fd);
        fclose(fd);
    }
    else
        throw "No se pudo abrir archivo para escritura\n";

    gpgme_release(ctx);
    gpgme_data_release(data);
    gpgme_data_release(cipher);
    gpgme_key_release(keys[0]);
}

std::string HacerPull()
{
    std::string command, salida;
    std::vector<std::string> v_cad;
    // Poner el directorio de trabajo a deposito
    
    // Montar path del archivo de log.
    std::filesystem::path tmp_file = std::filesystem::temp_directory_path() / "gtkmm_password.log";

    // std::cout << "Directorio de trabajo: "  << std::filesystem::current_path() << std::endl;
    command = "git pull > " + static_cast<std::string>(tmp_file);
    auto retorno = std::system(command.c_str());
    
    std::ifstream iftmp(tmp_file.c_str());
    if (!iftmp)
    {
        throw "Error al abrir archivo\n";
    }
    while(!iftmp.eof())
    {
        std::string tmp;
        std::getline(iftmp, tmp);
        salida += tmp + "\n";
    }
    command = "rm " + static_cast<std::string>(tmp_file);
    std::system(command.c_str());

    return salida;
}

std::string HacerPush()
{
    std::string command, salida;
    std::vector<std::string> v_cad;
    
    // Montar path del archivo de log.
    std::filesystem::path tmp_file = std::filesystem::temp_directory_path() / "gtkmm_password.log";

    // std::cout << "Directorio de trabajo: " << std::filesystem::current_path() << std::endl;
    command = "git add . >" + static_cast<std::string>(tmp_file);

    // std::cout << "Directorio de trabajo: " << std::filesystem::current_path() << std::endl;
    std::system(command.c_str());

    // std::cout << "Directorio de trabajo: " << std::filesystem::current_path() << std::endl;
    command = "git commit --allow-empty-message -m \"\" >> " + static_cast<std::string>(tmp_file);
    std::system(command.c_str());
    command = "git push >> " + static_cast<std::string>(tmp_file);
    std::system(command.c_str());

    std::ifstream iftmp(tmp_file.c_str());
    if (!iftmp)
    {
        throw "Error al abrir archivo\n";
    }
    while(!iftmp.eof())
    {
        std::string tmp;
        std::getline(iftmp, tmp);
        salida += tmp + "\n";
    }
    command = "rm " + static_cast<std::string>(tmp_file);
    std::system(command.c_str());

    return salida;
}


// Recuperar la direción del depósito guardado en el archivo de configuración.
int Confirguracion(std::string& deposito, std::string& HOME)
{
    // Recuperar variable de entorno HOME
    HOME = std::getenv("HOME");

    // Comprobar si existe archivo de configuración
    std::filesystem::path fconf = HOME +  "/.gtkmm_password.toml";
    if (!std::filesystem::exists(fconf))
    {
        std::cout << "No existe un archivo de configuración\n";
        std::cout << "Creando el archivo de comfigiguración...\n";
        std::ofstream myfile;
        myfile.open(fconf.string());
        std::filesystem::path deposito = HOME + "/.password-store";
        myfile << "deposito = " << "\"" << deposito.string() << "\"" << std::endl;
        myfile.close();
    }

    // Letura de la cadena.
    std::cout << "Ruta del archivo de configuración: " << fconf << std::endl;
    std::cout << "En caso de querer modificar la ruta al depósito, editar este archivo:" << fconf << std::endl;

    try
    {
        auto data = toml::parse(fconf);
        deposito = toml::find<std::string>(data, "deposito");
    }
    catch (...)
    {
        std::cerr << "Error al recuperar depósito.\n";
    }

    return 0;
}
