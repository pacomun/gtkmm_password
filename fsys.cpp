// Lectura de directorioo
#include <algorithm>
#include "fsys.hpp"
#include "auxiliar.h"


#define SIZE 512

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


clave DescifrarClave(std::filesystem::directory_entry& nombre_clave)
{
    // char *p;
    // char buf[SIZE];
    // size_t read_bytes;
    // int tmp;
    clave m_clave;
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

    print_data(data, NULL);

    gpgme_release(ctx);
    gpgme_data_release(cipher);
    gpgme_data_release(data);

    return m_clave;
}
