#include <iostream>
#include <string>
#include <cstdlib>  // Para system("cls")
#include "Tablero.h"
#include "Jugador.h"

/*Si quereis probar a jugar solo teneis que ir poniendo las filas y columnas origen y luego destino:
Si quiero que se mueva el peon de la fila 1 y columna 0 a fila 3 columna 0, pongo 1 (enter) 0(enter) 3(enter) 0(enter)
*/
bool salirDelJuego() {
    char respuesta;
    std::cout << "¿Quieres salir del juego? (s/n): ";
    std::cin >> respuesta;
    return respuesta == 's' || respuesta == 'S';
}

int main() {
    Jugador blanco("Blancas");
    Jugador negro("Negras");

    Tablero tablero(blanco, negro);
    tablero.inicializaTablero();

    tablero.mostrarTablero();

    while (true) {
        // Mostrar el jugador activo
        Jugador& jugadorActivo = blanco.getTurno() ? blanco : negro;
        std::cout << "Turno de " << jugadorActivo.getNombre() << " (" << (jugadorActivo.getTurno() ? "Blancas" : "Negras") << ")\n";

        // Pedir al usuario que ingrese el movimiento
        std::cout << "Ingrese el movimiento (origen fila origen columna destino fila destino columna) o presione Enter para salir: ";

        int origenFila, origenColumna, destinoFila, destinoColumna;
        std::cin >> origenFila >> origenColumna >> destinoFila >> destinoColumna;

        // Verificar si se presionó Enter para salir
        if (std::cin.fail()) {
            break;
        }

        // Realizar el movimiento
        Casilla origen = { origenFila, origenColumna };
        Casilla destino = { destinoFila, destinoColumna };

        tablero.moverPieza(origen, destino);
        tablero.mostrarTablero();

        // Cambiar el turno
        blanco.setTurno(!blanco.getTurno());
        negro.setTurno(!negro.getTurno());

        // Preguntar si el jugador quiere salir
        if (salirDelJuego()) {
            std::cout << "¡Juego terminado!" << std::endl;
            break;
        }
    }

    return 0;
}