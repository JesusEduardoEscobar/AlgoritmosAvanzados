# 📡 Actividad Integradora 1 – Equipo 5

## 🧾 Descripción del Proyecto

Este programa en C++ analiza archivos de transmisión de datos para detectar patrones maliciosos, similitudes y optimizar el análisis mediante compresión Huffman. Se divide en cuatro partes principales que combinan algoritmos clásicos y estructuras eficientes.

---

## 🎯 Objetivos

- Detectar si fragmentos de código malicioso están presentes en transmisiones.
- Identificar el palíndromo más largo en cada transmisión.
- Comparar transmisiones para encontrar el substring común más largo.
- Aplicar compresión Huffman para evaluar eficiencia y detectar anomalías.

---

## 📁 Archivos de Entrada

El programa trabaja con los siguientes archivos, ubicados en la carpeta Cadenas que se encuentra en el mismo directorio que el ejecutable:

- `transmission1.txt`
- `transmission2.txt`
- `mcode1.txt`
- `mcode2.txt`
- `mcode3.txt`

📌 Los archivos contienen únicamente caracteres del 0 al 9, letras de la A a la F y saltos de línea.

---

## 🧠 Funcionalidades del Programa

### 🔍 Parte 1 – Búsqueda de Sub-secuencias

Verifica si el contenido de cada archivo `mcodeX.txt` aparece como subcadena en `transmission1.txt` y `transmission2.txt`.

**Salida esperada (por cada combinación):** true `<posicion>` or false

📍 `<posición>` indica el índice donde inicia la subcadena (basado en 0).

---

### 🔁 Parte 2 – Detección de Palíndromos

Encuentra el palíndromo más largo en cada archivo de transmisión.

**Salida esperada (una línea por archivo):**

📍 Las posiciones comienzan en 1.

---

### 🧬 Parte 3 – Substring Común Más Largo

Compara ambas transmisiones para encontrar el substring más largo que comparten.

**Salida esperada:**

📍 Posiciones referidas a `transmission1.txt`.

---

### 📉 Parte 4 – Compresión Huffman

Construye un árbol de Huffman para cada transmisión y analiza:

- Longitud promedio esperada de codificación.
- Tamaño comprimido real.
- Codificación de cada `mcodeX.txt` usando ambos árboles.
- Detección de anomalías si la codificación es excesivamente larga.

**Salida esperada (por cada combinación transmisión–mcode):**

📍 Transmission 1 Lprom: 3.38846 bits, Tamano real: 881 bits
📍 transmission1 mcode1 sospechoso 24
📍 transmission1 mcode1 no-sospechoso 24

---

## ⚙️ Requisitos Técnicos

- Lenguaje: C++
- Compilador: g++ o compatible
- Librerías recomendadas: `fstream`, `string`, `vector`, `unordered_map`, `queue`

---

## 🚀 Ejecución

1. Coloca los 5 archivos `.txt` en el mismo directorio que el ejecutable.
2. Compila el programa:
   ```bash
   g++ main.cpp -o main.exe
4. Ejecuta el programa: 
    ```bash
   .\main.exe
