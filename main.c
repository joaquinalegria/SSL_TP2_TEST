#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

int main() {
    Token token_actual;

    printf("Iniciando escaner. Ingrese expresiones (Ctrl+Z en Windows para FDT/EOF):\n");

    // El ciclo termina al reconocer el token FDT
    do {
        // Se llama al escáner pasando el flujo estándar de entrada
        token_actual = (Token)escanear(stdin);

        // Se evalúa el token retornado y se imprime según las reglas de la consigna
        switch (token_actual) {
            case TOKEN_ID:
                printf("Token: Identificador\t| Lexema: %s\n", obtener_lexema());
                break;
            case TOKEN_CTE:
                printf("Token: Constante\t| Lexema: %s\n", obtener_lexema());
                break;
            case TOKEN_SUMA:
                printf("Token: Suma\n");
                break;
            case TOKEN_MAS_IGUAL:
                printf("Token: Asignacion += \n");
                break;
            case TOKEN_RESTA:
                printf("Token: Resta\n");
                break;
            case TOKEN_MENOS_IGUAL:
                printf("Token: Asignacion -= \n");
                break;
            case TOKEN_MULT:
                printf("Token: Multiplicacion\n");
                break;
            case TOKEN_MULT_IGUAL:
                printf("Token: Asignacion *= \n");
                break;
            case TOKEN_DIV:
                printf("Token: Division\n");
                break;
            case TOKEN_DIV_IGUAL:
                printf("Token: Asignacion /= \n");
                break;
            case TOKEN_POTENCIA:
                printf("Token: Potencia\n");
                break;
            case TOKEN_IGUAL:
                printf("Token: Asignacion =\n");
                break;
            case TOKEN_ERROR_LEXICO:
                printf("Error lexico\t\t| Lexema: %s\n", obtener_lexema());
                break;
            case TOKEN_FDT:
                printf("Token: Fin de Texto (FDT) reconocido. Terminando...\n");
                break;
            default:
                printf("Estado desconocido (%d)\n", token_actual);
                break;
        }
    } while (token_actual != TOKEN_FDT);

    return EXIT_SUCCESS;
}