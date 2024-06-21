#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "domicilios.h"
#include "cuentas.h"
#include "menu.h"
#include <string.h>
#define AR_CLIENTES "clientes.bin"
#define AR_CUENTAS "cuentas.bin"

int main()
{
    //muestraArchivoCliente(AR_CLIENTES);
    //muestraArchivoCliente(AR_CUENTAS);
    char valid_password[3][10] = {"32619370", "111", "222"};
    checkPassword(valid_password);

    return 0;
}
