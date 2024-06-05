#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "movimientosL.h"
#include "mocksMovimientos.h"

stMovimiento cargaUnMovimiento()
{
    stMovimiento m;
    int id=0;
    id++;
    m.id = id;

    printf (" ID de la cuenta n:\n",&id);
    scanf("%d",&m.idCuenta);
    printf ("Descripcion del movimiento\n");

     fflush(stdin);
    printf ("Detalle:\n");
    fgets(m.detalle, sizeof(m.detalle), stdin);
    //gets(&m.detalle);

    fflush(stdin);
    printf("importe:\n");
    scanf("%f",&m.importe);

    fflush(stdin);
    printf ("ingrese año, mes  y dia:\n");
    scanf ("%d %d %d",&m.anio,&m.mes,&m.dia);

    system("cls");
    return m;
}

void muestraUnMovimiento(stMovimiento m)
{

    printf("Detalle del movimiento..:%s\n",m.detalle);
    printf("cuenta n................:%d\n",m.idCuenta);
    printf("usuario n...............:%d\n",m.id);
    printf("importe.................:%.2f\n",m.importe);
    printf("dia.....................:%d \n",m.dia);
    printf("mes.....................:%d \n",m.mes);
    printf("anio....................:%d\n",m.anio);
    printf("Estado de cuenta........:%d\n",m.eliminado);
    printf ("=========================================\n");
}
int cargaMovimientos(stMovimiento a[], int v, int dim)
{
    char opcion = 0;
    while(v < dim && opcion != 27)
    {

        a[v] = cargaUnMovimiento();
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

void cargaArchMovimientoRandom(char nombreArchivo[] ,int cant){
FILE*archi = fopen(nombreArchivo,"wb");
stMovimiento movimiento;
int i=0;
if (archi)
{
    while (i<cant){

         movimiento =getMovimientoRandom();
        fwrite(&movimiento,sizeof(stMovimiento),1,archi);

    i++;
    }
    fclose(archi);

}
}


void muestraArchivoMovimimiento (char nombreArchivo[]){
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
