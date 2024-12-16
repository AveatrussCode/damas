#include <iostream>
#include <string>

using namespace std;

class GestorDeConfiguracion {
private:
    string datosDeConfiguracion;
    
    // Constructor privado
    GestorDeConfiguracion() {
        datosDeConfiguracion = "Configuracion predeterminada";
    }
    
    // Instancia estática única
    static GestorDeConfiguracion* instancia;

public:
    // Método estático para obtener la instancia
    static GestorDeConfiguracion* obtenerInstancia() {
        if (instancia == nullptr) {
            instancia = new GestorDeConfiguracion();
        }
        return instancia;
    }

    void establecerDatosDeConfiguracion(const string& datos) {
        datosDeConfiguracion = datos;
    }

    string obtenerDatosDeConfiguracion() const {
        return datosDeConfiguracion;
    }
};

// Inicializar el puntero estático
GestorDeConfiguracion* GestorDeConfiguracion::instancia = nullptr;

int main() {
    GestorDeConfiguracion* config1 = GestorDeConfiguracion::obtenerInstancia();
    GestorDeConfiguracion* config2 = GestorDeConfiguracion::obtenerInstancia();

    cout << "Configuracion inicial: " << config1->obtenerDatosDeConfiguracion() << endl;
    
    config1->establecerDatosDeConfiguracion("Nueva configuracion personalizada");
    
    cout << "Configuracion actualizada: " << config2->obtenerDatosDeConfiguracion() << endl;
    
    // Verificar que son la misma instancia
    cout << "Son la misma instancia? " 
         << (config1 == config2 ? "Si" : "No") << endl;

    return 0;
}
