#include "TableManips.h"
#include "Student.h"

extern void AdminFunctionsMenu() {
	const string OPTIONS_TO_CHOOSE[4] = {"����������� ��������� �������� � �������� ��������", "������������ ������ ������� ���������", "���������� ����������� ����� ��� �����", "�������� �������������� �����"};
	const string HEADER = { "���� ��������������" };
	int n;

	do {
		MenuWithOptionsHeaderCentralized(4, OPTIONS_TO_CHOOSE, HEADER);
		cin >> n;

		ClearTerminal();

		switch (n)
		{
		case(1):
			StudentsListOperations();
			break;
		default:
			break;
		}

		ClearTerminal();
	} while (n != 0);

}

void RegistrateStudents() {
	const string HEADER = "���������� ������� ������ ��������";

	HeaderSecondLevel(HEADER);

	cin.get();
	cout << "������� Enter ��� �����������" << endl;
	cin.get();
	
}

void StudentsListOperations() {
	const string OPTIONS_TO_CHOOSE[4] = { "����������� ��� ������� ������","�������� ������� ������/������", "������� ������� ������/������", "�������� ������� ������/������" };
	const string HEADER = { "���� �������� � �������� ��������" };
	int n;

	do {
		MenuWithOptionsHeaderCentralized(4, OPTIONS_TO_CHOOSE, HEADER);
		cin >> n;

		ClearTerminal();

		switch (n)
		{
		case(1):
			readStudentsFromFile(studentsFileDB);
			break;
		case(2):
			AddStudent();
			break;
		default:
			break;
		}

		ClearTerminal();
	} while (n != 0);

}
void readStudentsFromFile(fstream& file) {
	// ���������� ��������� ������ � ������ �����
	file.seekg(0, ios::beg);

	string line;
	while (getline(file, line)) {  // ������ ��������� �� ����� �����
		cout << line << endl;      // ������� ����������� ������ (����� �������)
	}

	// ����� ������ ���������� ��������� ������ � ����� ����� (���� ����� ����������)
	file.seekp(0, ios::end);
}

void AddStudent() {
	const string HEADER = "����������� ��������";
	HeaderSecondLevel(HEADER);

	string name;
	string secondname;
	string surname;
	int group;
	int course;

	int n;
	cout << left << setw(ENTER_PADDING) << "������� ���������� ����������� ���������: ";
	cin >> n;
	cin.ignore(); // ������� ������ ����� cin >> 

	for (int i = 0; i < n; i++) {
		// ���� �����
		cout << "������� " << i + 1<<":\n";
		cout << left << setw(ENTER_PADDING) << "���: ";
		getline(cin, name);

		// ���� �������
		cout << left << setw(ENTER_PADDING) << "�������: ";
		getline(cin, secondname);

		// ���� ��������
		cout << left << setw(ENTER_PADDING) << "��������: ";
		getline(cin, surname);

		// ���� ������ (�����)
		cout << left << setw(ENTER_PADDING) << "������: ";
		cin >> group;
		cin.ignore();  // ������� ������ ����� cin >> 

		// ���� ����� (�����)
		cout << left << setw(ENTER_PADDING) << "����: ";
		cin >> course;
		cin.ignore();  // ������� ������ ����� cin >>


		StudentCourseWork StudentCourse(name, secondname, surname, group, course);

		studentsFileDB << StudentCourse;
	}
}