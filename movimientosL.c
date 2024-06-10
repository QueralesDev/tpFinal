#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "movimientosL.h"
#include "mocksMovimientos.h"

stMovimiento cargaUnMovimiento(int idCuenta)
{
    stMovimiento m;

    int id=0;
    id++;
    m.id = id;
    m.idCuenta = idCuenta; // Asigna el valor del argumento 'idCuenta' al campo 'idCuenta' de 'm'

    printf("Descripcion del movimiento\n"); // Imprime un mensaje en la consola
    printf("Detalle:\n"); // Imprime otro mensaje en la consola

    fgets(m.detalle, sizeof(m.detalle), stdin); // Solicita al usuario que introduzca el detalle del movimiento y lo guarda en el campo 'detalle' de 'm'

    printf("importe:\n"); // Imprime un mensaje en la consola
    scanf("%f",&m.importe); // Solicita al usuario que introduzca el importe del movimiento y lo guarda en el campo 'importe' de 'm'

    printf("ingrese año, mes y dia:\n"); // Imprime un mensaje en la consola
    scanf("%d %d %d",&m.anio,&m.mes,&m.dia); // Solicita al usuario que introduzca el año, mes y día del movimiento y los guarda en los campos correspondientes de 'm'

    system("cls"); // Limpia la consola

    return m; // Devuelve la estructura 'm'
}


void muestraUnMovimiento(stMovimiento m)
{
    printf ("<<<<<<<<<<<<MOVIMIENTO>>>>>>>>>>>>>>\n");

    printf("DETALLE DE MOVIMIENTO...:%s\n",m.detalle);
    printf("CUENTA N................:%d\n",m.idCuenta);
    printf("USUARIO.................:%d\n",m.id);
    printf("IMPORTE.................:%.2f\n",m.importe);
    printf("DIA.....................:%d \n",m.dia);
    printf("MES.....................:%d \n",m.mes);
    printf("ANIO....................:%d\n",m.anio);
    printf("ESTADO DE CUENTA........:%d\n",m.eliminado);
    printf ("=========================================\n");
}
int cargaMovimientos(stMovimiento a[], int v, int dim)
{
    char opcion = 0;
    while(v < dim && opcion != 27)
    {

        a[v] = cargaUnMovimiento(a.idCuenta);
        v++;
        printf("\nESC para salir o cualquier tecla para continuar...");
        opcion = getch();
    }
    return v;
}
void muestraMovimientos(stMovimiento a[], int v)
{
    for(int i=0; i<v; i++)
    {
        muestraUnMovimiento(a[i]);
    }
    printf ("\n============================================");
}

void cargaArchMovimientoRandom(char nombreArchivo[],int cant)
{
    FILE*archi = fopen(nombreArchivo,"wb");
    stMovimiento movimiento;
    int i=0;
    if (archi)
    {
        while (i<cant)
        {

            movimiento =getMovimientoRandom();
            fwrite(&movimiento,sizeof(stMovimiento),1,archi);

            i++;
        }
        fclose(archi);

    }
}


void muestraArchivoMovimimiento (char nombreArchivo[])
{
    stMovimiento movimiento;
    FILE*archi = fopen(nombreArchivo,"rb");


    if (archi)
    {
        while (fread(&movimiento,sizeof(stMovimiento),1,archi)>0)
        {

            muestraUnMovimiento(movimiento);
        }
        fclose(archi);

    }
}

int ultimoIdMovimiento (char nombreArchivo[])
{
    int id =0;
    stMovimiento m;
    FILE*archi=fopen(nombreArchivo,"rb");
    if (archi)
    {

        fseek(archi,-1*sizeof(stMovimiento)),SEEK_END;
        if (fread(&m,sizeof(stMovimiento),1,archi)>0)
        {
            id=m.id
        }
        fclose(archi);
    }
    return id;
}

void cargaMovimientosAR (char nombreArchivo,int idCuenta){

stMovimiento m;
char opcion=0;
int static id;
id=ultimoIdMovimiento(AR_MOVIMIENTOS);
FILE*archi=fopen(nombreArchivo,"a+b");
if (archi){

    m=cargaUnMovimiento(idCuenta);
    fwrite(&m,sizeof(stMovimiento),1,archi);

}
fclose (archi);

}





