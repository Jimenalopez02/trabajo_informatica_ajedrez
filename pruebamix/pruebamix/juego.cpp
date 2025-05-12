#include "Juego.h"
#include <iostream>
#include <string>
#include <cctype>

Juego::Juego() : turnoBlancas(true) {}

void Juego::iniciar() {
    tablero.inicializar();
}

void Juego::jugar() {
    while (true) {
        tablero.mostrar();
        std::cout << "\nTurno de " << (turnoBlancas ? "blancas" : "negras") << ".\n";

        std::string origenStr, destinoStr;
        std::cout << "Ingrese la casilla de origen (ej. e2): ";
        std::cin >> origenStr;
        std::cout << "Ingrese la casilla de destino (ej. e4): ";
        std::cin >> destinoStr;

        // Validación básica de entrada
        if (origenStr.length() < 2 || destinoStr.length() < 2) {
            std::cout << "Entrada inválida.\n";
            continue;
        }

        int colOrigen = origenStr[0] - 'a';
        int filaOrigen = 7 - (origenStr[1] - '1');
        int colDestino = destinoStr[0] - 'a';
        int filaDestino = 7 - (destinoStr[1] - '1');


        if (colOrigen < 0 || colOrigen >= 10 || filaOrigen < 0 || filaOrigen >= 8 ||
            colDestino < 0 || colDestino >= 10 || filaDestino < 0 || filaDestino >= 8) {
            std::cout << "Coordenadas fuera de rango.\n";
            continue;
        }

        Pieza* pieza = tablero.getPieza(filaOrigen, colOrigen);
        if (!pieza) {
            std::cout << "No hay pieza en esa casilla.\n";
            continue;
        }

        // Verificar color de la pieza
        if ((turnoBlancas && pieza->getColor() != Color::Blancas) ||
            (!turnoBlancas && pieza->getColor() != Color::Negras)) {
            std::cout << "Esa pieza no te pertenece.\n";
            continue;
        }

        // Obtener movimientos válidos
        std::vector<Casilla> movs = pieza->getMovimientosPermitidos(tablero.getCasillas());
        bool esMovimientoValido = false;
        std::cout << "Destino: " << filaDestino << "," << colDestino << std::endl;
        for (const Casilla& mov : movs) {
            if (mov.fila == filaDestino && mov.columna == colDestino) {
                esMovimientoValido = true;
                break;
            }
        }

        if (!esMovimientoValido) {
            std::cout << "Movimiento inválido.\n";
            continue;
        }
        std::cout << "Movimiento realizado.\n";
        turnoBlancas = !turnoBlancas;

        // Mover la pieza
        tablero.moverPieza(filaOrigen, colOrigen, filaDestino, colDestino);
        turnoBlancas = !turnoBlancas; // Cambiar turno
    }
}
