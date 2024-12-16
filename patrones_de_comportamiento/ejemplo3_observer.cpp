
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Observer {
public:
    virtual void update(const string& message) = 0;
};

class Subject {
private:
    vector<Observer*> observers;
public:
  
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void notifyObservers(const string& message) {
        for (Observer* observer : observers) {
            observer->update(message);
        }
    }
};


class NewsAgency : public Subject {
private:
    string news;
public:

    void setNews(const string& newNews) {
        news = newNews;

        notifyObservers(news);
    }
};

class NewsChannel : public Observer {
private:
    string name;
public:
    NewsChannel(const string& channelName) : name(channelName) {}


    void update(const string& message) override {
        cout << "Canal " << name << " ha recibido las noticias: " << message << endl;
    }
};

int main() {
  
    NewsAgency newsAgency;
    NewsChannel cnn("CNN");
    NewsChannel bbc("BBC");
    NewsChannel fox("Fox News");


    newsAgency.addObserver(&cnn);
    newsAgency.addObserver(&bbc);
    newsAgency.addObserver(&fox);

    newsAgency.setNews("¡Nuevo descubrimiento en el espacio!");

    cout << "\nActualización de noticias:\n";
    newsAgency.setNews("La economía global muestra señales de recuperación.");

    return 0;
}
