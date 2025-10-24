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
        cout << "������: �� ������� ������� ���� " << filename << endl;
        return;
    }

    Device d;
    while (fin >> d.name >> d.type >> d.year) {
        devices.push_back(d);
    }

    fin.close();
    cout << "������ ������� ��������� (" << devices.size() << " �������)\n";
}


void showDevices(const vector<Device>& devices) {
    if (devices.empty()) {
        cout << "������ ��������� ����.\n";
        return;
    }

    cout << "\n������ ���������:\n";
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
        cout << "��� ������ ��� ��������������.\n";
        return;
    }

    size_t index;
    cout << "������� ����� ������ ��� ��������������: ";
    cin >> index;

    if (index < 1 || index > devices.size()) {
        cout << "�������� �����!\n";
        return;
    }

    cout << "������� ����� ������ (��� ��� ���): ";
    cin >> devices[index - 1].name >> devices[index - 1].type >> devices[index - 1].year;
    cout << "������ ���������.\n";
}

void calculate(const vector<Device>& devices) {
    if (devices.empty()) {
        cout << "��� ������ ��� ����������.\n";
        return;
    }

    int sum = 0;
    for (auto& d : devices)
        sum += d.year;

    double average = static_cast<double>(sum) / devices.size();
    cout << "\n������� ��� ������� ���������: " << average << endl;

    int limit;
    cout << "������� ���, ����� �������� ���������� ������ ���: ";
    cin >> limit;

    cout << "����������, ���������� �� " << limit << " ����:\n";
    for (auto& d : devices)
        if (d.year < limit)
            cout << d.name << " (" << d.type << "), " << d.year << endl;
}

void saveToFile(const vector<Device>& devices, const string& filename) {
    ofstream fout(filename);
    if (!fout) {
        cout << "������ ������ � ����!\n";
        return;
    }

    for (const auto& d : devices) {
        fout << d.name << " " << d.type << " " << d.year << endl;
    }

    fout.close();
    cout << "������ ��������� � ���� " << filename << endl;
}

int main() {
    setlocale(LC_ALL, "ru");

    vector<Device> devices;
    string filename;
    int choice;

    cout << "������� ��� �������� �����: ";
    cin >> filename;

    // ����� 1: ������ ������
    readFromFile(devices, filename);

    // ���� ��������
    do {
        cout << "\n=== ���� ===\n";
        cout << "1. �������� ������\n";
        cout << "2. �������������� ������\n";
        cout << "3. ���������� ������\n";
        cout << "4. �������� ������\n";
        cout << "5. ����������\n";
        cout << "6. ���������� ������ � ����� ����\n";
        cout << "0. �����\n";
        cout << "��� �����: ";
        cin >> choice;

        switch (choice) {
        case 1:
            showDevices(devices); // ����� 2
            break;
        case 2:
            editDevice(devices); // ����� 3
            break;
        case 3: {
            Device d;
            cout << "������� ������ ������ ���������� (��� ��� ���): ";
            cin >> d.name >> d.type >> d.year;
            devices.push_back(d);
            cout << "���������� ���������.\n";
            break;
        }
        case 4: {
            if (devices.empty()) { cout << "��� ������ ��� ��������.\n"; break; }
            size_t index;
            cout << "������� ����� ������ ��� ��������: ";
            cin >> index;
            if (index < 1 || index > devices.size()) {
                cout << "�������� �����!\n";
                break;
            }
            devices.erase(devices.begin() + index - 1);
            cout << "������ �������.\n";
            break;
        }
        case 5:
            calculate(devices); // ����� 4
            break;
        case 6: {
            string outFile;
            cout << "������� ��� ��������� �����: ";
            cin >> outFile;
            saveToFile(devices, outFile); // ����� 5
            break;
        }
        case 0:
            cout << "����� �� ���������.\n";
            break;
        default:
            cout << "�������� �����, ���������� �����.\n";
        }
    } while (choice != 0);

    return 0;
}
