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
			ReadStudentsFromFile();
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

void ReadStudentsFromFile() {
	getStudentsFromFile(DB_FILE_NAME);

	const string HEADER = "������� ���������";
	HeaderSecondLevel(HEADER);

	for (int i = 0; i < students_data.size(); i++) {
		RegistratedStudentTable(students_data[i]);
	}

	cin.get();
	WaitEnter();
}

void AddStudent() {
	const string HEADER = "����������� ��������";
	HeaderSecondLevel(HEADER);

	int userLevel;
	string name;
	string secondname;
	string surname;
	int group;
	int course;

	int currentStudentsNum = students_data.size() +1;

	string login;
	string password;

	int n;
	cout << left << setw(INPUT_PADDING) << "������� ���������� ����������� �������: ";
	cin >> n;
	cin.ignore(); // ������� ������ ����� cin >> 

	for (int i = 0; i < n; i++) {

		//������� �������
		cout << "������� ������� ������ (0 - �������, 1 - �������������): ";
		cin >> userLevel;
		cin.ignore();

		// ���� �����
		cout << "������ " << i + 1<<":\n\n";

		// ���� ������
		cout << left << setw(INPUT_PADDING) << "�����: ";
		getline(cin, login);

		// ���� ������
		cout << left << setw(INPUT_PADDING) << "������: ";
		getline(cin, password);

		cout << left << setw(INPUT_PADDING) << "���: ";
		getline(cin, name);

		// ���� �������
		cout << left << setw(INPUT_PADDING) << "�������: ";
		getline(cin, secondname);

		// ���� ��������
		cout << left << setw(INPUT_PADDING) << "��������: ";
		getline(cin, surname);

		if (userLevel == 1) {
			StudentCourseWork StudentCourse(
				currentStudentsNum + i,
				userLevel,
				password, 
				login, 
				name, 
				secondname, 
				surname);

			studentsFileDB << StudentCourse;
			return;
		}
		// ���� ������ (�����)
		cout << left << setw(INPUT_PADDING) << "������: ";
		cin >> group;
		cin.ignore();  // ������� ������ ����� cin >> 

		// ���� ����� (�����)
		cout << left << setw(INPUT_PADDING) << "����: ";
		cin >> course;
		cin.ignore();  // ������� ������ ����� cin >>


		StudentCourseWork StudentCourse(
			currentStudentsNum + i,
			userLevel,
			password,
			login,
			name, 
			secondname, 
			surname, 
			group, 
			course);

		studentsFileDB << StudentCourse;
	}
}