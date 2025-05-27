#include "freeglut.h"
#include "ETSIDI.h"
#include "Juego.h"

Juego juego;

void OnDraw() {
    juego.actualizar();  // Lógica de reloj y bot
    juego.dibujar();
}

void OnResize(int w, int h) {
    juego.redimensionar(w, h);
}

void OnMouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        juego.manejarClick(x, y);
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(1200, 1000);  // Ancho y alto ajustados
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Ajedrez de Capablanca");

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1200, 0, 1000, -1, 1); // sistema de coordenadas correcto
    glMatrixMode(GL_MODELVIEW);

    ETSIDI::playMusica("sonido/fondo.wav");

    glutDisplayFunc(OnDraw);
    glutReshapeFunc(OnResize);
    glutMouseFunc(OnMouseClick);
    glutMainLoop();

    return 0;
}
