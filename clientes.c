#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#include "domicilios.h"
#include "mocks_Domicilios_Clientes.h"
#define AR_CLIENTES "clientes.bin"
#define AR_CUENTAS "cuentas.bin"
#include <conio.h>
#include "cuentas.h"


stCliente cargaUnCliente ()
{
    stCliente c;

    static int id=0;
    id++;
    printf("Ingresa los datos del cliente del Banco\n");

    printf ("NRO DE CLIENTE: ");
    scanf("%d", &c.nroCliente);
    getchar();

    printf ("NOMBRE: ");
    fgets(c.nombre, sizeof(c.nombre), stdin);
    c.nombre[strcspn(c.nombre, "\n")] = 0;

    printf ("APELLIDO: ");
    fgets(c.apellido, sizeof(c.apellido), stdin);
    c.apellido[strcspn(c.apellido, "\n")] = 0;

    printf ("DNI: ");
    fgets(c.dni, sizeof(c.dni), stdin);
    c.dni[strcspn(c.dni, "\n")] = 0;

    printf ("E-MAIL: ");
    fgets(c.email, sizeof(c.email), stdin);
    c.email[strcspn(c.email, "\n")] = 0;

    printf ("TELEFONO: ");
    fgets(c.telefono, sizeof(c.telefono), stdin);
    c.telefono[strcspn(c.telefono, "\n")] = 0;

    c.domicilio = cargaUnDomicilio();

    return c;
}
void muestraUnCliente (stCliente c)
{
    printf ("\n=====================================================");
    printf ("\n\t::::::::NRO ID:::::::: %d",c.id);
    printf ("\n=====================================================");
    printf ("\nCLIENTE DEL BANCO NRO...........: %d", c.nroCliente);
    printf ("\n=====================================================");
    printf ("\nNOMBRE..........................: %s", c.nombre);
    printf ("\nAPELLIDO........................: %s", c.apellido);
    printf ("\nDNI.............................: %s", c.dni);
    printf ("\nE-MAIL..........................: %s", c.email);
    printf ("\nTELEFONO........................: %s", c.telefono);
    muestraUnDomicilio(c.domicilio);
    printf ("\n=====================================================\n");
}

int ultimoId(char nombreArchivo[])// estdiuarla
{
    int id = 0;
    stCliente c;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        fseek(archi, -1*(sizeof(stCliente)), SEEK_END);
        if(fread(&c,sizeof(stCliente), 1, archi)>0)
        {
            id = c.id;
        }
        fclose(archi);
    }

    return id;
}
int buscaDatoEnArchivoStr(char nombreArchivo[], char dato[])
{
    stCliente c;
    int flag = 0;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        while(flag == 0 && fread(&c, sizeof(stCliente), 1, archi)>0)
        {
            // Elimina el salto de l√≠nea al final del DNI, si existe
            if (c.dni[strlen(c.dni) - 1] == '\n')
            {
                c.dni[strlen(c.dni) - 1] = '\0';
            }

            if(strcmp(c.dni, dato) == 0) /// la funcion busca un string
            {
                flag = 1;
            }
        }
        fclose(archi);
    }

    return flag;  // Retorna 1 si se encontr√≥ el cliente, 0 en caso contrario
}
void cargaUnArchivoUsuario(char nombreArchivo[])
{
    stCliente c;
    char opcion;
    int static id;
    id = ultimoId(AR_CLIENTES);
    FILE* archi = fopen(nombreArchivo, "a+b");
    if(archi)
    {
        do
        {
            system("cls");
            c = cargaUnCliente();
            int clienteEncontrado = buscaDatoEnArchivoStr(nombreArchivo, c.dni);
            if(clienteEncontrado == 1) // Si se encontr√≥ el cliente
            {
                printf("ERROR - Cliente ya registrado");
            }
            else
            {
                id++;
                c.id = id;
                fwrite(&c, sizeof(stCliente), 1, archi);
            }
            printf("\nESC para salir cualquier otra tecla para continuar cargando......");

            opcion = getch();
        }
        while(opcion != 27);

        fclose(archi);
    }
}


void cargaArchClienteRandom(char nombreArchivo[], int cant)
{
    FILE* archi = fopen(nombreArchivo, "ab");
    stCliente cliente;
    int i = 0;
    if(archi !=NULL)
    {
        while(i<cant)
        {
            cliente = getClienteRandom();
            fwrite(&cliente, sizeof(stCliente), 1, archi);
            i++;
        }
        fclose(archi);
    }
}

void muestraArchivoCliente(char nombreArchivo[])
{
    stCliente cliente;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        while(fread(&cliente, sizeof(stCliente), 1, archi)>0)
        {
            muestraUnCliente(cliente);
        }
        fclose(archi);
    }
}

stCliente* buscaClientePorDNIPuntero(char nombreArchivo[], char dni[])
{
    stCliente* p = NULL;
    stCliente c;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        while(p == NULL && fread(&c, sizeof(stCliente), 1, archi)>0)
        {
            if(strcmp(c.dni, dni) == 0) // Si se encontr√≥ el cliente
            {
                p = malloc(sizeof(stCliente));
                *p = c;
            }
        }
        fclose(archi);
    }

    return p;  // Retorna un puntero al cliente encontrado o NULL si no se encontr√≥
}

/*void menu()
{
    int opcion;
    char dni[10];
    stCliente* p = NULL;  // Mueve la declaraci√≥n al inicio del bloque

    do
    {

        printf("1. Buscar cliente por DNI\n");
        printf("2. Modificar cliente por DNI\n");
        printf("3. Salir\n");
        printf("Elige una opci√≥n: ");
        scanf("%d", &opcion);
        getchar(); // Limpia el buffer de entrada


        switch(opcion)
        {
        case 1:
            printf("Ingresa el DNI del cliente: ");
            fgets(dni, 10, stdin);
            dni[strcspn(dni, "\n")] = 0; // Elimina el salto de l√≠nea
            p = buscaClientePorDNIPuntero(AR_CLIENTES, dni);
            if (p != NULL)   // Si se encontr√≥ el cliente
            {
                muestraUnCliente(*p); // Muestra los datos del cliente
                free(p); // No olvidarse de liberar la memoria cuando ya no la necesite
            }
            else
            {
                printf("No se encontro un cliente con el DNI %s\n", dni);
            }
            break;
        case 2:
            modificaCampoClientePorDNI(AR_CLIENTES, dni);
            break;
        case 3:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opci√≥n no v√°lida.\n");
            break;
        }
    }
    while(opcion != 3);
}*/
void menu()
{
    int opcion;
    char dni[10];
    stCliente* p = NULL;

    printf("\nIngresa el DNI del cliente: ");
    fgets(dni, 10, stdin);
    dni[strcspn(dni, "\n")] = 0; // Elimina el salto de lÌnea
    p = buscaClientePorDNIPuntero(AR_CLIENTES, dni);

    if (p != NULL)   // Si se encontrÛ el cliente
    {
        muestraUnCliente(*p); // Muestra los datos del cliente

        do
        {
            printf("\n================== Menu ==================\n");
            printf("1. Modificar datos del cliente\n");
            printf("2. Agregar una cuenta al cliente\n");
            printf("3. Buscar cuentas del cliente\n");
            printf("4. Salir\n");
            printf("==========================================\n");
            printf("Elige una opciÛn: ");
            scanf("%d", &opcion);
            getchar(); // Limpia el buffer de entrada

            switch(opcion)
            {
            case 1:
                modificaCampoClientePorDNI(AR_CLIENTES, dni);
                break;
            case 2:
                agregarCuentaACliente(AR_CUENTAS, p->id);
                break;
            case 3:
                buscaCuentasDeCliente(AR_CUENTAS, *p);
                break;
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("OpciÛn no v·lida.\n");
                break;
            }
        }
        while(opcion != 4);

        free(p); // No olvidarse de liberar la memoria cuando ya no la necesite
    }
    else
    {
        //printf("No se encontro un cliente con el DNI %s. \n", dni);
        cargarNuevoCliente();
    }
}

stCliente modificaCampoClientePorDNI(char nombreArchivo[], char dni[])
{
    stCliente c;

    int encontrado = 0;
    FILE* archi = fopen(nombreArchivo, "r+b"); // Abre el archivo para lectura y escritura
    if(archi)
    {
        while(!encontrado && fread(&c, sizeof(stCliente), 1, archi)>0)
        {
            if(strcmp(c.dni, dni) == 0) // Si se encontr√≥ el cliente
            {

                encontrado = 1;
                printf("Datos del cliente antes de la modificaci√≥n:\n");
                muestraUnCliente(c);

                printf("øQuÈ campo quieres modificar?\n");

                printf("1. Nombre\n2. Apellido\n3. Email\n4. Telefono\n5. Calle\n6. Numero\n7. Localidad\n8. Provincia\n9. C.Postal\n");
                int opcion;
                scanf("%d", &opcion);
                getchar(); // Limpia el buffer de entrada

                switch(opcion)
                {
                case 1:
                    printf("Ingresa el nuevo nombre: ");
                    fgets(c.nombre, sizeof(c.nombre), stdin);
                    c.nombre[strcspn(c.nombre, "\n")] = 0; // Elimina el salto de l√≠nea
                    break;
                case 2:
                    printf("Ingresa el nuevo apellido: ");
                    fgets(c.apellido, sizeof(c.apellido), stdin);

                    c.apellido[strcspn(c.apellido, "\n")] = 0;

                    break;
                case 3:
                    printf("Ingresa el nuevo email: ");
                    fgets(c.email, sizeof(c.email), stdin);

                    c.email[strcspn(c.email, "\n")] = 0;

                    break;
                case 4:
                    printf("Ingresa el nuevo telefono: ");
                    fgets(c.telefono, sizeof(c.telefono), stdin);

                    c.telefono[strcspn(c.telefono, "\n")] = 0;
                case 5:
                    printf("Ingresa una nueva Calle: ");
                    fgets(c.domicilio.calle, sizeof(c.domicilio.calle), stdin);
                    c.domicilio.calle[strcspn(c.domicilio.calle, "\n")] = 0;
                    break;
                case 6:
                    printf("Ingresa una nuevo Numero: ");
                    fgets(c.domicilio.nro, sizeof(c.domicilio.nro), stdin);
                    c.domicilio.nro[strcspn(c.domicilio.nro, "\n")] = 0;
                    break;
                case 7:
                    printf("Ingresa una nuevo Localidad: ");
                    fgets(c.domicilio.localidad, sizeof(c.domicilio.localidad), stdin);
                    c.domicilio.localidad[strcspn(c.domicilio.localidad, "\n")] = 0;
                    break;
                case 8:
                    printf("Ingresa una nueva Provincia: ");
                    fgets(c.domicilio.provincia, sizeof(c.domicilio.provincia), stdin);
                    c.domicilio.provincia[strcspn(c.domicilio.provincia, "\n")] = 0;
                    break;
                case 9:
                    printf("Ingresa un nuevo C.Postal: ");
                    fgets(c.domicilio.cpos, sizeof(c.domicilio.cpos), stdin);
                    c.domicilio.cpos[strcspn(c.domicilio.cpos, "\n")] = 0;
                    break;
                default:
                    printf("Opcion no valida.\n");
                    break;
                }

                printf("Datos del cliente despues de la modificacion:\n");
                muestraUnCliente(c);

                // Mueve el puntero del archivo a la posici√≥n del cliente encontrado
                fseek(archi, -sizeof(stCliente), SEEK_CUR);

                // Escribe los nuevos datos del cliente en el archivo
                fwrite(&c, sizeof(stCliente), 1, archi);
            }
        }
        fclose(archi);
    }

    return c;
}
void muestraClienteYCuentas(char nombreArchivoClientes[], char nombreArchivoCuentas[], int idCliente)
{
    stCliente cliente;
    stCuenta cuenta;
    FILE* archiClientes = fopen(nombreArchivoClientes, "rb");
    FILE* archiCuentas = fopen(nombreArchivoCuentas, "rb");

    if(archiClientes && archiCuentas)
    {
        // Buscar al cliente en el archivo de clientes
        while(fread(&cliente, sizeof(stCliente), 1, archiClientes)>0)
        {
            if(cliente.id == idCliente) // Si se encontrÛ el cliente
            {
                muestraUnCliente(cliente); // Muestra los datos del cliente

                // Buscar las cuentas del cliente en el archivo de cuentas
                while(fread(&cuenta, sizeof(stCuenta), 1, archiCuentas)>0)
                {
                    if(cuenta.idCliente == idCliente) // Si la cuenta pertenece al cliente
                    {
                        muestraUnaCuenta(cuenta); // Muestra los datos de la cuenta
                    }
                }
                break;
            }
        }
        fclose(archiClientes);
        fclose(archiCuentas);
    }
    else
    {
        printf("Error al abrir los archivos.\n");
    }
}

void checkPassword(char valid_password[3][10])
{
    char login[10];
    int i;

    printf("\n\tIngrese su contraseÒa para ingresar al sistema: ");
    fgets(login, 10, stdin);
    login[strcspn(login, "\n")] = 0;
    // Verifica si el DNI ingresado es v·lido
    for (i = 0; i < 3; i++)
    {
        if (strcmp(login, valid_password[i]) == 0)
        {
            menu();  // Si el DNI es v·lido, llama a la funciÛn menu
            return;
        }
    }
    printf("Acceso Denegado.\n");
}

void cargarNuevoCliente()
{
    char opcion;
    printf("\nCliente no encontrado. øDeseas cargar un nuevo cliente? (s/n): \n");
    scanf(" %c", &opcion);
    if (opcion == 's' || opcion == 'S')
    {
        cargaUnArchivoUsuario(AR_CLIENTES);
    }
    else if (opcion == 'n' || opcion == 'N')
    {
        printf("Saliendo del programa...\n");
    }
    else
    {
        printf("OpciÛn no valida.\n");
    }
    menu();//preguntar si se puede poner ahi
}
