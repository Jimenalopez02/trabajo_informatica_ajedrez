
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

public:
    Jugador(const std::string& nombre = "", bool maquina = false);
    std::string getNombre() const;
    void setNombre(const std::string& nuevoNombre);
    bool getTurno() const;
    void setTurno(bool t);
    bool EsMaquina() const;
    void setEsMaquina(bool m);
    void agregarPieza(Pieza* p);
    std::vector<Pieza*>& getPiezas();
};


