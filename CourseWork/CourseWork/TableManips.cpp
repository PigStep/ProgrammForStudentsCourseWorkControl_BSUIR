#include "TableManips.h"

void ClearTerminal() {
    system("cls");
}

ostream& headerBorder(ostream& stream) {
    stream << "+" << setfill('=') << setw(BORDERS_WIDTH) <<"" << "+" << setfill(' ') << endl;
    return stream;
}

void MenuWithOptionsHeaderCentralized(int optionsCount, const string optionsArray[], string header) {
    // ������� �������
    cout << headerBorder;

    int total_width = BORDERS_WIDTH - 1; // -1 ��� ������
    int padding = (total_width - header.length()) / 2;

    cout << "|" << setw(padding + header.length()) << right << header
        << setw(total_width - padding - header.length() + 2) << "|" << endl;

    // �����������
    cout << headerBorder;

    for (int i = 0; i < optionsCount; i++) {
        cout << "|"
            << left
            << setw(OPTIONS_PADDING) << (to_string(i + 1) + ".")  // "1. ", "10." � �.�.
            << setw(BORDERS_WIDTH - OPTIONS_PADDING) << optionsArray[i]
            << "|" << endl;

        cout << "+" << setfill('-') << setw(BORDERS_WIDTH) <<"" << "+" << setfill(' ') << endl;
    }

    cout << "|" << left << setw(OPTIONS_PADDING) << "0." << setw(BORDERS_WIDTH - OPTIONS_PADDING) << "�����" << "|" << endl;

    // ������ �������
    cout << headerBorder;
    cout << "��� �����: ";
}
void SubHeader(const string HEADER) { 
    cout << headerBorder;

    cout << "|" << HEADER
        << setw(BORDERS_WIDTH - HEADER.length()) << "" << "|" << endl;

    cout << headerBorder;
}
void LoginFormHeader(bool isAdmin) {
    // ������� �������
    cout << headerBorder;

    cout << "|" << " ���� " << (isAdmin ? "�������������" : "������������")
        << setw(BORDERS_WIDTH - 7 - (isAdmin ? 12 : 10)) << "" << "|" << endl;

    cout << headerBorder;
}

void LoginAutorizationStatus(bool isAdmin) {
    cout << "\n" << setfill('*') << setw(BORDERS_WIDTH) << "" << setfill(' ') << "\n"
        << "  ���� �������� ��� " << (isAdmin ? "�������������" : "������������") << "!\n"
        << setfill('*') << setw(BORDERS_WIDTH) << "" << setfill(' ') << endl;
}