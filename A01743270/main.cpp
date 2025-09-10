// Archivo main de la SP 1 con las pruebas de cada uno de los algoritmos
// Jesus Eduardo Escobar Meza - A01743270
// Santiago Tamez Gomez - A01723018
// Bruno Rivera Juárez - A01571663
// Fecha: 7 de septiembre de 2025
#include <algorithm>
#include <fstream>
#include <vector>
#include <filesystem>
#include <sstream>
#include "BusquedaDeSubsecuencias.h"
#include "Palindromo.h"
#include "arbolHuffman.h"

/*
Verifica si un string (patron) es subsecuencia de otro (texto). 
Es decir, si puedes encontrar todos los caracteres del patrón en 
el texto en orden, pero no necesariamente consecutivos.
Complejidades:
Tiempo: O(n) donde n es el tamaño del texto.
Espacio: O(1) espacio adicional.
*/

bool esSubsecuencia(const std::string& transmission, const std::string& mcode) {
    size_t i = 0, j = 0;
    while (i < transmission.size() && j < mcode.size()) {
        if (transmission[i] == mcode[j]) j++;
        i++;
    }
    return j == mcode.size();
}

/*
Encuentra el palíndromo más largo dentro de un string. 
Usa expansión desde el centro para cada carácter y par de caracteres.
Complejidades:
Tiempo: O(n^2) donde n es el tamaño del string.
Espacio: O(1) espacio adicional.
*/

std::string palindromoMasLargo(const std::string& texto) {
    int n = texto.size();
    if (n == 0) return "";

    int start = 0, maxLength = 1;

    for (int i = 0; i < n; ++i) {
        // Palíndromo impar
        int left = i;
        int right = i;
        while (left >= 0 && right < n && texto[left] == texto[right]) {
            if (right - left + 1 > maxLength) {
                start = left;
                maxLength = right - left + 1;
            }
            left--;
            right++;
        }

        // Palíndromo par
        left = i; // reinicia en i
        right = i + 1; // empieza en i+1
        while (left >= 0 && right < n && texto[left] == texto[right]) {
            if (right - left + 1 > maxLength) {
                start = left;
                maxLength = right - left + 1;
            }
            left--;
            right++;
        }
    }

    return texto.substr(start, maxLength);
}

/*
Lee el contenido de los archivos transmission y mcode
y los devuelve como strings.
*/

std::string leerArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
        return "";
    }
    std::string contenido((std::istreambuf_iterator<char>(archivo)), std::istreambuf_iterator<char>());
    archivo.close();
    return contenido;
}

/*
Encuentra el substring común más largo entre dos strings.
Complejidades:
Tiempo: O(n * m) donde n y m son los tamaños de los strings.
Espacio: O(n * m) espacio adicional para la matriz dp.
*/

void substringComunMasLargo(const std::string& s1, const std::string& s2) {
    // Divide ambos strings en substrings usando espacios
    std::vector<std::string> subs1, subs2;
    std::vector<int> pos1; // Guarda la posición inicial de cada substring en s1

    // Para s1
    int idx = 0;
    std::istringstream iss1(s1);
    std::string token;
    while (iss1 >> token) {
        // Encuentra la posición en el string original
        size_t found = s1.find(token, idx);
        subs1.push_back(token);
        pos1.push_back((int)found);
        idx = (int)found + (int)token.size();
    }

    // Para s2
    std::istringstream iss2(s2);
    while (iss2 >> token) {
        subs2.push_back(token);
    }

    // Busca el substring común más largo
    int maxLen = 0, idx1 = -1;
    for (int i = 0; i < subs1.size(); ++i) {
        for (int j = 0; j < subs2.size(); ++j) {
            if (subs1[i] == subs2[j] && subs1[i].size() > maxLen) {
                maxLen = subs1[i].size();
                idx1 = i;
            }
        }
    }

    if (idx1 != -1) {
        int startPos = pos1[idx1];
        int endPos = startPos + maxLen - 1;
        std::cout << "\nParte 3: substring comun mas largo\n";
        std::cout << "Posicion inicial: " << startPos << "\n";
        std::cout << "Posicion final: " << endPos << "\n";
        std::cout << "Substring: " << subs1[idx1] << "\n";
    } else {
        std::cout << "\nParte 3: No hay substring comun\n";
    }
}

/*
Este conjunto de funciones implementa la codificación de Huffman.
Incluye la construcción del árbol de Huffman, la generación de códigos,
y la codificación de mensajes. Complejidades:
Tiempo: O(n log n) donde n es el número de caracteres únicos.
Espacio: O(n) espacio adicional para la tabla de códigos y el árbol.
*/

// Generar códigos a partir del árbol
void generarCodigos(Node* root, std::unordered_map<char, std::string>& codes, std::string curr) {
    if (!root) return;
    if (!root->left && !root->right) {
        codes[root->ch] = curr;
        return;
    }
    
    // Recorre el árbol
    generarCodigos(root->left, codes, curr + '0');
    generarCodigos(root->right, codes, curr + '1');
}

// Construir el árbol de Huffman y generar la tabla de códigos
std::unordered_map<char, std::string> construirHuffman(const std::string& s, double& Lprom, int& tamanoReal) {
    std::unordered_map<char,int> freq;
    for (char c : s) {
        // Contar frecuencias de cada caracter
        freq[c]++;
    }

    // Construir la cola de prioridad
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for (auto &p : freq) pq.push(new Node(p.first, p.second));

    while (pq.size() >= 2) {
        // Extraer los dos nodos con menor frecuencia
        Node* a = pq.top(); pq.pop();
        Node* b = pq.top(); pq.pop();
        Node* padre = new Node('\0', a->freq + b->freq);

        padre->left = a; 
        padre->right = b;

        pq.push(padre);
    }

    Node* root = pq.top();
    std::unordered_map<char,std::string> tabla;
    generarCodigos(root, tabla, "");

    Lprom = 0.0;
    tamanoReal = 0;
    int n = s.size();

    // Calcular longitud promedio y tamaño real
    for (auto &p : freq) {
        double prob = (double)p.second / n;
        Lprom += prob * tabla[p.first].size();
        tamanoReal += p.second * tabla[p.first].size();
    }

    return tabla;
}

// Calcular la longitud en bits de un mensaje codificado
int codificarLongitud(const std::string& msg, const std::unordered_map<char,std::string>& tabla) {
    int bits = 0;
    for (char c : msg) {
        if (tabla.count(c)) bits += tabla.at(c).size();
    }
    return bits;
}

void huffmanCoding(const std::vector<std::string>& transmissions, const std::vector<std::string>& mcodes) {    
    std::cout << "\nParte 4: Huffman\n";
    for (int i = 0; i < transmissions.size(); i++) {

        // Elimina espacios de la transmisión antes de construir Huffman
        std::string transmissionSinEspacios = transmissions[i];
        std::string mcodeSinEspacios = mcodes[i];
        
        transmissionSinEspacios.erase(
            std::remove(transmissionSinEspacios.begin(), transmissionSinEspacios.end(), ' '),
            transmissionSinEspacios.end()
        );

        mcodeSinEspacios.erase(
            std::remove(mcodeSinEspacios.begin(), mcodeSinEspacios.end(), ' '),
            mcodeSinEspacios.end()
        );

        double Lprom;
        int tamanoReal;
        auto tabla = construirHuffman(transmissionSinEspacios, Lprom, tamanoReal);

        std::cout << "Transmission " << i+1
             << " Lprom: " << Lprom
             << " bits, Tamano real: " << tamanoReal << " bits\n";

        for (int j = 0; j < mcodes.size(); j++) {
            int Lmsg = codificarLongitud(mcodes[j], tabla);
            double esperadoMsg = mcodes[j].size() * Lprom;
  
            // Un mensaje es sospechoso si su longitud codificada excede la longitud esperada
            bool sospechoso = (Lmsg > esperadoMsg);

            std::cout << "transmission" << i+1
                 << " mcode" << j+1 << " "
                 << (sospechoso ? "sospechoso " : "no-sospechoso ")
                 << Lmsg << "\n";
        }
    }
}

int main() {
    std::vector<std::string> transmissions = {
        leerArchivo("Cadenas/transmission1.txt"),
        leerArchivo("Cadenas/transmission2.txt")
    };

    std::vector<std::string> mcodes = {
        leerArchivo("Cadenas/mcode1.txt"),
        leerArchivo("Cadenas/mcode2.txt"),
        leerArchivo("Cadenas/mcode3.txt")
    };

    std::cout << "Parte 1: subsecuencias\n";
    for (int i = 0; i < transmissions.size(); ++i) {
        for (int j = 0; j < mcodes.size(); ++j) {
            bool resultado = esSubsecuencia(transmissions[i], mcodes[j]);
            std::cout << "transmission" << i+1 << " mcode" << j+1 << " " << (resultado ? "SI" : "NO") << "\n";
        }
    }

    // Parte 2: Palíndromo más largo en cada archivo (12 líneas)
    std::cout << "\nParte 2: palindromos\n";
    for (int i = 0; i < transmissions.size(); ++i) {
        std::string pal = palindromoMasLargo(transmissions[i]);
        std::cout << "Archivo " << i+1 << ": " << pal << "\n";
    }

    // Parte 3: Substring común más largo (Punto Inicial y Final de transmission1.txt)
    substringComunMasLargo(transmissions[0], transmissions[1]);


    // Parte 4: Codificación de Huffman
    huffmanCoding(transmissions, mcodes);
    return 0;
}