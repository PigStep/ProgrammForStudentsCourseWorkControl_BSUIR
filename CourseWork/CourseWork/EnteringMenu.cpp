#include "TableManips.h"
#include "StudentFileManip.h"

fstream studentsFileReg; 
fstream studentsFileData;
fstream studentsFileDeadLines;


int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    FilePreparation();

    InitializeMenuLoginEntering();
}

void FilePreparation(){
    studentsFileReg.open(STUD_REG_FILE, ios::in | ios::out | ios::app);
    studentsFileData.open(STUD_DATA_FILE, ios::in | ios::out | ios::app);
    studentsFileDeadLines.open(DEAD_LINES_FILE, ios::in | ios::out | ios::app);

    LoadDeadlinesFromFile();
    LoadStudentsFromFile();
}

void InitializeMenuLoginEntering() {
    int choice;

    do {
        ClearTerminal();
        const string OPTIONS_TO_CHOOSE[2] = {"Вход как пользователь (в разработке)","Вход как администратор"};
        HeaderFirstLevel(2,OPTIONS_TO_CHOOSE,"СИСТЕМА ВХОДА");

        cin >> choice;

        LoadStudentsFromFile();

        ClearTerminal();

        switch (choice) {
        case 1: 
            UserAuthorizationMenu(false); //log as user
            break;
        case 2:
            if (UserAuthorizationMenu(true)) { //log as admin
                AdminFunctionsMenu();
            }
            break;
        case 0:
            cout << "Выход из программы...\n";
            break;
        default:
            cout << "Неверный выбор! Попробуйте снова.\n";
        }
        WaitEnterInput();
        ClearTerminal();

    } while (choice != 0);

    studentsFileReg.close();
    studentsFileDeadLines.close();
}

bool UserAuthorizationMenu(bool isAdmin) {
    LoginFormHeader(isAdmin); //show authorization menu

    string login, password;

    cout << left << setw(INPUT_PADDING) << "Логин: ";
    cin.get();
    getline(cin, login);

    cout << left << setw(INPUT_PADDING) << "Пароль: ";
    getline(cin, password);


    bool isRegistrated = CheckRegistration(isAdmin,login,password);

    if (isRegistrated)
        LoginAutorizationStatus(isAdmin);
    else
    {
        cout << REG_AUTH_FAIL<<endl;
        return false;
    }

    WaitEnterInput();

    return true;
}

bool CheckRegistration(bool isAdmin, string& login, string& password) {
    for (int i = 0; i < studentsArray.size(); i++) {
        if (studentsArray[i].getLogin() == login 
            && studentsArray[i].getPassword() == password
            && (bool)studentsArray[i].getUserLevel() == isAdmin) {
            return true;
        }
    }
    return false;
}