#include "Torre.h"
#include "Tablero.h"
#include "ETSIDI.h"
#include<iostream>

Torre::Torre(int color, int fila, int columna, const Tablero& tableroRef)
    : Pieza(color, fila, columna), tablero(tableroRef) {
}

TipoPieza Torre::getTipo() const {
    return TipoPieza::Torre;
}

std::vector<Casilla> Torre::getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas) const {
    std::vector<Casilla> movimientos;

    int direccionFila[] = { -1, 1, 0, 0 };
    int direccionCol[] = { 0, 0, -1, 1 };

    for (int d = 0; d < 4; ++d) {
        int f = filaActual;
        int c = columnaActual;

        while (true) {
            f += direccionFila[d];
            c += direccionCol[d];

            if (f < 0 || f >= 8 || c < 0 || c >= 10) break;

            if (!tablero.casillaOcupada(f, c)) {
                movimientos.push_back({ f, c });
            }
            else {
                if (tablero.hayPiezaOponente(f, c, color == ColorBlancas)) {
                    movimientos.push_back({ f, c });
                }
                break;
            }
        }
    }

    return movimientos;
}


std::string Torre::obtenerRutaImagen() const {
    return (color == ColorBlancas) ? "imagenes/torre_blanca.png" : "imagenes/torre_negra.png";
}

