#include "Caballo.h"
#include "Tablero.h"

Caballo::Caballo(int color, int fila, int columna, const Tablero& tableroRef)
    : Pieza(color, fila, columna), tablero(tableroRef) {
}

TipoPieza Caballo::getTipo() const {
    return TipoPieza::Caballo;
}
std::vector<Casilla> Caballo::getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas) const {
    std::vector<Casilla> movimientos;

    // Todos los posibles movimientos en L
    int desplazamientos[8][2] = {
        {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
        {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
    };

    for (const auto& d : desplazamientos) {
        int nuevaFila = filaActual + d[0];
        int nuevaColumna = columnaActual + d[1];

        if (nuevaFila >= 0 && nuevaFila < 8 && nuevaColumna >= 0 && nuevaColumna < 10) {
            if (!tablero.casillaOcupada(nuevaFila, nuevaColumna) ||
                tablero.hayPiezaOponente(nuevaFila, nuevaColumna, color == ColorBlancas)) {
                movimientos.push_back({ nuevaFila, nuevaColumna });
            }
        }
    }

    return movimientos;
}
