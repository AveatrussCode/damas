#include <iostream>
#include <cmath>
using namespace std;

enum class TipoPieza { NINGUNA, NORMAL, DAMA };
enum class ColorPieza { NINGUNO, BLANCO, NEGRO };

class Pieza {
public:
    ColorPieza color;
    TipoPieza tipo;

    Pieza(ColorPieza c = ColorPieza::NINGUNO, TipoPieza t = TipoPieza::NINGUNA)
        : color(c), tipo(t) {}

    bool puedeMover(int x1, int y1, int x2, int y2, Pieza tablero[8][8]) {
        if (tipo == TipoPieza::NORMAL) {
            int dx = abs(x2 - x1);
            int dy = abs(y2 - y1);

            if (dx == 1 && dy == 1) {
                return true;
            }

            if (dx == 2 && dy == 2) {
                int xMedio = (x1 + x2) / 2;
                int yMedio = (y1 + y2) / 2;

                Pieza& piezaMedio = tablero[xMedio][yMedio];

                if (piezaMedio.color != ColorPieza::NINGUNO && piezaMedio.color != color) {
                    return true;
                }
            }
        }

        return false;
    }

    void promover() {
        if (tipo == TipoPieza::NORMAL) {
            tipo = TipoPieza::DAMA;
        }
    }

    char obtenerSimbolo() const {
        if (color == ColorPieza::BLANCO)
            return tipo == TipoPieza::DAMA ? 'B' : 'b';
        if (color == ColorPieza::NEGRO)
            return tipo == TipoPieza::DAMA ? 'N' : 'n';
        return '.';
    }
};

class Tablero {
private:
    Pieza casillas[8][8];

public:
    Tablero() {
        inicializarPiezas();
    }

    void inicializarPiezas() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                casillas[i][j] = Pieza();
                if ((i + j) % 2 == 1) {
                    if (i < 3) {
                        casillas[i][j] = Pieza(ColorPieza::NEGRO, TipoPieza::NORMAL);
                    } else if (i >= 5) {
                        casillas[i][j] = Pieza(ColorPieza::BLANCO, TipoPieza::NORMAL);
                    }
                }
            }
        }
    }

    bool moverPieza(int x1, int y1, int x2, int y2) {
        if (!esMovimientoValido(x1, y1, x2, y2)) return false;

        Pieza& origen = casillas[x1][y1];
        Pieza& destino = casillas[x2][y2];

        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
        if (dx == 2 && dy == 2) {
            int xMedio = (x1 + x2) / 2;
            int yMedio = (y1 + y2) / 2;
            casillas[xMedio][yMedio] = Pieza();
        }

        destino = origen;
        origen = Pieza();

        if (destino.color == ColorPieza::BLANCO && x2 == 0) destino.promover();
        if (destino.color == ColorPieza::NEGRO && x2 == 7) destino.promover();

        return true;
    }

    bool esMovimientoValido(int x1, int y1, int x2, int y2) {
        if (!estaEnRango(x1, y1) || !estaEnRango(x2, y2)) return false;
        Pieza& origen = casillas[x1][y1];
        Pieza& destino = casillas[x2][y2];

        if (origen.color == ColorPieza::NINGUNO || destino.color != ColorPieza::NINGUNO) return false;

        return origen.puedeMover(x1, y1, x2, y2, casillas);
    }

    bool estaEnRango(int x, int y) {
        return x >= 0 && x < 8 && y >= 0 && y < 8;
    }

    void imprimirTablero() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                cout << casillas[i][j].obtenerSimbolo() << " ";
            }
            cout << endl;
        }
    }
};

class JuegoDamas {
private:
    Tablero tablero;
    ColorPieza jugadorActual;

public:
    JuegoDamas() : jugadorActual(ColorPieza::BLANCO) {}

    void jugar() {
        while (true) {
            cout << "Jugador actual: " << (jugadorActual == ColorPieza::BLANCO ? "Blanco" : "Negro") << endl;
            tablero.imprimirTablero();

            int x1, y1, x2, y2;
            cout << "Ingresa movimiento (x1 y1 x2 y2): ";
            cin >> x1 >> y1 >> x2 >> y2;

            if (tablero.moverPieza(x1, y1, x2, y2)) {
                jugadorActual = (jugadorActual == ColorPieza::BLANCO) ? ColorPieza::NEGRO : ColorPieza::BLANCO;
            } else {
                cout << "Movimiento inválido. Intenta de nuevo." << endl;
            }
        }
    }
};

int main() {
    JuegoDamas juego;
    juego.jugar();
    return 0;
}
