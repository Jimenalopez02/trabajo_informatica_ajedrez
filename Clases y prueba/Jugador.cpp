/*#include "Jugador.h"
#include "Pieza.h"

Jugador::Jugador(const std::string& nombre, bool maquina)
    : nombre(nombre), esMaquina(maquina), turno(false) {
}

std::string Jugador::getNombre() const {
    return nombre;
}

void Jugador::setNombre(const std::string& nuevoNombre) {
    nombre = nuevoNombre;
}

bool Jugador::getTurno() const {
    return turno;
}

void Jugador::setTurno(bool t) {
    turno = t;
}

bool Jugador::EsMaquina() const {
    return esMaquina;
}

void Jugador::setEsMaquina(bool m) {
    esMaquina = m;
}

void Jugador::agregarPieza(Pieza* p) {
    piezas.push_back(p);
}

std::vector<Pieza*>& Jugador::getPiezas() {
    return piezas;
}
#include "Jugador.h"

Jugador::Jugador(const std::string& nombre, bool maquina)
    : nombre(nombre), turno(false), esMaquina(maquina) {
}

std::string Jugador::getNombre() const { return nombre; }
void Jugador::setNombre(const std::string& nuevoNombre) { nombre = nuevoNombre; }
bool Jugador::getTurno() const { return turno; }
void Jugador::setTurno(bool t) { turno = t; }
bool Jugador::EsMaquina() const { return esMaquina; }
void Jugador::setEsMaquina(bool m) { esMaquina = m; }
void Jugador::agregarPieza(Pieza* p) { piezas.push_back(p); }
std::vector<Pieza*>& Jugador::getPiezas() { return piezas; }*/