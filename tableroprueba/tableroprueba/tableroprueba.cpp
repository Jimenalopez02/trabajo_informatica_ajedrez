#include "freeglut.h"
#include "ETSIDI.h"
#include <iostream>
#include <vector>
#include "tablero.h"

#define FILAS_TABLERO 8
#define COLUMNAS_TABLERO 10

using namespace std;

Tablero::Tablero(const Jugador& j1, const Jugador& j2)
    : jugador1(j1), jugador2(j2), casillas(FILAS_TABLERO, vector<Pieza*>(COLUMNAS_TABLERO, nullptr)) {
    CasillasaCoordenadas();
    inicializaTablero();
}

Tablero::~Tablero() {
    for (auto& fila : casillas) {
        for (auto& pieza : fila) {
            delete pieza;
        }
    }
}
void Tablero::CasillasaCoordenadas() {
    int k = 0;
    for (int fila = 0; fila < FILAS_TABLERO; fila++) {
        for (int col = 0; col < COLUMNAS_TABLERO; col++) {
            coordenadaSobreTablero[k].x = 0.93 - 0.186 * col;
            coordenadaSobreTablero[k].y = -0.675 + 0.23 * fila;
            k++;
        }
    }
}

void Tablero::inicializaTablero() {
    enum { blanco, negro };

    casillas[0][0] = new Torre({}, blanco, 0, 0, *this);
    casillas[0][1] = new Caballo({}, blanco, 0, 1);
    casillas[0][2] = new Alfil({}, blanco, 0, 2, *this);
    casillas[0][3] = new Arzobispo({}, blanco, 0, 3, *this);
    casillas[0][4] = new Reina({}, blanco, 0, 4, *this);
    casillas[0][5] = new Rey({}, blanco, 0, 5, *this);
    casillas[0][6] = new Canciller({}, blanco, 0, 6, *this);
    casillas[0][7] = new Alfil({}, blanco, 0, 7, *this);
    casillas[0][8] = new Caballo({}, blanco, 0, 8);
    casillas[0][9] = new Torre({}, blanco, 0, 9, *this);

    casillas[7][0] = new Torre({}, negro, 7, 0, *this);
    casillas[7][1] = new Caballo({}, negro, 7, 1);
    casillas[7][2] = new Alfil({}, negro, 7, 2, *this);
    casillas[7][3] = new Arzobispo({}, negro, 7, 3, *this);
    casillas[7][4] = new Reina({}, negro, 7, 4, *this);
    casillas[7][5] = new Rey({}, negro, 7, 5, *this);
    casillas[7][6] = new Canciller({}, negro, 7, 6, *this);
    casillas[7][7] = new Alfil({}, negro, 7, 7, *this);
    casillas[7][8] = new Caballo({}, negro, 7, 8);
    casillas[7][9] = new Torre({}, negro, 7, 9, *this);

    for (int i = 0; i < COLUMNAS_TABLERO; i++) {
        casillas[1][i] = new Peon({}, blanco, 1, i, *this);
        casillas[6][i] = new Peon({}, negro, 6, i, *this);
    }
}
void Tablero::dibuja() {
    glEnable(GL_TEXTURE_2D);
    GLuint texturaTablero = ETSIDI::getTexture("imagenes/tablero.png").id;
    glBindTexture(GL_TEXTURE_2D, texturaTablero);

    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glTexCoord2d(0, 1); glVertex2f(-1, -1);
    glTexCoord2d(1, 1); glVertex2f(1, -1);
    glTexCoord2d(1, 0); glVertex2f(1, 1);
    glTexCoord2d(0, 0); glVertex2f(-1, 1);
    glEnd();

    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    dibujaPieza();

    if (seleccionActiva) {
        DibujarPasosPermitidos();
    }
}

void Tablero::dibujaPieza() {
    for (auto& fila : casillas) {
        for (auto& pieza : fila) {
            if (pieza != nullptr) {
                pieza->dibujaPieza();
            }
        }
    }
}
const Jugador& Tablero::GetJugador1() const { return jugador1; }
const Jugador& Tablero::GetJugador2() const { return jugador2; }
Jugador& Tablero::GetJugador1() { return jugador1; }
Jugador& Tablero::GetJugador2() { return jugador2; }

void Tablero::SetJugador1(const Jugador& jugador) { jugador1 = jugador; }
void Tablero::SetJugador2(const Jugador& jugador) { jugador2 = jugador; }
Pieza* Tablero::getPieza(int fila, int columna) {
    if (fila < 0 || fila >= FILAS_TABLERO || columna < 0 || columna >= COLUMNAS_TABLERO)
        return nullptr;
    return casillas[fila][columna];
}

bool Tablero::casillaOcupada(int fila, int columna) const {
    if (fila < 0 || fila >= FILAS_TABLERO || columna < 0 || columna >= COLUMNAS_TABLERO)
        return false;
    return casillas[fila][columna] != nullptr;
}

bool Tablero::caminoDespejado(int filaInicial, int columnaInicial, int filaFinal, int columnaFinal) {
    int incrementoFila = (filaFinal > filaInicial) ? 1 : (filaFinal < filaInicial) ? -1 : 0;
    int incrementoColumna = (columnaFinal > columnaInicial) ? 1 : (columnaFinal < columnaInicial) ? -1 : 0;

    int fila = filaInicial + incrementoFila;
    int columna = columnaInicial + incrementoColumna;

    while (fila != filaFinal || columna != columnaFinal) {
        if (casillaOcupada(fila, columna)) return false;
        fila += incrementoFila;
        columna += incrementoColumna;
    }
    return true;
}
void Tablero::Selector(int x, int y) {
    int fila = (x - 36) / 90;
    int columna = (y - 36) / 90;

    if (fila < 0 || fila >= FILAS_TABLERO || columna < 0 || columna >= COLUMNAS_TABLERO) {
        cout << "Clic fuera del tablero.\n";
        return;
    }

    Jugador& j1 = GetJugador1();
    Jugador& j2 = GetJugador2();

    bool turno1 = j1.getTurno();
    bool turno2 = j2.getTurno();

    if (turno1 == turno2) {
        cout << "Error: turnos en conflicto.\n";
        return;
    }

    if (j2.EsMaquina() && turno2) return;

    Pieza* pieza = getPieza(fila, columna);

    if (!seleccionActiva) {
        if (pieza && pieza->getColor() == (turno1 ? ColorBlancas : ColorNegras)) {
            piezaOrigen = pieza;
            casOrigen = { fila, columna };
            seleccionActiva = true;
            cout << "Pieza seleccionada en (" << fila << ", " << columna << ")\n";
        }
        else {
            cout << "Casilla vacía o pieza del oponente.\n";
        }
    }
    else {
        if (fila == casOrigen.fila && columna == casOrigen.columna) {
            cout << "Deseleccionada.\n";
            seleccionActiva = false;
            piezaOrigen = nullptr;
            return;
        }

        casillas[casOrigen.fila][casOrigen.columna] = nullptr;
        casillas[fila][columna] = piezaOrigen;
        piezaOrigen->setFila(fila);
        piezaOrigen->setColumna(columna);
        piezaOrigen->setPosicion(coordenadaSobreTablero[fila * COLUMNAS_TABLERO + columna]);

        cout << "Movimiento a (" << fila << ", " << columna << ")\n";

        seleccionActiva = false;
        piezaOrigen = nullptr;

        j1.SetTurno(!turno1);
        j2.SetTurno(!turno2);
    }
}
void Tablero::ValidarMovimiento(bool turnoBlancas, bool& movimientoPermitido) {
    movimientoPermitido = false;

    if (!piezaOrigen) {
        cout << "No hay pieza seleccionada.\n";
        return;
    }

    auto movimientos = piezaOrigen->getMovimientosPermitidos(casOrigen.fila, casOrigen.columna, turnoBlancas);

    for (const Casilla& mov : movimientos) {
        if (mov.fila == casSeleccion.fila && mov.columna == casSeleccion.columna) {
            Pieza* tmp = casillas[mov.fila][mov.columna];
            casillas[mov.fila][mov.columna] = piezaOrigen;
            casillas[casOrigen.fila][casOrigen.columna] = nullptr;

            enJaque = estaEnJaque(!turnoBlancas);

            casillas[casOrigen.fila][casOrigen.columna] = piezaOrigen;
            casillas[mov.fila][mov.columna] = tmp;

            if (!enJaque) {
                movimientoPermitido = true;
                return;
            }
            else {
                cout << "No permitido: el rey quedaría en jaque.\n";
            }
        }
    }
}

bool Tablero::estaEnJaque(bool turnoBlancas) {
    int colorAtacante = turnoBlancas ? ColorNegras : ColorBlancas;
    Casilla rey = encontrarRey(turnoBlancas);
    if (rey.fila == -1) return true;

    for (int fila = 0; fila < FILAS_TABLERO; fila++) {
        for (int col = 0; col < COLUMNAS_TABLERO; col++) {
            Pieza* p = casillas[fila][col];
            if (p && p->getColor() == colorAtacante) {
                auto movs = p->getMovimientosPermitidos(fila, col, !turnoBlancas);
                for (const auto& m : movs) {
                    if (m.fila == rey.fila && m.columna == rey.columna) return true;
                }
            }
        }
    }
    return false;
}

bool Tablero::estaEnJaqueMate(bool turnoBlancas) {
    if (!estaEnJaque(turnoBlancas)) return false;

    int colorPropio = turnoBlancas ? ColorBlancas : ColorNegras;

    for (int fila = 0; fila < FILAS_TABLERO; fila++) {
        for (int col = 0; col < COLUMNAS_TABLERO; col++) {
            Pieza* p = casillas[fila][col];
            if (p && p->getColor() == colorPropio) {
                auto movs = p->getMovimientosPermitidos(fila, col, turnoBlancas);
                for (const auto& mov : movs) {
                    Pieza* tmp = casillas[mov.fila][mov.columna];
                    casillas[mov.fila][mov.columna] = p;
                    casillas[fila][col] = nullptr;

                    bool sigueEnJaque = estaEnJaque(turnoBlancas);

                    casillas[fila][col] = p;
                    casillas[mov.fila][mov.columna] = tmp;

                    if (!sigueEnJaque) return false;
                }
            }
        }
    }

    cout << "¡Jaque mate!\n";
    return true;
}

Casilla Tablero::encontrarRey(bool turnoBlancas) {
    int color = turnoBlancas ? ColorBlancas : ColorNegras;
    for (int fila = 0; fila < FILAS_TABLERO; fila++) {
        for (int col = 0; col < COLUMNAS_TABLERO; col++) {
            Pieza* p = casillas[fila][col];
            if (p && p->getTipo() == TipoPieza::Rey && p->getColor() == color)
                return { col, fila };
        }
    }
    return { -1, -1 };
}
Pieza* Tablero::HayCoronacion(Casilla casillaDestino, Pieza* tipoPieza) {
    if (!tipoPieza || tipoPieza->getTipo() != TipoPieza::Peon) return nullptr;

    if (tipoPieza->getColor() == ColorBlancas && casillaDestino.fila == 0)
        return CoronacionDeseada(tipoPieza, casillaDestino, true);
    if (tipoPieza->getColor() == ColorNegras && casillaDestino.fila == FILAS_TABLERO - 1)
        return CoronacionDeseada(tipoPieza, casillaDestino, false);

    return nullptr;
}

Pieza* Tablero::CoronacionDeseada(Pieza* actual, Casilla destino, bool blancas) {
    char opcion;
    int color = blancas ? ColorBlancas : ColorNegras;

    cout << "Selecciona pieza para coronar: T (Torre), C (Caballo), A (Alfil), R (Reina), Z (Canciller), X (Arzobispo): ";
    cin >> opcion;
    opcion = toupper(opcion);

    switch (opcion) {
    case 'T': return new Torre(actual->getPosicion(), color, destino.fila, destino.columna, *this);
    case 'C': return new Caballo(actual->getPosicion(), color, destino.fila, destino.columna);
    case 'A': return new Alfil(actual->getPosicion(), color, destino.fila, destino.columna, *this);
    case 'R': return new Reina(actual->getPosicion(), color, destino.fila, destino.columna, *this);
    case 'Z': return new Canciller(actual->getPosicion(), color, destino.fila, destino.columna, *this);
    case 'X': return new Arzobispo(actual->getPosicion(), color, destino.fila, destino.columna, *this);
    default:
        cout << "Selección inválida. Coronado como Reina.\n";
        return new Reina(actual->getPosicion(), color, destino.fila, destino.columna, *this);
    }
}

std::string Tablero::tipoPiezaToString(TipoPieza tipo) {
    switch (tipo) {
    case TipoPieza::Torre: return "Torre";
    case TipoPieza::Caballo: return "Caballo";
    case TipoPieza::Alfil: return "Alfil";
    case TipoPieza::Rey: return "Rey";
    case TipoPieza::Reina: return "Reina";
    case TipoPieza::Peon: return "Peon";
    case TipoPieza::Arzobispo: return "Arzobispo";
    case TipoPieza::Canciller: return "Canciller";
    default: return "Desconocido";
    }
}
void Tablero::realizarMovimientoMaquina() {
    if (jugador2.EsMaquina() && jugador2.getTurno()) {
        std::vector<std::pair<Pieza*, Casilla>> movimientosPosibles;

        for (int fila = 0; fila < FILAS_TABLERO; fila++) {
            for (int col = 0; col < COLUMNAS_TABLERO; col++) {
                Pieza* p = casillas[fila][col];
                if (p && p->getColor() == ColorNegras) {
                    auto movs = p->getMovimientosPermitidos(fila, col, false);
                    for (const auto& m : movs) {
                        movimientosPosibles.emplace_back(p, m);
                    }
                }
            }
        }

        if (movimientosPosibles.empty()) {
            std::cout << "La máquina no puede mover.\n";
            return;
        }

        std::pair<Pieza*, Casilla> elegido;
        if (nivelDificultad == 0) {
            std::random_shuffle(movimientosPosibles.begin(), movimientosPosibles.end());
            elegido = movimientosPosibles.front();
        }
        else {
            std::vector<std::pair<Pieza*, Casilla>> capturas;
            for (const auto& mov : movimientosPosibles) {
                if (casillas[mov.second.fila][mov.second.columna] &&
                    casillas[mov.second.fila][mov.second.columna]->getColor() == ColorBlancas) {
                    capturas.push_back(mov);
                }
            }
            if (!capturas.empty()) {
                std::random_shuffle(capturas.begin(), capturas.end());
                elegido = capturas.front();
            }
            else {
                std::random_shuffle(movimientosPosibles.begin(), movimientosPosibles.end());
                elegido = movimientosPosibles.front();
            }
        }

        Pieza* pieza = elegido.first;
        Casilla destino = elegido.second;
        int filaOrigen = pieza->getFila();
        int colOrigen = pieza->getColumna();

        if (casillas[destino.fila][destino.columna]) {
            delete casillas[destino.fila][destino.columna];
        }

        casillas[filaOrigen][colOrigen] = nullptr;
        casillas[destino.fila][destino.columna] = pieza;

        pieza->setFila(destino.fila);
        pieza->setColumna(destino.columna);
        pieza->setPosicion(coordenadaSobreTablero[destino.fila * COLUMNAS_TABLERO + destino.columna]);

        std::cout << "Máquina movió (" << colOrigen << ", " << filaOrigen
            << ") → (" << destino.columna << ", " << destino.fila << ")\n";

        // Coronación automática
        if (pieza->getTipo() == TipoPieza::Peon && destino.fila == FILAS_TABLERO - 1) {
            delete pieza;
            pieza = new Reina(coordenadaSobreTablero[destino.fila * COLUMNAS_TABLERO + destino.columna],
                ColorNegras, destino.fila, destino.columna, *this);
            casillas[destino.fila][destino.columna] = pieza;
            std::cout << "Peón coronado automáticamente a Reina.\n";
        }

        jugador2.SetTurno(false);
        jugador1.SetTurno(true);
    }
}
