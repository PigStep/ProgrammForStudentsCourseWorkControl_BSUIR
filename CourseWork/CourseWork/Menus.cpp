#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <cstdlib>


using namespace std;

#define BORDERS_WIDTH 100
#define HEADER_NAME_WIDTH 50
#define OPTIONS_WIDTH 50

void InitializeMenu();

void PrintMenu();

void ShowLoginForm(bool);

void ClearTerminal() {
    system("cls");
}

ostream& headerBorder(ostream& stream) {
    stream << "+" << setfill('=') << setw(BORDERS_WIDTH) << "+" << setfill(' ') << endl;
    return stream;
}

ostream& header(ostream& stream){
    string header = "СИСТЕМА ВХОДА";

    int total_width = BORDERS_WIDTH - 2; // -2 для границ
    int padding = (total_width - header.length()) / 2;

    stream << "|" << setw(padding + header.length()) << right << header
        << setw(total_width - padding - header.length() +2) << "|" << endl;

    return stream;
}

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    InitializeMenu();
}

void InitializeMenu() {
    int choice;

    do {
        PrintMenu();

        cin >> choice;

        switch (choice) {
        case 1:
            ClearTerminal();
            ShowLoginForm(false);
            break;
        case 2:
            ClearTerminal();
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
    // Верхняя граница
    cout << headerBorder;
    // Заголовок
    cout << header;
    // Разделитель
    cout << headerBorder;

    // Опции выбора
    cout << "|" << left << setw(BORDERS_WIDTH - 1) << " 1. Вход как пользователь (в разработке)" << "|" << endl;
    cout << "+" << setfill('-') << setw(BORDERS_WIDTH) << "+" << setfill(' ') << endl;

    cout << "|" << setw(BORDERS_WIDTH - 1) << " 2. Вход как администратор" << "|" << endl;
    cout << "+" << setfill('-') << setw(BORDERS_WIDTH) << "+" << setfill(' ') << endl;

    cout << "|" << setw(BORDERS_WIDTH - 1) << " 0. Выход" << "|" << endl;

    // Нижняя граница
    cout << "+" << setfill('=') << setw(BORDERS_WIDTH) << "+" << setfill(' ') << endl;
    cout << "Ваш выбор: ";
}

void ShowLoginForm(bool isAdmin) {
    string login, password;

    // Верхняя граница
    cout << headerBorder;

    cout << "|" << " ВХОД " << (isAdmin ? "АДМИНИСТРАТОР" : "ПОЛЬЗОВАТЕЛЬ")
        << setw(BORDERS_WIDTH - 8 - (isAdmin ? 12 : 10)) << " " << "|" << endl;

    cout << headerBorder;

    cout << left << setw(10) << "Логин: ";
    cin.get();
    getline(cin, login);

    cout << left << setw(10) << "Пароль: ";
    getline(cin, password);

    cout << "\n" << setfill('*') << setw(BORDERS_WIDTH) << "" << setfill(' ') << "\n"
        << "  Вход выполнен как " << (isAdmin ? "администратор" : "пользователь") << "!\n"
        << setfill('*') << setw(BORDERS_WIDTH) << "" << setfill(' ') << "\n"<<endl;
}