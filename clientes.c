#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "clientes.h"
#include "domicilios.h"
#include "cuentas.h"
#include "movimientos.h"
#include "mocks_Domicilios_Clientes.h"

#define AR_CLIENTES "clientes.bin"
#define AR_CUENTAS "cuentas.bin"
#define AR_MOVIMIENTOS "movimientos.bin"


stCliente cargaUnCliente ()
{
    stCliente c;

    static int id=0;
    id++;
    printf("INGRESO DE DATOS PERSONALES DEL CLIENTE\n");

    c.nroCliente = getNroCliente();

    printf ("NOMBRE.......................: ");
    fgets(c.nombre, sizeof(c.nombre), stdin);
    c.nombre[strcspn(c.nombre, "\n")] = 0;

    printf ("APELLIDO.....................: ");
    fgets(c.apellido, sizeof(c.apellido), stdin);
    c.apellido[strcspn(c.apellido, "\n")] = 0;

    printf ("DNI..........................: ");
    fgets(c.dni, sizeof(c.dni), stdin);
    c.dni[strcspn(c.dni, "\n")] = 0;

    printf ("E-MAIL.......................: ");
    fgets(c.email, sizeof(c.email), stdin);
    c.email[strcspn(c.email, "\n")] = 0;

    printf ("TELEFONO.....................: ");
    fgets(c.telefono, sizeof(c.telefono), stdin);
    c.telefono[strcspn(c.telefono, "\n")] = 0;

    c.domicilio = cargaUnDomicilio();

    c.eliminado = 0;


    return c;
}

void muestraUnCliente (stCliente c)
{
    printf ("\n=====================================================");
    printf ("\n\t::::::::NRO ID:::::::: %d", c.id);
    printf ("\n=====================================================");
    printf ("\nCLIENTE DEL BANCO NRO...........: %d", c.nroCliente);
    printf ("\n=====================================================");
    printf ("\nNOMBRE..........................: %s", c.nombre);
    printf ("\nAPELLIDO........................: %s", c.apellido);
    printf ("\nDNI.............................: %s", c.dni);
    printf ("\nE-MAIL..........................: %s", c.email);
    printf ("\nTELEFONO........................: %s", c.telefono);
    muestraUnDomicilio(c.domicilio);
    printf("\nESTADO DEL CLIENTE...............: %d", c.eliminado);
    printf ("\n=====================================================\n");
}

int ultimoId(char nombreArchivo[])
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
            // Elimina el salto de linea al final del DNI, si existe
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

    return flag;
}

void cargaUnArchivoUsuario(char nombreArchivo[])
{
    stCliente c;
    char opcion;
    int static id;// - Declara una variable estática id. Las variables estáticas mantienen su valor entre las llamadas a la función.
    id = ultimoId(AR_CLIENTES);
    FILE* archi = fopen(nombreArchivo, "a+b");
    if(archi)
    {
        do
        {
            system("cls");
            c = cargaUnCliente();
            int clienteEncontrado = buscaDatoEnArchivoStr(nombreArchivo, c.dni);
            int nroCuentaEncontrado = buscaNroClienteEnArchivoFlag(archi,c.nroCliente);
            if(clienteEncontrado == 1 || nroCuentaEncontrado == 1) // Si se encontro el cliente
            {
                printf("ERROR - CLIENTE YA REGISTRADO");
            }
            else
            {
                id++;
                c.id = id;
                fwrite(&c, sizeof(stCliente), 1, archi);
            }

            printf("\nESC PARA SALIR CUALQUIER OTRA TECLA PARA CONTINUAR CARGANDO......");

            opcion = getch();
        }
        while(opcion != 27);

        fclose(archi);
    }
}

void cargaArchClienteRandom(char nombreArchCliente[], int cant)
{
    FILE* archi = fopen(nombreArchCliente, "a+b");
    stCliente c;
    int static id;
    id = ultimoId(AR_CLIENTES);
    if(archi)
    {
        for (int i = 0; i < cant; i++)
        {
            c = getClienteRandom();
            int clienteEncontrado = buscaDatoEnArchivoStr(nombreArchCliente, c.dni);
            int nroCuentaEncontrado = buscaNroClienteEnArchivoFlag(archi,c.nroCliente);
            if(clienteEncontrado == 1 || nroCuentaEncontrado == 1) // Si se encontro el cliente
            {
                printf("ERROR - CLIENTE YA REGISTRADO");
            }
            else
            {
                id++;
                c.id = id;
                fwrite(&c, sizeof(stCliente), 1, archi);
            }
        }

    }
    fclose(archi);
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

int buscaNroClienteEnArchivoFlag(FILE* archi, int dato)
{
    stCliente c;
    int flag = 0;
    rewind(archi);
    if(archi)
    {
        while(flag == 0 && fread(&c, sizeof(stCliente), 1, archi)>0)
        {
            if(c.nroCliente == dato)
            {
                flag = 1;
            }
        }
        //fclose(archi);
    }
    return flag;
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
            if(strcmp(c.dni, dni) == 0) // Si se encontro el cliente
            {
                p = malloc(sizeof(stCliente));
                *p = c;
            }
        }
        fclose(archi);
    }

    return p;  // Retorna un puntero al cliente encontrado o NULL si no se encontro
}

void buscaClientes(char archClientes[], char archCuentas[], char archMovimientos[])
{
    int opcion;
    char dni[10];
    stCliente* p = NULL;

    stCuenta cuenta;

    printf("\nINGRESA EL DNI DEL CLIENTE: ");/// Solicitamos que el usuario ingrese el dni del cliente para podee ingresar al menu de opciones
    fgets(dni, 10, stdin);
    dni[strcspn(dni, "\n")] = 0; // Elimina el salto de línea
    p = buscaClientePorDNIPuntero(archClientes, dni);

    if (p != NULL)   // Verifica si se encontró un cliente. Si p es NULL, significa que no se encontró ningún cliente con el DNI dado.
    {
        muestraUnCliente(*p); // Muestra los datos del cliente

        do
        {
            printf("\n================== MENU ==================\n");
            printf("1. MODIFICAR DATOS DEL CLIENTE\n");
            printf("2. AGREGAR UNA CUENTA AL CLIENTE\n");
            printf("3. BUSCAR CUENTAS DEL CLIENTE\n");
            printf("4. OPERACIONES DE CUENTAS\n");
            printf("5. BAJA O ALTA CLIENTE\n");
            printf("6. BAJA O ALTA CUENTAS\n");
            printf("7. BAJA O ALTA MOVIMIENTOS\n");
            printf("8. SALIR\n");
            printf("============================================\n");
            printf("ELIGE UNA OPCION:");
            scanf("%d", &opcion);
            getchar(); // Limpia el buffer de entrada

            switch(opcion)
            {
            case 1:
                modificaCampoClientePorDNI(archClientes, dni);
                break;
            case 2:
                //agregarCuentaACliente(AR_CUENTAS, p->id);
                cargaCuentasEnArchivo(AR_CUENTAS, p->id);
                break;
            case 3:

                buscaCuentasDeCliente(archCuentas, *p);

                break;

            case 4:

                buscaCuentasDeCliente(archCuentas, *p);
                menuOperacionesCuenta(AR_CUENTAS, AR_MOVIMIENTOS);

                break;

            case 5:

                bajaAltaCliente(AR_CLIENTES,AR_CUENTAS, dni);

                break;

            case 6:

                printf("1.BAJA\n2.ALTA\n3.SALIR");
                int opcion;
                scanf("%d", &opcion);// Elegimos una opción que queremos modificar
                getchar(); // Limpia el buffer de entrada

                switch(opcion)
                {
                case 1:

                    buscaCuentasDeCliente(archCuentas, *p);
                    cuenta = seleccionaCuentaDeCliente(AR_CUENTAS);
                    bajaSoloCuenta(archCuentas, cuenta);
                    bajaMovimiento(archMovimientos,cuenta);
                    buscaCuentasDeCliente(archCuentas, *p);
                    buscaYmuestraMovimientosDeUnaCuenta(archMovimientos,cuenta);


                    break;
                case 2:
                    buscaCuentasDeCliente(archCuentas, *p);
                    cuenta = seleccionaCuentaDeCliente(AR_CUENTAS);
                    altaSoloCuenta(archCuentas,cuenta);
                    altaMovimiento(archMovimientos,cuenta);
                    buscaCuentasDeCliente(archCuentas, *p);
                    buscaYmuestraMovimientosDeUnaCuenta(archMovimientos,cuenta);

                    break;

                case 3:

                    printf("SALIENDO DEL PROGRAMA...\n");

                break;

                default:
                    printf("OPCION NO VALIDA.\n");
                    break;
                }

                break;

            case 7:

                break;
            case 8:

                printf("SALIENDO DEL PROGRAMA...\n");

                break;

            default:
                printf("OPCION NO VALIDA.\n");
                break;
            }
        }
        while(opcion != 8);//repite el menu hasta que el usuario quiera salir

        free(p); // No olvidarse de liberar la memoria cuando ya no la necesite
    }
    else
    {
        printf("NO SE ENCONTRO UN CLIENTE CON EL DNI %s.\n", dni);
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
            if(strcmp(c.dni, dni) == 0) // Si se encontro el cliente
            {

                encontrado = 1;
                printf("DATOS DEL CLIENTE ANTES DE MODIFICAR:\n");
                muestraUnCliente(c);//Mostramos al cliente para comparar

                printf("¿QUE CAMPO QUIERES MODIFICAR?\n");

                printf("1. NOMBRE\n2. APELLIDO\n3. EMAIL\n4. TELEFONO\n5. CALLE\n6. NUMERO\n7. LOCALIDAD\n8. PROVINCIA\n9. C.POSTAL\n");
                int opcion;
                scanf("%d", &opcion);// Elegimos una opción que queremos modificar
                getchar(); // Limpia el buffer de entrada

                switch(opcion)
                {
                case 1:
                    printf("INGRESA EL NUEVO NOMBRE: ");
                    fgets(c.nombre, sizeof(c.nombre), stdin);
                    c.nombre[strcspn(c.nombre, "\n")] = 0; // Elimina el salto de linea
                    break;
                case 2:
                    printf("INGRESA EL NUEVO APELLIDO: ");
                    fgets(c.apellido, sizeof(c.apellido), stdin);

                    c.apellido[strcspn(c.apellido, "\n")] = 0;

                    break;
                case 3:
                    printf("INGRESA EL NUEVO EMAIL: ");
                    fgets(c.email, sizeof(c.email), stdin);
                    c.email[strcspn(c.email, "\n")] = 0;
                    break;
                case 4:
                    printf("INGRESA EL NUEVO TELEFONO: ");
                    fgets(c.telefono, sizeof(c.telefono), stdin);
                    c.telefono[strcspn(c.telefono, "\n")] = 0;
                case 5:
                    printf("INGRESA UNA NUEVA CALLE: ");
                    fgets(c.domicilio.calle, sizeof(c.domicilio.calle), stdin);
                    c.domicilio.calle[strcspn(c.domicilio.calle, "\n")] = 0;
                    break;
                case 6:
                    printf("INGRESA UNA NUEVO NUMERO: ");
                    fgets(c.domicilio.nro, sizeof(c.domicilio.nro), stdin);
                    c.domicilio.nro[strcspn(c.domicilio.nro, "\n")] = 0;
                    break;
                case 7:
                    printf("INGRESA UNA NUEVO LOCALIDAD: ");
                    fgets(c.domicilio.localidad, sizeof(c.domicilio.localidad), stdin);
                    c.domicilio.localidad[strcspn(c.domicilio.localidad, "\n")] = 0;
                    break;
                case 8:
                    printf("INGRESA UNA NUEVA PROVINCIA: ");
                    fgets(c.domicilio.provincia, sizeof(c.domicilio.provincia), stdin);
                    c.domicilio.provincia[strcspn(c.domicilio.provincia, "\n")] = 0;
                    break;
                case 9:
                    printf("INGRESA UN NUEVO C.POSTAL: ");
                    fgets(c.domicilio.cpos, sizeof(c.domicilio.cpos), stdin);
                    c.domicilio.cpos[strcspn(c.domicilio.cpos, "\n")] = 0;
                    break;
                default:
                    printf("OPCION NO VALIDA.\n");
                    break;
                }

                printf("DATOS DEL CLIENTE DESPUES DE LA MODIFICACION: \n");
                muestraUnCliente(c);

                // Mueve el puntero del archivo a la posicion del cliente encontrado
                fseek(archi, -sizeof(stCliente), SEEK_CUR);

                // Escribe los nuevos datos del cliente en el archivo
                fwrite(&c, sizeof(stCliente), 1, archi);
            }
        }
        fclose(archi);
    }

    return c;
}

void checkPassword(char valid_password[3][10])
{
    char login[10];
    int i;
    int encontrado = 0;
    int intentos = 0;

    printf("\n\t\t\t\t\t::::::::::::::::::::::::::::::::::::::::::::");
    printf("\n\t\t\t\t\t\tWELCOME TO THE CRAZYBANK");
    printf("\n\t\t\t\t\t::::::::::::::::::::::::::::::::::::::::::::\n");

    while (!encontrado && intentos < 3)
    {
        printf("\n\t\tPASSWORD: ");
        fgets(login, 10, stdin);
        login[strcspn(login, "\n")] = 0; // Elimina el salto de línea

        // Verifica si la contraseña ingresada es válida
        for (i = 0; i < 3; i++)
        {
            if (strcmp(login, valid_password[i]) == 0)
            {
                encontrado = 1;
                menu();  // Si la contraseña es válida, llama a la función menu
            }
        }
        if (!encontrado)
        {
            printf("ACCESS DENIED\n");
            system("cls");
            intentos++;
        }
    }

    if (intentos == 3)
    {
        printf("YOU HAVE REACHED THE LIMIT OF ATTEMPTS. PLEASE, TRY AGAIN LATER.\n");
    }
}

void cargarClienteYCuenta(char nombreArchivoClientes[], char nombreArchivoCuentas[])
{
    char opcion;
    stCliente cliente;

    // Llama a la función para cargar un nuevo cliente en el archivo
    cargaUnArchivoUsuario(nombreArchivoClientes);

    // Obtiene el último cliente del archivo
    cliente = obtenerUltimoCliente(nombreArchivoClientes);

    printf("\nDESEA CARGAR UNA CUENTA? (S/N): ");
    scanf(" %c", &opcion);

    if(opcion == 's' || opcion == 'S')
    {
        // Llama a la función para cargar una nueva cuenta para el cliente en el archivo
        cargaCuentasEnArchivo(nombreArchivoCuentas, cliente.id);
    }
    else if(opcion == 'n' || opcion == 'N')
    {
        printf("SALIENDO DEL PROGRAMA..\n");
    }
    else
    {
        printf("OPCION NO VALIDA\n");
    }
}

void cargarClienteYCuentaYMovimientos(char nombreArchivoClientes[], char nombreArchivoCuentas[], char* nombreArchivoMovimientos)
{
    char opcion;
    stCliente cliente;
    stCuenta cuenta;

    // Llama a la función para cargar un nuevo cliente en el archivo
    cargaUnArchivoUsuario(nombreArchivoClientes);

    // Obtiene el último cliente del archivo
    cliente = obtenerUltimoCliente(nombreArchivoClientes);

    printf("\nDESEA CARGAR UNA CUENTA? (S/N): ");
    scanf(" %c", &opcion);

    if (opcion == 's' || opcion == 'S')
    {
        // Llama a la función para cargar una nueva cuenta para el cliente en el archivo

        cargaCuentasEnArchivo(nombreArchivoCuentas, cliente.id);
    }
    else if (opcion == 'n' || opcion == 'N')
    {
        printf("SALIENDO DEL PROGRAMA...\n");
    }
    else
    {
        printf("OPCIÓN NO VÁLIDA\n");
    }

    printf("\nDESEA HACER UN MOVIMIENTO EN LA CUENTA? (S/N): ");
    scanf(" %c", &opcion);

    if (opcion == 's' || opcion == 'S')
    {
        // Llama a la función para cargar un nuevo movimiento para la cuenta en el archivo
        buscaCuentasDeCliente(nombreArchivoCuentas,cliente);
        menuOperacionesCuenta(nombreArchivoCuentas, nombreArchivoMovimientos);
    }
    else if (opcion == 'n' || opcion == 'N')
    {
        printf("SALIENDO DEL PROGRAMA...\n");
    }
    else
    {
        printf("OPCIÓN NO VÁLIDA\n");
    }
}

stCliente obtenerUltimoCliente(char nombreArchivo[])
{
    stCliente cliente;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        fseek(archi, -sizeof(stCliente), SEEK_END);
        fread(&cliente, sizeof(stCliente), 1, archi);

        fclose(archi);
    }
    return cliente;
}

stCuenta obtenerUltimaCuenta(char nombreArchivo[])
{
    stCuenta cuentas;
    FILE* archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        fseek(archi, -sizeof(stCuenta), SEEK_END);
        fread(&cuentas, sizeof(stCuenta), 1, archi);

        fclose(archi);
    }
    return cuentas;
}

void archivo2arreglosActyElim(char nombreArchivo[],stCliente activo[], stCliente inactivo[],int *vActivos,int *vInactivos,int dim)
{
    FILE*archi=fopen(nombreArchivo,"rb");
    stCliente c;
    int vali = 0;
    int vala = 0;
    if (archi)
    {
        while (vali<dim && vala<dim &&(fread(&c,sizeof(stCliente),1,archi)>0))
        {
            if (c.eliminado == 1)
            {
                inactivo[vali]= c;
                vali++;
            }
            else
            {
                activo[vala]=c;
                vala++;
            }
        }
        fclose (archi);
    }

    *vInactivos = vali;
    *vActivos = vala;
}

void muestraClientes(stCliente c[], int v)
{
    for(int i=0; i<v; i++)
    {
        muestraUnCliente(c[i]);
    }
}
