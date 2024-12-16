#include <iostream>
#include <memory>

using namespace std;

// Interfaces para Botón
class Button {
public:
    virtual void paint() = 0;
    virtual ~Button() = default;
};

// Interfaces para CheckBox
class CheckBox {
public:
    virtual void paint() = 0;
    virtual ~CheckBox() = default;
};

// Botones para Windows
class WindowsButton : public Button {
public:
    void paint() override {
        cout << "Renderizando boton de Windows" << endl;
    }
};

class WindowsCheckBox : public CheckBox {
public:
    void paint() override {
        cout << "Renderizando checkbox de Windows" << endl;
    }
};

// Botones para MacOS
class MacButton : public Button {
public:
    void paint() override {
        cout << "Renderizando boton de MacOS" << endl;
    }
};

class MacCheckBox : public CheckBox {
public:
    void paint() override {
        cout << "Renderizando checkbox de MacOS" << endl;
    }
};

// Abstract Factory
class GUIFactory {
public:
    virtual unique_ptr<Button> createButton() = 0;
    virtual unique_ptr<CheckBox> createCheckBox() = 0;
    virtual ~GUIFactory() = default;
};

// Concrete Factories
class WindowsFactory : public GUIFactory {
public:
    unique_ptr<Button> createButton() override {
        return make_unique<WindowsButton>();
    }
    unique_ptr<CheckBox> createCheckBox() override {
        return make_unique<WindowsCheckBox>();
    }
};

class MacFactory : public GUIFactory {
public:
    unique_ptr<Button> createButton() override {
        return make_unique<MacButton>();
    }
    unique_ptr<CheckBox> createCheckBox() override {
        return make_unique<MacCheckBox>();
    }
};

int main() {
    WindowsFactory windowsFactory;
    MacFactory macFactory;

    auto windowsButton = windowsFactory.createButton();
    auto windowsCheckbox = windowsFactory.createCheckBox();

    auto macButton = macFactory.createButton();
    auto macCheckbox = macFactory.createCheckBox();

    windowsButton->paint();
    windowsCheckbox->paint();
    macButton->paint();
    macCheckbox->paint();

    return 0;
}
