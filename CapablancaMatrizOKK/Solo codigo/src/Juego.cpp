#include "Juego.h"
#include "freeglut.h"
#include <iostream>

Juego::Juego()
    : jugador1("Blancas", false, ColorBlancas),
    jugador2("Negras", false, ColorNegras),
    tablero(jugador1, jugador2),
    turnoBlancas(true),
    haySeleccion(false),
    casillaOrigen({ -1, -1 }) {
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
            // Verifica si el rey enemigo está en jaque
            bool enJaque = turnoBlancas
                ? tablero.estaEnJaque(jugador2, jugador1)
                : tablero.estaEnJaque(jugador1, jugador2);

            if (enJaque) {
                std::cout << "¡Rey en jaque!\n";
            }

            turnoBlancas = !turnoBlancas;
            std::cout << "Movimiento válido\n";
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

