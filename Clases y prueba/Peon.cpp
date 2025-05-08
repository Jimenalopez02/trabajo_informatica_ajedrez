
#include "Peon.h"
#include "Tablero.h"

Peon::Peon(int color, int fila, int columna, const Tablero& tableroRef)
    : Pieza(color, fila, columna), tablero(tableroRef) {
}

TipoPieza Peon::getTipo() const {
    return TipoPieza::Peon;
}

std::vector<Casilla> Peon::getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas) const {
    std::vector<Casilla> movimientos;
    int direccion = (color == ColorBlancas) ? 1 : -1;
    int filaSiguiente = filaActual + direccion;

    if (!tablero.casillaOcupada(filaSiguiente, columnaActual)) {
        movimientos.push_back({ filaSiguiente, columnaActual });

        if ((color == ColorBlancas && filaActual == 1) || (color == ColorNegras && filaActual == 6)) {
            int filaDoble = filaActual + 2 * direccion;
            if (!tablero.casillaOcupada(filaDoble, columnaActual)) {
                movimientos.push_back({ filaDoble, columnaActual });
            }
        }
    }

    for (int dc : {-1, 1}) {
        int colDestino = columnaActual + dc;
        if (colDestino >= 0 && colDestino < 10) {
            if (tablero.hayPiezaOponente(filaSiguiente, colDestino, color == ColorBlancas)) {
                movimientos.push_back({ filaSiguiente, colDestino });
            }
        }
    }

    return movimientos;
}