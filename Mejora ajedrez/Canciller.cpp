#include "Canciller.h"
#include "Tablero.h"
#include "Torre.h"
#include "Caballo.h"
Canciller::Canciller(int color, int fila, int columna, const Tablero& tableroRef)
    : Pieza(color, fila, columna), tablero(tableroRef) {
}

TipoPieza Canciller::getTipo() const {
    return TipoPieza::Canciller;
}
// para hacer esta clase, como ya tenemos creados torre y caballo, simplemente hay que hacer uso de friend class en ambas
// y crear el mismo vector de movimientos sumando los vectores posibles de los movimientos de una torre y los de un caballo
std::vector<Casilla> Canciller::getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas) const {
    std::vector<Casilla> movimientos;
    //se crean objetos temporales para saber como se pueden mover estas fichas
    Torre torre(color, filaActual, columnaActual, tablero);
    Caballo caballo(color, filaActual, columnaActual, tablero);

    std::vector<Casilla> movTorre = torre.getMovimientosPermitidos(filaActual, columnaActual, turnoBlancas);
    std::vector<Casilla> movCaballo = caballo.getMovimientosPermitidos(filaActual, columnaActual, turnoBlancas);
    //para introducir los vectores de cada movimiento en el general, se usan las funciones de la clase vector de insert, begin y end
    movimientos.insert(movimientos.end(), movTorre.begin(), movTorre.end());
    movimientos.insert(movimientos.end(), movCaballo.begin(), movCaballo.end());
    return movimientos;
}