#include "Canciller.h"
#include "Tablero.h"
#include "Torre.h"
#include "Caballo.h"
#include "ETSIDI.h"

Canciller::Canciller(int color, int fila, int columna, const Tablero& tableroRef)
    : Pieza(color, fila, columna), tablero(tableroRef) {
}

TipoPieza Canciller::getTipo() const {
    return TipoPieza::Canciller;
}

std::vector<Casilla> Canciller::getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas) const {
    std::vector<Casilla> movimientos;

    Torre torre(color, filaActual, columnaActual, tablero);
    Caballo caballo(color, filaActual, columnaActual, tablero);

    std::vector<Casilla> movTorre = torre.getMovimientosPermitidos(filaActual, columnaActual, turnoBlancas);
    std::vector<Casilla> movCaballo = caballo.getMovimientosPermitidos(filaActual, columnaActual, turnoBlancas);

    movimientos.insert(movimientos.end(), movTorre.begin(), movTorre.end());
    movimientos.insert(movimientos.end(), movCaballo.begin(), movCaballo.end());

    return movimientos;
}

std::string Canciller::obtenerRutaImagen() const {
    return (color == ColorBlancas) ? "imagenes/canciller_blanco.png" : "imagenes/canciller_negro.png";
}
