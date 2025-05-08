#include "Rey.h"
#include "Tablero.h"

Rey::Rey(int color, int fila, int columna, const Tablero& tableroRef)
    : Pieza(color, fila, columna), tablero(tableroRef) {
}

TipoPieza Rey::getTipo() const {
    return TipoPieza::Rey;
}

std::vector<Casilla> Rey::getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas) const {
    std::vector<Casilla> movimientos;

    // Todas las direcciones posibles (8 movimientos)
    int direcciones[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

    for (auto& dir : direcciones) {
        int fila = filaActual + dir[0];
        int col = columnaActual + dir[1];

        // Verificar límites del tablero
        if (fila >= 0 && fila < 8 && col >= 0 && col < 10) {
            if (!tablero.casillaOcupada(fila, col) || tablero.hayPiezaOponente(fila, col, turnoBlancas)) {
                movimientos.push_back({ fila, col });
            }
        }
    }

    return movimientos;
}