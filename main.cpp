#include <iostream>
#include <cmath>

using namespace std;

enum class TipoDePieza { NINGUNA, NORMAL, REY };
enum class ColorDePieza { NINGUNO, BLANCA, NEGRA };

class Pieza {
public:
    ColorDePieza color;
    TipoDePieza tipo;

    Pieza(ColorDePieza c = ColorDePieza::NINGUNO, TipoDePieza t = TipoDePieza::NINGUNA)
        : color(c), tipo(t) {}

    bool puedeMover(int x1, int y1, int x2, int y2) const {
        int dx = x2 - x1;
        int dy = y2 - y1;
        int absDx = abs(dx);
        int absDy = abs(dy);

        if (tipo == TipoDePieza::NORMAL) {
            if (color == ColorDePieza::BLANCA) {
                return dx == -1 && absDy == 1;
            }
            if (color == ColorDePieza::NEGRA) {
                return dx == 1 && absDy == 1;
            }
        }

        if (tipo == TipoDePieza::REY) {
            return absDx == 1 && absDy == 1;
        }

        return false;
    }

    bool puedeCapturar(int x1, int y1, int x2, int y2) const {
        int dx = x2 - x1;
        int dy = y2 - y1;
        int absDx = abs(dx);
        int absDy = abs(dy);

        if (tipo == TipoDePieza::NORMAL) {
            if (color == ColorDePieza::BLANCA) {
                return dx == -2 && absDy == 2;
            }
            if (color == ColorDePieza::NEGRA) {
                return dx == 2 && absDy == 2;
            }
        }

        if (tipo == TipoDePieza::REY) {
            return absDx == 2 && absDy == 2;
        }

        return false;
    }

    void promover() {
        if ((color == ColorDePieza::BLANCA && tipo == TipoDePieza::NORMAL) ||
            (color == ColorDePieza::NEGRA && tipo == TipoDePieza::NORMAL)) {
            tipo = TipoDePieza::REY;
        }
    }

    char obtenerSimbolo() const {
        if (color == ColorDePieza::BLANCA)
            return tipo == TipoDePieza::REY ? 'B' : 'b';
        if (color == ColorDePieza::NEGRA)
            return tipo == TipoDePieza::REY ? 'N' : 'n';
        return '.';
    }
};

class Tablero {
private:
    Pieza cuadrícula[8][8];  // Usamos un arreglo estático de 8x8

public:
    Tablero() {
        inicializarPiezas();
    }

    void inicializarPiezas() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 8; ++j) {
                if ((i + j) % 2 == 1)
                    cuadrícula[i][j] = Pieza(ColorDePieza::NEGRA, TipoDePieza::NORMAL);
            }
        }
        for (int i = 5; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if ((i + j) % 2 == 1)
                    cuadrícula[i][j] = Pieza(ColorDePieza::BLANCA, TipoDePieza::NORMAL);
            }
        }
    }

    bool moverPieza(int x1, int y1, int x2, int y2, ColorDePieza jugadorActual) {
        if (x1 < 0 || x1 >= 8 || y1 < 0 || y1 >= 8 || x2 < 0 || x2 >= 8 || y2 < 0 || y2 >= 8) {
            cout << "Movimiento fuera de los límites del tablero." << endl;
            return false;
        }

        Pieza& piezaOrigen = cuadrícula[x1][y1];
        Pieza& piezaDestino = cuadrícula[x2][y2];

        if (piezaOrigen.color != jugadorActual) {
            cout << "No es tu pieza." << endl;
            return false;
        }

        if (piezaDestino.color != ColorDePieza::NINGUNO) {
            cout << "La casilla de destino está ocupada." << endl;
            return false;
        }

        if (esCapturaPosible(jugadorActual)) {
            if (!esCapturaVálida(x1, y1, x2, y2)) {
                cout << "Hay capturas obligatorias. Debes capturar." << endl;
                return false;
            }

            int xCapturada = (x1 + x2) / 2;
            int yCapturada = (y1 + y2) / 2;
            Pieza& piezaCapturada = cuadrícula[xCapturada][yCapturada];
            if (piezaCapturada.color == ColorDePieza::NINGUNO || piezaCapturada.color == jugadorActual) {
                cout << "No se puede capturar esta pieza." << endl;
                return false;
            }
            piezaCapturada = Pieza();
        } else {
            if (!piezaOrigen.puedeMover(x1, y1, x2, y2)) {
                cout << "Movimiento no válido para esta pieza." << endl;
                return false;
            }
        }

        piezaDestino = piezaOrigen;
        piezaOrigen = Pieza();

        if ((piezaDestino.color == ColorDePieza::BLANCA && x2 == 0) || 
            (piezaDestino.color == ColorDePieza::NEGRA && x2 == 7)) {
            piezaDestino.promover();
        }

        return true;
    }

    bool esCapturaPosible(ColorDePieza jugadorActual) {
        for (int x = 0; x < 8; ++x) {
            for (int y = 0; y < 8; ++y) {
                Pieza& pieza = cuadrícula[x][y];
                if (pieza.color == jugadorActual) {
                    int direcciones[4][2] = {{-2,-2}, {-2,2}, {2,-2}, {2,2}};
                    for (auto& dir : direcciones) {
                        int nuevoX = x + dir[0];
                        int nuevoY = y + dir[1];
                        if (esCapturaVálida(x, y, nuevoX, nuevoY)) {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    bool esCapturaVálida(int x1, int y1, int x2, int y2) {
        if (x1 < 0 || x1 >= 8 || y1 < 0 || y1 >= 8 || x2 < 0 || x2 >= 8 || y2 < 0 || y2 >= 8) {
            return false;
        }

        Pieza& piezaOrigen = cuadrícula[x1][y1];
        Pieza& piezaDestino = cuadrícula[x2][y2];

        if (!piezaOrigen.puedeCapturar(x1, y1, x2, y2)) {
            return false;
        }

        if (piezaDestino.color != ColorDePieza::NINGUNO) {
            return false;
        }

        int xCapturada = (x1 + x2) / 2;
        int yCapturada = (y1 + y2) / 2;
        Pieza& piezaCapturada = cuadrícula[xCapturada][yCapturada];

        return (piezaCapturada.color != ColorDePieza::NINGUNO && 
                piezaCapturada.color != piezaOrigen.color);
    }

    void imprimirTablero() {
        cout << "  0 1 2 3 4 5 6 7" << endl;
        for (int i = 0; i < 8; ++i) {
            cout << i << " ";
            for (int j = 0; j < 8; ++j) {
                cout << cuadrícula[i][j].obtenerSimbolo() << " ";
            }
            cout << endl;
        }
    }

    int contarPiezas(ColorDePieza color) {
        int cuenta = 0;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (cuadrícula[i][j].color == color) {
                    cuenta++;
                }
            }
        }
        return cuenta;
    }

    bool tieneMovimientosVálidos(ColorDePieza color) {
        for (int x1 = 0; x1 < 8; ++x1) {
            for (int y1 = 0; y1 < 8; ++y1) {
                if (cuadrícula[x1][y1].color == color) {
                    for (int x2 = 0; x2 < 8; ++x2) {
                        for (int y2 = 0; y2 < 8; ++y2) {
                            if (esCapturaVálida(x1, y1, x2, y2) || 
                                (cuadrícula[x1][y1].puedeMover(x1, y1, x2, y2) && 
                                 cuadrícula[x2][y2].color == ColorDePieza::NINGUNO)) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
};

class JuegoDeDamas {
private:
    Tablero tablero;
    ColorDePieza jugadorActual;

public:
    JuegoDeDamas() : jugadorActual(ColorDePieza::BLANCA) {}

    void jugar() {
        while (true) {
            int piezasBlancas = tablero.contarPiezas(ColorDePieza::BLANCA);
            int piezasNegras = tablero.contarPiezas(ColorDePieza::NEGRA);

            if (piezasBlancas == 0) {
                cout << "¡Las negras ganan! Las blancas se quedaron sin piezas." << endl;
                break;
            }
            if (piezasNegras == 0) {
                cout << "¡Las blancas ganan! Las negras se quedaron sin piezas." << endl;
                break;
            }

            if (!tablero.tieneMovimientosVálidos(jugadorActual)) {
                ColorDePieza ganador = (jugadorActual == ColorDePieza::BLANCA) ? 
                    ColorDePieza::NEGRA : ColorDePieza::BLANCA;
                cout << (ganador == ColorDePieza::BLANCA ? "¡Las blancas ganan!" : "¡Las negras ganan!") 
                     << " El jugador actual no tiene movimientos válidos." << endl;
                break;
            }

            cout << "Jugador actual: " << (jugadorActual == ColorDePieza::BLANCA ? "Blanco" : "Negro") << endl;
            cout << "Piezas blancas: " << piezasBlancas << ", Piezas negras: " << piezasNegras << endl;
            tablero.imprimirTablero();

            int x1, y1, x2, y2;
            cout << "Ingresa el movimiento (x1 y1 x2 y2): ";
            cin >> x1 >> y1 >> x2 >> y2;

            if (tablero.moverPieza(x1, y1, x2, y2, jugadorActual)) {
                jugadorActual = (jugadorActual == ColorDePieza::BLANCA) ? ColorDePieza::NEGRA : ColorDePieza::BLANCA;
            }
        }
    }
};

int main() {
    JuegoDeDamas juego;
    juego.jugar();
    return 0;
}
