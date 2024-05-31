#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "cuenta.h"

#define AR_CUENTAS "cuentas.dat"
#define ESC 27
#define DIM 100

int ultimoId(char nombreArchivo[]);

int main()
{
    srand(time(NULL));

    stCuenta cuenta;
    stCuenta cuentas[DIM];
    int vCuentas = 0;

    //cuenta = cargaUnaCuenta();
    //muestraUnaCuenta(cuenta);

//    printf("\nELEMENTOS DEL ARREGLO CUENTAS");
//
//    vCuentas = cargaUnArreglo(cuentas, vCuentas, DIM);
//    muestraUnarreglo(cuentas, vCuentas);
//
//    printf("\n");
//
//    system("pause");

    cargaUnArchivoUsuario(AR_CUENTAS);
    printf("\nELEMENTOS DEL ARCHIVO CUENTAS");
    muestraUnArchivo(AR_CUENTAS);

    return 0;
}

void cargaUnArchivoUsuario(char nombreArchivo[]){

    stCuenta c;
    char opcion;
    int static id;
    int existe;
    id = ultimoId(AR_CUENTAS);
    FILE* archi = fopen(nombreArchivo, "a+b");
    if(archi){
        do{
        system("cls");

        c = cargaUnaCuenta();

        existe = buscaCuentaEnArchivoPro(archi, c.nroCuenta);
        printf("%d", existe);
        if(existe == 1){

            printf("ERROR - cuenta repetida");

        }else{
            id++;
            c.id = id;
            fwrite(&c, sizeof(stCuenta), 1, archi);

        }

        printf("\nESC para salir cualquier otra tecla para continuar cargando......");

        opcion = getch();

        }while(opcion != ESC);

        fclose(archi);
    }

}

void muestraUnArchivo(char nombreArchivo[]){
    stCuenta c;

    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi){

        while(fread(&c, sizeof(stCuenta), 1, archi)>0){

        muestraUnaCuenta(c);

        }
        fclose(archi);
    }

}

int ultimoId(char nombreArchivo[]){
    int id = 0;
    stCuenta c;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi){
        fseek(archi, -1*(sizeof(stCuenta)), SEEK_END);
        if(fread(&c,sizeof(stCuenta), 1, archi)>0){

            id = c.id;
        }

    fclose(archi);
    }

    return id;
}

int cargaUnArreglo(stCuenta c[], int v, int dim){
    char opcion = 0;
    while(v<dim && opcion != 27){
       c[v] = cargaUnaCuenta();
       v++;

       printf("ESC para salir");
       opcion = getch();
    }
    return v;
}

void muestraUnarreglo(stCuenta c[], int v){

    for(int i=0; i<v; i++){

        muestraUnaCuenta(c[i]);
    }
}

int buscaCuentaEnArchivo(char nombreArchivo[], int nroCuenta){

    stCuenta c;
    int flag = 0;
    //rewind(archi);
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi){
    while(flag == 0 && fread(&c, sizeof(stCuenta), 1, archi)>0){
            if(c.nroCuenta == nroCuenta){
            flag = 1;
            }
        }
        fclose(archi);
    }
    return flag;
}

///esta funcion es para ser usada con la funcion de cargaUnArchivo
/** \brief Funcion que filtra un dato en una carga de archivos
 *
 * \param FILE *archi - archivo abierto
 * \param int nroCuenta - dato a buscar en el archivo
 * \return flag - bandera en booleana
 *
 */

int buscaCuentaEnArchivoPro(FILE* archi, int nroCuenta){

    stCuenta c;
    int flag = 0;
    rewind(archi);
    if(archi){
    while(flag == 0 && fread(&c, sizeof(stCuenta), 1, archi)>0){
            if(c.nroCuenta == nroCuenta){
            flag = 1;
            }
        }
        //fclose(archi);
    }
    return flag;
    }

    int buscaDatoEnArchivoInt(char nombreArchivo[], int dato){

    stCuenta c;
    int flag = 0;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi){
    while(flag == 0 && fread(&c, sizeof(stCuenta), 1, archi)>0){
            if(c.nroCuenta == nroCuenta){/// en este caso la funcion busca un numero de cuenta
            flag = 1;
            }
        }
        fclose(archi);
    }
    return flag;
    }


