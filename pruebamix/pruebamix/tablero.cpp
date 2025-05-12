#include "Tablero.h"
#include <iostream>
#include "Peon.h" // Incluirás las demás piezas igual

Tablero::Tablero() {
    for (int f = 0; f < 8; f++)
        for (int c = 0; c < 10; c++)
            casillas[f][c] = nullptr;
}

Tablero::~Tablero() {
    for (int f = 0; f < 8; f++)
        for (int c = 0; c < 10; c++)
            delete casillas[f][c];
}


void Tablero::inicializar() {
    // Limpiar el tablero
    for (int f = 0; f < 8; f++)
        for (int c = 0; c < 10; c++)
            delete casillas[f][c], casillas[f][c] = nullptr;

    // Colocar peones blancos en fila 2 (índice 1)
    for (int c = 0; c < 10; c++) {
        casillas[1][c] = new Peon(Color::Blancas, 1, c);  // fila 2
    }

    // Colocar peones negros en fila 7 (índice 6)
    for (int c = 0; c < 10; c++) {
        casillas[6][c] = new Peon(Color::Negras, 6, c);  // fila 7
    }

    // (Opcional) Más adelante añadirás otras piezas aquí
}


void Tablero::mostrar() const {

    for (int f = 7; f >= 0; f--) {
        std::cout << f + 1 << " ";
        for (int c = 0; c < 10; c++) {
            if (casillas[f][c])
                std::cout << casillas[f][c]->getSimbolo() << " ";
            else
                std::cout << ". ";
        }
        std::cout << std::endl;
    }
    std::cout << "  a b c d e f g h i j\n";
}

Pieza* Tablero::getPieza(int fila, int columna) const {
    if (fila < 0 || fila >= 8 || columna < 0 || columna >= 10)
        return nullptr;
    return casillas[fila][columna];
}

void Tablero::moverPieza(int fo, int co, int fd, int cd) {
    delete casillas[fd][cd]; // por si hay una captura
    casillas[fd][cd] = casillas[fo][co];
    casillas[fo][co] = nullptr;
    casillas[fd][cd]->setPosicion(fd, cd); // esto es fundamental
}


