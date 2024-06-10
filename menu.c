#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#include "domicilios.h"
#include "mocks_Domicilios_Clientes.h"
#define AR_CLIENTES "clientes.bin"
#define AR_CUENTAS "cuentas.bin"
#include <conio.h>
#include "cuentas.h"


void menu()
{
    int opcion;
    char nombreArchivo[30];
    int cant;
    int cont;
    //stCliente a[100];
    //int dim = cuentaRegistros(AR_CLIENTES, sizeof(stCliente));
    //int v = arch2arregloClienteAct(AR_CLIENTES, a, dim);
    do
    {
        printf("\n================== MENU PRINCIPAL ==================\n");
        printf("1. BUSCAR CLIENTE POR DNI\n");
        printf("2. CARGAR UN NUEVO CLIENTE DEL BANCO\n");
        printf("3. CARGAR EN EL ARCHIVO CLIENTE ALEATORIO\n");
        printf("4. CLIENTES ACTIVOS Y CANTIDAD DE CLIENTES DEL BANCO\n");
        printf("5. SALIR\n");
        printf("===================================================\n");
        printf("ELIGE UNA OPCION: ");
        scanf("%d", &opcion);
        getchar();

        switch(opcion)
        {
        case 1:

            buscaClientes(AR_CLIENTES);
            break;
        case 2:

            cargaUnArchivoUsuario(AR_CLIENTES);
            break;
        case 3:

            printf("\nINGRESA LA CANTIDAD DE CLIENTES A CARGAR: ");
            scanf("%d", &cant);
            getchar();
            cargaArchClienteRandom(nombreArchivo, cant);
            break;
        case 4:

            cont = cuentaRegistros(AR_CLIENTES, sizeof(stCliente));
            printf("LA CANTIDAD DE REGISTROS ACTIVOS DEL BANCO SON: %d\n", cont);
            break;
        case 5:
            printf("SALIENDO DEL PROGRAMA...\n");
            break;
        default:
            printf("OPCION NO VALIDA.\n");
            break;
        }
    }
    while(opcion != 5);
}
