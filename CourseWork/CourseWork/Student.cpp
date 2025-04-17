#include "Student.h"
#include "TableManips.h";

vector<StudentCourseWork> students_data;

void Student::StudentEdit(const int bordersWidth, const int optionsPadding, const int inputPadding) {
	int choice;
	string newString;
	int newInt;

	do {
		// ����� ���� ������ ���������
		cout << setw(optionsPadding) << "" << "�������� �������� ��� ���������:\n";
		cout << setw(optionsPadding) << "" << "1. ���\n";
		cout << setw(optionsPadding) << "" << "2. �������\n";
		cout << setw(optionsPadding) << "" << "3. ��������\n";
		cout << setw(optionsPadding) << "" << "4. ������\n";
		cout << setw(optionsPadding) << "" << "5. ����\n";
		cout << setw(optionsPadding) << "" << "6. �����\n";
		cout << setw(optionsPadding) << "" << "7. ������\n\n";
		cout << setw(optionsPadding) << "" << "0. �����\n\n";

		// ���� ������ ������������
		cout << setw(inputPadding) << "" << "��� �����: ";
		cin >> choice;

		// ��������� ������
		switch (choice) {
		case 1:
			cout << setw(inputPadding) << "" << "������� ����� ���: ";
			cin >> newString;
			name = newString;
			break;
		case 2:
			cout << setw(inputPadding) << "" << "������� ����� �������: ";
			cin >> newString;
			secondname = newString;
			break;
		case 3:
			cout << setw(inputPadding) << "" << "������� ����� ��������: ";
			cin >> newString;
			surname = newString;
			break;
		case 4:
			cout << setw(inputPadding) << "" << "������� ����� ������: ";
			cin >> newInt;
			group = newInt;
			break;
		case 5:
			cout << setw(inputPadding) << "" << "������� ����� ����: ";
			cin >> newInt;
			course = newInt;
			break;
		case 6:
			cout << setw(inputPadding) << "" << "������� ����� �����: ";
			cin >> newString;
			login = newString;
			break;
		case 7:
			cout << setw(inputPadding) << "" << "������� ����� ������: ";
			cin >> newString;
			password = newString;
			break;
		case 0:
			break;
		default:
			cout << setw(inputPadding) << "" << "������: �������� �����!\n";
			break;
		}
	} while (choice != 0);
	
}

void getStudentsFromFile(const string& filename) {
	students_data;
	ifstream file(filename);

	students_data.clear();

	if (!file.is_open()) {
		throw runtime_error("Failed to open file: " + filename);
	}

	string line;
	while (getline(file, line)) {
		if (line.empty()) continue; // ���������� ������ ������

		istringstream iss(line);
		string token;
		vector<string> tokens;

		// ��������� ������ �� ����������� ';'
		while (getline(iss, token, ';')) {
			tokens.push_back(token);
		}

		// ���������, ��� �������� ��� 11 ����� (10 ';' � ������)
		if (tokens.size() != 11) {
			continue;
		}

		// ������� ������ StudentCourseWork
		// ����������� ������ � ���� �� ������ � �����
		int id = stoi(tokens[0]);
		int userLevel = stoi(tokens[1]);
		int group, course = -1;

		if(!tokens[7].empty())
			 group = stoi(tokens[7]);

		if (!tokens[8].empty())
			 course = stoi(tokens[8]);

		StudentCourseWork student(
			id,
			userLevel, 
			tokens[3], // password
			tokens[2], // login
			tokens[4], // name
			tokens[5], // secondname
			tokens[6], // surname
			group,
			course
		);

		// ������������� �������������� ����
		student.SetCourseWorkTheme(tokens[7]);
		student.SetCourseWorkStorageLink(tokens[8]);

		students_data.push_back(student);

	}
}

void RegistrateStudentInFile() {

	int userLevel;
	string name;
	string secondname;
	string surname;
	int group;
	int course;

	string login;
	string password;
	int currentStudentsNum = students_data.size() + 1;

	int n;
	cout << left << setw(OPTIONS_PADDING) << "������� ���������� ����������� �������: ";
	cin >> n;
	cin.ignore(); // ������� ������ ����� cin >> 

	for (int i = 0; i < n; i++) {
		currentStudentsNum += i;

		//������� �������
		cout << "������� ������� ������ (0 - �������, 1 - �������������): ";
		cin >> userLevel;
		cin.ignore();

		// ���� �����
		cout << "������ " << i + 1 << ":\n\n";

		// ���� ������
		cout << left << setw(OPTIONS_PADDING) << "�����: ";
		getline(cin, login);

		// ���� ������
		cout << left << setw(OPTIONS_PADDING) << "������: ";
		getline(cin, password);

		cout << left << setw(OPTIONS_PADDING) << "���: ";
		getline(cin, name);

		// ���� �������
		cout << left << setw(OPTIONS_PADDING) << "�������: ";
		getline(cin, secondname);

		// ���� ��������
		cout << left << setw(OPTIONS_PADDING) << "��������: ";
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
			continue;
		}

		// ���� ������ (�����)
		cout << left << setw(OPTIONS_PADDING) << "������: ";
		cin >> group;
		cin.ignore();  // ������� ������ ����� cin >> 

		// ���� ����� (�����)
		cout << left << setw(OPTIONS_PADDING) << "����: ";
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

void EditStudents() {

}