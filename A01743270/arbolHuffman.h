#ifndef ARBOLHUFFMAN_H
#define ARBOLHUFFMAN_H

/*
Este conjunto de funciones implementa la codificación de Huffman.
Incluye la construcción del árbol de Huffman, la generación de códigos,
y la codificación de mensajes. Complejidades:
Tiempo: O(n log n) donde n es el número de caracteres únicos.
Espacio: O(n) espacio adicional para la tabla de códigos y el árbol.
*/

#include <iostream>
#include <queue>
#include <unordered_map>
#include <algorithm>

// Clase para representar un nodo en el árbol de Huffman
class Node {
public:
    char ch;     // Caracter
    int freq;    // Frecuencia
    Node *left, *right;
    Node(char c, int f) {
        ch = c;
        freq = f;
        left = nullptr;
        right = nullptr;
    }
};

// Comparador para la cola de prioridad
class Compare {
    public:
    // Nodo con menor frecuencia tiene mayor prioridad
        bool operator() (Node* a, Node* b) {
            return a->freq > b->freq;
        }
        void generarCodigos(Node* root, std::unordered_map<char, std::string>& codes, std::string curr);
        std::unordered_map<char, std::string> construirHuffman(const std::string& s, double& Lprom, int& tamanoReal);
        int codificarLongitud(const std::string& msg, const std::unordered_map<char,std::string>& tabla);


};



#endif // ARBOLHUFFMAN_H