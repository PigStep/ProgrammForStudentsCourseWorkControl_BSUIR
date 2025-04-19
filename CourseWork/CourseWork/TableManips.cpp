#include "TableManips.h"

void ClearTerminal() {
    system("cls");
}
void WaitEnterInput() {
    cout << ENTER_INP_WAIT << endl;
    cin.ignore();
    ClearTerminal();
}

ostream& headerBorder(ostream& stream) {
    stream << "+" << setfill('=') << setw(BORDERS_WIDTH) <<"" << "+" << setfill(' ') << endl;
    return stream;
}

void HeaderFirstLevel(int optionsCount, const string optionsArray[], string header) {
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
void HeaderSecondLevel(const string HEADER) { 
    cout << headerBorder;

    cout << "|" << HEADER
        << setw(BORDERS_WIDTH - HEADER.length()) << "" << "|" << endl;

    cout << headerBorder;
}
void LogMessage(string& message) {
    cout << "\n" << setfill('*') << setw(BORDERS_WIDTH) << "" << setfill(' ') << "\n"
        << "  "<< message<<endl
        << setfill('*') << setw(BORDERS_WIDTH) << "" << setfill(' ') << endl;
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


void printBorder(char fill = '=') {
    cout << "+" << string(BORDERS_WIDTH, fill) << "+" << endl;
}

void printTableRow(const string& label, const string& value, char border = '|') {
    // ������������ ����������� ������ ��� ��������
    const int value_width = BORDERS_WIDTH - HEADER_WIDTH * 4 - 4; // 4 = 2 ������� + 2 �������

    cout << border << " "
        << left << setw(HEADER_WIDTH * 4) << label
        << border << " "
        << left << setw(value_width) << value
        << border << endl;
}

void RegistratedStudentTable(Student student) {
    // ������� �������
    printBorder('-');

    printTableRow("ID:", to_string(student.getId()));

    bool isAdmin = student.isUserAdmin();
    printTableRow("������� �������:", ( isAdmin ? "�������������" : "�������"));

    printBorder('-');

    // ������ ������ � ������
    printTableRow("�����:", student.getLogin());
    printTableRow("������:", student.getPassword());

    // �����������
    printBorder('-');

    // ������ ���
    printTableRow("�������:", student.getSecondName());
    printTableRow("���:", student.getName());
    printTableRow("��������:", student.getSurname());

    // �����������
    printBorder('-');
    if (isAdmin)
        return;

    // ������ ������� ����������
    printTableRow("������:", to_string(student.getGroup()));
    printTableRow("����:", to_string(student.getCourse()));

    // ������ �������
    printBorder('-');
}

void StudentWorkCourseTable(StudentCourseWork studentCourseWork) {
    bool isAdmin = studentCourseWork.isUserAdmin();

    if (isAdmin)
        return;

    // ������� �������
    printBorder('-');

    printTableRow("ID:", to_string(studentCourseWork.getId()));

    printBorder('-');

    // ������ ���
    printTableRow("�������:", studentCourseWork.getSecondName());
    printTableRow("���:", studentCourseWork.getName());
    printTableRow("��������:", studentCourseWork.getSurname());

    // �����������
    printBorder('-');
    if (isAdmin)
        return;

    // ������ ������� ����������
    printTableRow("������:", to_string(studentCourseWork.getGroup()));
    printTableRow("����:", to_string(studentCourseWork.getCourse()));

    // �����������
    printBorder('-');

    // ������ ������ �������� ������
    printTableRow("���� ��������:", studentCourseWork.getCourseWorkTheme());
    printTableRow("������ �� ������:", studentCourseWork.getCourseWorkLink());


    printBorder('-');
    for (int i = 0; i < NUM_OF_DEADLINES; i++) {
        string markMessage = "����� �� ����������� ����� (" + courseDeadLinePoints[i].getDate() + "): ";

        string mark = to_string(studentCourseWork.getMark(i));
        bool isDefault = to_string(DEFAULT_MARK) == mark;

        printTableRow(markMessage, (isDefault ? DEFAULT_MARK_TEXT:mark));
    }
    // ������ �������
    printBorder('-');


}