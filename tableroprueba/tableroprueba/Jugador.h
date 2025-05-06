#pragma once
#include <string>
#include <vector>

class Pieza;  

class Jugador {
private:
    std::string nombre;
    bool turno = false;
    bool esMaquina = false;
    std::vector<Pieza*> piezas;  // Relaci�n directa con  objetos Pieza

public:
    // Constructor
    Jugador(const std::string& nombre = "", bool maquina = false);

    // Nombre
    std::string getNombre() const;
    void setNombre(const std::string& nuevoNombre);

    // Turno
    bool getTurno() const;
    void setTurno(bool t);

    // Maquina
    bool EsMaquina() const;
    void setEsMaquina(bool m);

    // Piezas
    void agregarPieza(Pieza* p);
    std::vector<Pieza*>& getPiezas();
};


