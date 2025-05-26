#include "Jugador.h"
#include "Pieza.h"

void Jugador::eliminarPieza(Pieza* pieza) {
    if (!pieza) return;

    // Buscar la pieza en el vector y eliminarla
    auto& piezas = this->piezas;  // asumo que tienes std::vector<Pieza*> piezas;

    auto it = std::find(piezas.begin(), piezas.end(), pieza);
    if (it != piezas.end()) {
        piezas.erase(it);
        delete pieza;  // liberar memoria de la pieza
    }
}