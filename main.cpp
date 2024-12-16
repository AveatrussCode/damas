#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>
using namespace std;

// Definición de constantes
const int TAMANO_TABLERO = 8; // El tablero es de 8x8

// Clase base para las piezas
class Pieza {
protected:
    string color; // "Blanca" o "Negra"
public:
    Pieza(string c) : color(c) {}
    virtual ~Pieza() = default;
    virtual bool movimientoValido(int x1, int y1, int x2, int y2) const = 0; // Método abstracto
    string getColor() const { return color; }
};

// Pieza básica
class PiezaNormal : public Pieza {
public:
    PiezaNormal(string c) : Pieza(c) {}
    bool movimientoValido(int x1, int y1, int x2, int y2) const override {
        if (color == "Blanca") {
            return (x2 == x1 + 1) && (abs(y2 - y1) == 1);
        } else {
            return (x2 == x1 - 1) && (abs(y2 - y1) == 1);
        }
    }
};

// Clase para celdas del tablero
class Celda {
    shared_ptr<Pieza> pieza; // Puntero a la pieza en esta celda (puede ser nullptr)
public:
    Celda() : pieza(nullptr) {}
    bool estaVacia() const { return pieza == nullptr; }
    void colocarPieza(shared_ptr<Pieza> nuevaPieza) { pieza = nuevaPieza; }
    void eliminarPieza() { pieza = nullptr; }
    shared_ptr<Pieza> getPieza() const { return pieza; }
};

// Clase para el tablero
class Tablero {
    vector<vector<Celda>> celdas;
public:
    Tablero() : celdas(TAMANO_TABLERO, vector<Celda>(TAMANO_TABLERO)) {}
    void inicializarTablero() {
        for (int i = 0; i < TAMANO_TABLERO; ++i) {
            for (int j = 0; j < TAMANO_TABLERO; ++j) {
                if (i < 3 && (i + j) % 2 != 0) { // Fichas negras
                    celdas[i][j].colocarPieza(make_shared<PiezaNormal>("Negra"));
                } else if (i > 4 && (i + j) % 2 != 0) { // Fichas blancas
                    celdas[i][j].colocarPieza(make_shared<PiezaNormal>("Blanca"));
                }
            }
        }
    }
    Celda& obtenerCelda(int x, int y) {
        if (x < 0 || x >= TAMANO_TABLERO || y < 0 || y >= TAMANO_TABLERO) {
            throw out_of_range("Posición fuera del tablero");
        }
        return celdas[x][y];
    }
    void mostrarTablero() const {
        for (int i = 0; i < TAMANO_TABLERO; ++i) {
            for (int j = 0; j < TAMANO_TABLERO; ++j) {
                if (celdas[i][j].estaVacia()) {
                    cout << ". ";
                } else {
                    cout << (celdas[i][j].getPieza()->getColor() == "Blanca" ? "B " : "N ");
                }
            }
            cout << endl;
        }
    }
};

// Clase principal para manejar el juego
class JuegoDeDamas {
    Tablero tablero;
    string turno; // "Blanca" o "Negra"
public:
    JuegoDeDamas() : turno("Blanca") {
        tablero.inicializarTablero();
    }

    void jugar() {
        while (true) {
            cout << "Turno de " << turno << ":\n";
            tablero.mostrarTablero();

            char opcion;
            cout << "Escribe 'f' para terminar o cualquier tecla para continuar: ";
            cin >> opcion;

            if (opcion == 'f') {
                cout << "Juego terminado.\n";
                break;
            }

            int x1, y1, x2, y2;
            cout << "Ingresa la posición de la ficha a mover (fila columna): ";
            cin >> x1 >> y1;
            cout << "Ingresa la posición destino (fila columna): ";
            cin >> x2 >> y2;

            try {
                moverPieza(x1, y1, x2, y2);
                cambiarTurno();
            } catch (const exception& e) {
                cout << "Movimiento inválido: " << e.what() << endl;
            }
        }
    }

private:
    void moverPieza(int x1, int y1, int x2, int y2) {
        auto& origen = tablero.obtenerCelda(x1, y1);
        auto& destino = tablero.obtenerCelda(x2, y2);

        if (origen.estaVacia()) {
            throw runtime_error("La celda origen está vacía");
        }

        auto pieza = origen.getPieza();
        if (pieza->getColor() != turno) {
            throw runtime_error("No puedes mover una pieza del color contrario");
        }

        if (!destino.estaVacia()) {
            throw runtime_error("La celda destino no está vacía");
        }

        if (!pieza->movimientoValido(x1, y1, x2, y2)) {
            throw runtime_error("Movimiento no válido para esta pieza");
        }

        destino.colocarPieza(pieza);
        origen.eliminarPieza();
    }

    void cambiarTurno() {
        turno = (turno == "Blanca") ? "Negra" : "Blanca";
    }
};

int main() {
    JuegoDeDamas juego;
    juego.jugar();
    return 0;
}
