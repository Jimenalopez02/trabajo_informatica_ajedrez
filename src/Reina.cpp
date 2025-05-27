#include "Tablero.h"
#include "Reina.h"
#include "Alfil.h"
#include "Torre.h"
#include "ETSIDI.h"

Reina::Reina(int color, int fila, int columna, const Tablero& tableroRef)
    : Pieza(color, fila, columna), tablero(tableroRef) {
}

TipoPieza Reina::getTipo() const {
    return TipoPieza::Reina;
}

std::vector<Casilla> Reina::getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas) const {
    std::vector<Casilla> movimientos;

    Alfil alfil(color, filaActual, columnaActual, tablero);
    Torre torre(color, filaActual, columnaActual, tablero);

    std::vector<Casilla> movAlfil = alfil.getMovimientosPermitidos(filaActual, columnaActual, turnoBlancas);
    std::vector<Casilla> movTorre = torre.getMovimientosPermitidos(filaActual, columnaActual, turnoBlancas);

    movimientos.insert(movimientos.end(), movAlfil.begin(), movAlfil.end());
    movimientos.insert(movimientos.end(), movTorre.begin(), movTorre.end());

    return movimientos;
}
std::string Reina::obtenerRutaImagen() const {
    return (color == ColorBlancas) ? "imagenes/reina_blanca.png" : "imagenes/reina_negra.png";
}
