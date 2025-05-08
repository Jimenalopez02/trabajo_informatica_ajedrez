#include "Tablero.h"
#include "Reina.h"
#include "Alfil.h"
#include "Torre.h"
Reina::Reina(int color, int fila, int columna, const Tablero& tableroRef)
    : Pieza(color, fila, columna), tablero(tableroRef) {
}

TipoPieza Reina::getTipo() const {
    return TipoPieza::Reina;
}
// para hacer esta clase, como ya tenemos creados torre y caballo, simplemente hay que hacer uso de friend class en ambas
// y crear el mismo vector de movimientos sumando los vectores posibles de los movimientos de una torre y los de un caballo
std::vector<Casilla> Reina::getMovimientosPermitidos(int filaActual, int columnaActual, bool turnoBlancas) const {
    std::vector<Casilla> movimientos;
    //se crean objetos temporales para saber como se pueden mover estas fichas
    Alfil alfil(color, filaActual, columnaActual, tablero);
    Torre torre(color, filaActual, columnaActual, tablero);

    std::vector<Casilla> movAlfil = alfil.getMovimientosPermitidos(filaActual, columnaActual, turnoBlancas);
    std::vector<Casilla> movTorre = torre.getMovimientosPermitidos(filaActual, columnaActual, turnoBlancas);
    //para introducir los vectores de cada movimiento en el general, se usan las funciones de la clase vector de insert, begin y end
    movimientos.insert(movimientos.end(), movAlfil.begin(), movAlfil.end());
    movimientos.insert(movimientos.end(), movTorre.begin(), movTorre.end());

    return movimientos;
}