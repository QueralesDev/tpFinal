#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "clientes.h"
#include "mocks_Domicilios_Clientes.h"
#include "domicilios.h"
#define AR_CLIENTES "clientes.bin"
#include <conio.h>


stCliente cargaUnCliente ()
{
    stCliente c;
    static int id=0;
    id++;
    printf("Ingresa los datos para poder ser cliente del Banco\n");

    printf ("NRO DE CLIENTE: ");
    scanf("%d", &c.nroCliente);
    getchar();

    printf ("NOMBRE: ");
    fgets(c.nombre, sizeof(c.nombre), stdin);

    printf ("APELLIDO: ");
    fgets(c.apellido, sizeof(c.apellido), stdin);

    printf ("DNI: ");
    fgets(c.dni, sizeof(c.dni), stdin);

    printf ("E-MAIL: ");
    fgets(c.email, sizeof(c.email), stdin);

    printf ("TELEFONO: ");
    fgets(c.telefono, sizeof(c.telefono), stdin);

    return c;
}
void muestraUnCliente (stCliente c)
{
    printf ("\n=====================================================");
    printf ("\n\t::::::::NRO ID:::::::: %d",c.id);
    printf ("\n=====================================================");
    printf ("\nCLIENTE DEL BANCO NRO...........: %d", c.nroCliente);
    printf ("\n=====================================================");
    printf ("\nNOMBRE..........................: %s", c.nombre);
    printf ("\nAPELLIDO........................: %s", c.apellido);
    printf ("\nDNI.............................: %s", c.dni);
    printf ("\nE-MAIL..........................: %s", c.email);
    printf ("\nTELEFONO........................: %s", c.telefono);
    printf ("\n=====================================================\n");
}

int cargaClientes (stCliente c[], int v, int dim)
{
    char opcion = 0;

    while(v < dim && opcion != 27)
    {
        system("cls");
        c[v] = cargaUnCliente();
        v++;
        printf("\nESC para salir o cualquier tecla para continuar...");
        opcion = getch();
    }

    return v;
}

void muestraClientes(stCliente c[], int v)
{
    for(int i=0; i<v; i++)
    {
        muestraUnCliente(c[i]);
    }
}

int ultimoId(char nombreArchivo[])
{
    int id = 0;
    stCliente c;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        fseek(archi, -1*(sizeof(stCliente)), SEEK_END);
        if(fread(&c,sizeof(stCliente), 1, archi)>0)
        {
            id = c.id;
        }

        fclose(archi);
    }

    return id;
}

void cargaUnArchivoUsuario(char nombreArchivo[])
{
    stCliente c;
    char opcion;
    int static id;
    int existe;
    id = ultimoId(AR_CLIENTES);
    int dni_int = atoi(c.dni);
    FILE* archi = fopen(nombreArchivo, "a+b");
    if(archi)
    {
        do
        {
            system("cls");
            c = cargaUnCliente();
            existe = buscaCuentaEnArchivoPro(archi, dni_int);
            printf("%d", existe);
            if(existe == 1)
            {
                printf("ERROR - Cliente ya registrado");
            }
            else
            {
                id++;
                c.id = id;
                fwrite(&c, sizeof(stCliente), 1, archi);
            }
            printf("\nESC para salir cualquier otra tecla para continuar cargando......");

            opcion = getch();
        }
        while(opcion != 27);

        fclose(archi);
    }

}
int buscaCuentaEnArchivoPro(FILE* archi, int nroCliente)
{
    stCliente c;
    int flag = 0;
    rewind(archi);
    if(archi)
    {
        while(flag == 0 && fread(&c, sizeof(stCliente), 1, archi)>0)
        {
            if(c.nroCliente == nroCliente)
            {
                flag = 1;
            }
        }
        //fclose(archi);
    }
    return flag;
}

void cargaArchClienteRandom(char nombreArchivo[], int cant)
{
    FILE* archi = fopen(nombreArchivo, "ab");
    stCliente cliente;
    int i = 0;
    if(archi)
    {
        while(i<cant)
        {
            cliente = getClienteRandom();
            fwrite(&cliente, sizeof(stCliente), 1, archi);
            i++;
        }
        fclose(archi);
    }
}

void muestraArchivoCliente(char nombreArchivo[])
{
    stCliente cliente;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        while(fread(&cliente, sizeof(stCliente), 1, archi)>0)
        {
            muestraUnCliente(cliente);
        }
        fclose(archi);
    }
}
/*stCliente cargaClientes()
{
    stCliente c;

    c = cargaArchClienteRandom();
    c.domicilio = cargaArchDomiciliosRandom();

    return c;
}
*/

/** \brief Función que busca y valida un dni. Se puede utilizar para ingresar al sistema.
 *
 * \param strcpy(c.dni, "-1") En este caso, se asume que un DNI de “-1” significa que el cliente no se encontró.
          while(flag == 0 && fread(&c, sizeof(stCliente), 1, archi)>0): Lee el archivo binario una estructura stCliente a la vez.
          Continúa leyendo hasta que se encuentre el cliente (es decir, flag se establece en 1) o hasta que se haya leído todo el archivo.
          if(strcmp(c.dni, dato) == 0): Compara el DNI del cliente actual con el DNI buscado.
          Si son iguales, establece flag en 1 para indicar que se encontró el cliente.
          if (flag == 0) { strcpy(c.dni, "-1"); }: Si no se encontró el cliente después de leer todo el archivo,
          restablece c.dni a “-1” para indicar que no se encontró el cliente.
 * \return Devuelve la estructura stCliente. Si se encontró el cliente, esta estructura contendrá los datos
           del cliente. Si no se encontró el cliente, c.dni será “-1”
 */

stCliente buscaDatoEnArchivoStr(char nombreArchivo[], char dato[])
{
    stCliente c;
    strcpy(c.dni, "-1");
    int flag = 0;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        while(flag == 0 && fread(&c, sizeof(stCliente), 1, archi)>0)
        {
            if(strcmp(c.dni, dato) == 0) /// en este caso la funcion busca un string
            {
                flag = 1;
            }
        }
        fclose(archi);
    }
    if (flag == 0)  // Si no se encontró el cliente, restablece c.dni a -1
    {
        strcpy(c.dni, "-1");
    }

    return c;
}


void buscaYMuestraClientePorDNI(char nombreArchivo[], char dni[])
{
    stCliente c= buscaDatoEnArchivoStr(AR_CLIENTES, dni);

    if (strcmp(c.dni, "-1") != 0)   // Si se encontró el cliente
    {
        muestraUnCliente(c); // Muestra los datos del cliente
    }
    else
    {
        printf("No se encontro un cliente con el DNI %s.\n", dni);

    }
}
/*int ultimoID (char nombreArchivo[]){
int id;

FILE* archi = fopen(nombreArchivo, "ab");
if (a)


}
int factorialT(int x)
{
    return (x>0)?x*factorialT(x-1):1;
}

int sumaArreglo(int a[], int v, int i)
{
    int suma;
    if(i==v-1)
    {
        suma=a[i];
    }
    else
    {
        suma= a[i] +  sumaArreglo(a, v, i+1)
    }

    return suma;
}

int sumaArregloImp factorial(int x)
{
    int suma=0;
    if(i<v)
    {
        suma=a[i]+ sumaArreglo(a,v, i+1);
    }
    return suma;
}
int sumaArregloTer(int a[], int v, int i)
{

    return (i<v)?a[i]+ sumaArregloTer(a,v,i+1):0;
}

void muestraArreglo (int a[], int v, int i)
{
    if (i<v)
    {
        printf ("\n %d", a[i]);
        muestraArreglo(a, v, i+1);
    }

}
*/
