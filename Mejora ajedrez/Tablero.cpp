
#include "Tablero.h"
#include "Peon.h"
#include "Caballo.h"
#include <iostream>
#include "Torre.h"
#include "Canciller.h"
#include "Alfil.h"
#include "Arzobispo.h"
#include "Reina.h"
#include "Rey.h"
Tablero::Tablero(Jugador& j1,Jugador& j2)
    : jugadorActivo(&j1), jugadorRival(&j2) {
    casillas.resize(8, std::vector<Pieza*>(10, nullptr));  // 8 filas, 10 columnas
}

Tablero::~Tablero() {
    for (auto& fila : casillas)
        for (auto& p : fila)
            delete p;
}
Pieza* Tablero::getPieza(int fila, int columna) {
    if (fila < 0 || fila >= 8 || columna < 0 || columna >= 10)
        return nullptr;
    return casillas[fila][columna];
}
void Tablero::cambiarTurno() {
    std::swap(jugadorActivo, jugadorRival);
}
void Tablero::inicializaTablero() {
    for (int col = 0; col < 10; ++col) {
        Pieza* peonBlanco = new Peon(ColorBlancas, 1, col, *this);
        casillas[1][col] = peonBlanco;
        jugadorActivo->agregarPieza(peonBlanco);

        Pieza* peonNegro = new Peon(ColorNegras, 6, col, *this);
        casillas[6][col] = peonNegro;
        jugadorRival->agregarPieza(peonNegro);
    }
    casillas[0][0] = new Torre(ColorBlancas, 0, 0, *this);
    casillas[0][9] = new Torre(ColorBlancas, 0, 9, *this);
    casillas[0][1] = new Caballo(ColorBlancas, 0, 1, *this);
    casillas[0][2] = new Canciller(ColorBlancas, 0, 2, *this);
    casillas[0][8] = new Caballo(ColorBlancas, 0, 8, *this);
    casillas[0][3] = new Alfil(ColorBlancas, 0, 3, *this);
    casillas[0][6] = new Alfil(ColorBlancas, 0, 6, *this);
    casillas[0][7] = new Arzobispo(ColorBlancas, 0, 7, *this);
    casillas[0][4] = new Reina(ColorBlancas, 0, 4, *this);
    casillas[0][5] = new Rey(ColorBlancas, 0, 5, *this);
    
    casillas[7][0] = new Torre(ColorNegras, 7, 0, *this);
    casillas[7][9] = new Torre(ColorNegras, 7, 9, *this);
    casillas[7][1] = new Caballo(ColorNegras, 7, 1, *this);
    casillas[7][2] = new Canciller(ColorNegras, 7, 2, *this);
    casillas[7][8] = new Caballo(ColorNegras, 7, 8, *this);
    casillas[7][3] = new Alfil(ColorNegras, 7, 3, *this);
    casillas[7][6] = new Alfil(ColorNegras, 7, 6, *this);
    casillas[7][7] = new Arzobispo(ColorNegras, 7, 7, *this);
    casillas[7][4] = new Reina(ColorNegras, 7, 4, *this);
    casillas[7][5] = new Rey(ColorNegras, 7, 5, *this);
}

void Tablero::mostrarTablero() const {
    std::cout << "    ";
    for (int col = 0; col < 10; ++col)
        std::cout << int(0 + col) << " ";
    std::cout << "\n";

    for (int fila = 7; fila >= 0; --fila) {
        std::cout << fila << " | ";
        for (int col = 0; col < 10; ++col) {
            Pieza* p = casillas[fila][col];
            if (p) {
                if (p->getTipo() == TipoPieza::Peon)
                    std::cout << (p->getColor() == ColorBlancas ? "P" : "p") << " ";
                else if (p->getTipo() == TipoPieza::Torre)
                    std::cout << (p->getColor() == ColorBlancas ? "T" : "t") << " ";
                else if (p->getTipo() == TipoPieza::Caballo)
                    std::cout << (p->getColor() == ColorBlancas ? "C" : "c") << " ";
                else if (p->getTipo() == TipoPieza::Canciller)
                    std::cout << (p->getColor() == ColorBlancas ? "H" : "h") << " ";
                else if (p->getTipo() == TipoPieza::Alfil)
                    std::cout << (p->getColor() == ColorBlancas ? "A" : "a") << " ";
                else if (p->getTipo() == TipoPieza::Arzobispo)
                    std::cout << (p->getColor() == ColorBlancas ? "Z" : "z") << " ";
                else if (p->getTipo() == TipoPieza::Reina)
                    std::cout << (p->getColor() == ColorBlancas ? "Q" : "q") << " ";
                else if (p->getTipo() == TipoPieza::Rey)
                    std::cout << (p->getColor() == ColorBlancas ? "K" : "k") << " ";
                else
                    std::cout << "? ";
            }
            else {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }
}

void Tablero::mostrarMovimientos(int fila, int columna) const {
    if (fila < 0 || fila >= 8 || columna < 0 || columna >= 10) {
        std::cout << "Posición fuera de rango.\n";
        return;
    }

    Pieza* p = casillas[fila][columna];
    if (!p) {
        std::cout << "No hay ninguna pieza en esa posición.\n";
        return;
    }

    std::vector<Casilla> movimientos = p->getMovimientosPermitidos(fila, columna, p->getColor() == ColorBlancas);
    if (movimientos.empty()) {
        std::cout << "La pieza no tiene movimientos disponibles.\n";
    }
    else {
        std::cout << "Movimientos disponibles para la pieza en (" << fila << ", " << columna << "):\n";
        for (const Casilla& mov : movimientos) {
            std::cout << " - (" << mov.fila << ", " << mov.columna << ")\n";
        }
    }
}
std::vector<Casilla> Tablero::obtenerMovimientosPermitidos(int fila, int columna, bool turnoBlancas) const {
    if (!esPosicionValida(fila, columna)) return {};

    Pieza* p = casillas[fila][columna];
    if (!p || p->getColor() != (turnoBlancas ? ColorBlancas : ColorNegras)) return {};

    return p->getMovimientosPermitidos(fila, columna, turnoBlancas);
}

bool Tablero::esPosicionValida(int fila, int columna) const {
    return fila >= 0 && fila < 8 && columna >= 0 && columna < 10;
}

bool Tablero::casillaOcupada(int fila, int columna) const {
    return esPosicionValida(fila, columna) && casillas[fila][columna];
}

bool Tablero::hayPiezaOponente(int fila, int columna, bool turnoBlancas) const {
    if (!casillaOcupada(fila, columna)) return false;
    return casillas[fila][columna]->getColor() != (turnoBlancas ? Color::BLANCO : Color::NEGRO);
}
void Tablero::moverPieza(const Casilla& origen, const Casilla& destino) {
    Pieza* pieza = getPieza(origen.fila, origen.columna);
    if (!pieza) {
        std::cout << "No hay ninguna pieza en la casilla de origen.\n";
        return;
    }

    if (pieza->getColor() != jugadorActivo->getColor()) {
        std::cout << "No es el turno del jugador para mover esta pieza.\n";
        return;
    }

    std::vector<Casilla> movimientos = pieza->getMovimientosPermitidos(
        origen.fila, origen.columna, jugadorActivo->getColor() == ColorBlancas);

    bool movimientoValido = false;
    for (const Casilla& m : movimientos) {
        if (m.fila == destino.fila && m.columna == destino.columna) {
            movimientoValido = true;
            break;
        }
    }

    if (!movimientoValido) {
        std::cout << "Movimiento no permitido.\n";
        return;
    }

    // Simulación del movimiento
    Pieza* piezaCapturada = casillas[destino.fila][destino.columna];
    casillas[destino.fila][destino.columna] = pieza;
    casillas[origen.fila][origen.columna] = nullptr;
    pieza->setFila(destino.fila);
    pieza->setColumna(destino.columna);

    // Verificar jaque al rey propio
   /* if (reyEnJaque(*jugadorActivo)) {
        std::cout << "Este movimiento deja al rey en jaque.\n";
        // Revertir movimiento
        casillas[origen.fila][origen.columna] = pieza;
        casillas[destino.fila][destino.columna] = piezaCapturada;
        pieza->setFila(origen.fila);
        pieza->setColumna(origen.columna);
        return;
    }*/

    if (piezaCapturada) delete piezaCapturada;

    // Cambiar turno
    cambiarTurno();
}
/*bool Tablero::reyEnJaque(const Jugador& jugador) {
    // 1. Buscar el rey del jugador
    Pieza* rey = nullptr;
    for (Pieza* pieza : jugador.getPiezas()) {
        if (pieza->getTipo() == TipoPieza::Rey) {
            rey = pieza;
            break;
        }
    }

    if (!rey) {
        std::cerr << "Error: Rey no encontrado para el jugador.\n";
        return false; // No debería ocurrir
    }

    // 2. Verificar si alguna pieza rival puede capturar al rey
    for (Pieza* piezaRival : jugadorRival->getPiezas()) {
        std::vector<Casilla> movimientos = piezaRival->getMovimientosPermitidos(
            piezaRival->getFila(),
            piezaRival->getColumna(),
            jugadorRival->getColor() == ColorBlancas
        );

        for (const Casilla& mov : movimientos) {
            if (mov.fila == rey->getFila() && mov.columna == rey->getColumna()) {
                return true; // El rey está en jaque
            }
        }
    }

    return false; // Rey no está en jaque
}*/