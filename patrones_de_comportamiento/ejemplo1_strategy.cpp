#include <iostream>
using namespace std;

// Interfaz de estrategia
class SoundStrategy {

public:
    virtual void makeSound() = 0;
};

// Estrategias concretas


class GatoSound : public SoundStrategy {
public:
    void makeSound() override {
        cout << "El gato maulla." << endl;
    }
};

class PerroSound : public SoundStrategy {
public:
    void makeSound() override {
        cout << "El perro ladra." << endl;
    }
};

// Contexto
class Animal {
private:
    SoundStrategy* soundStrategy;
public:
    Animal(SoundStrategy* strategy) : soundStrategy(strategy) {}
    void setStrategy(SoundStrategy* strategy) {
        soundStrategy = strategy;
    }
    void makeSound() {
        soundStrategy->makeSound();  // Delegación al comportamiento actual
    }
};
int main() {
    GatoSound gato;
    PerroSound perro;
    Animal miAnimal(&gato); // El animal inicialmente hace sonido de gato
    miAnimal.makeSound();  // Imprime "El gato maulla."

    miAnimal.setStrategy(&perro); // Cambiamos la estrategia a "PerroSound"
    miAnimal.makeSound();  // Imprime "El perro ladra."
    
    return 0;
}
