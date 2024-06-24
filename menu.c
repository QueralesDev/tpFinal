#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "clientes.h"
#include "domicilios.h"
#include "cuentas.h"
#include "movimientos.h"
#include "mocks_Domicilios_Clientes.h"

#define AR_CLIENTES "clientes.bin"
#define AR_CUENTAS "cuentas.bin"
#define AR_MOVIMIENTOS "movimientos.bin"


void menu()
{

    stCliente clienteAct[500];
    stCliente clienteIna[500];
    int vAct = 0;
    int vInac = 0;
    int opcion;
    int cant;
    int cont;
    do
    {
        printf("\n================== MENU PRINCIPAL ==================\n");
        printf("1. BUSCAR CLIENTE POR DNI\n");
        printf("2. CARGAR UN NUEVO CLIENTE DEL BANCO\n");
        printf("3. CARGAR CLIENTES DE MANERA ALEATORIA\n");
        printf("4. CLIENTES ACTIVOS Y CANTIDAD DE CLIENTES DEL BANCO\n");
        printf("5. SALIR\n");
        printf("===================================================\n");
        printf("ELIGE UNA OPCION: ");
        scanf("%d", &opcion);
        getchar();

        switch(opcion)
        {
        case 1:
            buscaClientes(AR_CLIENTES, AR_CUENTAS, AR_MOVIMIENTOS);
            break;
        case 2:
            cargarClienteYCuentaYMovimientos(AR_CLIENTES, AR_CUENTAS, AR_MOVIMIENTOS);
            //cargarClienteYCuenta(AR_CLIENTES, AR_CUENTAS);
            //cargaUnArchivoUsuario(AR_CLIENTES);
            break;
        case 3:
            printf("\nINGRESA LA CANTIDAD DE CLIENTES A CARGAR: ");
            scanf("%d", &cant);
            getchar();
            cargaArchClienteRandom(AR_CLIENTES, cant);
            break;
        case 4:
            archivo2arreglosActyElim(AR_CLIENTES,clienteAct,clienteIna,&vAct, &vInac,500);
            cont = cuentaRegistros(AR_CLIENTES, sizeof(stCliente));
            printf("LA CANTIDAD DE CLIENTES DEL BANCO SON: %d\n", cont);
            printf("LA CANTIDAD DE REGISTROS ACTIVOS DEL BANCO SON: %d\n", vAct);
            printf("LA CANTIDAD DE REGISTROS INACTIVOS DEL BANCO SON: %d\n", vInac);

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
