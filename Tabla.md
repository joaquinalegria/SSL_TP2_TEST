# Tabla de Transición

| Estado| Letra | Dígito | Punto | + | - | * | / | ^ | = | Espacio | \n | FDT | Otro |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **0** | 1 | 2 | 3 | 5 | 6 | 7 | 8 | 110 | 111 | 0 | 113 | 112 | 200 |
| **1** | 1 | 1 | 100 | 100 | 100 | 100 | 100 | 100 | 100 | 100 | 100 | 100 | 100 |
| **2** | 101 | 2 | 4 | 101 | 101 | 101 | 101 | 101 | 101 | 101 | 101 | 101 | 101 |
| **3** | 200 | 4 | 200 | 200 | 200 | 200 | 200 | 200 | 200 | 200 | 200 | 200 | 200 |
| **4** | 101 | 4 | 200 | 101 | 101 | 101 | 101 | 101 | 101 | 101 | 101 | 101 | 101 |
| **5** | 102 | 102 | 102 | 102 | 102 | 102 | 102 | 102 | 103 | 102 | 102 | 102 | 102 |
| **6** | 104 | 104 | 104 | 104 | 104 | 104 | 104 | 104 | 105 | 104 | 104 | 104 | 104 |
| **7** | 106 | 106 | 106 | 106 | 106 | 106 | 106 | 106 | 107 | 106 | 106 | 106 | 106 |
| **8** | 108 | 108 | 108 | 108 | 108 | 108 | 108 | 108 | 109 | 108 | 108 | 108 | 108 |

---

## Documentación de la Tabla

### Columnas (Clases de caracteres - Alfabeto)
*   **Letra:** Caracteres alfabéticos (`a-z`, `A-Z`)
*   **Dígito:** Números (`0-9`)
*   **Punto (.):** Carácter decimal
*   **`+`, `-`, `*`, `/`, `^`, `=`:** Operadores matemáticos y de asignación
*   **Espacio:** Tabuladores y espacios en blanco, funcionan como  separadores y se ignoran
*   **`\n`:** Salto de línea. Terminador de la expresión a evaluar.
*   **FDT:** Fin de Texto (EOF).
*   **Otro:** Cualquier carácter que no esté incluido en la gramática (Por ej.: @, #).

### Filas: Estados de Trabajo
Rango [0 - 99]. El autómata consume caracteres e incrementa el buffer.
*   **0:** Estado Inicial
*   **1:** Reconociendo identificador
*   **2:** Reconociendo parte entera de una constante
*   **3:** Reconociendo constante que inicia con punto y espera un dígito.
*   **4:** Reconociendo constante fraccionaria
*   **5:** Reconociendo operador `+` --> Espera a evaluar si el siguiente es `=`
*   **6:** Reconociendo operador `-` --> Espera a evaluar si el siguiente es `=`
*   **7:** Reconociendo operador `*` --> Espera a evaluar si el siguiente es `=`.
*   **8:** Reconociendo operador `/` --> Espera a evaluar si el siguiente es `=`.

### Estados Aceptores (Tokens reconocidos)
Rango [100 - 199]. El autómata interrumpe la lectura y clasifica el lexema.
*   **100 (TOKEN_ID):** Identificador reconocido. (Requiere centinela).
*   **101 (TOKEN_CTE):** Constante reconocida. (Requiere centinela).
*   **102 (TOKEN_SUMA):** Operador `+` reconocido. (Requiere centinela).
*   **103 (TOKEN_MAS_IGUAL):** Operador `+=` reconocido.
*   **104 (TOKEN_RESTA):** Operador `-` reconocido. (Requiere centinela).
*   **105 (TOKEN_MENOS_IGUAL):** Operador `-=` reconocido.
*   **106 (TOKEN_MULT):** Operador `*` reconocido. (Requiere centinela).
*   **107 (TOKEN_MULT_IGUAL):** Operador `*=` reconocido.
*   **108 (TOKEN_DIV):** Operador `/` reconocido. (Requiere centinela).
*   **109 (TOKEN_DIV_IGUAL):** Operador `/=` reconocido.
*   **110 (TOKEN_POTENCIA):** Operador `^` reconocido.
*   **111 (TOKEN_IGUAL):** Operador `=` reconocido.
*   **112 (TOKEN_FDT):** Fin de Texto reconocido.
*   **113 (TOKEN_NL):** Nueva línea reconocida. Indica el final de la expresión matemática.

### Estados de Error
Rango [200 - 299]. Detienen el ciclo y terminan el análisis del token actual.
*   **200 (ERR_LEXICO):** Error léxico. Agrupa fallos como caracteres inválidos (Otro) o puntos decimales aislados sin dígitos posteriores.