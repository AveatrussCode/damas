#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Receptor (Light)
class Light {
public:
    void turnOn() {
        cout << "La luz esta encendida." << endl;
    }

    void turnOff() {
        cout << "La luz esta apagada." << endl;
    }
};

// Interfaz Comando
class Command {
public:
    virtual void execute() = 0;
};

// Comando Concreto para encender la luz
class LightOnCommand : public Command {
private:
    Light* light;
public:
    LightOnCommand(Light* l) : light(l) {}

    void execute() override {
        light->turnOn();
    }
};

// Comando Concreto para apagar la luz
class LightOffCommand : public Command {
private:
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
    Light light;

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
