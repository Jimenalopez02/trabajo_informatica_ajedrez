
#pragma once
#include <string>
#include <vector>
class Pieza; // Forward declaration

class Jugador {
private:
    std::string nombre;
    bool turno;
    bool esMaquina;
    std::vector<Pieza*> piezas;
    int color;  // Añadido para determinar el color del jugador (Blanco o Negro)

public:
    Jugador(const std::string& nombre = "", bool maquina = false, int color = 0)
        : nombre(nombre), turno(false), esMaquina(maquina), color(color) {
    }

    std::string getNombre() const { return nombre; }
    void setNombre(const std::string& nuevoNombre) { nombre = nuevoNombre; }

    bool getTurno() const { return turno; }
    void setTurno(bool t) { turno = t; }

    bool EsMaquina() const { return esMaquina; }
    void setEsMaquina(bool m) { esMaquina = m; }

    void agregarPieza(Pieza* p) { piezas.push_back(p); }
    std::vector<Pieza*>& getPiezas() { return piezas; }       
    const std::vector<Pieza*>& getPiezas() const { return piezas;} // Acceso de solo lectura
    int getColor() const { return color; }  // Devuelve el color del jugador (Blanco o Negro)

};


