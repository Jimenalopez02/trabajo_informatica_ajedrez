#include "Pieza.h"

class Tablero; // Forward declaration

class Torre : public Pieza {
private:
    const Tablero& tablero;
public:
    Torre(int color, int fila, int columna, const Tablero& tablero);
    TipoPieza getTipo() const override;
    std::vector<Casilla> getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas) const override;
    friend class Canciller;
    friend class Torre;
    std::string obtenerRutaImagen() const override;


};

