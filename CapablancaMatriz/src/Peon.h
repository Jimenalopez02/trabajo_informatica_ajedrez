/*#pragma once
#include "Pieza.h"
#include "Tablero.h"

class Peon : public Pieza {
public:
   // Peon(int color, int fila, int columna, const Coordenada& pos);
    Peon(int col, int fila, int columna);
    virtual TipoPieza getTipo() const override;

    // Se pasa el tablero solo al método de movimientos permitidos, no al constructor
    virtual std::vector<Casilla> getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas, const Tablero& tablero);
};*/
#pragma once
#include "Pieza.h"
 // Forward declaration
class Tablero;
class Peon : public Pieza {
private:
    const Tablero& tablero;
public:
    Peon(int color, int fila, int columna, const Tablero& tablero);
    TipoPieza getTipo() const override;
    std::vector<Casilla> getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas) const override;
};


