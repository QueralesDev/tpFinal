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

 printf ("la de tu señora ");
     printf ("la de tu señora 2");
    stMovimiento movimientos[10];
    stMovimiento movimientos2[10];
    int vMovimientos=0;
    int vMovimientos2=0;





    vMovimientos=cargaMovimientos(movimientos,vMovimientos,10);
    muestraMovimientos(movimientos,vMovimientos);

cargaArchMovimientoRandom (AR_MOVIMIENTOS,1);
    muestraArchivoMovimimiento (AR_MOVIMIENTOS);



    printf ("\n");
    printf ("\Bye bye world");
    return 0;
}


