#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "string.h"
#include "movimientosL.h"
#include "mocksMovimientos.h"


#define AR_MOVIMIENTOS "movimientos.dat"

/*

Alta, Baja, Modificación, Consulta y Listados de Movimientos por Cuenta y por mes.
Alta de movimientos aleatorios del año actual anteriores a la fecha actual.
La función deberá agregar 1000 eligiendo de manera aleatoria el cliente el  mes y el
día. Si el importe es negativo en descripción deberá insertar un  texto relativo a
un pago, transferencia a cuenta propia, transferencia a
cuenta de terceros, pago de TC, o pagos con TD. Si es positivo en descripción
deberá insertar un texto relativo a un cobro, ej. crédito Haberes, transferencia
de cuenta propia, transferencia de cuenta ajena, acreditación de plazo fijo, etc.
Cada vez que se ingresa o modifica un movimiento se debe actualizar el saldo de la cuenta.
Validación en el ingreso de los Datos.
Buscar Movimientos por fecha.
Buscar Clientes.
*/

int main()
{

    stMovimiento movimientos[10];

    int vMovimientos=0;
    int n, opcion;
    int cuentaUNo;
    int monto;
    int montoR;
    do
    {
        printf( "\n   1. ver movimientos.");
        printf( "\n   2. ingresar dinero.");
        printf( "\n   3. retirar dinero." );
        printf( "\n   4. crear movimiento ." );
        printf( "\n   5. cargar movimientos random ." );


        scanf( "%d", &opcion );

        /* Inicio del anidamiento */

        switch ( opcion )
        {
        case 1:
            printf( "\n  listado de movimientos: \n");

            printf( "\n  elija tipo de cuenta\n");

            break;

        case 2:
            printf( "\n Monto a ingresar : ");
            scanf( "%d", &montoR );

            printf( "\n  El monto a ingresar es :%d\n",monto);
            break;

        case 3:
            printf( "\n  monto a retirar:");
            scanf( "%d", &montoR );

            printf( "\n  El monto a retirar es :%d\n)",montoR);
            break;

        case 4:
            printf( "\n  carga movimiento por usuario ");
            vMovimientos=cargaMovimientos(movimientos,vMovimientos,10);
            muestraMovimientos(movimientos,vMovimientos);


            break;
        case 5:
            printf( "\n  carga movimientos random: ");

            cargaArchMovimientoRandom (AR_MOVIMIENTOS,10);
            muestraArchivoMovimimiento (AR_MOVIMIENTOS);
            break;

        }


    }
   while ( opcion != 27 );
    opcion=getch();

    return 0;
}


