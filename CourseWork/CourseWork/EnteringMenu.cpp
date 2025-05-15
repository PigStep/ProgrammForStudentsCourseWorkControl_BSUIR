#include "TableManips.h"
#include "StudentFileManip.h"

fstream studentsFileReg; 
fstream studentsFileData;
fstream studentsFileDeadLines;

StudentCourseWork* userAccountLink;

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

        choice = GetIntegerInput(0,2);

        LoadStudentsFromFile();

        ClearTerminal();

        switch (choice) {
        case 1: 
            if (UserAuthorizationMenu(false)) {
                UserFunctionsMenu();
            }
            else
                WaitEnterInput();
            break;
        case 2:
            if (UserAuthorizationMenu(true)) {
                AdminFunctionsMenu();
            }
            else
                WaitEnterInput();
            break;
        case 0:
            return;
            break;
        default:
            break;
        }
    } while (choice != 0);

    studentsFileReg.close();
    studentsFileDeadLines.close();
}

bool UserAuthorizationMenu(bool isAdmin) {
    LoginFormHeader(isAdmin);

    string login, password;

    login = GetStringInput("Логин: ",false);

    password = GetPasswordInput("Пароль: ");

    bool isRegistrated = CheckRegistration(isAdmin,login,password);

    if (isRegistrated)
        LoginAutorizationStatus(isAdmin);
    else {
        if (!isAdmin && !IsLoginExist(login)) {
            cout << "Возможна регистрация пользователя с логином: " << login << endl;
            if (GetUserApprove()) {
                RegistrateStudentInFile(false, login);

                string successMessage = "УСПЕШНО, ОЖИДАЙТЕ ПОДТВЕРЖДЕНИЕ АДМИНИСТРАТОРОМ";
                LogMessage(successMessage);

                WaitEnterInput();
            }
        }
        return false;
    }
;

    WaitEnterInput();

    return true;
}