#include <stdio.h>
#include <stdlib.h>
#include "cuenta.h"

stCuenta cargaUnaCuenta(){
    stCuenta c;

    static int i = 0;
    i++;

    c.id = i;/// campo único y autoincremental
    c.idCliente = 0;///stCliente.nroCliente;// Id del Cliente dueño de la Cuenta;
    //printf("\nIngrese un numero de cuenta:");
    c.nroCuenta = getNumeroDeCuenta();
    printf("\nIngrese un tipo de cuenta 1. Caja de Ahorro en Pesos, 2. Caja de Ahorro en Dólares, 3. Cta Cte en $:");
    scanf("%d", &c.tipoDeCuenta);
    creaTipoDeCuenta(c.tipoDeCuenta);
    c.costoMensual=0;
    c.saldo = 0;
    c.eliminado = 0; /// 0 si está activo - 1 si está eliminado

    return c;
}
void muestraUnaCuenta(stCuenta c){

    printf("\nid...............................:%d", c.id);
    printf("\nidCliente........................:%d", c.idCliente);
    printf("\nNro de Cuenta....................:%d", c.nroCuenta);
    printf("\nTipo de Cuenta...................:%d", c.tipoDeCuenta);
    printf("\nCosto de Mantenimiento Mensual...:%.2f", c.costoMensual);
    printf("\nSaldo en Cuenta..................:%.2f", c.saldo);
    printf("\nSaldo en Cuenta..................:%c", c.eliminado);
    printf("\n==================================================================");

}

int getNumeroDeCuenta(){
    int nro;

    nro = rand()%1000000 + 10000;

    return nro;
}

void creaTipoDeCuenta(int dato){

    if(dato == 1){
        printf("Se creo una Caja de ahorro en pesos");
    }
    if(dato == 2){
        printf("Se creo una Caja de ahorro en Dolares");
    }
    if(dato == 3){
        printf("Se creo una Cuenta Corriente");
    }
}






