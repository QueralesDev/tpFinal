#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#include "domicilios.h"
#include "cuentas.h"
#include "movimientos.h"
#include "menu.h"
#define AR_CLIENTES "clientes.bin"
#define AR_CUENTAS "cuentas.bin"
#define AR_MOVIMIENTOS "movimientos.bin"
#define AR_DOMICILIOS "domicilios.bin"


int main()
{
    srand(time(NULL));

    char valid_password[3][10] = {"32619370", "96006057", "33266432"};
    checkPassword(valid_password);

    return 0;
}
