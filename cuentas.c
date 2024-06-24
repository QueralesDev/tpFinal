#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "cuentas.h"
#include "clientes.h"
#include "movimientos.h"
#include "mocks_Domicilios_Clientes.h"


#define AR_CUENTAS "cuentas.bin"
#define AR_MOVIMIENTOS "movimientos.bin"


stCuenta cargaUnaCuenta(int idDuenioCuenta)
{
    stCuenta c;
    int dato;
    int flag = 0;

    c.id =0;
    c.idCliente = idDuenioCuenta; // Asigna el id del cliente
    //printf("INGRESE NUMERO DE CUENTA: ");
    c.nroCuenta = rand()%1000000 + 100000;

    do
    {

        printf("\nINGRESE TIPO DE CUENTA (\n1. CAJA DE AHORRO EN PESOS\n2. CAJA DE AHORRO EN DOLARES\n3. CTA CTE EN PESOS): ");
        scanf("%d", &dato);
        fflush(stdin);

        if(dato >0  && dato < 4)
        {
            c.tipoDeCuenta = dato;
            flag = 1;

        }
        else
        {
            system("cls");
            printf("TIPO DE CUENTA INVALIDO PORFAVOR INGRESE UN TIPO DE CUENTA VALIDO:");

        }
    }
    while(flag == 0);

    //printf("INGRESE COSTO MENSUAL DE MANTENIMIENTO: ");
    c.costoMensual = 5000;
    //printf("INGRESE SALDO INICIAL DE LA CUENTA: ");
    c.saldo = 0;
    //printf("INGRESE ESTADO DE LA CUENTA (0 SI ESTÁ ACTIVO - 1 SI ESTA ELIMINADO): ");
    c.eliminado = 0;

    return c;
}
void muestraUnaCuenta(stCuenta c)
{
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
void muestraUnaCuentaPuntero(stCuenta *c)
{
    printf("\nID DE LA CUENTA: %d", c->id);
    printf("\nID DEL CLIENTE: %d", c->idCliente);
    printf("\nNUMERO DE CUENTA: %d", c->nroCuenta);
    printf("\nTIPO DE CUENTA: ");
    imprimeTipoDeCuenta(c->tipoDeCuenta);
    printf("\nCOSTO DE MANTENIMIENTO MENSUAL: %.2f", c->costoMensual);
    printf("\nSALDO EN CUENTA: %.2f", c->saldo);
    printf("\nESTADO DE LA CUENTA (0 SI ESTA ACTIVO - 1 SI ESTA ELIMINADO): %d",c->eliminado );
    printf("\n==================================================================");
}

void imprimeTipoDeCuenta(int dato)
{

    if(dato == 1)
    {
        printf("CAJA DE AHORRO EN PESOS");
    }
    if(dato == 2)
    {
        printf("CAJA DE AHORRO EN DOLARES");
    }
    if(dato == 3)
    {
        printf("CUENTA CORRIENTE");
    }
}

void cargaCuentasEnArchivo(char nombreArchivo[], int idCliente)
{
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
            existeTipoCuenta = buscaTipoCuentaEnArchivoFlag(archi, idCliente, c.tipoDeCuenta);

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

            printf("\nESC PARA SALIR, CUALQUIER TECLA PARA AGREGAR OTRA CUENTA......");

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

int buscaTipoCuentaEnArchivoFlag(FILE* archi, int idCliente, int dato)
{
    stCuenta c;
    int flag = 0;
    rewind(archi);
    if(archi)
    {
        while(flag == 0 && fread(&c, sizeof(stCuenta), 1, archi)>0)
        {
            if(c.tipoDeCuenta == dato && c.idCliente == idCliente)
            {
                flag = 1;
            }
        }
        //fclose(archi);
    }
    return flag;
}

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

void buscaCuentasDeCliente(char nombreArchivoCuentas[], stCliente cliente)
{
    FILE* archi = fopen(nombreArchivoCuentas, "rb");//abre el archivo de cuentas en modo de lectura
    stCuenta cuenta;

    // Buscar las cuentas del cliente en el archivo de cuentas
    while (fread(&cuenta, sizeof(stCuenta), 1, archi))
    {
        // Si el id del cliente de la cuenta actual coincide con el id del cliente dado
        if (cuenta.idCliente == cliente.id)  //verifica si el idCliente de la cuenta coincide con el id del cliente. Si es así, significa que la cuenta pertenece al cliente
        {
            //printf("\nCUENTA ENCONTRADA: %d\n", cuenta.nroCuenta);
            muestraUnaCuenta(cuenta);
        }
    }

    fclose(archi);
}

void bajaCuenta(char nombreArchivoCuentas[], stCliente cliente)
{
    stCuenta cuenta;
    FILE* archi = fopen(nombreArchivoCuentas, "r+b");//abre el archivo de cuentas en modo de lectura Y escritura

    if(archi)
    {
        // Buscar las cuentas del cliente en el archivo de cuentas
        while (fread(&cuenta, sizeof(stCuenta), 1, archi)>0)
        {
            // Si el id del cliente de la cuenta actual coincide con el id del cliente dado
            if (cuenta.idCliente == cliente.id)  //verifica si el idCliente de la cuenta coincide con el id del cliente. Si es así, significa que la cuenta pertenece al cliente
            {
                cuenta.eliminado = 1;

                // Mueve el puntero del archivo a la posicion del cliente encontrado
                fseek(archi, -sizeof(stCuenta), SEEK_CUR);

                // Escribe los nuevos datos del cliente en el archivo
                fwrite(&cuenta, sizeof(stCuenta), 1, archi);

                // Importante: Avanzar el puntero al siguiente registro
                fseek(archi, 0, SEEK_CUR);
            }
        }
        fclose(archi);
    }
}
///esta funcion da de baja solo la cuenta que le paso por parametro
void bajaSoloCuenta(char nombreArchivoCuentas[], stCuenta cuentaParaBaja)
{
    stCuenta cuenta;
    FILE* archi = fopen(nombreArchivoCuentas, "r+b");//abre el archivo de cuentas en modo de lectura Y escritura

    if(archi)
    {
        // Buscar las cuentas del cliente en el archivo de cuentas
        while (fread(&cuenta, sizeof(stCuenta), 1, archi)>0)
        {
            // Si el id del cliente de la cuenta actual coincide con el id del cliente dado
            if (cuenta.nroCuenta == cuentaParaBaja.nroCuenta)  //verifica si el idCliente de la cuenta coincide con el id del cliente. Si es así, significa que la cuenta pertenece al cliente
            {
                cuenta.eliminado = 1;

                // Mueve el puntero del archivo a la posicion del cliente encontrado
                fseek(archi, -sizeof(stCuenta), SEEK_CUR);

                // Escribe los nuevos datos del cliente en el archivo
                fwrite(&cuenta, sizeof(stCuenta), 1, archi);

                // Importante: Avanzar el puntero al siguiente registro
                fseek(archi, 0, SEEK_CUR);
            }
        }
        fclose(archi);
    }
}
 ///esta funcion da de alta todas las cuentas del cliente pasado por parametro
void altaCuenta(char nombreArchivoCuentas[], stCliente cliente)
{

    FILE* archi = fopen(nombreArchivoCuentas, "r+b");//abre el archivo de cuentas en modo de lectura y escritura
    stCuenta cuenta;
    if(archi)
    {
        // Buscar las cuentas del cliente en el archivo de cuentas
        while (fread(&cuenta, sizeof(stCuenta), 1, archi)>0)
        {
            // Si el id del cliente de la cuenta actual coincide con el id del cliente dado
            if (cuenta.idCliente == cliente.id)  //verifica si el idCliente de la cuenta coincide con el id del cliente. Si es así, significa que la cuenta pertenece al cliente
            {
                cuenta.eliminado = 0;
                // Mueve el puntero del archivo a la posicion del cliente encontrado
                fseek(archi, -sizeof(stCuenta), SEEK_CUR);

                // Escribe los nuevos datos del cliente en el archivo
                fwrite(&cuenta, sizeof(stCuenta), 1, archi);

                // Importante: Avanzar el puntero al siguiente registro
                fseek(archi, 0, SEEK_CUR);
            }
        }
        fclose(archi);
    }
}

void altaSoloCuenta(char nombreArchivoCuentas[], stCuenta cuentaParaAlta)
{
    stCuenta cuenta;
    FILE* archi = fopen(nombreArchivoCuentas, "r+b");//abre el archivo de cuentas en modo de lectura Y escritura

    if(archi)
    {
        // Buscar las cuentas del cliente en el archivo de cuentas
        while (fread(&cuenta, sizeof(stCuenta), 1, archi)>0)
        {
            // Si el id del cliente de la cuenta actual coincide con el id del cliente dado
            if (cuenta.nroCuenta == cuentaParaAlta.nroCuenta)  //verifica si el idCliente de la cuenta coincide con el id del cliente. Si es así, significa que la cuenta pertenece al cliente
            {
                cuenta.eliminado = 0;

                // Mueve el puntero del archivo a la posicion del cliente encontrado
                fseek(archi, -sizeof(stCuenta), SEEK_CUR);

                // Escribe los nuevos datos del cliente en el archivo
                fwrite(&cuenta, sizeof(stCuenta), 1, archi);

                // Importante: Avanzar el puntero al siguiente registro
                fseek(archi, 0, SEEK_CUR);
            }
        }
        fclose(archi);
    }
}
///esta funcion da de baja o alta al cliente y todas sus cuentas
void bajaAltaCliente(char nombreArchiClientes[], char nombreArchiCuentas[], char dni[])
{
    stCliente c;

    int encontrado = 0;
    FILE* archi = fopen(nombreArchiClientes, "r+b"); // Abre el archivo para lectura y escritura
    if(archi)
    {
        while(!encontrado && fread(&c, sizeof(stCliente), 1, archi)>0)
        {
            if(strcmp(c.dni, dni) == 0) // Si se encontro el cliente
            {

                encontrado = 1;
                printf("DATOS DEL CLIENTE ANTES DE MODIFICAR:\n");
                muestraUnCliente(c);//Mostramos al cliente para comparar
                //buscaCuentasDeCliente(AR_CUENTAS,unCliente);

                printf("\n");

                printf("1.BAJA\n2.ALTA\n3.SALIR");
                int opcion;
                scanf("%d", &opcion);// Elegimos una opción que queremos modificar
                getchar(); // Limpia el buffer de entrada

                switch(opcion)
                {
                case 1:

                    bajaCuenta(nombreArchiCuentas,c);
                    c.eliminado = 1;
                    break;
                case 2:

                    altaCuenta(nombreArchiCuentas,c);
                    c.eliminado = 0;
                    break;

                case 3:

                    break;

                default:
                    printf("OPCION NO VALIDA.\n");
                    break;
                }

                // Mueve el puntero del archivo a la posicion del cliente encontrado
                fseek(archi, -sizeof(stCliente), SEEK_CUR);

                // Escribe los nuevos datos del cliente en el archivo
                fwrite(&c, sizeof(stCliente), 1, archi);

                printf("DATOS DEL CLIENTE DESPUES DE LA MODIFICACION: \n");
                muestraUnCliente(c);
                buscaCuentasDeCliente(AR_CUENTAS,c);
            }

        }
        fclose(archi);
    }
}
////////////////////////////////////////////////////////////////////////////



//void buscaCuentaPorNumero(char nombreArchivoCuentas[], int numeroCuenta)
//{
//    FILE* archi = fopen(nombreArchivoCuentas, "rb");
//    stCuenta cuenta;
//    int cuentaEncontrada = 0; // Bandera para indicar si se encontró la cuenta
//
//    if (archi)
//    {
//        while (fread(&cuenta, sizeof(stCuenta), 1, archi))
//        {
//            if (cuenta.nroCuenta == numeroCuenta)
//            {
//                muestraUnaCuenta(cuenta);
//                cuentaEncontrada = 1;
//            }
//        }
//
//        fclose(archi);
//
//        if (!cuentaEncontrada)
//        {
//            printf("Cuenta no encontrada.\n");
//        }
//    }
//    else
//    {
//        printf("Error al abrir el archivo.\n");
//    }
//}

stCuenta buscaCuentaPorNumero(FILE* archi, int nroCuenta)
{
    stCuenta c;
    int flag = 0;
    //rewind(archi);

    if (archi)
    {
        while (flag == 0 && fread(&c, sizeof(stCuenta), 1, archi) > 0)
        {
            if (c.nroCuenta == nroCuenta)
            {
                flag = 1;
            }
        }
    }
    return c;
}

stCuenta seleccionaCuentaDeCliente(char archCuentas[])
{
    FILE* archi = fopen(archCuentas, "rb");
    stCuenta cuentaSeleccionada;
    int nroCuentaSeleccionada;

    if (archi)
    {

        printf("\nINGRESE EL NUMERO DE LA CUENTA QUE QUIERES SELECCIONAR:");
        scanf("%d", &nroCuentaSeleccionada);
        getchar();

        // Llamamos a la función buscaCuentaPorNumero para obtener la cuenta seleccionada
        cuentaSeleccionada = buscaCuentaPorNumero(archi, nroCuentaSeleccionada);

        fclose(archi);
    }

    return cuentaSeleccionada;
}


