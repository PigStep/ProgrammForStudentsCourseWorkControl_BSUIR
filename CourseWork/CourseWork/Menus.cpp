#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <limits>

using namespace std;

void InitializeMenu();

void PrintMenu();

void ShowLoginForm(bool);

void ClearCin();

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    InitializeMenu();
}

void ClearCin() {
    cin.clear();
}

void InitializeMenu() {
    int choice;

    do {
        PrintMenu();

        cin >> choice;
        ClearCin();

        switch (choice) {
        case 1:
            ShowLoginForm(false);
            break;
        case 2:
            ShowLoginForm(true);
            break;
        case 0:
            cout << "Выход из программы...\n";
            break;
        default:
            cout << "Неверный выбор! Попробуйте снова.\n";
        }

    } while (choice != 0);
}

void PrintMenu() {
    const int BORDERS_WIDTH = 100;
    const int HEADER_NAME_WIDTH = 50;

    const int OPTIONS_WIDTH = 50;
    //заголовок

    cout << setfill('=') << setw(BORDERS_WIDTH) << "" << setfill(' ') << endl;
    cout << setw(HEADER_NAME_WIDTH) << "СИСТЕМА ВХОДА" << endl;
    cout << setfill('=') << setw(BORDERS_WIDTH) << "" << setfill(' ') << endl;

    //опции выбора
    cout << left << setw(OPTIONS_WIDTH) << "1. Вход как пользователь (в разработке)" << endl;
    cout << setfill('-') << setw(BORDERS_WIDTH) << "" << setfill(' ') << endl;

    cout << setw(OPTIONS_WIDTH) << "2. Вход как администратор" << endl;
    cout << setfill('-') << setw(BORDERS_WIDTH) << "" << setfill(' ') << endl;

    cout << setw(OPTIONS_WIDTH) << "0. Выход" << endl;

    cout << setfill('=') << setw(BORDERS_WIDTH) << "" << setfill(' ') << endl;
    cout << "Ваш выбор: ";
}

void ShowLoginForm(bool isAdmin) {
    string login, password;

    cout << setfill('-') << setw(40) << "" << setfill(' ') << "\n"
        << "  " << (isAdmin ? "АДМИНИСТРАТОР" : "ПОЛЬЗОВАТЕЛЬ") << "\n"
        << setfill('-') << setw(40) << "" << setfill(' ') << "\n";

    cout << left << setw(10) << "Логин: ";
    cin.get();
    getline(cin, login);

    cout << left << setw(10) << "Пароль: ";
    getline(cin, password);

    cout << "\n" << setfill('*') << setw(40) << "" << setfill(' ') << "\n"
        << "  Вход выполнен как " << (isAdmin ? "администратор" : "пользователь") << "!\n"
        << setfill('*') << setw(40) << "" << setfill(' ') << "\n\n";
}