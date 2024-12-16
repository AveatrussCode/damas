#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Interfaz del Observador
class Observer {
public:
    virtual void update(const string& message) = 0;
};

// Sujeto que mantiene la lista de observadores
class Subject {
private:
    vector<Observer*> observers;
public:
    // Método para agregar un observador
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    // Método para notificar a todos los observadores
    void notifyObservers(const string& message) {
        for (Observer* observer : observers) {
            observer->update(message);
        }
    }
};

// Clase concreta de Sujeto
class NewsAgency : public Subject {
private:
    string news;
public:
    // Método para cambiar las noticias
    void setNews(const string& newNews) {
        news = newNews;
        // Notifica a los observadores cada vez que cambia el estado
        notifyObservers(news);
    }
};

// Clase concreta de Observador
class NewsChannel : public Observer {
private:
    string name;
public:
    NewsChannel(const string& channelName) : name(channelName) {}

    // Recibe las actualizaciones del sujeto
    void update(const string& message) override {
        cout << "Canal " << name << " ha recibido las noticias: " << message << endl;
    }
};

int main() {
    // Crear el sujeto
    NewsAgency newsAgency;

    // Crear observadores (canales de noticias)
    NewsChannel cnn("CNN");
    NewsChannel bbc("BBC");
    NewsChannel fox("Fox News");

    // Registrar observadores en el sujeto
    newsAgency.addObserver(&cnn);
    newsAgency.addObserver(&bbc);
    newsAgency.addObserver(&fox);

    // Cambiar el estado en el sujeto (nuevas noticias)
    newsAgency.setNews("¡Nuevo descubrimiento en el espacio!");

    cout << "\nActualización de noticias:\n";
    newsAgency.setNews("La economía global muestra señales de recuperación.");

    return 0;
}
