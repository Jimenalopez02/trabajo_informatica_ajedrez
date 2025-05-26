
// Pieza.h (declaración con soporte para dibujaPieza)
#pragma once
#include <vector>
#include "Casilla.h"
#include "Coordenada.h"
#include <string>

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
    Pieza(int color, int fila, int columna) : color(color), fila(fila), columna(columna) {}
    virtual ~Pieza() = default;

    virtual TipoPieza getTipo() const = 0;
    virtual std::vector<Casilla> getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas) const = 0;

    virtual void dibujaPieza(float x, float y, float tam) const;
    virtual std ::string obtenerRutaImagen() const = 0;

    int getColor() const { return color; }
    int getFila() const { return fila; }
    int getColumna() const { return columna; }

    void setFila(int f) { fila = f; }
    void setColumna(int c) { columna = c; }
};
