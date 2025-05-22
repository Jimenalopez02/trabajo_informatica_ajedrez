#pragma once
#include "Pieza.h"
// Forward declaration
class Tablero;
class Arzobispo : public Pieza {
private:
    const Tablero& tablero;
public:
    Arzobispo(int color, int fila, int columna, const Tablero& tablero);
    TipoPieza getTipo() const override;
    std::vector<Casilla> getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas) const override;
};

