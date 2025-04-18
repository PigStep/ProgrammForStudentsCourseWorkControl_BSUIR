#include "TableManips.h"

void ClearTerminal() {
    system("cls");
}
void WaitEnterInput() {
    cout << ENTER_INP_WAIT << endl;
    cin.get();
    ClearTerminal();
}

ostream& headerBorder(ostream& stream) {
    stream << "+" << setfill('=') << setw(BORDERS_WIDTH) <<"" << "+" << setfill(' ') << endl;
    return stream;
}

void MenuWithOptionsHeaderCentralized(int optionsCount, const string optionsArray[], string header) {
    // Верхняя граница
    cout << headerBorder;

    int total_width = BORDERS_WIDTH - 1; // -1 для границ
    int padding = (total_width - header.length()) / 2;

    cout << "|" << setw(padding + header.length()) << right << header
        << setw(total_width - padding - header.length() + 2) << "|" << endl;

    // Разделитель
    cout << headerBorder;

    for (int i = 0; i < optionsCount; i++) {
        cout << "|"
            << left
            << setw(OPTIONS_PADDING) << (to_string(i + 1) + ".")  // "1. ", "10." и т.д.
            << setw(BORDERS_WIDTH - OPTIONS_PADDING) << optionsArray[i]
            << "|" << endl;

        cout << "+" << setfill('-') << setw(BORDERS_WIDTH) <<"" << "+" << setfill(' ') << endl;
    }

    cout << "|" << left << setw(OPTIONS_PADDING) << "0." << setw(BORDERS_WIDTH - OPTIONS_PADDING) << "Выход" << "|" << endl;

    // Нижняя граница
    cout << headerBorder;
    cout << "Ваш выбор: ";
}
void HeaderSecondLevel(const string HEADER) { 
    cout << headerBorder;

    cout << "|" << HEADER
        << setw(BORDERS_WIDTH - HEADER.length()) << "" << "|" << endl;

    cout << headerBorder;
}
void LoginFormHeader(bool isAdmin) {
    // Верхняя граница
    cout << headerBorder;

    cout << "|" << " ВХОД " << (isAdmin ? "АДМИНИСТРАТОР" : "ПОЛЬЗОВАТЕЛЬ")
        << setw(BORDERS_WIDTH - 7 - (isAdmin ? 12 : 10)) << "" << "|" << endl;

    cout << headerBorder;
}

void LoginAutorizationStatus(bool isAdmin) {
    cout << "\n" << setfill('*') << setw(BORDERS_WIDTH) << "" << setfill(' ') << "\n"
        << "  Вход выполнен как " << (isAdmin ? "администратор" : "пользователь") << "!\n"
        << setfill('*') << setw(BORDERS_WIDTH) << "" << setfill(' ') << endl;
}


void printBorder(char fill = '=') {
    cout << "+" << string(BORDERS_WIDTH - 2, fill) << "+" << endl;
}

void printTableRow(const string& label, const string& value, char border = '|') {
    cout << border << " " << left << setw(HEADER_PADDING * 4) << label
        << border << " " << setw(BORDERS_WIDTH - HEADER_PADDING * 4 - OPTIONS_PADDING-1) << value
        << " " << border << endl;
}

void RegistratedStudentTable(Student student) {
    // Верхняя граница
    printBorder('-');

    printTableRow("ID:", to_string(student.getId()));

    bool isAdmin = student.isUserAdmin();
    printTableRow("УРОВЕНЬ ДОСТУПА:", ( isAdmin ? "ПРЕПОДАВАТЕЛЬ" : "СТУДЕНТ"));

    printBorder('-');

    // Секция логина и пароля
    printTableRow("Логин:", student.getLogin());
    printTableRow("Пароль:", student.getPassword());

    // Разделитель
    printBorder('-');

    // Секция ФИО
    printTableRow("Имя:", student.getName());
    printTableRow("Фамилия:", student.getSecondName());
    printTableRow("Отчество:", student.getSurname());

    // Разделитель
    printBorder('-');
    if (isAdmin)
        return;

    // Секция учебной информации
    printTableRow("Группа:", to_string(student.getGroup()));
    printTableRow("Курс:", to_string(student.getCourse()));

    // Нижняя граница
    printBorder('-');
}

void StudentWorkCourseTable(StudentCourseWork studentCourseWork) {
    bool isAdmin = studentCourseWork.isUserAdmin();

    if (isAdmin)
        return;

    // Верхняя граница
    printBorder('-');

    printTableRow("ID:", to_string(studentCourseWork.getId()));

    printBorder('-');

    // Секция ФИО
    printTableRow("Имя:", studentCourseWork.getName());
    printTableRow("Фамилия:", studentCourseWork.getSecondName());
    printTableRow("Отчество:", studentCourseWork.getSurname());

    // Разделитель
    printBorder('-');
    if (isAdmin)
        return;

    // Секция учебной информации
    printTableRow("Группа:", to_string(studentCourseWork.getGroup()));
    printTableRow("Курс:", to_string(studentCourseWork.getCourse()));

    // Нижняя граница
    printBorder('-');

    // Секция данных курсовой работы
    printTableRow("Тема курсовой:", studentCourseWork.getCourseWorkTheme());
    printTableRow("Ссылка на ресурс:", studentCourseWork.getCourseWorkLink());

    // Нижняя граница
    printBorder('-');
}