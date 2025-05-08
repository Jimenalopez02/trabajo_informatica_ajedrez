
#pragma once

#include <vector>
#include "Pieza.h"
#include "Jugador.h"
#include "Casilla.h"

class Tablero {
private:
    std::vector<std::vector<Pieza*>> casillas;

    Jugador jugador1;
    Jugador jugador2;

public:
    Tablero(const Jugador& j1, const Jugador& j2);
    ~Tablero();

    void inicializaTablero();
    void mostrarTablero() const;
    void mostrarMovimientos(int fila, int columna) const;
    std::vector<Casilla> obtenerMovimientosPermitidos(int fila, int columna, bool turnoBlancas) const;
    Pieza* getPieza(int fila, int columna);
    //bool casillaOcupada(int fila, int columna) const;
    bool casillaOcupada(int fila, int columna) const;
    bool hayPiezaOponente(int fila, int columna, bool turnoBlancas) const;
    void moverPieza(const Casilla& origen, const Casilla& destino);
    bool reyEnJaque(const Jugador& );
};