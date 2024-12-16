#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Interfaz Comando
class Command {
public:
    virtual void execute() = 0;
};

// Comando Concreto
class LightOnCommand : public Command {
private:
    class Light {
    public:
        void turnOn() {
            cout << "La luz está encendida." << endl;
        }
    };
    
    Light* light;
public:
    LightOnCommand(Light* l) : light(l) {}

    void execute() override {
        light->turnOn();
    }
};

// Otro Comando Concreto
class LightOffCommand : public Command {
private:
    class Light {
    public:
        void turnOff() {
            cout << "La luz está apagada." << endl;
        }
    };
    
    Light* light;
public:
    LightOffCommand(Light* l) : light(l) {}

    void execute() override {
        light->turnOff();
    }
};

// Clase Invocadora
class RemoteControl {
private:
    Command* command;
public:
    void setCommand(Command* cmd) {
        command = cmd;
    }

    void pressButton() {
        command->execute();
    }
};

int main() {
    // Crear el receptor (la luz)
    class Light light;

    // Crear los comandos
    LightOnCommand lightOnCommand(&light);
    LightOffCommand lightOffCommand(&light);

    // Crear la invocadora (el control remoto)
    RemoteControl remoteControl;

    // Enviar comandos a través del control remoto
    remoteControl.setCommand(&lightOnCommand);
    remoteControl.pressButton();  // La luz está encendida.

    remoteControl.setCommand(&lightOffCommand);
    remoteControl.pressButton();  // La luz está apagada.

    return 0;
}

