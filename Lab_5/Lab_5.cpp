#include <iostream>
#include <string>
#include <vector>
#include <map>

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
    virtual PeripheralDevice* createPeripheral(int id) = 0;
};

// Фабрика для создания наушников
class HeadphonesFactory : public PeripheralFactory {
private:
    string brand, constructionType, mountingMethod;
    double price = 0;

public:
    PeripheralDevice* createPeripheral(int id) override {
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
    string brand;
    int frequencyRange = 0, sensitivity = 0;
    double price = 0;

public:
    PeripheralDevice* createPeripheral(int id) override {
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
    string brand, switchType, interface;
    double price = 0;

public:
    PeripheralDevice* createPeripheral(int id) override {
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

    map<int, PeripheralDevice*> devicesMap;

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

            // Вводим ID устройства
            int deviceId;
            cout << "Enter the ID for the device: ";
            cin >> deviceId;

            // Проверяем, есть ли устройство с таким же ID
            if (devicesMap.find(deviceId) != devicesMap.end()) {
                cout << "Device with ID " << deviceId << " already exists." << endl;
                break;
            }

            switch (chosen_number) {
                // Выбраны наушники
            case 1:
                devicesMap[deviceId] = headphonesFactory.createPeripheral(deviceId);
                break;

                // Выбран микрофон
            case 2:
                devicesMap[deviceId] = microphoneFactory.createPeripheral(deviceId);
                break;

                // Выбрана клавиатура
            case 3:
                devicesMap[deviceId] = keyboardFactory.createPeripheral(deviceId);
                break;

            default:
                cout << "Invalid number." << endl;
                break;
            }
            break;

            // Вывести все устройства
        case 2:
            cout << "List of all devices:" << endl;
            for (const auto& device : devicesMap) {
                device.second->displayInfo();
            }
            cout << endl;
            break;

            // Вывести информацию о конкретном устройстве
        case 3:
            int deviceIndex;
            cout << "Enter the ID of the device: ";
            cin >> deviceIndex;
            if (devicesMap.find(deviceIndex) != devicesMap.end()) {
                devicesMap[deviceIndex]->displayInfo();
                cout << endl;
            }
            else {
                cout << "Device with ID " << deviceIndex << " not found." << endl;
                cout << endl;
            }
            break;

            // Выход
        case -1:
            // Освобождаем память
            for (const auto& device : devicesMap) {
                delete device.second;
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
