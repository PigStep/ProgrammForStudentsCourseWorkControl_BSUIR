#include "TableManips.h"

void ClearTerminal() {
    system("cls");
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
void SubHeader(const string HEADER) { 
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