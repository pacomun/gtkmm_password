// Lectura de directorioo
#include <algorithm>
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
