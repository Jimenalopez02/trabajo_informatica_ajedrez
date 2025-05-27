#include "Pieza.h"
#include "ETSIDI.h"

void Pieza::dibujaPieza(float x, float y, float tam) const {
    float escala = 0.8f; // Un 80% del tamaño de la casilla
    float lado = tam * escala;

    ETSIDI::Sprite sprite(obtenerRutaImagen().c_str(), lado, lado);
    sprite.setCenter(lado / 2, lado / 2);      // Centra el sprite en su punto medio
    sprite.setPos(x, y);                       // Lo posiciona directamente en el centro de la casilla

    sprite.draw();
}
