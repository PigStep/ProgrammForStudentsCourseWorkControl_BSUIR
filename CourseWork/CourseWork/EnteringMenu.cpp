#include "TableManips.h"

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    InitializeMenuLoginEntering();
}


void InitializeMenuLoginEntering() {
    int choice;

    //do {
        const string OPTIONS_TO_CHOOSE[2] = {"Вход как пользователь (в разработке)","Вход как администратор"};
        PrintMenuWithOptionsHeaderCentralized(2,OPTIONS_TO_CHOOSE,"СИСТЕМА ВХОДА");

        cin >> choice;

        switch (choice) {
        case 1:
            ClearTerminal();
            ShowLoginForm(false);
            break;
        case 2:
            ClearTerminal();
            ShowLoginForm(true);
            AdminFunctionsMenu();
            break;
        case 0:
            cout << "Выход из программы...\n";
            break;
        default:
            cout << "Неверный выбор! Попробуйте снова.\n";
        }


    //} while (choice != 0);
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

    //CheckPaswordAdmin();

    cout << "\n" << setfill('*') << setw(BORDERS_WIDTH) << "" << setfill(' ') << "\n"
        << "  Вход выполнен как " << (isAdmin ? "администратор" : "пользователь") << "!\n"
        << setfill('*') << setw(BORDERS_WIDTH) << "" << setfill(' ') << endl;

    cout << "Нажмите Enter для продолжения"<<endl;
    cin.get();
    ClearTerminal();
}