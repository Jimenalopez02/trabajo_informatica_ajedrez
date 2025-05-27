#include "Tablero.h"
#include "Arzobispo.h"
#include "Alfil.h"
#include "Caballo.h"
#include "ETSIDI.h"

Arzobispo::Arzobispo(int color, int fila, int columna, const Tablero& tableroRef)
    : Pieza(color, fila, columna), tablero(tableroRef) {
}

TipoPieza Arzobispo::getTipo() const {
    return TipoPieza::Arzobispo;
}

std::vector<Casilla> Arzobispo::getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas) const {
    std::vector<Casilla> movimientos;

    // Objetos temporales para calcular movimientos de Alfil y Caballo
    Alfil alfil(color, filaActual, columnaActual, tablero);
    Caballo caballo(color, filaActual, columnaActual, tablero);

    std::vector<Casilla> movAlfil = alfil.getMovimientosPermitidos(filaActual, columnaActual, turnoBlancas);
    std::vector<Casilla> movCaballo = caballo.getMovimientosPermitidos(filaActual, columnaActual, turnoBlancas);

    movimientos.insert(movimientos.end(), movAlfil.begin(), movAlfil.end());
    movimientos.insert(movimientos.end(), movCaballo.begin(), movCaballo.end());

    return movimientos;
}

std::string Arzobispo::obtenerRutaImagen() const {
    return (color == ColorBlancas) ? "imagenes/arzobispo_blanco.png" : "imagenes/arzobispo_negro.png";
}
