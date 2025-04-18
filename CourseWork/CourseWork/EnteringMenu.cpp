#include "TableManips.h"
#include "Student.h"

fstream studentsFileReg; 
fstream studentsCorseDeadLines;

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    FilePreparation();

    InitializeMenuLoginEntering();
}

void FilePreparation(){
    studentsFileReg.open(STUD_REG_FILE, ios::in | ios::out | ios::app);
    studentsCorseDeadLines.open(DEAD_LINES_FILE, ios::in | ios::out | ios::app);

    LoadDeadlinesFromFile();
    GetStudentsFromFile();
}

void InitializeMenuLoginEntering() {
    int choice;

    do {
        const string OPTIONS_TO_CHOOSE[2] = {"Вход как пользователь (в разработке)","Вход как администратор"};
        MenuWithOptionsHeaderCentralized(2,OPTIONS_TO_CHOOSE,"СИСТЕМА ВХОДА");

        cin >> choice;

        ClearTerminal();

        switch (choice) {
        case 1: 
            UserAuthorizationMenu(false); //log as user
            break;
        case 2:
            UserAuthorizationMenu(true); //log as admin
            AdminFunctionsMenu();
            break;
        case 0:
            cout << "Выход из программы...\n";
            break;
        default:
            cout << "Неверный выбор! Попробуйте снова.\n";
        }


    } while (choice != 0);

    studentsFileReg.close();
    studentsCorseDeadLines.close();
}

bool UserAuthorizationMenu(bool isAdmin) {
    LoginFormHeader(isAdmin); //show authorization menu

    string login, password;

    cout << left << setw(INPUT_PADDING) << "Логин: ";
    cin.get();
    getline(cin, login);

    cout << left << setw(INPUT_PADDING) << "Пароль: ";
    getline(cin, password);

    LoginAutorizationStatus(isAdmin);


    WaitEnterInput();

    return true;
}