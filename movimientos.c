#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "clientes.h"
#include "domicilios.h"
#include "mocks_Domicilios_Clientes.h"
#include "cuentas.h"
#include "movimientos.h"
#define AR_CLIENTES "clientes.bin"
#define AR_CUENTAS "cuentas.bin"
#define AR_MOVIMIENTOS "movimientos.bin"


stMovimiento cargaUnMovimiento(int idCuenta)
{
    stMovimiento m;

    int id=0;
    id++;
    m.id = id;
    m.idCuenta = idCuenta;
    m.anio = obtenerAnio();
    m.mes = obtenerMes();
    m.dia = obtenerDia();
    m.eliminado = 0;
    system("cls");

    return m;
}


void muestraUnMovimiento(stMovimiento m)
{
    printf ("<<<<<<<<<<<<MOVIMIENTO>>>>>>>>>>>>>>\n");

    printf("Id................:%d\n",m.id);
    printf("CUENTA NRO..............:%d\n",m.idCuenta);
    printf("DETALLE DE MOVIMIENTO...:%s\n",m.detalle);

    printf("IMPORTE.................:%.2f\n",m.importe);
    printf("DIA.....................:%d \n",m.dia);
    printf("MES.....................:%d \n",m.mes);
    printf("ANIO....................:%d\n",m.anio);
    printf("ESTADO DE CUENTA........:%d\n",m.eliminado);
    printf ("=========================================\n");
}

int obtenerDia()
{
    time_t tiempo = time(NULL);
    struct tm *tiempoLocal = localtime(&tiempo);
    int dia = tiempoLocal->tm_mday;
    return dia;
}

int obtenerMes()
{
    time_t tiempo = time(NULL);
    struct tm *tiempoLocal = localtime(&tiempo);
    int mes = tiempoLocal->tm_mon + 1; // Se suma 1 porque los meses en struct tm van de 0 a 11
    return mes;
}

int obtenerAnio()
{
    time_t tiempo = time(NULL);
    struct tm *tiempoLocal = localtime(&tiempo);
    int anio = tiempoLocal->tm_year + 1900; // Se suma 1900 porque el campo tm_year cuenta los años desde 1900

    return anio;
}

int ultimoIdMovimiento (char nombreArchivo[])
{
    int id =0;
    stMovimiento m;
    FILE*archi=fopen(nombreArchivo,"rb");
    if (archi)
    {
        fseek(archi,-1*sizeof(stMovimiento),SEEK_END);
        if (fread(&m,sizeof(stMovimiento),1,archi)>0)
        {
            id=m.id;
        }
        fclose(archi);
    }
    return id;
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

void cargaMovimientosAR(char nombreArchivo[], int idCuenta)
{
    stMovimiento m;
    char opcion;
    int static id;
    id = ultimoIdMovimiento(nombreArchivo);
    FILE* archi = fopen(nombreArchivo, "a+b");
    if (archi)
    {
        do
        {
            system("cls");
            m = cargaUnMovimiento(idCuenta);
            id++;
            fwrite(&m, sizeof(stMovimiento), 1, archi);
            printf("MOVIMIENTO REGISTRADO CON EXITO\n");
            printf("ESC PARA SALIR, CUALQUIER OTRA TECLA PARA CONTINUAR CARGANDO...");
            opcion = getch();
        }
        while (opcion != 27);
        fclose(archi);
    }
}

void depositar(char* archMovimientos, stCuenta* cuenta)
{
    float monto;
    printf("INGRESA EL MONTO A DEPOSITAR: ");
    scanf("%f", &monto);
    getchar();
    cargaMovimientosAR(archMovimientos, cuenta->id);
    cuenta->saldo += monto;

    printf("\nDeposito realizado con exito. Su nuevo saldo es: %.2f\n", cuenta->saldo);


}

void retirar(char* archMovimientos, stCuenta* cuenta, float monto)
{
    if (cuenta->saldo >= monto)
    {
        cuenta->saldo -= monto;
        printf("Retiro realizado con éxito. Su nuevo saldo es: %.2f\n", cuenta->saldo);
        cargaMovimientosAR(archMovimientos, cuenta->id);
    }
    else
    {
        printf("Saldo insuficiente para realizar el retiro.\n");
    }
}

void actualizaCuentaEnArchivo(char archCuentas[], stCuenta* cuentaActualizada)
{
    FILE* archi = fopen(archCuentas, "r+b");
    stCuenta c;

    if (archi)
    {
        while (fread(&c, sizeof(stCuenta), 1, archi) > 0)
        {
            if (c.nroCuenta == cuentaActualizada->nroCuenta && !c.eliminado)
            {
                fseek(archi, -sizeof(stCuenta), SEEK_CUR);
                fwrite(cuentaActualizada, sizeof(stCuenta), 1, archi);
                break; // Termina la búsqueda cuando se encuentra la cuenta
            }
        }
        fclose(archi);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }
}

void buscaYmuestraMovimientosDeUnaCuenta(char nombreArchiMovimientos[], stCuenta cuenta)
{
    FILE* archi = fopen(nombreArchiMovimientos, "rb");//abre el archivo de cuentas en modo de lectura
    stMovimiento m;

    // Buscar las cuentas del cliente en el archivo de cuentas
    while (fread(&m, sizeof(stMovimiento), 1, archi))
    {
        // Si el id del cliente de la cuenta actual coincide con el id del cliente dado
        if (m.idCuenta == cuenta.id)  //verifica si el idCliente de movimientos coincide con el id de cuenta. Si es así, significa que los movimientos pertenecen a esa cuenta
        {
            //printf("\nCUENTA ENCONTRADA: %d\n", cuenta.nroCuenta);
            muestraUnMovimiento(m);
        }
    }

    fclose(archi);
}


void menuOperacionesCuenta(char archCuentas[], char archMovimientos[])
{
    stCuenta cuenta;
    stCuenta cuentaDestino;

    cuenta = seleccionaCuentaDeCliente(AR_CUENTAS);

    int monto;
    int opcion;
    do
    {
        printf("\n================== MENU ==================\n");
        printf("1. DEPOSITAR\n2. RETIRAR\n3. CONSULTAR SALDO\n4. TRANSFERIR\n5. MOSTRAR MOVIMIENTOS\n6. SALIR\n");
        printf("============================================\n");
        printf("ELIGE UNA OPCION: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion)
        {
        case 1:

            printf("INGRESA EL MONTO A DEPOSITAR: ");
            fflush(stdin);
            scanf("%d",&monto);
            depositarPuntero(archMovimientos,&cuenta, monto);

            break;

        case 2:
            printf("INGRESA EL MONTO A RETIRAR: ");
            scanf("%d", &monto);
            getchar();
            retirarPuntero(archMovimientos,&cuenta,monto);
            break;

        case 3:
            printf("EL SALDO DE LA CUENTA ES:");
            break;

        case 4:
            printf("INGRESA EL MONTO A TRANSFERIR: ");
            scanf("%d", &monto);
            getchar();
            cuentaDestino = seleccionaCuentaDeCliente(AR_CUENTAS);
            transferenciaPuntero(archMovimientos,&cuenta, &cuentaDestino, monto);
            break;
        case 5:

            buscaYmuestraMovimientosDeUnaCuenta(archMovimientos,cuenta);

            break;

        case 6:

            printf("SALIENDO DEL PROGRAMA...\n");
            break;
        default:
            printf("OPCION NO VALIDA.\n");
            break;
        }

        //actualizaCuentaEnArchivo(archCuentas, cuenta);



    }
    while (opcion != 6);

    //free(cuenta); // No olvides liberar la memoria cuando ya no la necesites

}

//int cargaMovimientos(stMovimiento a[], int v, int dim)
//{
//    char opcion = 0;
//    while(v < dim && opcion != 27)
//    {
//
//        a[v] = cargaUnMovimiento(a.idCuenta);
//        v++;
//        printf("\nESC para salir o cualquier tecla para continuar...");
//        opcion = getch();
//    }
//    return v;
//}

void muestraMovimientos(stMovimiento a[], int v)
{
    for(int i=0; i<v; i++)
    {
        muestraUnMovimiento(a[i]);
    }
    printf ("\n============================================");
}

//void cargaArchMovimientoRandom(char nombreArchivo[],int cant)
//{
//    FILE*archi = fopen(nombreArchivo,"wb");
//    stMovimiento movimiento;
//    int i=0;
//    if (archi)
//    {
//        while (i<cant)
//        {
//
//            movimiento =getMovimientoRandom();
//            fwrite(&movimiento,sizeof(stMovimiento),1,archi);
//
//            i++;
//        }
//        fclose(archi);
//
//    }
//}

void depositarPuntero(char nombreArchivoMov[], stCuenta* cuenta, int monto)
{
    if (cuenta->eliminado == 0)
    {
        impactoMonto(AR_CUENTAS, monto,cuenta->id,1);


        //cuenta->saldo += (float) monto;


        stMovimiento m;
        int id;
        id = ultimoIdMovimiento(nombreArchivoMov);
        FILE* archi = fopen(nombreArchivoMov, "ab");
        if (archi)
        {

            m = cargaUnMovimiento(cuenta->id);
            id++;
            m.id = id;
            //movimiento->idCuenta = cuenta->id;
            m.importe = monto;
            snprintf(m.detalle, 100, "Deposito de %.2d", monto);
            fwrite(&m, sizeof(stMovimiento), 1, archi);

            fclose(archi);
        }

        printf("Deposito realizado correctamente.\n");
    }
    else
    {
        printf("La cuenta esta eliminada. No se puede realizar el deposito.\n");
    }
}

void retirarPuntero(char nombreArchivoMov[], stCuenta* cuenta, int monto)
{
    if (cuenta->eliminado == 0 && cuenta->saldo > 0)
    {
        impactoMonto(AR_CUENTAS, monto,cuenta->id,0);


        //cuenta->saldo += (float) monto;


        stMovimiento m;
        int id;
        id = ultimoIdMovimiento(nombreArchivoMov);
        FILE* archi = fopen(nombreArchivoMov, "ab");
        if (archi)
        {

            m = cargaUnMovimiento(cuenta->id);
            id++;
            m.id = id;
            //movimiento->idCuenta = cuenta->id;
            m.importe = monto;
            snprintf(m.detalle, 100, "Deposito de %.2d", monto);
            fwrite(&m, sizeof(stMovimiento), 1, archi);

            fclose(archi);
        }

        printf("RETIRO REALIZADO EXITOSAMENTE.\n");
    }
    else
    {
        printf("La cuenta esta eliminada o no tiene saldo. No es posible realizar el retiro.\n");
    }
}

void transferenciaPuntero(char nombreArchivoMov[], stCuenta* cuentaOrigen, stCuenta* cuentaDestino, int monto)
{

    retirarPuntero(nombreArchivoMov, cuentaOrigen, monto);
    depositarPuntero(nombreArchivoMov, cuentaDestino, monto);

}

void impactoMonto (char archivoCuentas [], int monto, int idCuenta, int positivoNegativo)
{

    stCuenta cuenta;
    int montoV = 0;
    FILE*archi = fopen (archivoCuentas, "r+b");

    int flag =0, pos;

    if (archi)
    {


        while (flag == 0 && fread (&cuenta, sizeof (stCuenta), 1, archi) > 0)
        {

            if (cuenta.id == idCuenta)
            {

                flag =1;
                pos = ftell(archi)-sizeof (stCuenta);
                if (positivoNegativo == 0)
                {
                    montoV = cuenta.saldo;
                    cuenta.saldo = montoV - monto;

                }
                else
                {
                    montoV = cuenta.saldo;
                    cuenta.saldo = montoV + monto;

                }

                fseek (archi, pos, SEEK_SET);
                fwrite (&cuenta, sizeof (stCuenta),1,archi);
            }

        }
        fclose (archi);
    }
}

void bajaMovimiento(char nombreArchMovimientos[], stCuenta cuenta)
{
    stMovimiento movimiento;
    FILE* archi = fopen(nombreArchMovimientos, "r+b");//abre el archivo de cuentas en modo de lectura Y escritura

    if(archi)
    {
        // Buscar las cuentas del cliente en el archivo de cuentas
        while (fread(&movimiento, sizeof(movimiento), 1, archi)>0)
        {
            // Si el id del cliente de la cuenta actual coincide con el id del cliente dado
            if (movimiento.idCuenta == cuenta.id)  //verifica si el idCliente del movimiento coincide con el id de la cuenta Si es así, significa que los movimientos pertenecen a la cuenta
            {
                movimiento.eliminado = 1;

                // Mueve el puntero del archivo a la posicion del cliente encontrado
                fseek(archi, -sizeof(stMovimiento), SEEK_CUR);

                // Escribe los nuevos datos del cliente en el archivo
                fwrite(&movimiento, sizeof(stMovimiento), 1, archi);

                // Importante: Avanzar el puntero al siguiente registro
                fseek(archi, 0, SEEK_CUR);
            }
        }
        fclose(archi);
    }
}

void altaMovimiento(char nombreArchMovimientos[], stCuenta cuenta)
{
    stMovimiento movimiento;
    FILE* archi = fopen(nombreArchMovimientos, "r+b");//abre el archivo de cuentas en modo de lectura Y escritura

    if(archi)
    {
        // Buscar las cuentas del cliente en el archivo de cuentas
        while (fread(&movimiento, sizeof(movimiento), 1, archi)>0)
        {
            // Si el id del cliente de la cuenta actual coincide con el id del cliente dado
            if (movimiento.idCuenta == cuenta.id)  //verifica si el idCliente del movimiento coincide con el id de la cuenta Si es así, significa que los movimientos pertenecen a la cuenta
            {
                movimiento.eliminado = 0;

                // Mueve el puntero del archivo a la posicion del cliente encontrado
                fseek(archi, -sizeof(stMovimiento), SEEK_CUR);

                // Escribe los nuevos datos del cliente en el archivo
                fwrite(&movimiento, sizeof(stMovimiento), 1, archi);

                // Importante: Avanzar el puntero al siguiente registro
                fseek(archi, 0, SEEK_CUR);
            }
        }
        fclose(archi);
    }
}

void muestraListadoMovimiento(char nombreArchivo[])
{
    stMovimiento movimiento;
    FILE*archi=fopen(nombreArchivo, "rb");
    if(archi)
    {
        while(fread(&movimiento, sizeof(stMovimiento), 1,archi)>0)
        {
            muestraUnMovimiento(movimiento);
        }
        fclose(archi);
    }
}





