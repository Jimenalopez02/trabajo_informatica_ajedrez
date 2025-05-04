#pragma once
// include/tablero.h
#include "freeglut.h"
#include "ETSIDI.h"
#include <stdlib.h>
#include <algorithm> 

Tablero::Tablero(const Jugador& j1, const Jugador& j2)
    : jugador1(j1), jugador2(j2), casillas(8, vector<Pieza*>(10, nullptr)) {
    CasillasaCoordenadas();
    inicializaTablero();
}

Tablero::~Tablero() {
    for (auto& fila : casillas) {
        for (auto& pieza : fila) {
            delete pieza;
        }
    }
}

void Tablero::dibujaPieza() {
    for (auto& fila : casillas) {
        for (auto& pieza : fila) {
            if (pieza != nullptr) {
                pieza->dibujaPieza();
            }
        }
    }
}

Pieza* Tablero::getPieza(int fila, int columna) {
    if (fila < 0 || fila >= 8 || columna < 0 || columna >= 10) {
        return nullptr;
    }
    return casillas[fila][columna];
}

bool Tablero::hayPiezaOponente(int fila, int columna, bool turnoBlancas) const {
    Pieza* pieza = casillas[fila][columna];
    if (pieza == nullptr)
        return false;

    return (turnoBlancas && pieza->getColor() == 1) || (!turnoBlancas && pieza->getColor() == 0);
}



void Tablero::SetJugador1(Jugador jugador1) {
    this->jugador1 = jugador1;
}

void Tablero::SetJugador2(Jugador jugador2) {
    this->jugador2 = jugador2;
}

Jugador Tablero::GetJugador1() {
    return jugador1;
}

Jugador Tablero::GetJugador2() {
    return jugador2;
}

void Tablero::dibuja() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/tablero.png").id);
    glDisable(GL_LIGHTING);
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glTexCoord2d(0, 1); glVertex2f(-1, -1);
    glTexCoord2d(1, 1); glVertex2f(1, -1);
    glTexCoord2d(1, 0); glVertex2f(1, 1);
    glTexCoord2d(0, 0); glVertex2f(-1, 1);
    glEnd();
    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    if (seleccionActiva) {
        DibujarPasosPermitidos();
    }
}

void Tablero::CasillasaCoordenadas() {
    int k = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 8; j++) {
            coordenadaSobreTablero[k].x = 0.93 - 0.186 * i; // Ajuste para 10 columnas
            coordenadaSobreTablero[k].y = -0.675 + 0.23 * j;
            k++;
        }
    }


void Tablero::inicializaTablero() {
        enum { blanco, negro };

        // Coloca las piezas blancas
        casillas[0][0] = new Torre(coordenadaSobreTablero[0 * 10 + 0], blanco, 0, 0, *this);
        casillas[0][1] = new Caballo(coordenadaSobreTablero[0 * 10 + 1], blanco, 0, 1);
        casillas[0][2] = new Alfil(coordenadaSobreTablero[0 * 10 + 2], blanco, 0, 2, *this);
        casillas[0][3] = new Arzobispo(coordenadaSobreTablero[0 * 10 + 3], blanco, 0, 3, *this);
        casillas[0][4] = new Reina(coordenadaSobreTablero[0 * 10 + 4], blanco, 0, 4, *this);
        casillas[0][5] = new Rey(coordenadaSobreTablero[0 * 10 + 5], blanco, 0, 5, *this);
        casillas[0][6] = new Canciller(coordenadaSobreTablero[0 * 10 + 6], blanco, 0, 6, *this);
        casillas[0][7] = new Alfil(coordenadaSobreTablero[0 * 10 + 7], blanco, 0, 7, *this);
        casillas[0][8] = new Caballo(coordenadaSobreTablero[0 * 10 + 8], blanco, 0, 8);
        casillas[0][9] = new Torre(coordenadaSobreTablero[0 * 10 + 9], blanco, 0, 9, *this);

        // Igual para las negras
        casillas[7][0] = new Torre(coordenadaSobreTablero[7 * 10 + 0], negro, 7, 0, *this);
        casillas[7][1] = new Caballo(coordenadaSobreTablero[7 * 10 + 1], negro, 7, 1);
        casillas[7][2] = new Alfil(coordenadaSobreTablero[7 * 10 + 2], negro, 7, 2, *this);
        casillas[7][3] = new Arzobispo(coordenadaSobreTablero[7 * 10 + 3], negro, 7, 3, *this);
        casillas[7][4] = new Reina(coordenadaSobreTablero[7 * 10 + 4], negro, 7, 4, *this);
        casillas[7][5] = new Rey(coordenadaSobreTablero[7 * 10 + 5], negro, 7, 5, *this);
        casillas[7][6] = new Canciller(coordenadaSobreTablero[7 * 10 + 6], negro, 7, 6, *this);
        casillas[7][7] = new Alfil(coordenadaSobreTablero[7 * 10 + 7], negro, 7, 7, *this);
        casillas[7][8] = new Caballo(coordenadaSobreTablero[7 * 10 + 8], negro, 7, 8);
        casillas[7][9] = new Torre(coordenadaSobreTablero[7 * 10 + 9], negro, 7, 9, *this);

        // Peones
        for (int i = 0; i < 10; i++) {
            casillas[1][i] = new Peon(coordenadaSobreTablero[1 * 10 + i], blanco, 1, i, *this);
            casillas[6][i] = new Peon(coordenadaSobreTablero[6 * 10 + i], negro, 6, i, *this);
        }
    }

void Tablero::Selector(int x, int y) {
    if (jugador2.EsMaquina() && jugador2.getTurno()) {
        return; // Salir inmediatamente para bloquear la interacción
    }

    system("cls");
    bool turno1 = jugador1.getTurno();
    bool turno2 = jugador2.getTurno();
    int colorturno;

    if (turno1 == turno2) {
        std::cout << "Error: no puede ser el turno de los dos jugadores a la vez" << std::endl;
        return;
    }

    casSeleccion.columna = (y - 36) / 90;
    casSeleccion.fila = (x - 36) / 90;
    piezaSeleccionada = getPieza(casSeleccion.fila, casSeleccion.columna);
    std::cout << "Has pulsado en la casilla: Columna: (" << casSeleccion.columna << "), Fila: (" << casSeleccion.fila << ")" << std::endl;

    if (turno1) {
        colorturno = ColorBlancas;
        std::cout << "Se dispone a jugar el jugador 1 con las blancas" << std::endl;
    }
    else {
        colorturno = ColorNegras;
        std::cout << "Se dispone a jugar el jugador 2 con las negras" << std::endl;
    }

    if (!seleccionActiva) {
        if (piezaSeleccionada != nullptr && piezaSeleccionada->getColor() == colorturno) {
            casOrigen.fila = casSeleccion.fila;
            casOrigen.columna = casSeleccion.columna;
            piezaOrigen = piezaSeleccionada;
            seleccionActiva = true;
            ETSIDI::play("musica/click.mp3");
            piezaSeleccionada->seleccionActivada = true;
        }
        else {
            std::cout << "Estas no son tus piezas o la casilla está vacía." << std::endl;
        }
    }
    else {
        if (casOrigen.fila == casSeleccion.fila && casOrigen.columna == casSeleccion.columna) {
            std::cout << "Deseleccionando la pieza en la casilla: (" << casOrigen.columna << ", " << casOrigen.fila << ")" << std::endl;
            piezaOrigen = nullptr;
            seleccionActiva = false;
            piezaSeleccionada->seleccionActivada = false;
        }
        else if (piezaSeleccionada != nullptr && piezaSeleccionada->getColor() == piezaOrigen->getColor()) {
            piezaOrigen->seleccionActivada = false;
            casOrigen.fila = casSeleccion.fila;
            casOrigen.columna = casSeleccion.columna;
            piezaOrigen = piezaSeleccionada;
            piezaSeleccionada->seleccionActivada = true;
            std::cout << "Usted ha pinchado en la casilla: Fila: (" << casSeleccion.fila << "), Columna: (" << casSeleccion.columna << ")" << std::endl;
            ETSIDI::play("musica/click.mp3");
        }
        else {
            bool movimientoPermitido = false;

            ValidarMovimiento(turno1, movimientoPermitido);

            if (movimientoPermitido) {
                casDestino = casSeleccion;
                movimientoActivado = true;
                piezaDestino = piezaOrigen;
                piezaDestino->setColumna(casDestino.columna);
                piezaDestino->setFila(casDestino.fila);
                piezaOrigen->seleccionActivada = false;


                // Realizar el movimiento
                Pieza* piezaTemporal = casillas[casDestino.fila][casDestino.columna];
                casillas[casDestino.fila][casDestino.columna] = piezaDestino;
                casillas[casOrigen.fila][casOrigen.columna] = nullptr;

                enJaqueMate = estaEnJaqueMate(turno1);

                if (enJaqueMate) {
                    exit(0);
                }

                // Movimiento válido, eliminar la pieza temporal si es necesario
                if (piezaTemporal != nullptr && piezaTemporal != piezaDestino) {
                    delete piezaTemporal;
                }

                piezaDestino->setPosicion(coordenadaSobreTablero[casDestino.fila * 8 + casDestino.columna]);
                ETSIDI::play("musica/sonido-mover.mp3");
                std::cout << "Has seleccionado un movimiento desde (" << casOrigen.columna << ", " << casOrigen.fila << ") hasta (" << casDestino.columna << ", " << casDestino.fila << ")" << std::endl;

                // Guardamos el valor del ultimo movimiento doble realizado por un peon
                if (piezaOrigen->getTipo() == TipoPieza::Peon && std::abs(casDestino.fila - casOrigen.fila) == 2) {
                    ultimoPeonDobleMovFila = casDestino.fila;
                    ultimoPeonDobleMovColumna = casDestino.columna;
                }
                else {
                    ultimoPeonDobleMovFila = -1;
                    ultimoPeonDobleMovColumna = -1;

                }

                //Realizamos la comprobacion de la captura al paso
                if (piezaOrigen->getTipo() == TipoPieza::Peon && std::abs(casDestino.fila - casOrigen.fila) == 1 && std::abs(casDestino.columna - casOrigen.columna) == 1 && casillas[casDestino.fila][casDestino.columna] == nullptr) {
                    int direction = (piezaOrigen->getColor() == 0) ? -1 : 1;
                    delete casillas[casDestino.fila + direction][casDestino.columna];
                    casillas[casDestino.fila + direction][casDestino.columna] = nullptr;
                    std::cout << "Captura al paso en (" << casDestino.columna << ", " << casDestino.fila + direction << ")" << std::endl;
                }

                Pieza* piezaCoronada = HayCoronacion(casSeleccion, piezaOrigen);
                if (piezaCoronada != nullptr)
                {
                    // TODO: Cambiar este sonido a uno de celebración
                    ETSIDI::play("musica/achievement.mp3");
                    casillas[piezaDestino->getFila()][piezaDestino->getColumna()] = piezaCoronada;
                }




                movimientoActivado = false;
                seleccionActiva = false;
                piezaOrigen = nullptr;
                piezaSeleccionada = nullptr;
                piezaDestino = nullptr;
                comer = false;

                // Cambiar el turno
                jugador1.SetTurno(!turno1);
                jugador2.SetTurno(turno1);
            }
            else {
                std::cout << "No se permite ese movimiento." << std::endl;
            }
        }
    }
}

Casilla Tablero::encontrarRey(bool turnoBlancas) {

    int colorRey = turnoBlancas ? ColorNegras : ColorBlancas;
    for (int fila = 0; fila < 8; fila++)
    {
        for (int columna = 0; columna < 10; columna++)
        {
            Pieza* pieza = casillas[fila][columna];
            if (pieza != nullptr && pieza->getTipo() == TipoPieza::Rey && pieza->getColor() == colorRey)
            {

                return Casilla{ columna, fila };

                std::cout << "Se ha encontrado al rey de color " << colorRey << "( " << fila << " " << columna << ")" << std::endl;
                return Casilla{ columna, fila };

            }
        }
    }
    return Casilla{ -1, -1 };
}

bool Tablero::casillaOcupada(int fila, int columna) const {
    return casillas[fila][columna] != nullptr;
}

bool Tablero::caminoDespejado(int filaInicial, int columnaInicial, int filaFinal, int columnaFinal) {
    int incrementoFila = (filaFinal > filaInicial) ? 1 : (filaFinal < filaInicial) ? -1 : 0;
    int incrementoColumna = (columnaFinal > columnaInicial) ? 1 : (columnaFinal < columnaInicial) ? -1 : 0;

    int fila = filaInicial + incrementoFila;
    int columna = columnaInicial + incrementoColumna;

    while (fila != filaFinal || columna != columnaFinal) {
        if (casillaOcupada(fila, columna)) {
            return false;
        }
        fila += incrementoFila;
        columna += incrementoColumna;
    }
    return true;
}

string Tablero::tipoPiezaToString(TipoPieza tipo) {
        switch (tipo) {
        case TipoPieza::Torre: return "Torre";
        case TipoPieza::Caballo: return "Caballo";
        case TipoPieza::Alfil: return "Alfil";
        case TipoPieza::Rey: return "Rey";
        case TipoPieza::Reina: return "Reina";
        case TipoPieza::Peon: return "Peon";
        case TipoPieza::Arzobispo: return "Arzobispo";
        case TipoPieza::Canciller: return "Canciller";
        case TipoPieza::Ninguno: return "Ninguno";
        }
        return "Desconocido";
    }

Pieza* Tablero::HayCoronacion(Casilla casillaDestino, Pieza* tipoPieza)
{
    Pieza* piezaDeseada = nullptr;
    if (tipoPieza != nullptr)
    {
        if (tipoPieza->getTipo() == TipoPieza::Peon)
        {
            if (casillaDestino.fila == 0)
            {
                piezaDeseada = CoronacionDeseada(tipoPieza, casillaDestino, false);
            }
            else if (casillaDestino.fila == 7)
            {
                piezaDeseada = CoronacionDeseada(tipoPieza, casillaDestino, true);
            }
        }
    }
    return piezaDeseada;
}

unsigned char Tablero::getCambioPieza() {
    return letracoronacioncambiopieza;
}

void Tablero::setCambioPieza(unsigned char letracambiopieza) {                                          //esto
    letracoronacioncambiopieza = letracambiopieza;
}

Pieza* Tablero::CoronacionDeseada(Pieza* piezaActual, Casilla casillaDestino, bool blancas)
{
    //El color de pieza tiene que ser el mismo que del turno
    //GetConsoleWindow();
    char piezaDeseada = 'z';
    Pieza* nuevaPieza = nullptr;

    int colorPieza = blancas ? 0 : 1;
    unsigned char letra_antes = letracoronacioncambiopieza;
    //coronacion = true;


    std::cout << "Escoge Pieza para la Coronacion: ( T : Torre , C : Caballo , A: Alfil, R : Reina)" << std::endl;

    bool quit = false;
    bool mensajeImpreso = false;
    while (!quit) {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            quit = true;
            continue;
        }

        bool teclaAceptablePresionada = false;
        for (int key = 0; key < 256; key++) {
            if (GetAsyncKeyState(key) & 0x8000) {
                char ascii = MapVirtualKey(key, MAPVK_VK_TO_CHAR);
                if (ascii == 't' || ascii == 'c' || ascii == 'a' || ascii == 'r' ||
                    ascii == 'T' || ascii == 'C' || ascii == 'A' || ascii == 'R') {
                    // Tecla aceptable, salir del bucle
                    quit = true;
                    piezaDeseada = ascii; // Actualizar la pieza deseada
                    teclaAceptablePresionada = true;
                }
                else {
                    // Tecla no aceptable
                    teclaAceptablePresionada = false;
                }
            }
        }

        if (!teclaAceptablePresionada && !mensajeImpreso) {
            // Imprimir mensaje si la tecla no es aceptable
            std::cout << "El tipo de pieza seleccionada no esta disponible." << std::endl;
            mensajeImpreso = true;
        }
    }

    switch (piezaDeseada) {
    case 't':
        nuevaPieza = new Torre(piezaActual->getPosicion(), colorPieza, casillaDestino.fila, casillaDestino.columna, *this);
        break;
    case 'T':
        nuevaPieza = new Torre(piezaActual->getPosicion(), colorPieza, casillaDestino.fila, casillaDestino.columna, *this);
        break;
    case 'c':
        nuevaPieza = new Caballo(piezaActual->getPosicion(), colorPieza, casillaDestino.fila, casillaDestino.columna);
        break;
    case 'C':
        nuevaPieza = new Caballo(piezaActual->getPosicion(), colorPieza, casillaDestino.fila, casillaDestino.columna);
        break;
    case 'a':
        nuevaPieza = new Alfil(piezaActual->getPosicion(), colorPieza, casillaDestino.fila, casillaDestino.columna, *this);
        break;
    case 'A':
        nuevaPieza = new Alfil(piezaActual->getPosicion(), colorPieza, casillaDestino.fila, casillaDestino.columna, *this);
        break;
    case 'r':
        nuevaPieza = new Reina(piezaActual->getPosicion(), colorPieza, casillaDestino.fila, casillaDestino.columna, *this);
        break;
    case 'R':
        nuevaPieza = new Reina(piezaActual->getPosicion(), colorPieza, casillaDestino.fila, casillaDestino.columna, *this);
        break;
    }
    coronacion = false;
    return nuevaPieza;
}

void Tablero::ValidarMovimiento(bool turnoBlancas, bool& movimientoPermitido) {
    if (piezaOrigen == nullptr) {
        movimientoPermitido = false;
        return;
    }

    std::vector<Casilla> movimientosPermitidos = piezaOrigen->getMovimientosPermitidos(casOrigen.fila, casOrigen.columna, turnoBlancas);
    std::cout << "Movimientos permitidos para la pieza en (" << casOrigen.columna << ", " << casOrigen.fila << "): ";
    for (const auto& movimiento : movimientosPermitidos) {
        std::cout << "(" << movimiento.columna << ", " << movimiento.fila << ") ";
        if (movimiento.fila == casSeleccion.fila && movimiento.columna == casSeleccion.columna) {
            // Simular el movimiento
            Pieza* piezaDestinoOriginal = casillas[movimiento.fila][movimiento.columna];
            casillas[movimiento.fila][movimiento.columna] = piezaOrigen;
            casillas[casOrigen.fila][casOrigen.columna] = nullptr;

            Casilla posicionRey = encontrarRey(turnoBlancas);

            enJaque = estaEnJaque(!turnoBlancas);

            // Revertir el movimiento
            casillas[casOrigen.fila][casOrigen.columna] = piezaOrigen;
            casillas[movimiento.fila][movimiento.columna] = piezaDestinoOriginal;

            if (enJaque) {
                std::cout << "Movimiento invalido: dejaria al rey en jaque." << std::endl;
                movimientoPermitido = false;
            }
            else {
                movimientoPermitido = true;
                std::cout << "Movimiento permitido encontrado." << std::endl;
                return;
            }
        }
    }
    std::cout << std::endl;
    movimientoPermitido = false;
    std::cout << "No se encontro un movimiento permitido." << std::endl;
}

bool Tablero::estaEnJaque(bool turnoBlancas)
{
    int colorOponente = turnoBlancas ? ColorNegras : ColorBlancas;
    int miColor = turnoBlancas ? ColorBlancas : ColorNegras;
    Casilla reyOponente = encontrarRey(turnoBlancas);

    // 1 - Primero buscamos todas NUESTRAS piezas 
    std::vector<Pieza*> misPiezas;
    for (int fila = 0; fila < 8; ++fila) {
        for (int columna = 0; columna < 10; ++columna) {
            Pieza* pieza = casillas[fila][columna];
            if (pieza != nullptr && pieza->getColor() == miColor) {
                misPiezas.push_back(pieza);
            }
        }
    }

    // 2 - Verificar si alguna pieza de nuestras piezas puede moverse a la posición del rey, por lo que estaía provocando un jaque
    for (Pieza* pieza : misPiezas)
    {
        if (pieza != nullptr)
        {
            std::vector<Casilla> movimientosPermitidos = pieza->getMovimientosPermitidos(pieza->getFila(), pieza->getColumna(), turnoBlancas);
            for (const Casilla& movimiento : movimientosPermitidos)
            {
                if (movimiento.fila == reyOponente.fila && movimiento.columna == reyOponente.columna)
                {
                    cout << "Se ha detectado un jaque al rey de la pieza " << tipoPiezaToString(pieza->getTipo());
                    return true;
                }
            }
        }
    }
    return false;
}

bool Tablero::estaEnJaqueMate(bool turnoBlancas)
{
    // Solo si está en jaque miramos el jaque mate
    if (enJaque) {
        int miColor = turnoBlancas ? ColorBlancas : ColorNegras;

        Casilla reyOponente = encontrarRey(turnoBlancas);
        Pieza* piezaRey = casillas[reyOponente.fila][reyOponente.columna];
        std::vector<Casilla> movimientosDelReyEnemigo = piezaRey->getMovimientosPermitidos(reyOponente.fila, reyOponente.columna, !turnoBlancas);

        // Verificar si el rey puede moverse a alguna casilla segura
        for (const Casilla& movimiento : movimientosDelReyEnemigo) {
            Pieza* piezaDestinoOriginal = casillas[movimiento.fila][movimiento.columna];
            moverPieza(reyOponente, movimiento);
            moverPieza(movimiento, reyOponente);  // Deshacer movimiento
            casillas[movimiento.fila][movimiento.columna] = piezaDestinoOriginal;  // Restaurar pieza capturada

            if (!enJaque) {
                return false;
            }
        }

        cout << "Se ha detectado un JAQUE MATE al rey de la pieza";
        // Si no se encontró ningún movimiento válido para escapar del jaque, es jaque mate
        return true;
    }
    return false;
}

void Tablero::moverPieza(const Casilla& origen, const Casilla& destino) {
    casillas[destino.fila][destino.columna] = casillas[origen.fila][origen.columna];
    casillas[origen.fila][origen.columna] = nullptr;
}

void Tablero::DibujarPasosPermitidos() {
    bool turnoBlancas = true;//la funcion getmovimientospermitidos necesita esto para funcionar

    if (jugador1.getTurno() && (!jugador2.getTurno())) {
        turnoBlancas = true;
    }
    else if (jugador2.getTurno() && (!jugador1.getTurno())) {
        turnoBlancas = false;
    }


    // Deshabilitar iluminación y texturas para asegurar que no interfieran
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // dibujar la pieza seleccionada en blanco
    float xSeleccion = coordenadaSobreTablero[casOrigen.fila * 8 + casOrigen.columna].x;
    float ySeleccion = coordenadaSobreTablero[casOrigen.fila * 8 + casOrigen.columna].y;


    glColor4f(1.0, 1.0, 1.0, 0.5); // color blanco semitransparente

    // dibujar el círculo en las coordenadas reales
    glPushMatrix();
    glTranslatef(-xSeleccion + 0.125, -ySeleccion + 0.12, 0.1); // centro del círculo
    GLUquadric* qobj = gluNewQuadric();
    gluDisk(qobj, 0, 0.1, 20, 1); // disco con radio y 10 subdivisiones
    gluDeleteQuadric(qobj);
    glPopMatrix();


    //ahora dibujamos los circulitos verdes
    std::vector<Casilla> movimientosPermitidos = piezaOrigen->getMovimientosPermitidos(casOrigen.fila, casOrigen.columna, turnoBlancas);
    for (const Casilla& casilla : movimientosPermitidos) {


        // coordenadas reales de la casilla
        float sel_x = coordenadaSobreTablero[casilla.fila * 8 + casilla.columna].x;
        float sel_y = coordenadaSobreTablero[casilla.fila * 8 + casilla.columna].y;

        if (casillas[casilla.fila][casilla.columna] == nullptr) {
            glColor4f(0.2, 1.0, 0.2, 0.5); // color verde semitransparente

            //  coordenadas reales
            glPushMatrix();
            glTranslatef(-sel_x + 0.125, -sel_y + 0.12, 0.1); //  centro del círculo
            GLUquadric* qobj = gluNewQuadric();
            gluDisk(qobj, 0, 0.05, 20, 1); //disco con radio y 10 subdivisiones
            gluDeleteQuadric(qobj);
            glPopMatrix();


        }


        else if (casillas[casilla.fila][casilla.columna]->getColor() != piezaOrigen->getColor()) {

            glColor4f(1.0, 1.0, 0.0, 0.5); // color amarillo semitransparente

            //coordenadas reales
            glPushMatrix();
            glTranslatef(-sel_x + 0.125, -sel_y + 0.12, 0.1); //  centro del círculo
            GLUquadric* qobj = gluNewQuadric();
            gluDisk(qobj, 0, 0.08, 20, 1); //disco con radio y 10 subdivisiones
            gluDeleteQuadric(qobj);
            glPopMatrix();
        }
    }

    // Restaurar el estado anterior de OpenGL
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
}

void Tablero::realizarMovimientoMaquina() {

    if (jugador2.EsMaquina() && jugador2.getTurno()) {
        std::vector<Pieza*> piezasMaquina;
        std::vector<std::pair<Pieza*, Casilla>> movimientosPosibles;

        // Recopilar todas las piezas de la máquina y sus movimientos permitidos
        for (int fila = 0; fila < 8; fila++) {
            for (int columna = 0; columna < 10; columna++) {
                Pieza* pieza = casillas[fila][columna];
                if (pieza != nullptr && pieza->getColor() == ColorNegras) {
                    std::vector<Casilla> movimientos = pieza->getMovimientosPermitidos(fila, columna, false);
                    for (const Casilla& movimiento : movimientos) {
                        movimientosPosibles.push_back(std::make_pair(pieza, movimiento));
                    }
                }
            }
        }

        // Seleccionar un movimiento basado en el nivel de dificultad
        if (!movimientosPosibles.empty()) {
            std::pair<Pieza*, Casilla> movimientoSeleccionado;

            if (nivelDificultad == 0) {
                // Nivel Fácil: Movimiento aleatorio
                std::random_shuffle(movimientosPosibles.begin(), movimientosPosibles.end());
                movimientoSeleccionado = movimientosPosibles.front();
            }
            else if (nivelDificultad == 1) {
                // Nivel Intermedio: Movimiento aleatorio que prioriza capturas
                std::vector<std::pair<Pieza*, Casilla>> movimientosDeCaptura;
                for (const auto& movimiento : movimientosPosibles) {
                    if (casillas[movimiento.second.fila][movimiento.second.columna] != nullptr) {
                        movimientosDeCaptura.push_back(movimiento);
                    }
                }

                if (!movimientosDeCaptura.empty()) {
                    std::random_shuffle(movimientosDeCaptura.begin(), movimientosDeCaptura.end());
                    movimientoSeleccionado = movimientosDeCaptura.front();
                }
                else {
                    std::random_shuffle(movimientosPosibles.begin(), movimientosPosibles.end());
                    movimientoSeleccionado = movimientosPosibles.front();
                }
            }


            // Obtener la pieza a mover y la casilla destino
            Pieza* piezaAMover = movimientoSeleccionado.first;
            Casilla destino = movimientoSeleccionado.second;

            int filaOrigen = piezaAMover->getFila();
            int columnaOrigen = piezaAMover->getColumna();
            int filaDestino = destino.fila;
            int columnaDestino = destino.columna;

            // Realizar el movimiento
            casillas[filaOrigen][columnaOrigen] = nullptr;
            casillas[filaDestino][columnaDestino] = piezaAMover;
            piezaAMover->setFila(filaDestino);
            piezaAMover->setColumna(columnaDestino);
            piezaAMover->setPosicion(coordenadaSobreTablero[filaDestino * 8 + columnaDestino]);

            std::cout << "La máquina ha movido la pieza desde (" << columnaOrigen << ", " << filaOrigen << ") hasta (" << columnaDestino << ", " << filaDestino << ")" << std::endl;

            // Cambiar el turno
            jugador2.SetTurno(false);
            jugador1.SetTurno(true);
        }
        else {
            std::cout << "No se puede mover ninguna pieza." << std::endl;
        }
    }


}