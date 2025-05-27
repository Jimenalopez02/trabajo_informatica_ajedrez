#pragma once
#include "Pieza.h"
// Forward declaration
class Tablero;
class Alfil : public Pieza {
private:
    const Tablero& tablero;
public:
    Alfil(int color, int fila, int columna, const Tablero& tablero);
    TipoPieza getTipo() const override;
    std::vector<Casilla> getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas) const override;
    friend class Arzobispo;
    friend class Reina; 
    std::string obtenerRutaImagen() const override;

};
