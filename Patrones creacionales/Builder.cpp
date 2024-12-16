#include <iostream>
#include <string>

using namespace std;  // Ahora puedes usar nombres de la biblioteca estándar sin el prefijo 'std::'

// Producto complejo
class Casa {
public:
    void setParedes(const string& paredes) { 
        this->paredes = paredes; 
    }
    void setTecho(const string& techo) { 
        this->techo = techo; 
    }
    void setPuerta(const string& puerta) { 
        this->puerta = puerta; 
    }
    void setVentanas(const string& ventanas) { 
        this->ventanas = ventanas; 
    }

    void mostrarDetalles() const {
        cout << "Casa construida:" << endl;
        cout << "Paredes: " << paredes << endl;
        cout << "Techo: " << techo << endl;
        cout << "Puerta: " << puerta << endl;
        cout << "Ventanas: " << ventanas << endl;
    }

private:
    string paredes;
    string techo;
    string puerta;
    string ventanas;
};

// Builder abstracto
class CasaBuilder {
public:
    virtual void construirParedes() = 0;
    virtual void construirTecho() = 0;
    virtual void construirPuerta() = 0;
    virtual void construirVentanas() = 0;
    virtual Casa obtenerCasa() = 0;
    virtual ~CasaBuilder() = default;
};

// Builder concreto para casa de campo
class CasaDeCampoBuilder : public CasaBuilder {
public:
    CasaDeCampoBuilder() { casa = new Casa(); }
    
    void construirParedes() override {
        casa->setParedes("Paredes de madera");
    }
    
    void construirTecho() override {
        casa->setTecho("Techo de tejas");
    }
    
    void construirPuerta() override {
        casa->setPuerta("Puerta de madera rustica");
    }
    
    void construirVentanas() override {
        casa->setVentanas("Ventanas con marco de madera");
    }
    
    Casa obtenerCasa() override {
        return *casa;
    }

private:
    Casa* casa;
};

// Director
class Constructor {
public:
    Casa construirCasa(CasaBuilder& builder) {
        builder.construirParedes();
        builder.construirTecho();
        builder.construirPuerta();
        builder.construirVentanas();
        return builder.obtenerCasa();
    }
};

int main() {
    Constructor constructor;
    CasaDeCampoBuilder builderCampo;

    Casa miCasa = constructor.construirCasa(builderCampo);
    miCasa.mostrarDetalles();

    return 0;
}
