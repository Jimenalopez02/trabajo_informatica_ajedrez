#pragma once
#include "Pieza.h"
// Forward declaration
class Tablero;
class Caballo : public Pieza {
private:
    const Tablero& tablero;
public:
    Caballo(int color, int fila, int columna, const Tablero& tablero);
    TipoPieza getTipo() const override;
    std::vector<Casilla> getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas) const override;
    friend class Canciller;
    friend class Arzobispo;
    std::string obtenerRutaImagen() const override ;

    
};

