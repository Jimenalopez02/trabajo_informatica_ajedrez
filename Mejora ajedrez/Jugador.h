
#pragma once
#include <string>
#include <vector>

class Pieza; // Declaración adelantada

enum Color {
    BLANCO = 0,
    NEGRO = 1
};
class Jugador {
private:
    std::string nombre;
    bool esMaquina;
    std::vector<Pieza*> piezas;
    Color color;  // 0 = blanco, 1 = negro (puedes usar un enum para más claridad)

public:
    Jugador(const std::string& nombre = "", bool maquina = false, Color color = BLANCO)
        : nombre(nombre), esMaquina(maquina), color(color) {
    }

    std::string getNombre() const { return nombre; }
    void setNombre(const std::string& nuevoNombre) { nombre = nuevoNombre; }

    bool EsMaquina() const { return esMaquina; }
    void setEsMaquina(bool m) { esMaquina = m; }

    void agregarPieza(Pieza* p) { piezas.push_back(p); }

    std::vector<Pieza*>& getPiezas() { return piezas; }
    const std::vector<Pieza*>& getPiezas() const { return piezas; }

    int getColor() const { return color; }
};


