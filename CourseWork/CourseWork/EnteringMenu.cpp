#include "TableManips.h"
#include "StudentFileManip.h"

fstream studentsFileReg; 
fstream studentsFileData;
fstream studentsFileDeadLines;

StudentCourseWork* userAccount;

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    FilePreparation();

    InitializeMenuLoginEntering();
}

//Функция провери и создания Админа в случае его отсутвия
void CheckAdmins() {
    if (AdminArrayCount() == 0) {
        CreateBaseAdmin();
        cout << NO_ADMIN_FOUND << endl;
    }

}

void FilePreparation(){
    studentsFileReg.open(STUD_REG_FILE, ios::in | ios::out | ios::app);
    studentsFileData.open(STUD_DATA_FILE, ios::in | ios::out | ios::app);
    studentsFileDeadLines.open(DEAD_LINES_FILE, ios::in | ios::out | ios::app);


    LoadStudentsFromFile();
    CheckAdmins();

    LoadDeadlinesFromFile();
    LoadStudentsFromFile();
}

void InitializeMenuLoginEntering() {
    int choice;

    do {
        const string OPTIONS_TO_CHOOSE[2] = {"Вход как пользователь","Вход как администратор"};
        HeaderFirstLevel(2,OPTIONS_TO_CHOOSE,"СИСТЕМА ВХОДА");

        cin >> choice;

        LoadStudentsFromFile();

        ClearTerminal();

        switch (choice) {
        case 1: 
            if (UserAuthorizationMenu(false)) {
                UserFunctionsMenu();
            }
            break;
        case 2:
            if (UserAuthorizationMenu(true)) {
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
    LoginFormHeader(isAdmin);

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
            && studentsArray[i].checkPassword(password)
            && (bool)studentsArray[i].getUserLevel() == isAdmin) {
            userAccount = &studentsArray[i];
            return true;
        }
    }
    return false;
}