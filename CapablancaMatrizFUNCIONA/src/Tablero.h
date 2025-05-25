#pragma once
#include <vector>
#include "Pieza.h"
#include "Jugador.h"
#include "Casilla.h"
#include "Coordenada.h"

// Tablero.h para sistema de coordenadas en píxeles (800x800)
constexpr int FILAS_TABLERO = 8;
constexpr int COLUMNAS_TABLERO = 10;
constexpr int TAM_CASILLA = 100;
constexpr int MARGEN_X = 100;
constexpr int MARGEN_Y = 100;

class Tablero {
private:
    std::vector<std::vector<Pieza*>> casillas;
    Jugador jugador1;
    Jugador jugador2;

public:
    Tablero(const Jugador& j1, const Jugador& j2);
    ~Tablero();

    Coordenada coordenadaSobreTablero[FILAS_TABLERO * COLUMNAS_TABLERO];
    void CasillasaCoordenadas();
    virtual void dibujar() const;
    void inicializaTablero();

    Pieza* getPieza(int fila, int columna);
    bool casillaOcupada(int fila, int columna) const;
    bool hayPiezaOponente(int fila, int columna, bool turnoBlancas) const;
    std::vector<Casilla> obtenerMovimientosPermitidos(int fila, int columna, bool turnoBlancas) const;

    void mostrarTablero() const;
    void mostrarMovimientos(int fila, int columna) const;
    void moverPieza(const Casilla& origen, const Casilla& destino);
    bool reyEnJaque(const Jugador& jugador);

    const Jugador& GetJugador1() const;
    const Jugador& GetJugador2() const;
    Jugador& GetJugador1();
    Jugador& GetJugador2();
    void SetJugador1(const Jugador& jugador);
    void SetJugador2(const Jugador& jugador);
};
