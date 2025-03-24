#include "auxiliar.h"
#include <locale.h>
/* Funciones auxiliares */

void init_gpgme(gpgme_protocol_t proto)
{
    /* Inicializa las variables de entorno */
    setlocale(LC_ALL, "");
    gpgme_check_version(NULL);
    gpgme_set_locale(NULL, LC_CTYPE,
            setlocale(LC_CTYPE, ""));
    /* En caso de  MS Windows */
#ifdef LC_MESSAGES
    gpgme_set_locale(NULL, LC_MESSAGES,
            setlocale(LC_MESSAGES, NULL));
#endif
    gpgme_error_t err;
    err = gpgme_engine_check_version(proto);
    if (err != GPG_ERR_NO_ERROR)
    {
        fprintf(stderr, "Error: protocolo no válido.\n");
        exit (1);
    }
    
}

void mostrarKey(gpgme_key_t key)
{
    fprintf(stderr,"key ID: %s\n"
               "key revoked: %s\n"
               "key expired: %s\n"
               "key can encrypt: %s\n"
               "key is invalid: %s\n"
               "key can sign: %s\n"
               "key is secret: %s\n"
               ,key->fpr,
               key->revoked ? "true" : "false",
               key->expired ? "true" : "false",
               key->can_encrypt ? "true" : "false",
               key->invalid ? "true" : "false",
               key->can_sign ? "true" : "false",
               key->secret ? "true" : "false"
               );

}

void print_data(gpgme_data_t data, FILE* fd)
{
    char buf[SIZE + 1];
    int ret;    

    ret = gpgme_data_seek(data, 0, SEEK_SET);
    while ((ret = gpgme_data_read(data, buf, SIZE )) > 0)
        if (fd)
            fwrite(buf, ret, sizeof(char), fd);
        else
            fwrite(buf, ret, 1, stderr);

    ret = gpgme_data_seek(data, 0, SEEK_SET);
}

