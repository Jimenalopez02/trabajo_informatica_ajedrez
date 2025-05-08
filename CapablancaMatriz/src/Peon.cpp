/*#include "Peon.h"
#include "Casilla.h"
Peon::Peon(int color, int fila, int columna, const Coordenada& pos)
    : Pieza(color, pos, "imagenes/peon.png")  // Ajusta la ruta del sprite si es necesario
{
    setFila(fila);
    setColumna(columna);
}
Peon::Peon(int col, int fila, int columna): Pieza(col,fila,columna)
      // Ajusta la ruta del sprite si es necesario
{
    color = col;
    setFila(fila);
    setColumna(columna);
}

TipoPieza Peon::getTipo() const {
    return TipoPieza::Peon;
}

std::vector<Casilla> Peon::getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas, const Tablero& tablero){
    std::vector<Casilla> movimientos;
    int direccion = (color == ColorBlancas) ? -1 : 1;
    int filaSiguiente = filaActual + direccion;

    // Movimiento hacia adelante
    if (!tablero.casillaOcupada(filaSiguiente, columnaActual)) {
        movimientos.push_back(Casilla(filaSiguiente, columnaActual));

        // Movimiento doble desde fila inicial
        if ((color == ColorBlancas && filaActual == 6) || (color == ColorNegras && filaActual == 1)) {
            int filaDoble = filaActual + 2 * direccion;
            if (!tablero.casillaOcupada(filaDoble, columnaActual)) {
                movimientos.push_back(Casilla(filaDoble, columnaActual));
            }
        }
    }

    // Capturas diagonales
    for (int dc : {-1, 1}) {
        int columnaDestino = columnaActual + dc;
        if (columnaDestino >= 0 && columnaDestino < 10) {  // Ajusta si tu tablero no es de 10 columnas
            if (tablero.hayPiezaOponente(filaSiguiente, columnaDestino, turnoBlancas)) {
                movimientos.push_back(Casilla(filaSiguiente, columnaDestino));
            }
        }
    }

    return movimientos;
}*/

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
        if (colDestino >= 0 && colDestino < 8) {
            if (tablero.hayPiezaOponente(filaSiguiente, colDestino, turnoBlancas)) {
                movimientos.push_back({ filaSiguiente, colDestino });
            }
        }
    }

    return movimientos;
}