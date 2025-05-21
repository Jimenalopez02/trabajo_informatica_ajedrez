#include "menu.h"
#include <iostream>
#include <freeglut.h>

// Variables globales
Menu* menu;  // Instancia de la clase Menu
bool gameStarted = false;  // Bandera para controlar si el juego ha comenzado
// Funci�n de renderizado
// Funci�n de renderizado
void OnDraw() {
    glClear(GL_COLOR_BUFFER_BIT);  // Limpiar la pantalla

    if (gameStarted) {
        // Dibujar la pantalla del juego
        glColor3f(1.0f, 0.0f, 0.0f);  // Rojo para la pantalla de "Juego Iniciado"
        glPushMatrix();
        glTranslatef(-0.5f, 0.0f, 0.0f);  // Centrar el texto
        glScalef(0.01f, 0.01f, 1.0f);
        std::string title = "�Juego Iniciado!";
        for (char c : title) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
        }
        glPopMatrix();
    }
    else {
        // Dibujar el men�
        menu->Draw();
    }

    glutSwapBuffers();  // Intercambiar los buffers para mostrar lo que hemos dibujado
}

// Funci�n para manejar el teclado (seleccionar opciones)
void OnKeyboardDown(unsigned char key, int x, int y) {
    menu->HandleKeyboardInput(key);

    if (key == '\r') {  // 'Enter' para seleccionar la opci�n
        int selected = menu->GetSelectedMode();
        switch (selected) {
        case 0:
            std::cout << "Iniciar juego..." << std::endl;
            gameStarted = true;  // Cambiar a la pantalla de juego
            break;
        case 1:
            std::cout << "Salir..." << std::endl;
            exit(0);  // Cerrar el programa
            break;
        default:
            break;
        }
    }
}
// Funci�n para manejar el rat�n (clics en el men�)
void OnMouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        menu->HandleMouseClick(x, y);  // Manejar clic en el men�
    }
}

// Funci�n principal
int main(int argc, char** argv) {
    // Inicializaci�n de GLUT
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Ajedrez - Men�");

    // Crear el objeto Menu y agregar �tems
    menu = new Menu();
    menu->AddItem("Iniciar Juego", 0);
    menu->AddItem("Salir", 1);

    // Configuraci�n de callbacks
    glutDisplayFunc(OnDraw);
    glutKeyboardFunc(OnKeyboardDown);
    glutMouseFunc(OnMouseClick);

    // Configuraci�n OpenGL
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Fondo oscuro

    // Iniciar el ciclo de GLUT
    glutMainLoop();

    return 0;
}