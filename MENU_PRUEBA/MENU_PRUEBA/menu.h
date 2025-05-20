#pragma once
#include"freeglut.h"
#include "ETSIDI.h"
#include <string>
#include <vector>

class Menu {
private:
    struct MenuItem {
        std::string label;
        int mode;
        float x, y, width, height; // Posición y tamaño del botón
    };

    std::vector<MenuItem> items;   // Contenedor de los elementos del menú
    int selectedMode;              // Indica el ítem seleccionado
    bool isActive;                 // Si el menú está activo o no

public:
    // Constructor
    Menu();

    // Agregar un ítem al menú
    void AddItem(const std::string& label, int mode);

    // Dibujar el menú en la pantalla
    void Draw();

    // Manejar el clic del mouse sobre los ítems del menú
    void HandleMouseClick(int x, int y);

    // Obtener el modo seleccionado
    int GetSelectedMode() const;

    // Verificar si el menú está activo
    bool IsActive() const;

    // Desactivar el menú
    void Deactivate();

    // Activar el menú
    void Activate();
};
