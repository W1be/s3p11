#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


struct Device {
    string name;
    string type;
    int year;
};


void readFromFile(vector<Device>& devices, const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return;
    }

    Device d;
    while (fin >> d.name >> d.type >> d.year) {
        devices.push_back(d);
    }

    fin.close();
    cout << "Данные успешно загружены (" << devices.size() << " записей)\n";
}


void showDevices(const vector<Device>& devices) {
    if (devices.empty()) {
        cout << "Список устройств пуст.\n";
        return;
    }

    cout << "\nСписок устройств:\n";
    cout << "--------------------------------------\n";
    for (size_t i = 0; i < devices.size(); ++i) {
        cout << i + 1 << ". "
            << devices[i].name << " | "
            << devices[i].type << " | "
            << devices[i].year << endl;
    }
    cout << "--------------------------------------\n";
}


void editDevice(vector<Device>& devices) {
    if (devices.empty()) {
        cout << "Нет данных для редактирования.\n";
        return;
    }

    size_t index;
    cout << "Введите номер записи для редактирования: ";
    cin >> index;

    if (index < 1 || index > devices.size()) {
        cout << "Неверный номер!\n";
        return;
    }

    cout << "Введите новые данные (имя тип год): ";
    cin >> devices[index - 1].name >> devices[index - 1].type >> devices[index - 1].year;
    cout << "Запись обновлена.\n";
}

void calculate(const vector<Device>& devices) {
    if (devices.empty()) {
        cout << "Нет данных для вычислений.\n";
        return;
    }

    int sum = 0;
    for (auto& d : devices)
        sum += d.year;

    double average = static_cast<double>(sum) / devices.size();
    cout << "\nСредний год выпуска устройств: " << average << endl;

    int limit;
    cout << "Введите год, чтобы показать устройства старше его: ";
    cin >> limit;

    cout << "Устройства, выпущенные до " << limit << " года:\n";
    for (auto& d : devices)
        if (d.year < limit)
            cout << d.name << " (" << d.type << "), " << d.year << endl;
}

void saveToFile(const vector<Device>& devices, const string& filename) {
    ofstream fout(filename);
    if (!fout) {
        cout << "Ошибка записи в файл!\n";
        return;
    }

    for (const auto& d : devices) {
        fout << d.name << " " << d.type << " " << d.year << endl;
    }

    fout.close();
    cout << "Данные сохранены в файл " << filename << endl;
}

int main() {
    setlocale(LC_ALL, "ru");

    vector<Device> devices;
    string filename;
    int choice;

    cout << "Введите имя входного файла: ";
    cin >> filename;

    // Пункт 1: чтение данных
    readFromFile(devices, filename);

    // Меню действий
    do {
        cout << "\n=== МЕНЮ ===\n";
        cout << "1. Просмотр данных\n";
        cout << "2. Редактирование записи\n";
        cout << "3. Добавление записи\n";
        cout << "4. Удаление записи\n";
        cout << "5. Вычисления\n";
        cout << "6. Сохранение данных в новый файл\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            showDevices(devices); // пункт 2
            break;
        case 2:
            editDevice(devices); // пункт 3
            break;
        case 3: {
            Device d;
            cout << "Введите данные нового устройства (имя тип год): ";
            cin >> d.name >> d.type >> d.year;
            devices.push_back(d);
            cout << "Устройство добавлено.\n";
            break;
        }
        case 4: {
            if (devices.empty()) { cout << "Нет данных для удаления.\n"; break; }
            size_t index;
            cout << "Введите номер записи для удаления: ";
            cin >> index;
            if (index < 1 || index > devices.size()) {
                cout << "Неверный номер!\n";
                break;
            }
            devices.erase(devices.begin() + index - 1);
            cout << "Запись удалена.\n";
            break;
        }
        case 5:
            calculate(devices); // пункт 4
            break;
        case 6: {
            string outFile;
            cout << "Введите имя выходного файла: ";
            cin >> outFile;
            saveToFile(devices, outFile); // пункт 5
            break;
        }
        case 0:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор, попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}
