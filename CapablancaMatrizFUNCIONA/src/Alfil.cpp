#include "Alfil.h"
#include "Tablero.h"
#include "ETSIDI.h"

Alfil::Alfil(int color, int fila, int columna, const Tablero& tableroRef)
    : Pieza(color, fila, columna), tablero(tableroRef) {
}

TipoPieza Alfil::getTipo() const {
    return TipoPieza::Alfil;
}
std::vector<Casilla> Alfil::getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas) const {
    std::vector<Casilla> movimientos;

    int direcciones[4][2] = { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

    for (auto& dir : direcciones) {
        int fila = filaActual + dir[0];
        int col = columnaActual + dir[1];

        while (fila >= 0 && fila < 8 && col >= 0 && col < 10) {
            if (!tablero.casillaOcupada(fila, col)) {
                movimientos.push_back({ fila, col });
            }
            else {
                if (tablero.hayPiezaOponente(fila, col, turnoBlancas)) {
                    movimientos.push_back({ fila, col });
                }
                break;
            }
            fila += dir[0];
            col += dir[1];
        }
    }

    return movimientos;
}

std::string Alfil::obtenerRutaImagen() const {
    return (color == ColorBlancas) ? "imagenes/alfil_blanco.png" : "imagenes/alfil_negro.png";
}
