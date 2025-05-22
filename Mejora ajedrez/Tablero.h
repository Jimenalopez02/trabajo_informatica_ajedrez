
#pragma once

#include <vector>
#include "Pieza.h"
#include "Jugador.h"
#include "Casilla.h"

class Tablero {
private:
    std::vector<std::vector<Pieza*>> casillas;

    Jugador* jugadorActivo;
    Jugador* jugadorRival;

public:
    Tablero(Jugador& j1,Jugador& j2);
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
    bool reyEnJaque(const Jugador& jugador);
    bool esPosicionValida(int fila, int columna) const;
    void cambiarTurno();
    const Jugador* getJugadorActivo() const { return jugadorActivo; }
};