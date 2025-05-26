#include "ETSIDI.h"
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

    // Movimiento hacia adelante
    if (filaSiguiente >= 0 && filaSiguiente < FILAS_TABLERO &&
        !tablero.casillaOcupada(filaSiguiente, columnaActual)) {

        movimientos.push_back({ filaSiguiente, columnaActual });

        // Movimiento doble si está en su fila inicial
        if ((color == ColorBlancas && getFila() == 1) ||
            (color == ColorNegras && getFila() == 6)) {

            int filaDoble = filaActual + 2 * direccion;
            if (filaDoble >= 0 && filaDoble < FILAS_TABLERO &&
                !tablero.casillaOcupada(filaDoble, columnaActual)) {
                movimientos.push_back({ filaDoble, columnaActual });
            }
        }
    }

    // Capturas diagonales
    for (int dc : {-1, 1}) {
        int colDestino = columnaActual + dc;
        if (colDestino >= 0 && colDestino < COLUMNAS_TABLERO) {
            if (tablero.casillaOcupada(filaSiguiente, colDestino)) {
                movimientos.push_back({ filaSiguiente, colDestino });
            }
        }
    }

    return movimientos;
}

std::string Peon::obtenerRutaImagen() const {
    return (color == ColorBlancas) ? "imagenes/peon_blanco.png" : "imagenes/peon_negro.png";
}
