#ifndef CUENTA_H_INCLUDED
#define CUENTA_H_INCLUDED
#include "clientes.h"
#include "cuentas.h"
#include "movimientos.h"

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
stCuenta cargaUnaCuenta(int idDuenioCuenta);
int buscaTipoCuentaEnArchivoFlag(FILE* archi, int idCliente, int dato);
void bajaAltaCliente(char nombreArchiClientes[], char nombreArchiCuentas[], char dni[]);
void depositar(char* archMovimientos, stCuenta* cuenta);
void retirar(char* archMovimientos, stCuenta* cuenta, float monto);
void actualizaCuentaEnArchivo(char archCuentas[], stCuenta* cuenta);
void operacionesMovimientos (char nombreArchivo[], stCuenta* cuenta);
stCuenta buscaCuentaPorNumero(FILE* archi, int nroCuenta);
stCuenta seleccionaCuentaDeCliente(char archCuentas[]);
float obtenerSaldo(stCuenta* cuenta);



//void buscaCuentaPorNumero(char nombreArchivoCuentas[], int numeroCuenta);
#endif // CUENTA_H_INCLUDED
