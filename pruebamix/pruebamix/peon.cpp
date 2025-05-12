#include "Peon.h"
std::vector<Casilla> Peon::getMovimientosPermitidos(Pieza* const (*tablero)[10]) const {
    std::vector<Casilla> movs;
    int direccion = (color == Color::Blancas) ? 1 : -1;
    int filaInicio = (color == Color::Blancas) ? 1 : 6;
    int f = posicion.fila + direccion;
    int c = posicion.columna;

    // Una casilla hacia adelante
    if (f >= 0 && f < 8 && tablero[f][c] == nullptr)
        movs.emplace_back(f, c);

    // Dos casillas si está en la fila inicial
    int f2 = posicion.fila + 2 * direccion;
    if (posicion.fila == filaInicio &&
        tablero[f][c] == nullptr && f2 >= 0 && f2 < 8 &&
        tablero[f2][c] == nullptr) {
        movs.emplace_back(f2, c);
    }

    // Captura izquierda
    if (c > 0 && f >= 0 && f < 8) {
        Pieza* izq = tablero[f][c - 1];
        if (izq && izq->getColor() != color)
            movs.emplace_back(f, c - 1);
    }

    // Captura derecha
    if (c < 9 && f >= 0 && f < 8) {
        Pieza* der = tablero[f][c + 1];
        if (der && der->getColor() != color)
            movs.emplace_back(f, c + 1);
    }

    return movs;
}


