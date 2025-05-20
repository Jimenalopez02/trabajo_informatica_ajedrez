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
        float x, y, width, height; // Posici�n y tama�o del bot�n
    };

    std::vector<MenuItem> items;   // Contenedor de los elementos del men�
    int selectedMode;              // Indica el �tem seleccionado
    bool isActive;                 // Si el men� est� activo o no

public:
    // Constructor
    Menu();

    // Agregar un �tem al men�
    void AddItem(const std::string& label, int mode);

    // Dibujar el men� en la pantalla
    void Draw();

    // Manejar el clic del mouse sobre los �tems del men�
    void HandleMouseClick(int x, int y);

    // Obtener el modo seleccionado
    int GetSelectedMode() const;

    // Verificar si el men� est� activo
    bool IsActive() const;

    // Desactivar el men�
    void Deactivate();

    // Activar el men�
    void Activate();
};
