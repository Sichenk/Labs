#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Базовый класс
class PeripheralDevice {
protected:
    int id;
    string brand;
    double price;

public:
    PeripheralDevice(int id, const string& brand, double price)
        : id(id), brand(brand), price(price) {}

    virtual ~PeripheralDevice() {}

    virtual void displayInfo() const = 0;
};

// Класс для наушников
class Headphones : public PeripheralDevice {
private:
    string constructionType;
    string mountingMethod;

public:
    Headphones(int id, const string& brand, double price, const string& constructionType, const string& mountingMethod)
        : PeripheralDevice(id, brand, price), constructionType(constructionType), mountingMethod(mountingMethod) {}

    void displayInfo() const override {
        cout << "Type: Headphones, Brand: " << brand << ", Price: " << price
            << ", Construction Type: " << constructionType
            << ", Mounting Method: " << mountingMethod << endl;
    }
};

// Класс для микрофонов
class Microphone : public PeripheralDevice {
private:
    int frequencyRange;
    int sensitivity;

public:
    Microphone(int id, const string& brand, double price, int frequencyRange, int sensitivity)
        : PeripheralDevice(id, brand, price), frequencyRange(frequencyRange), sensitivity(sensitivity) {}

    void displayInfo() const override {
        cout << "Type: Microphone, Brand: " << brand << ", Price: " << price
            << ", Frequency Range: " << frequencyRange
            << ", Sensitivity: " << sensitivity << endl;
    }
};

// Класс для клавиатур
class Keyboard : public PeripheralDevice {
private:
    string switchType;
    string interface;

public:
    Keyboard(int id, const string& brand, double price, const string& switchType, const string& interface)
        : PeripheralDevice(id, brand, price), switchType(switchType), interface(interface) {}

    void displayInfo() const override {
        cout << "Type: Keyboard, Brand: " << brand << ", Price: " << price
            << ", Switch Type: " << switchType
            << ", Interface: " << interface << endl;
    }
};

// Фабричный метод для создания периферийных устройств
class PeripheralFactory {
public:
    virtual PeripheralDevice* createPeripheral() = 0;
};

// Фабрика для создания наушников
class HeadphonesFactory : public PeripheralFactory {
private:
    int id = 0;
    string brand, constructionType, mountingMethod;
    double price = 0;

public:
    PeripheralDevice* createPeripheral() override {
        cout << "Enter the ID for the headphones: ";
        cin >> id;
        cout << "Enter the brand for the headphones: ";
        cin.ignore();
        getline(cin, brand);
        cout << "Enter the construction type for the headphones: ";
        getline(cin, constructionType);
        cout << "Enter the mounting method for the headphones: ";
        getline(cin, mountingMethod);
        cout << "Enter the price for the headphones: ";
        cin >> price;
        cout << endl;
        return new Headphones(id, brand, price, constructionType, mountingMethod);
    }
};

// Фабрика для создания микрофонов
class MicrophoneFactory : public PeripheralFactory {
private:
    int id = 0, frequencyRange = 0, sensitivity = 0;
    string brand;
    double price = 0;

public:
    PeripheralDevice* createPeripheral() override {
        cout << "Enter the ID for the microphone: ";
        cin >> id;
        cout << "Enter the brand for the microphone: ";
        cin.ignore();
        getline(cin, brand);
        cout << "Enter the frequency range for the microphone: ";
        cin >> frequencyRange;
        cout << "Enter the sensitivity for the microphone: ";
        cin >> sensitivity;
        cout << "Enter the price for the microphone: ";
        cin >> price;
        cout << endl;
        return new Microphone(id, brand, price, frequencyRange, sensitivity);
    }
};

// Фабрика для создания клавиатур
class KeyboardFactory : public PeripheralFactory {
private:
    int id = 0;
    string brand, switchType, interface;
    double price = 0;

public:
    PeripheralDevice* createPeripheral() override {
        cout << "Enter the ID for the keyboard: ";
        cin >> id;
        cout << "Enter the brand for the keyboard: ";
        cin.ignore();
        getline(cin, brand);
        cout << "Enter the switch type for the keyboard: ";
        getline(cin, switchType);
        cout << "Enter the interface for the keyboard: ";
        getline(cin, interface);
        cout << "Enter the price for the keyboard: ";
        cin >> price;
        cout << endl;
        return new Keyboard(id, brand, price, switchType, interface);
    }
};

int main() {
    // Создаем фабрики
    HeadphonesFactory headphonesFactory;
    MicrophoneFactory microphoneFactory;
    KeyboardFactory keyboardFactory;

    vector<PeripheralDevice*> devices;

    while (true) {
        int choice = 0;
        cout << "Available functions: " << endl;
        cout << "<1> Add a device" << endl << "<2> Display a list of all devices" << endl << "<3> Display information on a specific device" << endl << "<-1> Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            // Добавить устройство
        case 1:
            int chosen_number;
            cout << "<1> Headphones" << endl << "<2> Microphone" << endl << "<3> Keyboard" << endl;
            cout << "Enter the device number: ";
            cin >> chosen_number;
            switch (chosen_number) {
                // Выбраны наушники
            case 1:
                devices.push_back(headphonesFactory.createPeripheral());
                break;

                // Выбран микрофон
            case 2:
                devices.push_back(microphoneFactory.createPeripheral());
                break;

                // Выбрана клавиатура
            case 3:
                devices.push_back(keyboardFactory.createPeripheral());
                break;

            default:
                cout << "Invalid number." << endl;
                break;
            }
            break;

            // Вывести все устройства
        case 2:
            cout << "List of all devices:" << endl;
            for (const auto& device : devices) {
                device->displayInfo();
            }
            cout << endl;
            break;

            // Вывести информацию о конкретном устройстве
        case 3:
            int deviceIndex;
            cout << "Enter the index of the device: ";
            cin >> deviceIndex;
            if (deviceIndex >= 0 && deviceIndex < devices.size()) {
                devices[deviceIndex]->displayInfo();
                cout << endl;
            }
            else {
                cout << "Invalid index." << endl;
                cout << endl;
            }
            break;

            // Выход
        case -1:
            for (const auto& device : devices) {
                delete device;
            }
            return 0;
            break;

        default:
            cout << "Invalid number." << endl;
            break;
        }
    }

    return 0;
}