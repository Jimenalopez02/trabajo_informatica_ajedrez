#pragma once
#include "Tablero.h"
#include "Jugador.h"
#include "Casilla.h"
#include <vector>

class Juego {
private:
    Jugador jugador1;
    Jugador jugador2;
    Tablero tablero;
    bool turnoBlancas;
    bool haySeleccion;
    Casilla casillaOrigen;
    std::vector<Casilla> movimientosValidos;

public:
    Juego();
    void dibujar() const;
    void manejarClick(int x, int y);
    void redimensionar(int w, int h);
};