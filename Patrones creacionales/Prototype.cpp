#include <iostream>
#include <memory>
#include <string>

using namespace std;  // Ahora puedes usar elementos de la biblioteca estándar sin el prefijo 'std::'

// Clase Prototipo
class Personaje {
public:
    virtual unique_ptr<Personaje> clonar() const = 0;
    virtual void mostrarDetalles() const = 0;
    virtual ~Personaje() = default;
};

// Prototipos concretos
class Guerrero : public Personaje {
public:
    Guerrero(const string& nombre, int vida, int fuerza) 
        : nombre(nombre), vida(vida), fuerza(fuerza) {}

    unique_ptr<Personaje> clonar() const override {
        return make_unique<Guerrero>(*this);
    }

    void mostrarDetalles() const override {
        cout << "Guerrero: " << nombre 
             << ", Vida: " << vida 
             << ", Fuerza: " << fuerza << endl;
    }

private:
    string nombre;
    int vida;
    int fuerza;
};

class Mago : public Personaje {
public:
    Mago(const string& nombre, int vida, int mana) 
        : nombre(nombre), vida(vida), mana(mana) {}

    unique_ptr<Personaje> clonar() const override {
        return make_unique<Mago>(*this);
    }

    void mostrarDetalles() const override {
        cout << "Mago: " << nombre 
             << ", Vida: " << vida 
             << ", Mana: " << mana << endl;
    }

private:
    string nombre;
    int vida;
    int mana;
};

int main() {
    Guerrero guerreroOriginal("Aragorn", 100, 85);
    Mago magoOriginal("Gandalf", 80, 150);

    // Clonar personajes
    auto guerreroClonado = guerreroOriginal.clonar();
    auto magoClonado = magoOriginal.clonar();

    cout << "Personaje Original:" << endl;
    guerreroOriginal.mostrarDetalles();

    cout << "Personaje Clonado:" << endl;
    guerreroClonado->mostrarDetalles();

    cout << "\nMago Original:" << endl;
    magoOriginal.mostrarDetalles();

    cout << "Mago Clonado:" << endl;
    magoClonado->mostrarDetalles();

    return 0;
}
