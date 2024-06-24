#ifndef MOVIMIENTOS_H_INCLUDED
#define MOVIMIENTOS_H_INCLUDED
#include "clientes.h"
#include "cuentas.h"


typedef struct
{
    int id; /// campo único y autoincremental
    int idCuenta; /// Id de la cuenta
    char detalle[100];
    float importe;
    int anio;
    int mes; /// 1 a 12
    int dia; /// 1 a … dependiendo del mes
    int eliminado; /// 0 si está activo - 1 si está eliminado

}stMovimiento;

void cargaMovimientosAR(char nombreArchivo[], int idCuenta);
void muestraArchivoMovimimiento (char nombreArchivo[]);
int ultimoIdMovimiento (char nombreArchivo[]);

//void menuOperacionesCuenta(char archCuentas[], char archMovimientos[], stCliente cliente);



#endif // MOVIMIENTOS_H_INCLUDED
