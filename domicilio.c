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

    printf ("CALLE.........................: ");
    fgets(d.calle, sizeof(d.calle), stdin);
    d.calle[strcspn(d.calle, "\n")] = 0;

    printf ("NRO...........................: ");
    fgets(d.nro, sizeof(d.nro), stdin);
    d.nro[strcspn(d.nro, "\n")] = 0;

    printf ("LOCALIDAD.....................: ");
    fgets(d.localidad, sizeof(d.localidad), stdin);
    d.localidad[strcspn(d.localidad, "\n")] = 0;

    printf ("PROVINCIA.....................: ");
    fgets(d.provincia, sizeof(d.provincia), stdin);
    d.provincia[strcspn(d.provincia, "\n")] = 0;

    printf ("CODIGO POSTAL.................: ");
    fgets(d.cpos, sizeof(d.cpos), stdin);
    d.cpos[strcspn(d.cpos, "\n")] = 0;

    return d;
}
void muestraUnDomicilio (stDomicilio d)
{
    printf ("\n=====================================================");
    printf ("\n\tDOMICILIO REAL DE RESIDENCIA HABITUAL\n");
    printf ("\nCALLE............................: %s", d.calle);
    printf ("\nNRO..............................: %s", d.nro);
    printf ("\nLOCALIDAD........................: %s", d.localidad);
    printf ("\nPROVINCIA........................: %s", d.provincia);
    printf ("\nCODIGO POSTAL....................: %s", d.cpos);
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
