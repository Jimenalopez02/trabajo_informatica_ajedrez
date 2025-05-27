#include "Juego.h"
#include "freeglut.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Juego::Juego()
    : jugador1("Blancas", false, ColorBlancas),
    jugador2("Negras", false, ColorNegras),
    tablero(jugador1, jugador2),
    turnoBlancas(true),
    haySeleccion(false),
    casillaOrigen({ -1, -1 }) {
    iniciarTurno();
}

void Juego::dibujar() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    tablero.dibujar();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 1.0f, 0.0f, 0.3f);

    for (const Casilla& c : movimientosValidos) {
        float x = MARGEN_X + c.columna * TAM_CASILLA;
        float y = MARGEN_Y + c.fila * TAM_CASILLA;

        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + TAM_CASILLA, y);
        glVertex2f(x + TAM_CASILLA, y + TAM_CASILLA);
        glVertex2f(x, y + TAM_CASILLA);
        glEnd();
    }

    glDisable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glutSwapBuffers();
}

void Juego::manejarClick(int x, int y) {
    if (!turnoBlancas) return; // Ignorar clics si es turno del bot

    int fila = (1000 - y - MARGEN_Y) / TAM_CASILLA;
    int columna = (x - MARGEN_X) / TAM_CASILLA;

    if (fila < 0 || fila >= FILAS_TABLERO || columna < 0 || columna >= COLUMNAS_TABLERO)
        return;

    Jugador& jugadorActual = turnoBlancas ? jugador1 : jugador2;
    Jugador& jugadorOponente = turnoBlancas ? jugador2 : jugador1;
    Pieza* pieza = tablero.getPieza(fila, columna);

    if (!haySeleccion) {
        if (pieza && pieza->getColor() == jugadorActual.getColor()) {
            casillaOrigen = { fila, columna };
            movimientosValidos = tablero.obtenerMovimientosPermitidos(fila, columna, turnoBlancas);

            if (!movimientosValidos.empty()) {
                haySeleccion = true;
                std::cout << "Pieza seleccionada en (" << fila << ", " << columna << ")\n";
            }
        }
    }
    else {
        Casilla destino = { fila, columna };
        bool valido = false;
        for (const auto& mov : movimientosValidos) {
            if (mov.fila == destino.fila && mov.columna == destino.columna) {
                valido = true;
                break;
            }
        }

        if ((valido && tablero.esMovimientoLegal(casillaOrigen, destino, jugadorActual, jugadorOponente))) {
            Pieza* destinoPieza = tablero.getPieza(destino.fila, destino.columna);
            if (destinoPieza && destinoPieza->getTipo() == TipoPieza::Rey &&
                destinoPieza->getColor() == pieza->getColor()) {
                std::cout << "No puedes comerte tu propio rey.\n";
                return;
            }
            tablero.moverPieza(casillaOrigen, destino);
            bool enJaque = turnoBlancas
                ? tablero.estaEnJaque(jugador2, jugador1)
                : tablero.estaEnJaque(jugador1, jugador2);

            if (enJaque) {
                std::cout << "¡Rey en jaque!\n";
            }

            turnoBlancas = !turnoBlancas;
            iniciarTurno(); // Reiniciar temporizador
        }
        else if (valido) {
            std::cout << "Ese movimiento dejaría a tu rey en jaque. No permitido.\n";
        }
        else {
            std::cout << "Movimiento inválido\n";
        }

        haySeleccion = false;
        movimientosValidos.clear();
        glutPostRedisplay();
    }
}

void Juego::redimensionar(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void Juego::iniciarTurno() {
    tiempoInicioTurno = std::chrono::steady_clock::now();
}

bool Juego::tiempoAgotado() {
    auto ahora = std::chrono::steady_clock::now();
    int transcurrido = std::chrono::duration_cast<std::chrono::seconds>(ahora - tiempoInicioTurno).count();
    return transcurrido >= TIEMPO_MAXIMO_SEGUNDOS;
}

bool Juego::esBotTurno() const {
    return !turnoBlancas;
}

void Juego::actualizar() {
    if (tiempoAgotado()) {
        std::cout << "¡Tiempo agotado!\n";
        turnoBlancas = !turnoBlancas;
        iniciarTurno();
    }

    if (esBotTurno()) {
        moverBot();
    }
}

std::vector<Movimiento> Juego::obtenerMovimientosBot() {
    std::vector<Movimiento> movimientos;

    for (int fila = 0; fila < FILAS_TABLERO; ++fila) {
        for (int col = 0; col < COLUMNAS_TABLERO; ++col) {
            Pieza* p = tablero.getPieza(fila, col);
            if (p && p->getColor() == jugador2.getColor()) {
                std::vector<Casilla> destinos = tablero.obtenerMovimientosPermitidos(fila, col, false);
                for (const Casilla& destino : destinos) {
                    Movimiento mov;
                    mov.desdeFila = fila;
                    mov.desdeColumna = col;
                    mov.hastaFila = destino.fila;
                    mov.hastaColumna = destino.columna;
                    movimientos.push_back(mov);
                }
            }
        }
    }

    return movimientos;
}

void Juego::moverBot() {
    std::vector<Movimiento> movimientos = obtenerMovimientosBot();
    if (movimientos.empty()) {
        std::cout << "El bot no tiene movimientos\n";
        return;
    }

    std::srand(std::time(nullptr));
    Movimiento elegido = movimientos[std::rand() % movimientos.size()];
    Casilla origen = { elegido.desdeFila, elegido.desdeColumna };
    Casilla destino = { elegido.hastaFila, elegido.hastaColumna };

    tablero.moverPieza(origen, destino);
    std::cout << "Bot movió de (" << origen.fila << ", " << origen.columna << ") a ("
        << destino.fila << ", " << destino.columna << ")\n";

    if (tablero.estaEnJaque(jugador1, jugador2)) {
        std::cout << "¡Rey humano en jaque!\n";
    }

    turnoBlancas = true;
    iniciarTurno();
    glutPostRedisplay();
}
