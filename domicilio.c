#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "clientes.h"
#include "domicilios.h"
#include "mocks_Domicilios_Clientes.h"

stDomicilio cargaUnDomicilio ()
{
    stDomicilio d;

    printf ("CALLE: ");
    fgets(d.calle, sizeof(d.calle), stdin);
    d.calle[strcspn(d.calle, "\n")] = 0;
    /**Aquí está pidiendo al usuario que ingrese la calle. Usas fgets para leer la entrada del usuario y almacenarla en d.calle.
     Luego usamos strcspn para encontrar el índice del carácter de nueva línea (\n) en d.calle y lo reemplaza con el carácter nulo
     (\0) para eliminar el carácter de nueva línea de la entrada.*/

    printf ("NRO: ");
    fgets(d.nro, sizeof(d.nro), stdin);
    d.nro[strcspn(d.nro, "\n")] = 0;

    printf ("LOCALIDAD: ");
    fgets(d.localidad, sizeof(d.localidad), stdin);
    d.localidad[strcspn(d.localidad, "\n")] = 0;

    printf ("PROVINCIA: ");
    fgets(d.provincia, sizeof(d.provincia), stdin);
    d.provincia[strcspn(d.provincia, "\n")] = 0;

    printf ("CODIGO POSTAL: ");
    fgets(d.cpos, sizeof(d.cpos), stdin);
    d.cpos[strcspn(d.cpos, "\n")] = 0;

    return d;
}
void muestraUnDomicilio (stDomicilio d)
{
    printf ("\n=====================================================");
    printf ("\n\tDOMICILIO REAL DE RESIDENCIA HABITUAL\n");
    printf ("\nCALLE........................: %s", d.calle);
    printf ("\nNRO..........................: %s", d.nro);
    printf ("\nLOCALIDAD....................: %s", d.localidad);
    printf ("\nPROVINCIA....................: %s", d.provincia);
    printf ("\nCODIGO POSTAL................: %s", d.cpos);
}

int cargaDomicilios (stDomicilio d[], int v, int dim){
    char opcion = 0;

    while(v < dim && opcion != 27){
        system("cls");
        d[v] = cargaUnDomicilio();
        v++;
        printf("\nESC para salir o cualquier tecla para continuar...");
        opcion = getch();
    }

    return v;
}

void muestraDomicilios(stDomicilio d[], int v){
    for(int i=0;i<v;i++){
        muestraUnDomicilio(d[i]);
    }
}

void cargaArchDomiciliosRandom(char nombreArchivo[], int cant){
    FILE* archi = fopen(nombreArchivo, "ab");
    stDomicilio domicilio;
    int i = 0;
    if(archi){
        while(i<cant){
            domicilio = getDomicilioRandom();
            fwrite(&domicilio, sizeof(stDomicilio), 1, archi);
            i++;
        }
        fclose(archi);
    }
}

void muestraArchivoDomicilio(char nombreArchivo[]){
    stDomicilio domicilio;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi){
        while(fread(&domicilio, sizeof(stDomicilio), 1, archi)>0){
            muestraUnDomicilio(domicilio);
        }
        fclose(archi);
    }
}
