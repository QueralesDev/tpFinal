#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "clientes.h"
#include "mocks_Domicilios_Clientes.h"
#include "domicilios.h"


stCliente cargaUnCliente ()
{
    stCliente c;
    static int id=0;
    id++;

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
stCliente buscaClientePorDNI(char nombreArchivo[], char dni[]) {
    stCliente cliente;
    int flag = 0;
    FILE* archi = fopen(nombreArchivo, "rb");

    if(archi) {
        while(!flag && fread(&cliente, sizeof(stCliente), 1, archi) > 0) {
            if(strcmp(cliente.dni, dni) == 0) {
                flag = 1;
            }
        }
        fclose(archi);
    }

    // Si no se encontró el cliente, establecemos el DNI en -1
    if(!flag) {
        strcpy(cliente.dni, "-1");
    }

    return cliente;
}
void buscaYMuestraClientePorDNI(char nombreArchivo[], char dni[]) {
    stCliente cliente = buscaClientePorDNI(nombreArchivo, dni);
    if (strcmp(cliente.dni, "-1") != 0) { // Si se encontró el cliente
        muestraUnCliente(cliente); // Muestra los datos del cliente
    } else {
        printf("No se encontró un cliente con el DNI %s.\n", dni);
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
