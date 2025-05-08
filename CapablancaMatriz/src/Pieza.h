#pragma once
/*#include "freeglut.h"
#include "ETSIDI.h"
#include "Coordenada.h"
#include "casilla.h"
#include <vector>
#include <string>
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
using ETSIDI::SpriteSequence;
using std::vector;
const int ColorBlancas = 0;
const int ColorNegras = 1;
class Pieza{
protected:
    
    int color;                  // ColorBlancas o ColorNegras
    int fila, columna;          // Posici�n l�gica en el tablero
    Coordenada posicion;        // Posici�n gr�fica para ETSIDI
    SpriteSequence sprite;
    // Animaci�n/imagen de la pieza

public:
    bool seleccionActivada = false;

    // Constructor base
   // Pieza(int col, const Coordenada& pos, const char* rutaSprite, float escala = 1.0f);
    Pieza(int col, int fil, int colum);
    virtual ~Pieza();

    // M�todos gr�ficos
    virtual void dibujaPieza();

    // M�todos virtuales puros
    virtual TipoPieza getTipo() const = 0;
    virtual vector<Casilla> getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas);

    // Accesores y mutadores
    bool getColor() const { return color; };
    
    int getFila() const { return fila; };
    int getColumna() const { return columna; };

    void setFila(int f) { fila = f; };
    void setColumna(int c) { columna = c; };

    Coordenada getPosicion() const { return posicion; };
    void setPosicion(const Coordenada& pos) { posicion = pos; };
};*/
#pragma once
#include <vector>
#include "Casilla.h"
enum class TipoPieza {
    Peon,
    Torre,
    Caballo,
    Alfil,
    Reina,
    Rey,
    Arzobispo,
    Canciller,
    Ninguno
};
const int ColorBlancas = 0;
const int ColorNegras = 1;

class Pieza {
    protected:
        int color;
        int fila, columna;

    public:
        Pieza(int color, int fila, int columna) : color(color), fila(fila), columna(columna) {};
        virtual ~Pieza() = default;

        virtual TipoPieza getTipo() const = 0;
        virtual std::vector<Casilla> getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas) const = 0;

        int getColor() const { return color; }
        int getFila() const { return fila; }
        int getColumna() const { return columna; }

        void setFila(int f) { fila = f; }
        void setColumna(int c) { columna = c; }
};

