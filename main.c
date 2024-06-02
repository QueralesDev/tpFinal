#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "domicilios.h"
#include <string.h>
#define AR_CLIENTES "clientes.bin"
#define AR_DOMICILIOS "domicilios.bin"

//int buscarUltimoId (FILE * archi);
int main()
{

    stCliente cliente[10];
    int vClientes=0;

    vClientes=cargaClientes(cliente, vClientes, 10);
    muestraClientes(cliente, vClientes);


    cargaArchClienteRandom(AR_CLIENTES, 10);
    printf("\n Listado de Clientes del archivo ");
    muestraArchivoCliente(AR_CLIENTES);

    char dni[10];
    printf("Ingresa el DNI del cliente que deseas buscar: ");
    fgets(dni, 10, stdin);

    // Elimina el salto de l�nea al final de la entrada, si existe
    if (dni[strlen(dni) - 1] == '\n') {
        dni[strlen(dni) - 1] = '\0';
    }

    buscaYMuestraClientePorDNI(AR_CLIENTES, dni);


    /*cargaArchClienteRandom(AR_CLIENTES, 10);
    printf("\n Listado de Clientes del archivo ");
    muestraArchivoCliente(AR_CLIENTES);

    cargaArchDomiciliosRandom(AR_DOMICILIOS, 10);
    printf("\n Listado de domicilios del archivo ");
    muestraArchivoDomicilio(AR_DOMICILIOS);*/




    return 0;

}
/*
int buscarUltimoId (FILE * archi)
{
    stCliente c;
    if(archi)
    {
        fseek(archi,-sizeof(stCliente),2);
        fread(&c,sizeof(stCliente),1,archi);
    }
    c.id++;
    return c.id;
}
*/
