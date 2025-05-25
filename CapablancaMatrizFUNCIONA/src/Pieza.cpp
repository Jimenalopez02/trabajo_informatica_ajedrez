
#include "Pieza.h"
#include "ETSIDI.h"

void Pieza::dibujaPieza(float x, float y, float tam) const {
    float escala = 0.3f;
    float lado = tam * escala;
    ETSIDI::Sprite sprite(obtenerRutaImagen().c_str(), lado, lado);
    sprite.setCenter(lado / 2, lado / 2);
    sprite.setPos(x - tam * 0.3f, y-tam * 0.3f); // Mueve 5% del tamaño a la izquierda

    sprite.draw();
}
