#ifndef CUENTA_H_INCLUDED
#define CUENTA_H_INCLUDED
#include "clientes.h"


typedef struct{
    int id; /// campo único y autoincremental
    int idCliente; /// Id del Cliente dueño de la Cuenta;
    int nroCuenta;
    int tipoDeCuenta; /// 1. Caja de Ahorro en Pesos, 2. Caja de Ahorro en Dólares, 3. Cta Cte en $
    float costoMensual; /// Costo de mantenimiento del producto;
    float saldo; /// Debe actualizarse al modidificar o cargar un movimiento.
    int eliminado; /// 0 si está activo - 1 si está eliminado
}stCuenta;

stCuenta cargaUnaCuenta(int idCliente);
void muestraUnaCuenta(stCuenta c);
stCuenta getCuentasRandom ();
void imprimeTipoDeCuenta(int dato);
void cargaCuentasEnArchivo(char nombreArchivo[], int idCliente);
int ultimoIdCuentas(char nombreArchivo[]);
int buscaCuentaEnArchivo(char nombreArchivo[], int dato);
int buscaCuentaEnArchivoFlag(FILE* archi, int dato);
int buscaPosEnArchivo(char nombreArchivo[], int dato);
int cuentaRegistros(char nombreArchivo[], int tamanioEstructura);
void muestraUnArchivo(char nombreArchivo[]);
void agregarCuentaACliente(char nombreArchivoCuentas[], int idCliente);
void buscaCuentasDeCliente(char nombreArchivoCuentas[], stCliente cliente);
stCuenta cargaUnaCuenta(int idDuenioCuenta);
void bajaAltaCliente(char nombreArchiClientes[], char nombreArchiCuentas[], char dni[]);


#endif // CUENTA_H_INCLUDED
