#pragma once
#include "Pieza.h"

class Peon : public Pieza {
public:
    Peon(Color color, int fila, int columna)
        : Pieza(color, fila, columna, TipoPieza::Peon) {}

    // Peon.h
    std::vector<Casilla> getMovimientosPermitidos(Pieza* const (*tablero)[10]) const override;


    char getSimbolo() const override {
        return color == Color::Blancas ? 'P' : 'p';
    }
};

