#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

typedef struct
{
    int id; /// campo único y autoincremental
    int nroCliente;
    char nombre[30];
    char apellido[30];
    char dni[10];
    char email[30];
    //stDomicilio domicilio;
    char telefono[12];
    int eliminado; /// 0 si está activo - 1 si está eliminado
} stCliente;

stCliente cargaUnCliente ();
void muestraUnCliente (stCliente c);
int cargaClientes (stCliente c[], int v, int dim);
void muestraClientes(stCliente c[], int v);
void cargaUnArchivoUsuario(char nombreArchivo[]);
int buscaCuentaEnArchivoPro(FILE* archi, int nroCliente);
void cargaArchClienteRandom(char nombreArchivo[], int cant);
void muestraArchivoCliente(char nombreArchivo[]);
stCliente getClienteRandom();
void buscaYMuestraClientePorDNI(char nombreArchivo[], char dni[]);
stCliente buscaDatoEnArchivoStr(char nombreArchivo[], char dato[]);


#endif // CLIENTE_H_INCLUDED
