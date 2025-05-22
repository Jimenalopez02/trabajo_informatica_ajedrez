#pragma once
#include "Pieza.h"
class Tablero;
class Rey : public Pieza {
private: 
	const Tablero& tablero;
public:
	Rey(int color, int fila, int columna, const Tablero& tablero);
	TipoPieza getTipo() const override;
	std::vector<Casilla> getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas) const override;
};

