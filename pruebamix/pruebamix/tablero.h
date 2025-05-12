#pragma once
#include "Pieza.h"

class Tablero {
private:
    Pieza* casillas[8][10];  // Aquí va declarada la matriz del tablero

public:
    Tablero();
    ~Tablero();

    void inicializar();  // Colocar piezas en sus posiciones iniciales
    void mostrar() const;
    Pieza* getPieza(int fila, int columna) const;
    void moverPieza(int filaOrigen, int colOrigen, int filaDest, int colDest);

    // Getter para pasar el tablero a las piezas
    Pieza* const (*getCasillas() const)[10]{
    return casillas;
    }

};
