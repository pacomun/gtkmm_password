#ifndef AUXILIAR_H
#define AUXILIAR_H
#include <gpgme.h>
#include <string>
#include <stdlib.h>
/* Funciones auxiliares */

#define SIZE 512

/* Inicialización de gpgme */
void init_gpgme(gpgme_protocol_t proto);


/* Muestra algunas propiedades de una clave */
void mostrarKey(gpgme_key_t key);

/* Imprimir datos de salida. fd es un archivo abierto para escritura, en caso
 * de ser NULL la salida será stderr. */
void print_data(gpgme_data_t data, FILE* fd);

#endif /* AUXILIAR_H */
