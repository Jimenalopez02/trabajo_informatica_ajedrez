#pragma once
#include "Tablero.h"

class Juego {
private:
    Tablero tablero;
    bool turnoBlancas;

public:
    Juego();
    void iniciar();
    void jugar();
};

