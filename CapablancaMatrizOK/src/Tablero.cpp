#include "Tablero.h"
#include "Peon.h"
#include "Caballo.h"
#include "Torre.h"
#include "Canciller.h"
#include "Alfil.h"
#include "Arzobispo.h"
#include "Reina.h"
#include "Rey.h"
#include "ETSIDI.h"
#include <iostream>

Tablero::Tablero(const Jugador& j1, const Jugador& j2)
    : jugador1(j1), jugador2(j2) {
    casillas.resize(FILAS_TABLERO, std::vector<Pieza*>(COLUMNAS_TABLERO, nullptr));
    CasillasaCoordenadas();
    inicializaTablero();
}

Tablero::~Tablero() {
    for (auto& fila : casillas)
        for (auto& p : fila)
            delete p;
}

void Tablero::CasillasaCoordenadas() {
    int k = 0;
    for (int fila = 0; fila < FILAS_TABLERO; fila++) {
        for (int col = 0; col < COLUMNAS_TABLERO; col++) {
            coordenadaSobreTablero[k].x = MARGEN_X + col * TAM_CASILLA + TAM_CASILLA / 2.0f;
            coordenadaSobreTablero[k].y = MARGEN_Y + fila * TAM_CASILLA + TAM_CASILLA / 2.0f;
            k++;
        }
    }
}

void Tablero::inicializaTablero() {
    for (int col = 0; col < 10; ++col) {
        Pieza* peonBlanco = new Peon(ColorBlancas, 1, col, *this);
        casillas[1][col] = peonBlanco;
        jugador1.agregarPieza(peonBlanco);

        Pieza* peonNegro = new Peon(ColorNegras, 6, col, *this);
        casillas[6][col] = peonNegro;
        jugador2.agregarPieza(peonNegro);
    }

    // Blancas
    casillas[0][0] = new Torre(ColorBlancas, 0, 0, *this);
    casillas[0][1] = new Caballo(ColorBlancas, 0, 1, *this);
    casillas[0][2] = new Canciller(ColorBlancas, 0, 2, *this);
    casillas[0][3] = new Alfil(ColorBlancas, 0, 3, *this);
    casillas[0][4] = new Reina(ColorBlancas, 0, 4, *this);
    casillas[0][5] = new Rey(ColorBlancas, 0, 5, *this);
    casillas[0][6] = new Alfil(ColorBlancas, 0, 6, *this);
    casillas[0][7] = new Arzobispo(ColorBlancas, 0, 7, *this);
    casillas[0][8] = new Caballo(ColorBlancas, 0, 8, *this);
    casillas[0][9] = new Torre(ColorBlancas, 0, 9, *this);

    // Negras
    casillas[7][0] = new Torre(ColorNegras, 7, 0, *this);
    casillas[7][1] = new Caballo(ColorNegras, 7, 1, *this);
    casillas[7][2] = new Canciller(ColorNegras, 7, 2, *this);
    casillas[7][3] = new Alfil(ColorNegras, 7, 3, *this);
    casillas[7][4] = new Reina(ColorNegras, 7, 4, *this);
    casillas[7][5] = new Rey(ColorNegras, 7, 5, *this);
    casillas[7][6] = new Alfil(ColorNegras, 7, 6, *this);
    casillas[7][7] = new Arzobispo(ColorNegras, 7, 7, *this);
    casillas[7][8] = new Caballo(ColorNegras, 7, 8, *this);
    casillas[7][9] = new Torre(ColorNegras, 7, 9, *this);
}

void Tablero::dibujar() const {
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    GLuint textura = ETSIDI::getTexture("imagenes/tablero_etsidi.png").id;
    glBindTexture(GL_TEXTURE_2D, textura);

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glTexCoord2d(0, 1); glVertex2f(MARGEN_X, MARGEN_Y);
    glTexCoord2d(1, 1); glVertex2f(MARGEN_X + TAM_CASILLA * COLUMNAS_TABLERO, MARGEN_Y);
    glTexCoord2d(1, 0); glVertex2f(MARGEN_X + TAM_CASILLA * COLUMNAS_TABLERO, MARGEN_Y + TAM_CASILLA * FILAS_TABLERO);
    glTexCoord2d(0, 0); glVertex2f(MARGEN_X, MARGEN_Y + TAM_CASILLA * FILAS_TABLERO);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    for (int fila = 0; fila < FILAS_TABLERO; fila++) {
        for (int col = 0; col < COLUMNAS_TABLERO; col++) {
            if (casillas[fila][col]) {
                int index = fila * COLUMNAS_TABLERO + col;
                float x = coordenadaSobreTablero[index].x;
                float y = coordenadaSobreTablero[index].y;
                casillas[fila][col]->dibujaPieza(x, y, TAM_CASILLA);
            }
        }
    }
}

Pieza* Tablero::getPieza(int fila, int columna) {
    if (fila < 0 || fila >= FILAS_TABLERO || columna < 0 || columna >= COLUMNAS_TABLERO)
        return nullptr;
    return casillas[fila][columna];
}

void Tablero::moverPieza(const Casilla& origen, const Casilla& destino) {
    Pieza* pieza = casillas[origen.fila][origen.columna];
    if (!pieza) return;

    pieza->setFila(destino.fila);
    pieza->setColumna(destino.columna);

    if (casillas[destino.fila][destino.columna] != nullptr)
        delete casillas[destino.fila][destino.columna];

    casillas[destino.fila][destino.columna] = pieza;
    casillas[origen.fila][origen.columna] = nullptr;
}

bool Tablero::casillaOcupada(int fila, int columna) const {
    if (fila < 0 || fila >= FILAS_TABLERO || columna < 0 || columna >= COLUMNAS_TABLERO)
        return false;
    return casillas[fila][columna] != nullptr;
}

bool Tablero::hayPiezaOponente(int fila, int columna, bool turnoBlancas) const {
    if (fila < 0 || fila >= FILAS_TABLERO || columna < 0 || columna >= COLUMNAS_TABLERO)
        return false;

    Pieza* p = casillas[fila][columna];
    if (!p) return false;

    return p->getColor() != (turnoBlancas ? ColorBlancas : ColorNegras);
}

std::vector<Casilla> Tablero::obtenerMovimientosPermitidos(int fila, int columna, bool turnoBlancas) const {
    if (fila < 0 || fila >= FILAS_TABLERO || columna < 0 || columna >= COLUMNAS_TABLERO)
        return {};

    Pieza* p = casillas[fila][columna];
    if (!p) return {};

    if ((turnoBlancas && p->getColor() != ColorBlancas) ||
        (!turnoBlancas && p->getColor() != ColorNegras))
        return {};

    return p->getMovimientosPermitidos(p->getFila(), p->getColumna(), turnoBlancas);
}


