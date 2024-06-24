#ifndef DOMICILIO_H_INCLUDED
#define DOMICILIO_H_INCLUDED

typedef struct
{
    char calle[30];
    char nro[6];
    char localidad[50];
    char provincia[40];
    char cpos[6];
} stDomicilio;

stDomicilio cargaUnDomicilio ();
void muestraUnDomicilio (stDomicilio d);
int cargaDomicilios (stDomicilio d[], int v, int dim);
void muestraArchivoDomicilio(char nombreArchivo[]);
stDomicilio getDomicilioRandom();
void cargaArchDomiciliosRandom(char nombreArchivo[], int cant);

#endif // DOMICILIO_H_INCLUDED
