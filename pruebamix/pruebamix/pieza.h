#pragma once
#include <vector>

// Enumeraci�n para el color de la pieza
enum class Color {
    Blancas,
    Negras
};

// Enumeraci�n para el tipo de pieza (ajedrez de Capablanca incluido)
enum class TipoPieza {
    Peon,
    Torre,
    Caballo,
    Alfil,
    Reina,
    Rey,
    Arzobispo,   // Alfil + Caballo
    Canciller,   // Torre + Caballo
    Ninguna
};

// Representa una casilla (coordenada del tablero)
struct Casilla {
    int fila;
    int columna;

    Casilla(int f, int c) : fila(f), columna(c) {}
    bool operator==(const Casilla& otra) const {
        return fila == otra.fila && columna == otra.columna;
    }
};

// Clase base abstracta para todas las piezas
class Pieza {
protected:
    Color color;
    Casilla posicion;
    TipoPieza tipo;

public:
    Pieza(Color c, int fila, int columna, TipoPieza t)
        : color(c), posicion(fila, columna), tipo(t) {}

    virtual ~Pieza() = default;

    Color getColor() const { return color; }
    Casilla getPosicion() const { return posicion; }
    TipoPieza getTipo() const { return tipo; }

    void setPosicion(int nuevaFila, int nuevaColumna) {
        posicion.fila = nuevaFila;
        posicion.columna = nuevaColumna;
    }

    // M�todo virtual puro: cada pieza define c�mo se mueve
    // Pieza.h
    virtual std::vector<Casilla> getMovimientosPermitidos(Pieza* const (*tablero)[10]) const = 0;


    // M�todo para obtener el car�cter con el que se imprimir� en consola
    virtual char getSimbolo() const = 0;
};
