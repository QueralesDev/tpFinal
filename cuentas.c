#include <stdio.h>
#include <stdlib.h>
#include "cuentas.h"
#include "clientes.h"
#include <conio.h>
#include "mocks_Domicilios_Clientes.h"
#define AR_CUENTAS "cuentas.bin"


stCuenta cargaUnaCuenta(int idCliente){
    stCuenta c;

    c.id = idCliente; // Asigna el id del cliente
    printf("Ingrese número de cuenta: ");
    scanf("%d", &c.nroCuenta);
    printf("Ingrese tipo de cuenta (1. Caja de Ahorro en Pesos, 2. Caja de Ahorro en Dólares, 3. Cta Cte en $): ");
    scanf("%d", &c.tipoDeCuenta);
    printf("Ingrese costo mensual de mantenimiento: ");
    scanf("%f", &c.costoMensual);
    printf("Ingrese saldo inicial de la cuenta: ");
    scanf("%f", &c.saldo);
    printf("Ingrese estado de la cuenta (0 si está activo - 1 si está eliminado): ");
    scanf("%d", &c.eliminado);

    return c;
}
void muestraUnaCuenta(stCuenta c){
    printf("\nID de la cuenta: %d", c.id);
    printf("\nID del cliente: %d", c.idCliente);
    printf("\nNúmero de cuenta: %d", c.nroCuenta);
    printf("\nTipo de cuenta: ");
    imprimeTipoDeCuenta(c.tipoDeCuenta);
    printf("\nCosto de mantenimiento mensual: %.2f", c.costoMensual);
    printf("\nSaldo en cuenta: %.2f", c.saldo);
    printf("\nEstado de la cuenta (0 si está activo - 1 si está eliminado): %d", c.eliminado);
    printf("\n==================================================================");
}

void imprimeTipoDeCuenta(int dato){

    if(dato == 1){
        printf("Caja de ahorro en pesos");
    }
    if(dato == 2){
        printf("Caja de ahorro en Dolares");
    }
    if(dato == 3){
        printf("Cuenta Corriente");
    }
}

void cargaCuentasEnArchivo(char nombreArchivo[])
{
    stCuenta c;
    char opcion;
    int static id;
    int existe;
    id = ultimoIdCuentas(AR_CUENTAS);
    FILE* archi = fopen(nombreArchivo, "a+b");
    if(archi)
    {
        do
        {
            system("cls");

            c = cargaUnaCuenta(c.idCliente);

            existe = buscaCuentaEnArchivoFlag(archi, c.nroCuenta);
            printf("%d", existe);
            if(existe == 1)
            {

                printf("ERROR - cuenta repetida");

            }
            else
            {
                id++;
                c.id = id;
                fwrite(&c, sizeof(stCuenta), 1, archi);

            }

            printf("\nESC para salir cualquier otra tecla para continuar cargando......");

            opcion = getch();

        }
        while(opcion != 27);

        fclose(archi);
    }

}

void muestraUnArchivo(char nombreArchivo[])
{
    stCuenta c;

    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {

        while(fread(&c, sizeof(stCuenta), 1, archi)>0)
        {

            muestraUnaCuenta(c);

        }
        fclose(archi);
    }

}

int ultimoIdCuentas(char nombreArchivo[])
{
    int id = 0;
    stCuenta c;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        fseek(archi, -1*(sizeof(stCuenta)), SEEK_END);
        if(fread(&c,sizeof(stCuenta), 1, archi)>0)
        {

            id = c.id;
        }

        fclose(archi);
    }

    return id;
}

int buscaCuentaEnArchivo(char nombreArchivo[], int nroCuenta)
{
    stCuenta c;
    int flag = 0;
    //rewind(archi);
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        while(flag == 0 && fread(&c, sizeof(stCuenta), 1, archi)>0)
        {
            if(c.nroCuenta == nroCuenta)
            {
                flag = 1;
            }
        }
        fclose(archi);
    }
    return flag;
}
int buscaCuentaEnArchivoFlag(FILE* archi, int nroCuenta)
{
    stCuenta c;
    int flag = 0;
    rewind(archi);
    if(archi)
    {
        while(flag == 0 && fread(&c, sizeof(stCuenta), 1, archi)>0)
        {
            if(c.nroCuenta == nroCuenta)
            {
                flag = 1;
            }
        }
        //fclose(archi);
    }
    return flag;
}

/*int buscaCuentasUsuarioEnArchivo(char nombreArchivo[], stCuenta a[], int v, int dato)
{
    stCuenta c;
    int flag = 0;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        while(fread(&c, sizeof(stCuenta), 1, archi)>0)
        {
            if(c.idCliente == dato)
            {
                a[v]= c;
                v++;
            }
        }
        fclose(archi);
    }
    return v;
}*/

int buscaDatoEnArchivoInt(char nombreArchivo[], int dato)
{

    stCuenta c;
    int flag = 0;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        while(flag == 0 && fread(&c, sizeof(stCuenta), 1, archi)>0)
        {
            if(c.nroCuenta == dato) /// en este caso la funcion busca un numero de cuenta
            {
                flag = 1;
            }
        }
        fclose(archi);
    }
    return flag;
}
int cuentaRegistros(char nombreArchivo[], int tamanioEstructura)
{

    int cont = 0;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {

        fseek(archi, 0, SEEK_END);
        cont = ftell(archi) / tamanioEstructura;

        fclose(archi);
    }
    return cont;
}

void buscaCuentasDeCliente(char nombreArchivoCuentas[], int idCliente) {
    FILE* archi = fopen(nombreArchivoCuentas, "r");
    stCuenta cuenta;

    // Buscar las cuentas del cliente en el archivo de cuentas
    while (fread(&cuenta, sizeof(stCuenta), 1, archi)) {
        if (cuenta.idCliente == idCliente) {
            printf("Cuenta encontrada: %d\n", cuenta.nroCuenta);
            muestraUnaCuenta(cuenta);
        }
    }

    fclose(archi);
}
void agregarCuentaACliente(char nombreArchivoCuentas[], int idCliente) {
    FILE* archi = fopen(nombreArchivoCuentas, "a"); // Abre el archivo en modo de agregar

    // Carga los detalles de la nueva cuenta
    stCuenta nuevaCuenta = cargaUnaCuenta(idCliente);

    // Asigna el ID del cliente a la nueva cuenta
    nuevaCuenta.idCliente = idCliente;

    // Escribe la nueva cuenta en el archivo
    fwrite(&nuevaCuenta, sizeof(stCuenta), 1, archi);

    fclose(archi);
}
