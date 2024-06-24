#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include "domicilios.h"
#include "cuentas.h"
#include "movimientos.h"


typedef struct
{
    int id; /// campo único y autoincremental
    int nroCliente;
    char nombre[30];
    char apellido[30];
    char dni[10];
    char email[30];
    stDomicilio domicilio;
    char telefono[12];
    int eliminado; /// 0 si está activo - 1 si está eliminado
} stCliente;

stCliente cargaUnCliente ();
void muestraUnCliente (stCliente c);
int cargaClientes (stCliente c[], int v, int dim);
void muestraClientes(stCliente c[], int v);
void cargaUnArchivoUsuario(char nombreArchivo[]);
void cargaArchClienteRandom(char nombreArchCliente[], int cant);
void muestraArchivoCliente(char nombreArchivo[]);
stCliente getClienteRandom();
void buscaYMuestraClientePorDNI(char nombreArchivo[], char dni[]);
int buscaDatoEnArchivoStr(char nombreArchivo[], char dato[]);
stCliente* buscaClientePorDNIPuntero(char nombreArchivo[], char dni[]);
void menu();
stCliente modificaCampoClientePorDNI(char nombreArchivo[], char dni[]);
void muestraClienteYCuentas(char nombreArchivoClientes[], char nombreArchivoCuentas[], int idCliente);
void cargarNuevoCliente();
void checkPassword(char valid_password[3][10]);
void buscaCuentasDeCliente(char nombreArchivoCuentas[], stCliente cliente);
int arch2arregloClienteAct (char archClientes[], stCliente a[], int dim);
void cargarClienteYCuenta(char nombreArchivoClientes[], char nombreArchivoCuentas[]);
void buscaClientes(char archClientes[], char archCuentas[], char archMovimientos[]);
stCliente obtenerUltimoCliente(char nombreArchivo[]);
void altaCuenta(char nombreArchivoCuentas[], stCliente cliente);
void bajaCuenta(char nombreArchivoCuentas[], stCliente cliente);
void cargarClienteYCuentaYMovimientos(char nombreArchivoClientes[], char nombreArchivoCuentas[], char* nombreArchivoMovimientos);

#endif // CLIENTE_H_INCLUDED
