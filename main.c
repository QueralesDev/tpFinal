#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "domicilios.h"
#include "cuentas.h"
#include <string.h>
#define AR_CLIENTES "clientes.bin"
#define AR_CUENTAS "cuentas.bin"

int main()
{
    int cont;
    stCliente cliente;
    //cargaUnArchivoUsuario(AR_CLIENTES);
    //muestraArchivoCliente(AR_CLIENTES);

    char dni[10];
    printf("Ingresa su DNI para ingresar al sistema: ");
    fgets(dni, 10, stdin);
    dni[strcspn(dni, "\n")] = 0; // Elimina el salto de línea


    menu(dni);  // Llama a la función menu pasando el DNI como argumento


    /*cargaCuentasEnArchivo(AR_CUENTAS);
    printf("\nELEMENTOS DEL ARCHIVO CUENTAS");
    muestraUnArchivo(AR_CUENTAS);*/

    muestraClienteYCuentas(AR_CLIENTES,AR_CUENTAS, cliente.id);
    cont = cuentaRegistros(AR_CUENTAS, sizeof(stCuenta));
    printf("\nLa cantidad de registros en el Archivo es :%d\n", cont);
    muestraClienteYCuentas(AR_CLIENTES, AR_CUENTAS, cliente.id);
    return 0;

}
