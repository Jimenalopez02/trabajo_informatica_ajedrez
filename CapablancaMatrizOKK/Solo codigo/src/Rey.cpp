#include "Rey.h"
#include "Tablero.h"
#include "ETSIDI.h"

Rey::Rey(int color, int fila, int columna, const Tablero& tableroRef)
    : Pieza(color, fila, columna), tablero(tableroRef) {
}

TipoPieza Rey::getTipo() const {
    return TipoPieza::Rey;
}

std::vector<Casilla> Rey::getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas) const {
    std::vector<Casilla> movimientos;

    // Direcciones posibles (8 alrededor)
    int direcciones[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

    for (auto& dir : direcciones) {
        int fila = filaActual + dir[0];
        int col = columnaActual + dir[1];

        if (fila >= 0 && fila < FILAS_TABLERO && col >= 0 && col < COLUMNAS_TABLERO) {
            Pieza* destino = tablero.getPieza(fila, col);

            // Si la casilla está vacía o tiene una pieza (propia o enemiga) distinta del propio rey
            if (!destino || destino->getTipo() != TipoPieza::Rey || destino->getColor() != color) {
                movimientos.push_back({ fila, col });
            }
        }
    }

    return movimientos;
}

std::string Rey::obtenerRutaImagen() const {
    return (color == ColorBlancas) ? "imagenes/rey_blanco.png" : "imagenes/rey_negro.png";
}

