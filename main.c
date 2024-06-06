#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "domicilios.h"
#include <string.h>
#define AR_CLIENTES "clientes.bin"

int main()
{
    //cargaUnArchivoUsuario(AR_CLIENTES);
    muestraArchivoCliente(AR_CLIENTES);

    char dni[10];
    printf("Ingresa su DNI para ingresar al sistema: ");
    fgets(dni, 10, stdin);
    dni[strcspn(dni, "\n")] = 0; // Elimina el salto de línea

    menu(dni);  // Llama a la función menu pasando el DNI como argumento

    return 0;

}
