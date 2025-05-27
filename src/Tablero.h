#pragma once
#include <vector>
#include "Pieza.h"
#include "Jugador.h"
#include "Casilla.h"
#include "Coordenada.h"

constexpr int FILAS_TABLERO = 8;
constexpr int COLUMNAS_TABLERO = 10;
constexpr int TAM_CASILLA = 100;
constexpr int MARGEN_X = 100;
constexpr int MARGEN_Y = 100;

class Tablero {
private:
    std::vector<std::vector<Pieza*>> casillas;
    Jugador &jugador1;
    Jugador &jugador2;

public:
    Coordenada coordenadaSobreTablero[FILAS_TABLERO * COLUMNAS_TABLERO];

    Tablero(Jugador& j1,Jugador& j2);
    ~Tablero();

    void CasillasaCoordenadas();
    void inicializaTablero();
    void dibujar() const;

    Pieza* getPieza(int fila, int columna)const;
    bool casillaOcupada(int fila, int columna) const;
    bool hayPiezaOponente(int fila, int columna, bool turnoBlancas) const;
    std::vector<Casilla> obtenerMovimientosPermitidos(int fila, int columna, bool turnoBlancas) const;

    void moverPieza(const Casilla& origen, const Casilla& destino);
    bool estaEnJaque(const Jugador& jugador, const Jugador& oponente);
    bool esMovimientoLegal(const Casilla& origen, const Casilla& destino, Jugador& jugador, Jugador& oponente);
    void eliminarPiezaDeJugador(Pieza* pieza);
};
