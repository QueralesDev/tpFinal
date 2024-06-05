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
    int cont;


    cargaCuentasEnArchivo(AR_CUENTAS);
    printf("\nELEMENTOS DEL ARCHIVO CUENTAS");
    muestraUnArchivo(AR_CUENTAS);

    cont = cuentaRegistros(AR_CUENTAS, sizeof(stCuenta));
    printf("\nLa cantidad de registros en el Archivo es :%d\n", cont);

    vCuentas = buscaCuentasUsuarioEnArchivo(AR_CUENTAS,cuentas,vCuentas,3);
    printf("\nELEMENTOS DEL ARREGLO CUENTAS");
    muestraUnArreglo(cuentas, vCuentas);

    return 0;
}

/** \brief Funcion que carga datos en un archivo
 *
 * \param char nombreArchivo[] - nombre del archivo a cargar
 * Dentro de esta funcion tambien se llama a la funcion buscaCuentaEnArchivoPro(), para
 filtrar los datos antes de que sean cargados al archivo con la finalidad de que no
 esten repetidos en el archivo, en este caso el dato a filtrar numeros de cuenta.
 * \return sin retorno
 *
 */
void cargaCuentasEnArchivo(char nombreArchivo[])
{
    stCuenta c;
    char opcion;
    int static id;
    int existe;
    id = ultimoId(AR_CUENTAS);
    FILE* archi = fopen(nombreArchivo, "a+b");
    if(archi)
    {
        do
        {
            system("cls");

            c = cargaUnaCuenta();

            existe = buscaCuentaEnArchivoFlag(archi, c.nroCuenta);
            printf("%d", existe);
            if(existe == 1)
            {

                printf("ERROR - cuenta repetida");

            }
            else
            {
                id++;
                c.id = id;
                fwrite(&c, sizeof(stCuenta), 1, archi);

            }

            printf("\nESC para salir cualquier otra tecla para continuar cargando......");

            opcion = getch();

        }
        while(opcion != ESC);

        fclose(archi);
    }

}

/** \brief Funcion que muestra un archivo
 *
 * \param char nombreArchivo[] - nombre del archivo a mostrar
 * \return sin retono
 *
 */

void muestraUnArchivo(char nombreArchivo[])
{
    stCuenta c;

    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {

        while(fread(&c, sizeof(stCuenta), 1, archi)>0)
        {

            muestraUnaCuenta(c);

        }
        fclose(archi);
    }

}
///Funcion para tener un id unico y autoincremental
/** \brief Funcion que retorna el ultimo Id utilizado
 *
 * \param char nombreArchivo[] - nombre del archivo del que queremos retornar el id
 * \return id - ultimo id usado
 *
 */

int ultimoId(char nombreArchivo[])
{
    int id = 0;
    stCuenta c;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        fseek(archi, -1*(sizeof(stCuenta)), SEEK_END);
        if(fread(&c,sizeof(stCuenta), 1, archi)>0)
        {

            id = c.id;
        }

        fclose(archi);
    }

    return id;
}

/** \brief Funcion que carga un arreglo tipo estructura
 *
 * \param stCuenta c[] - arreglo que se va a cargar
 * \param int v - cantidad de elementos validos del arreglo y primera pos vacia
 * \param int dim - dimension del arreglo
 * \return v - cantidad de elementos cargados en el arreglo
 *
 */
int cargaUnArregloConCuentasRandom(stCuenta c[], int v, int dim)
{
    char opcion = 0;
    while(v<dim && opcion != 27)
    {
        c[v] = cargaUnaCuenta();
        v++;

        printf("ESC para salir");
        opcion = getch();
    }
    return v;
}


void muestraUnArreglo(stCuenta c[], int v)
{

    for(int i=0; i<v; i++)
    {

        muestraUnaCuenta(c[i]);
    }
}


/** \brief Funcion que busca un dato en una en un archivo
 *
 * \param char nombreArchivo - nombre del archivo en el que queremos buscar
 * \param int nroCuenta - dato a buscar en el archivo
 * \return flag - bandera en booleana
 *
 */
int buscaCuentaEnArchivo(char nombreArchivo[], int nroCuenta)
{
    stCuenta c;
    int flag = 0;
    //rewind(archi);
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        while(flag == 0 && fread(&c, sizeof(stCuenta), 1, archi)>0)
        {
            if(c.nroCuenta == nroCuenta)
            {
                flag = 1;
            }
        }
        fclose(archi);
    }
    return flag;
}

///esta funcion es para ser usada con la funcion de cargaUnArchivo
/** \brief Funcion que busca un dato en una carga de archivos
 *
 * \param FILE *archi - archivo abierto(OJO)
 * \param int nroCuenta - dato a buscar en el archivo
 * \return flag - bandera en booleana
 *
 */
int buscaCuentaEnArchivoFlag(FILE* archi, int nroCuenta)
{
    stCuenta c;
    int flag = 0;
    rewind(archi);
    if(archi)
    {
        while(flag == 0 && fread(&c, sizeof(stCuenta), 1, archi)>0)
        {
            if(c.nroCuenta == nroCuenta)
            {
                flag = 1;
            }
        }
        //fclose(archi);
    }
    return flag;
}

int buscaCuentasUsuarioEnArchivo(char nombreArchivo[], stCuenta a[], int v, int dato)
{
    stCuenta c;
    int flag = 0;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        while(fread(&c, sizeof(stCuenta), 1, archi)>0)
        {
            if(c.idCliente == dato)
            {
                a[v]= c;
                v++;
            }
        }
        fclose(archi);
    }
    return v;
}

/** \brief Funcion que busca un dato tipo entero en un archivo
 *
 * \param char nombreArchivo - nombre del archivo
 * \param int dato -   dato a buscar en el archivo
 * \return flag - bandera booleana en caso de que el dato exista o no en el archivo
 *
 */

int buscaDatoEnArchivoInt(char nombreArchivo[], int dato)
{

    stCuenta c;
    int flag = 0;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        while(flag == 0 && fread(&c, sizeof(stCuenta), 1, archi)>0)
        {
            if(c.nroCuenta == dato) /// en este caso la funcion busca un numero de cuenta
            {
                flag = 1;
            }
        }
        fclose(archi);
    }
    return flag;
}


/** \brief Funcion que busca un dato tipo string en un archivo
 *
 * \param char nombreArchivo - nombre del archivo
 * \param char dato -   dato a buscar en el archivo
 * \return flag - bandera booleana en caso de que el string exista o no en el archivo
 *
 */
int buscaDatoEnArchivoStr(char nombreArchivo[], char dato[])
{
    stCuenta c;
    int flag = 0;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        while(flag == 0 && fread(&c, sizeof(stCuenta), 1, archi)>0)
        {
            if(strcmp(c.nroCuenta, dato) == 0) /// en este caso la funcion busca un string
            {
                flag = 1;
            }
        }
        fclose(archi);
    }
    return flag;
}


/** \brief Funcion para contar cantidad de registros en un archivo
 *
 * \param char nombreArchivo - nombre del archivo del que queremos saber los registros
 * \param int tamanioEstructura - tamaño total en bytes de la estructura con sizeof()
 *Primero ubico el cursor al final del archivo con FSEEK(), despues con FTELL() leo
 la cantidad total de datos en el archivo y luego lo divido entre el tamaño de la
 estructura.
 * \return int cant - retorna el numero de registros que tiene el archivo
 * al dividir lo que le devuelve ftell() dividido por el tamanio de la estructura
 */
int cuentaRegistros(char nombreArchivo[], int tamanioEstructura)
{

    int cont = 0;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {

        fseek(archi, 0, SEEK_END);
        cont = ftell(archi) / tamanioEstructura;

        fclose(archi);
    }
    return cont;
}
///funcion pendiente por terminar
int buscaPosEnArchivo(char nombreArchivo[], int dato)
{
    int pos;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {

        fclose(archi);
    }
    return pos;
}

/** \brief Funcion que pasa elementos de un Archivo a un Arreglo
 *
 * \param char nombreArchivo - Nombre del archivo del que provienen los datos(ORIGEN)
 * \param stCuenta[] - arreglo tipo estructura a donde van los datos(DESTINO)
 * \param int v - elementos validos del arreglo
 * \param int dim - dimension del arreglo
 * \return v - cantidad de elementos cargados al arreglo
 *
 */
int archi2Arreglo(char nombreArchivo[], stCuenta c[], int v, int dim)
{

    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {

        while(v<dim && fread(&c[v],sizeof(stCuenta),1, archi)>0)
        {

            v++;
        }
        fclose(archi);
    }
    return v;
}

/** \brief Funcion para pasar de archivo a arreglo con filtro de string usando la funcion
atoi() para dividir por %2 y pasar los elementos pares
     *
     * \param char nombreArchivo - Nombre del archivo del que provienen los datos(ORIGEN)
     * \param stCuenta[] - arreglo tipo estructura a donde van los datos(DESTINO)
     * \param int v - elementos validos del arreglo
     * \param int dim - dimension del arreglo
     * \return cantidad de elementos cargados al arreglo
     */
int archi2ArregloDNI(char nombreArchivo[], stCuenta arreglo[], int v, int dim)
{

    FILE* archi = fopen(nombreArchivo, "rb");
    stCuenta c;

    if(archi)
    {

        while(v<dim && fread(&c,sizeof(stCuenta),1, archi)>0)
        {
            ///if(atoi(c.dni)%2 == 0) la funcion atoi() convierte un string a entero

            arreglo[v] = c;
            v++;

        }
        fclose(archi);
    }
    return v;
}
int buscaPosicionCuentaEnArchivo(int idCuenta){
int pos = -1;

//buscas la cuenta


return pos;
}
void modificaDatoEnArchivo(char nombreArchivo[], int pos, stCuenta aModificar)
{
    //stCuenta c;
    FILE* archi = fopen(nombreArchivo,"a+b");
    if(archi)
    {

        fseek(archi, 0, SEEK_SET);
        fseek(archi, pos*sizeof(stCuenta), SEEK_SET);
        fseek(archi, -1 *sizeof(stCuenta), SEEK_CUR);
      //  fread(&c,sizeof(stCuenta),1,archi);

        //c = cargaUnaCuenta();
        fwrite(&aModificar,sizeof(stCuenta),1,archi);
    }
    fclose(archi);
}

