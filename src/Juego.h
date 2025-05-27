#pragma once
#include "Tablero.h"
#include "Jugador.h"
#include "Casilla.h"
#include <vector>
#include <chrono>

struct Movimiento {
    int desdeFila, desdeColumna;
    int hastaFila, hastaColumna;
};

class Juego {
private:
    Jugador jugador1;
    Jugador jugador2;
    Tablero tablero;
    bool turnoBlancas;
    bool haySeleccion;
    Casilla casillaOrigen;
    std::vector<Casilla> movimientosValidos;

    // Temporizador
    std::chrono::time_point<std::chrono::steady_clock> tiempoInicioTurno;
    const int TIEMPO_MAXIMO_SEGUNDOS = 30;

    // Bot
    bool esBotTurno() const;
    void moverBot();
    std::vector<Movimiento> obtenerMovimientosBot();

public:
    Juego();
    void dibujar() const;
    void manejarClick(int x, int y);
    void redimensionar(int w, int h);

    // Temporizador
    void iniciarTurno();
    bool tiempoAgotado();
    void actualizar();
};
