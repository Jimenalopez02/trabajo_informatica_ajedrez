#include "menu.h"
#include <iostream>
#include "freeglut.h"


// Constructor
Menu::Menu() : selectedMode(0), isActive(true) {}

// Agregar un �tem al men�
void Menu::AddItem(const std::string& label, int mode) {
    float yOffset = -0.2f * items.size(); // Espaciado entre botones
    items.push_back({ label, mode, -0.5f, 0.5f + yOffset, 1.0f, 0.15f });
}

// Dibujar el men� en la pantalla
void Menu::Draw() {
    if (!isActive) return;

    // Configuraci�n para ortograf�a 2D
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Desactivar iluminaci�n y otros efectos 3D
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    // Fondo de color degradado
    glBegin(GL_QUADS);
    glColor3f(0.05f, 0.05f, 0.15f); // Azul oscuro
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glColor3f(0.15f, 0.05f, 0.2f); // Morado oscuro
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();

    // T�tulo del juego
    glColor3f(1.0f, 0.95f, 0.7f); // Dorado para el t�tulo
    glPushMatrix();
    glTranslatef(-0.7f, 0.8f, 0.0f);  // Posicionar
    glScalef(0.002f, 0.002f, 1.0f);   // Escalar tama�o del texto
    std::string title = "Mi Ajedrez";
    for (char c : title) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
    }
    glPopMatrix();

    // Dibujar botones
    for (const auto& item : items) {
        // Sombra para el bot�n
        glBegin(GL_QUADS);
        glColor3f(0.12f, 0.12f, 0.25f); // Color de la sombra
        glVertex2f(item.x + 0.01f, item.y - 0.01f);
        glVertex2f(item.x + item.width + 0.01f, item.y - 0.01f);
        glVertex2f(item.x + item.width + 0.01f, item.y - item.height - 0.01f);
        glVertex2f(item.x + 0.01f, item.y - item.height - 0.01f);
        glEnd();

        // Bot�n con degradado de color
        glBegin(GL_QUADS);
        glColor3f(0.3f, 0.3f, 0.7f); // Color m�s claro en la parte superior
        glVertex2f(item.x, item.y);
        glVertex2f(item.x + item.width, item.y);
        glColor3f(0.2f, 0.2f, 0.4f); // Color m�s oscuro en la parte inferior
        glVertex2f(item.x + item.width, item.y - item.height);
        glVertex2f(item.x, item.y - item.height);
        glEnd();

        // Borde de color brillante
        glLineWidth(1.0f);
        glBegin(GL_LINE_LOOP);
        glColor3f(0.5f, 0.5f, 0.9f); // Azul claro brillante
        glVertex2f(item.x, item.y);
        glVertex2f(item.x + item.width, item.y);
        glVertex2f(item.x + item.width, item.y - item.height);
        glVertex2f(item.x, item.y - item.height);
        glEnd();

        // Texto del bot�n
        glColor3f(0.9f, 0.9f, 1.0f);  // Blanco con un toque azulado
        glRasterPos2f(item.x + 0.05f, item.y - 0.1f);
        for (char c : item.label) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }

    // Restaurar configuraciones GL
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

// Manejar el clic del mouse sobre los �tems del men�
void Menu::HandleMouseClick(int x, int y) {
    // Convertir la posici�n del mouse a coordenadas del men� y verificar si el click est� sobre alg�n bot�n
    // Aqu� se implementar�a la l�gica para seleccionar un �tem del men�
    for (size_t i = 0; i < items.size(); ++i) {
        const auto& item = items[i];
        if (x >= item.x * 800 && x <= (item.x + item.width) * 800 &&
            y >= item.y * 600 && y <= (item.y - item.height) * 600) {
            selectedMode = item.mode;
            std::cout << "Opci�n seleccionada: " << item.label << std::endl;
        }
    }
}

// Obtener el modo seleccionado
int Menu::GetSelectedMode() const {
    return selectedMode;
}

// Verificar si el men� est� activo
bool Menu::IsActive() const {
    return isActive;
}

// Desactivar el men�
void Menu::Deactivate() {
    isActive = false;
}

// Activar el men�
void Menu::Activate() {
    isActive = true;
}
    // Manejo de teclado (navegar por el men�)
    void Menu::HandleKeyboardInput(unsigned char key) {
        if (key == 27) {  // 'Esc' para salir
            exit(0);
        }
        // Si se presiona 'Arriba' o 'Abajo', se cambia la opci�n seleccionada
        if (key == 'w' || key == 'W') {
            selectedMode = (selectedMode - 1 + items.size()) % items.size();
        }
        if (key == 's' || key == 'S') {
            selectedMode = (selectedMode + 1) % items.size();
        }
}