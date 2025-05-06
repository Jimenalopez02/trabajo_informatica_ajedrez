#pragma once
#include "freeglut.h"
#include "ETSIDI.h"
#include "Coordenada.h"
#include "casilla.h"
#include <vector>
#include <string>

using ETSIDI::SpriteSequence;
using std::vector;

enum class TipoPieza {
    Peon,
    Torre,
    Caballo,
    Alfil,
    Reina,
    Rey,
    Arzobispo,  // Alfil + Caballo
    Canciller,  // Torre + Caballo
    Ninguno
};

const int ColorBlancas = 0;
const int ColorNegras = 1;

class Pieza {
protected:
    int color;                  // ColorBlancas o ColorNegras
    int fila, columna;          // Posición en el tablero
    Coordenada posicion;        // Posición gráfica para ETSIDI
    SpriteSequence sprite;      // imagen pieza

public:
    bool seleccionActivada = false;

    // Constructor 
    Pieza(int color, const Coordenada& posicion, const char* rutaSprite, float escala = 1.0f);

    virtual ~Pieza();

    // Métodos gráficos
    virtual void dibujaPieza();

    // Métodos virtuales puros
    virtual TipoPieza getTipo() const = 0;
    virtual vector<Casilla> getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas) const = 0;

    
    int getColor() const;
    int getFila() const;
    int getColumna() const;

    void setFila(int f);
    void setColumna(int c);

    Coordenada getPosicion() const;
    void setPosicion(const Coordenada& pos);
};
