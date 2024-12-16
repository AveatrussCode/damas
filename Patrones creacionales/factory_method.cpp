#include <iostream>
#include <memory>

using namespace std;

// Clase base de transporte
class Transporte {
public:
    virtual void entregar() = 0;
    virtual ~Transporte() = default;
};

// Implementaciones concretas
class Camion : public Transporte {
public:
    void entregar() override {
        cout << "Entrega por camion terrestre" << endl;
    }
};

class Barco : public Transporte {
public:
    void entregar() override {
        cout << "Entrega por barco maritimo" << endl;
    }
};

// Clase creadora abstracta
class FabricaLogistica {
public:
    virtual unique_ptr<Transporte> crearTransporte() = 0;
    virtual ~FabricaLogistica() = default;
};

// Fábricas concretas
class LogisticaTerrestre : public FabricaLogistica {
public:
    unique_ptr<Transporte> crearTransporte() override {
        return make_unique<Camion>();
    }
};

class LogisticaMaritima : public FabricaLogistica {
public:
    unique_ptr<Transporte> crearTransporte() override {
        return make_unique<Barco>();
    }
};

int main() {
    LogisticaTerrestre fabricaTerrestre;
    LogisticaMaritima fabricaMaritima;

    auto camion = fabricaTerrestre.crearTransporte();
    auto barco = fabricaMaritima.crearTransporte();

    camion->entregar();
    barco->entregar();

    return 0;
}

// Salida esperada:
// Entrega por camión terrestre
// Entrega por barco marítimo
