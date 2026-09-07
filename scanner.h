#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>

// Enumerado que mapea los tokens a los estados aceptores y de error de la Tabla de Transición.
typedef enum {
    TOKEN_ID = 100,
    TOKEN_CTE = 101,
    TOKEN_SUMA = 102,
    TOKEN_MAS_IGUAL = 103,
    TOKEN_RESTA = 104,
    TOKEN_MENOS_IGUAL = 105,
    TOKEN_MULT = 106,
    TOKEN_MULT_IGUAL = 107,
    TOKEN_DIV = 108,
    TOKEN_DIV_IGUAL = 109,
    TOKEN_POTENCIA = 110,
    TOKEN_IGUAL = 111,
    TOKEN_FDT = 112,
    TOKEN_ERROR_LEXICO = 200
} Token;

// No agrego errores pq ya estan en la TT, donde se agrupan todos los errores en el estado 200

// Declaración de la función principal del escáner.
// Recibe un flujo de archivo (que puede ser stdin) y retorna el Token reconocido.
int escanear(FILE *archivo);

// Declaración del getter para acceder al lexema almacenado en el buffer estático.
const char* obtener_lexema(void);

#endif // SCANNER_H
