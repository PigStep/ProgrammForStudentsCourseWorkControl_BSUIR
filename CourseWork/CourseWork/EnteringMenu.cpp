#include "TableManips.h"
#include "Student.h"

fstream studentsFileDB; //global file stream variable (link in header)
//vector<StudentCourseWork> students_DB;

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    studentsFileDB.open(DB_FILE_NAME, ios::in | ios::out | ios::app);

    InitializeMenuLoginEntering();
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

    studentsFileDB.close();
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