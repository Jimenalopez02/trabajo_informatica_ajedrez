#pragma once
#include "Pieza.h"
#include "Casilla.h"
#include <vector>

class Tablero;  // Forward declaration

class Peon : public Pieza {
private:
    const Tablero& tablero;

public:
    Peon(int color, int fila, int columna, const Tablero& tablero);

    TipoPieza getTipo() const override;
    std::vector<Casilla> getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas) const override;
    std::string obtenerRutaImagen() const override;

};


