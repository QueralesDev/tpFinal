#include <stdio.h>
#include <stdlib.h>
#include "cuentas.h"
#include "clientes.h"
#include <conio.h>
#include "mocks_Domicilios_Clientes.h"
#define AR_CUENTAS "cuentas.bin"


stCuenta cargaUnaCuenta(int idDuenioCuenta){
    stCuenta c;
    int dato;
    int flag = 0;

    c.id =0;
    c.idCliente = idDuenioCuenta; // Asigna el id del cliente
    //printf("INGRESE NUMERO DE CUENTA: ");
    c.nroCuenta = rand()%1000000 + 100000;

    do{

    printf("\nINGRESE TIPO DE CUENTA (1. CAJA DE AHORRO EN PESOS, 2. CAJA DE AHORRO EN DOLARES, 3. CTA CTE EN PESOS): ");
    scanf("%d", &dato);
    fflush(stdin);

        if(dato >0  && dato < 4){
            c.tipoDeCuenta = dato;
            flag = 1;

        }else{

        system("cls");
           printf("TIPO DE CUENTA INVALIDO PORFAVOR INGRESE UN TIPO DE CUENTA VALIDO:");

        }
    }while(flag == 0);

    //printf("INGRESE COSTO MENSUAL DE MANTENIMIENTO: ");
    c.costoMensual = 5000;
    //printf("INGRESE SALDO INICIAL DE LA CUENTA: ");
    c.saldo = 0;
    //printf("INGRESE ESTADO DE LA CUENTA (0 SI ESTÁ ACTIVO - 1 SI ESTA ELIMINADO): ");
    c.eliminado = 0;

    return c;
}
void muestraUnaCuenta(stCuenta c){
    printf("\nID DE LA CUENTA: %d", c.id);
    printf("\nID DEL CLIENTE: %d", c.idCliente);
    printf("\nNUMERO DE CUENTA: %d", c.nroCuenta);
    printf("\nTIPO DE CUENTA: ");
    imprimeTipoDeCuenta(c.tipoDeCuenta);
    printf("\nCOSTO DE MANTENIMIENTO MENSUAL: %.2f", c.costoMensual);
    printf("\nSALDO EN CUENTA: %.2f", c.saldo);
    printf("\nESTADO DE LA CUENTA (0 SI ESTA ACTIVO - 1 SI ESTA ELIMINADO): %d",c.eliminado );
    printf("\n==================================================================");
}

void imprimeTipoDeCuenta(int dato){

    if(dato == 1){
        printf("CAJA DE AHORRO EN PESOS");
    }
    if(dato == 2){
        printf("CAJA DE AHORRO EN DOLARES");
    }
    if(dato == 3){
        printf("CUENTA CORRIENTE");
    }
}

void cargaCuentasEnArchivo(char nombreArchivo[], int idCliente) {
    stCuenta c;
    char opcion;
    int static id;
    int existeNroCuenta;
    int existeTipoCuenta;
    id = ultimoIdCuentas(AR_CUENTAS);
    FILE* archi = fopen(nombreArchivo, "a+b");
    if(archi)
    {
        do
        {
            system("cls");

            c = cargaUnaCuenta(idCliente); // Aquí pasamos el idCliente
            existeNroCuenta = buscaCuentaEnArchivoFlag(archi, c.nroCuenta);
            existeTipoCuenta = buscaTipoCuentaEnArchivoFlag(archi, c.tipoDeCuenta);

            if(existeNroCuenta == 1 || existeTipoCuenta == 1)
            {
                printf("ERROR - CUENTA REPETIDA");

            }
            else
            {
                id++;
                c.id = id;
                fwrite(&c, sizeof(stCuenta), 1, archi);
                printf("CUENTA CREADA CON EXITO");
            }

            printf("\nESC PARA SALIR CUALQUIER OTRA TECLA PARA CONTINUAR CARGANDO......");

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

int buscaCuentaEnArchivo(char nombreArchivo[], int dato)
{
    stCuenta c;
    int flag = 0;
    //rewind(archi);
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        while(flag == 0 && fread(&c, sizeof(stCuenta), 1, archi)>0)
        {
            if(c.nroCuenta == dato)
            {
                flag = 1;
            }
        }
        fclose(archi);
    }
    return flag;
}
int buscaCuentaEnArchivoFlag(FILE* archi, int dato)
{
    stCuenta c;
    int flag = 0;
    rewind(archi);
    if(archi)
    {
        while(flag == 0 && fread(&c, sizeof(stCuenta), 1, archi)>0)
        {
            if(c.nroCuenta == dato)
            {
                flag = 1;
            }
        }
        //fclose(archi);
    }
    return flag;
}

int buscaTipoCuentaEnArchivoFlag(FILE* archi, int dato)
{
    stCuenta c;
    int flag = 0;
    rewind(archi);
    if(archi)
    {
        while(flag == 0 && fread(&c, sizeof(stCuenta), 1, archi)>0)
        {
            if(c.tipoDeCuenta == dato)
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

void buscaCuentasDeCliente(char nombreArchivoCuentas[], stCliente cliente) {
    FILE* archi = fopen(nombreArchivoCuentas, "r");//abre el archivo de cuentas en modo de lectura
    stCuenta cuenta;

    // Buscar las cuentas del cliente en el archivo de cuentas
    while (fread(&cuenta, sizeof(stCuenta), 1, archi)) {
        // Si el id del cliente de la cuenta actual coincide con el id del cliente dado
        if (cuenta.idCliente == cliente.id) {//verifica si el idCliente de la cuenta coincide con el id del cliente. Si es así, significa que la cuenta pertenece al cliente
            printf("CUENTA ENCONTRADA: %d\n", cuenta.nroCuenta);
            muestraUnaCuenta(cuenta);
        }
    }

    fclose(archi);
}
/*void agregarCuentaACliente(char nombreArchivoCuentas[], int idCliente) {
    FILE* archi = fopen(nombreArchivoCuentas, "a"); // Abre el archivo en modo de agregar

    // Carga los detalles de la nueva cuenta
    stCuenta nuevaCuenta = cargaUnaCuenta(idCliente);

    // Asigna el ID del cliente a la nueva cuenta
    nuevaCuenta.idCliente = idCliente;

    // Escribe la nueva cuenta en el archivo
    fwrite(&nuevaCuenta, sizeof(stCuenta), 1, archi);

    fclose(archi);
}*/
