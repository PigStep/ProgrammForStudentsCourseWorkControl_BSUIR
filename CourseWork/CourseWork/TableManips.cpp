#include "TableManips.h"

void ClearTerminal() {
    system("cls");
}

ostream& headerBorder(ostream& stream) {
    stream << "+" << setfill('=') << setw(BORDERS_WIDTH) << "+" << setfill(' ') << endl;
    return stream;
}

void PrintMenuWithOptionsHeaderCentralized(int optionsCount, const string optionsArray[], string header) {
    // Верхняя граница
    cout << headerBorder;

    int total_width = BORDERS_WIDTH - 2; // -2 для границ
    int padding = (total_width - header.length()) / 2;

    cout << "|" << setw(padding + header.length()) << right << header
        << setw(total_width - padding - header.length() + 2) << "|" << endl;

    // Разделитель
    cout << headerBorder;

    for (int i = 0; i < optionsCount; i++) {
        cout << "|"
            << left
            << setw(OPTIONS_PADDING) << (to_string(i + 1) + ".")  // "1. ", "10." и т.д.
            << setw(BORDERS_WIDTH - OPTIONS_PADDING - 1) << optionsArray[i]
            << "|" << endl;

        cout << "+" << setfill('-') << setw(BORDERS_WIDTH) << "+" << setfill(' ') << endl;
    }

    cout << "|" << left << setw(OPTIONS_PADDING) << "0." << setw(BORDERS_WIDTH - OPTIONS_PADDING - 1) << "Выход" << "|" << endl;

    // Нижняя граница
    cout << "+" << setfill('=') << setw(BORDERS_WIDTH) << "+" << setfill(' ') << endl;
    cout << "Ваш выбор: ";
}