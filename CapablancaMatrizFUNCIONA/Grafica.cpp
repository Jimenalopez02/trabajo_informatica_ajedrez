#include"freeglut.h"
#include "ETSIDI.h"
#include "Tablero.h"
#include "Jugador.h"
#include "Casilla.h"
#include <iostream>

// ==================== Variables globales =====s q===============
bool haySeleccion = false;
bool turnoBlancas = true;
Casilla casillaOrigen = { -1, -1 };
std::vector<Casilla> movimientosValidos;

Jugador jugador1("Blancas", false, ColorBlancas);
Jugador jugador2("Negras", false, ColorNegras);
Tablero tablero(jugador1, jugador2);

// ==================== Función de dibujo ====================
void OnDraw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    tablero.dibujar();

    // Dibujar resaltado de movimientos válidos
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 1.0f, 0.0f, 0.3f); // Verde translúcido

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

// ==================== Cambio de tamaño ====================
void OnResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

// ==================== Lógica de clic ====================
void OnMouseClick(int button, int state, int x, int y) {
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;

    int fila = (800 - y - MARGEN_Y) / TAM_CASILLA;
    int columna = (x - MARGEN_X) / TAM_CASILLA;

    if (fila < 0 || fila >= FILAS_TABLERO || columna < 0 || columna >= COLUMNAS_TABLERO)
        return;

    Jugador& jugadorActual = turnoBlancas ? jugador1 : jugador2;
    Pieza* pieza = tablero.getPieza(fila, columna);

    std::cout << "Turno de: " << (turnoBlancas ? "Blancas" : "Negras") << std::endl;

    if (!haySeleccion) {
        if (pieza && pieza->getColor() == jugadorActual.getColor()) {
            casillaOrigen = { fila, columna };
            movimientosValidos = tablero.obtenerMovimientosPermitidos(pieza->getFila(), pieza->getColumna(), turnoBlancas);

            if (movimientosValidos.empty()) {
                std::cout << "La pieza no tiene movimientos válidos.\n";
                return;
            }

            haySeleccion = true;
            std::cout << "Pieza seleccionada en (" << fila << ", " << columna << ")\n";
        }
        else {
            std::cout << "No puedes seleccionar esta pieza.\n";
        }
    }
    else {
        Casilla destino = { fila, columna };
        bool movimientoValido = false;

        for (const auto& mov : movimientosValidos) {
            if (mov.fila == destino.fila && mov.columna == destino.columna) {
                movimientoValido = true;
                break;
            }
        }

        if (movimientoValido) {
            tablero.moverPieza(casillaOrigen, destino);
            turnoBlancas = !turnoBlancas;
            std::cout << "Movimiento válido\n";
        }
        else {
            std::cout << "Movimiento inválido\n";
        }

        haySeleccion = false;
        movimientosValidos.clear();
        glutPostRedisplay();
    }
}

// ==================== Función principal ====================
int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Ajedrez de Capablanca");

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 800, 0, 800, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    ETSIDI::playMusica("sonido/fondo.wav");

    glutDisplayFunc(OnDraw);
    glutReshapeFunc(OnResize);
    glutMouseFunc(OnMouseClick);

    glutMainLoop();
    return 0;
}
