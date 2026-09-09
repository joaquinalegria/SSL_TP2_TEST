#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "scanner.h"

// Buffer estático para informar el lexema exigido por la consigna.
static char buffer_lexema[256];

// Tabla de transición optimizada por clases de caracteres.
// Filas: Estados (0 al 8)
// Columnas: Letra(0), Dígito(1), Punto(2), +(3), -(4), *(5), /(6), ^(7), =(8), Espacio(9), FDT(10), Otro(11)
static const int tabla_transicion[9][13] = {
    {  1,   2,   3,  5,  6,  7,  8, 110, 111,  0, 113, 112, 200}, // Estado 0
    {  1,   1, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100}, // Estado 1 (ID)
    {101,   2,   4, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101}, // Estado 2 (Int)
    {200,   4, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200}, // Estado 3 (Punto)
    {101,   4, 200, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101}, // Estado 4 (Float)
    {102, 102, 102, 102, 102, 102, 102, 102, 103, 102, 102, 102, 102}, // Estado 5 (+)
    {104, 104, 104, 104, 104, 104, 104, 104, 105, 104, 104, 104, 104}, // Estado 6 (-)
    {106, 106, 106, 106, 106, 106, 106, 106, 107, 106, 106, 106, 106}, // Estado 7 (*)
    {108, 108, 108, 108, 108, 108, 108, 108, 109, 108, 108, 108, 108}  // Estado 8 (/)
};

// No entiendo que es lo de buffer_lexema
// Todavia no llego a entender como y para que sirve la tabla de transicion, osea que significan todos los numeros adentro, y como se utilizaria?

// Retorna el índice de la columna para la tabla de transición
static int obtener_columna(int c) {
    if (isalpha(c)) return 0;
    if (isdigit(c)) return 1;
    if (c == '.') return 2;
    if (c == '+') return 3;
    if (c == '-') return 4;
    if (c == '*') return 5;
    if (c == '/') return 6;
    if (c == '^') return 7;
    if (c == '=') return 8;
    if (c == ' ' || c == '\t' || c == '\r') return 9; 
    if (c == '\n') return 10;                         
    if (c == EOF) return 11;                          
    return 12;                                        
}

// Determina si el estado aceptor requiere devolver el carácter espurio al flujo
static bool requiere_centinela(int estado) {
    // 100: ID, 101: Constante, 102: +, 104: -, 106: *, 108: /
    return (estado == 100 || estado == 101 || estado == 102 || 
            estado == 104 || estado == 106 || estado == 108);
}

// Función principal que retorna el estado final reconocido (mapeable a un Token)
int escanear(FILE *archivo) {
    int estado = 0; // INICIAL
    int indice_lexema = 0;
    int c;

    // Los estados menores a 100 son de trabajo. Aceptores (100+) o Error (200) cortan el ciclo.
    while (estado < 100) {
        c = fgetc(archivo);
        int columna = obtener_columna(c);
        int estado_siguiente = tabla_transicion[estado][columna];

        if (estado_siguiente >= 100) {
            // Llegamos a un estado de parada (Aceptor o Error).
            if (requiere_centinela(estado_siguiente)) {
                ungetc(c, archivo); // El centinela no es parte del lexema, vuelve al flujo.
            } else {
                // Si no requiere centinela (ej. el '=' en '+=' o un EOF), forma parte del token.
                if (c != EOF && estado_siguiente != 112) {
                    buffer_lexema[indice_lexema++] = (char)c;
                }
            }
            estado = estado_siguiente;
            break; 
        } else {
            // Es un estado de trabajo. 
            // Excepción: Los espacios leídos en el estado inicial se ignoran y no van al buffer.
            if (!(estado == 0 && columna == 9)) {
                buffer_lexema[indice_lexema++] = (char)c;
            }
            estado = estado_siguiente;
        }
    }
    
    // Finalizar la cadena de texto del lexema en C
    buffer_lexema[indice_lexema] = '\0';
    
    return estado; 
}

// Getter para exponer el buffer al main.c
const char* obtener_lexema() {
    return buffer_lexema;
}