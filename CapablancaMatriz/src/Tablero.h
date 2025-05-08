#pragma once

/*#include <stdlib.h>
#include <algorithm> 
#include <vector>
#include <string>
#include "Pieza.h"
#include "Coordenada.h"
#include "Jugador.h"
#include "Casilla.h"

class Tablero {
private:
    std::vector<std::vector<Pieza*>> casillas;
    Coordenada coordenadaSobreTablero[64];

    Jugador jugador1;
    Jugador jugador2;

    Casilla casSeleccion;
    Casilla casOrigen;
    Casilla casDestino;

    Pieza* piezaSeleccionada = nullptr;
    Pieza* piezaOrigen = nullptr;
    Pieza* piezaDestino = nullptr;

    bool seleccionActiva = false;
    bool movimientoActivado = false;
    bool comer = false;
    bool enJaque = false;
    bool enJaqueMate = false;

    int nivelDificultad = 1;
    unsigned char letracoronacioncambiopieza;

public:
    // Constructor y destructor
    Tablero(const Jugador& j1, const Jugador& j2);
    ~Tablero();

    // Inicializaci�n
    void CasillasaCoordenadas();
    void inicializaTablero();
    // Dibujo
    void dibuja();
    void dibujaPieza();
    void DibujarPasosPermitidos();

    // Interacci�n
    void Selector(int x, int y);

    // Movimiento y validaciones
    Pieza* getPieza(int fila, int columna);
    bool hayPiezaOponente(int fila, int columna, bool turnoBlancas) const;
    bool casillaOcupada(int fila, int columna) const;
    bool caminoDespejado(int filaInicial, int columnaInicial, int filaFinal, int columnaFinal);

    void moverPieza(const Casilla& origen, const Casilla& destino);
    void ValidarMovimiento(bool turnoBlancas, bool& movimientoPermitido);

    // Jaque y jaque mate
    Casilla encontrarRey(bool turnoBlancas);
    bool estaEnJaque(bool turnoBlancas);
    bool estaEnJaqueMate(bool turnoBlancas);
    // Coronaci�n
    Pieza* HayCoronacion(Casilla casillaDestino, Pieza* tipoPieza);
    Pieza* CoronacionDeseada(Pieza* piezaActual, Casilla casillaDestino, bool blancas);
    std::string tipoPiezaToString(TipoPieza tipo);

    // Jugadores
    const Jugador& GetJugador1() const;
    const Jugador& GetJugador2() const;
    Jugador& GetJugador1();
    Jugador& GetJugador2();
    void SetJugador1(const Jugador& jugador);
    void SetJugador2(const Jugador& jugador);

    // IA
    void realizarMovimientoMaquina();
 };*/
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
    void mostrarMovimientosPeon(int fila, int columna, bool turnoBlancas) const;

    Pieza* getPieza(int fila, int columna);
    //bool casillaOcupada(int fila, int columna) const;
    bool casillaOcupada(int fila, int columna) const;
    bool hayPiezaOponente(int fila, int columna, bool turnoBlancas) const;
    void moverPieza(const Casilla& origen, const Casilla& destino);
};