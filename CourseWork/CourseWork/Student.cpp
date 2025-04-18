#include "Student.h"
#include "TableManips.h";

vector<StudentCourseWork> studentsArray;

using namespace std;

int StudentEditMenuChoice() {
	int choice;

	// ����� ���� ������ ���������
	cout << setw(OPTIONS_PADDING) << "" << "�������� �������� ��� ���������:\n";
	cout << setw(OPTIONS_PADDING) << "" << "1. ���\n";
	cout << setw(OPTIONS_PADDING) << "" << "2. �������\n";
	cout << setw(OPTIONS_PADDING) << "" << "3. ��������\n";
	cout << setw(OPTIONS_PADDING) << "" << "4. ������\n";
	cout << setw(OPTIONS_PADDING) << "" << "5. ����\n";
	cout << setw(OPTIONS_PADDING) << "" << "6. �����\n";
	cout << setw(OPTIONS_PADDING) << "" << "7. ������\n\n";
	cout << setw(OPTIONS_PADDING) << "" << "0. �����\n\n";

	// ���� ������ ������������
	cout << setw(INPUT_PADDING) << "" << "��� �����: ";
	cin >> choice;

	return choice;

} 

void DeleteStudentArray(int index) {
	studentsArray.erase(studentsArray.begin() + index);
}

void RefreshStudentsId() {
	for (int i = 0; i < studentsArray.size(); i++) {
		studentsArray[i].setId(i + 1);
	}
}

//�������� ����� ��������� ������
int FindStudentInFileMenu() {
	int choice;

	// ����� ���� ������ ���������
	cout << setw(OPTIONS_PADDING) << "" << "�������� �������� ��� ������:\n";

	cout << setw(OPTIONS_PADDING) << "" << "1. ID ������������\n";
	cout << setw(OPTIONS_PADDING) << "" << "2. ���\n";
	cout << setw(OPTIONS_PADDING) << "" << "3. �������\n";
	cout << setw(OPTIONS_PADDING) << "" << "4. ��������\n";
	cout << setw(OPTIONS_PADDING) << "" << "5. ������\n";
	cout << setw(OPTIONS_PADDING) << "" << "6. ����\n";
	cout << setw(OPTIONS_PADDING) << "" << "7. �����\n";
	cout << setw(OPTIONS_PADDING) << "" << "8. ������\n\n";
	cout << setw(OPTIONS_PADDING) << "" << "0. �����\n\n";

	// ���� ������ ������������
	cout << setw(INPUT_PADDING) << "" << "��� �����: ";
	cin >> choice;

	return choice;

}

//�������� ������ ��������� �� �����
vector<int> FindStudentInFile() {
	vector<int> studentsIndexes;
	string searchValue;
	int intSearchValue;

	int choice = FindStudentInFileMenu();

	if (choice == 0) return studentsIndexes; // �����

	// ������ �������� ��� ������
	cout << setw(INPUT_PADDING) << "" << "������� �������� ��� ������: ";
	if (choice == 1 || choice == 5 || choice == 6) {
		cin >> intSearchValue;
	}
	else {
		cin.ignore(); // ������� ����� ����� ������� ������
		getline(cin, searchValue);
	}

	// ����� �� ���������� ���������
	for (int i = 0; i < studentsArray.size(); i++) {
		
		bool found = false;

		switch (choice) {
		case 1: // ID ������������
			found = (studentsArray[i].getId() == intSearchValue);
			break;
		case 2: // ���
			found = (studentsArray[i].getName() == searchValue);
			break;
		case 3: // �������
			found = (studentsArray[i].getSurname() == searchValue);
			break;
		case 4: // ��������
			found = (studentsArray[i].getSecondName() == searchValue);
			break;
		case 5: // ������
			found = (studentsArray[i].getGroup() == intSearchValue);
			break;
		case 6: // ����
			found = (studentsArray[i].getCourse() == intSearchValue);
			break;
		case 7: // �����
			found = (studentsArray[i].getLogin() == searchValue);
			break;
		case 8: // ������
			found = (studentsArray[i].getPassword() == searchValue);
			break;
		default:
			cout << setw(INPUT_PADDING) << "" << "�������� �����!\n";
		}

		if (found) {
			studentsIndexes.push_back(i);
		}
	}

	if (studentsIndexes.size() == 0) {
		cout << setw(INPUT_PADDING) << "" << "������� �� ������!\n";
		cin.ignore();
		WaitEnterInput();
	}

	return studentsIndexes;
}

void GetStudentsFromFile() {
	studentsArray;
	ifstream file(DB_FILE_NAME);

	studentsArray.clear();

	if (!file.is_open()) {
		throw runtime_error("Failed to open file");
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

		if (!tokens[7].empty())
			group = stoi(tokens[7]);

		if (!tokens[8].empty())
			course = stoi(tokens[8]);

		StudentCourseWork student(
			id,
			userLevel,
			tokens[2], // password
			tokens[3], // login
			tokens[4], // name
			tokens[5], // secondname
			tokens[6], // surname
			group,
			course
		);

		// ������������� �������������� ����
		student.SetCourseWorkTheme(tokens[7]);
		student.SetCourseWorkStorageLink(tokens[8]);

		studentsArray.push_back(student);

	}
}

void Student::StudentEdit() {
	int choice;
	string newString;
	int newInt;

	do {
		choice = StudentEditMenuChoice();

		// ��������� ������
		switch (choice) {
		case 1:
			cout << setw(INPUT_PADDING) << "" << "������� ����� ���: ";
			cin >> newString;
			name = newString;
			break;
		case 2:
			cout << setw(INPUT_PADDING) << "" << "������� ����� �������: ";
			cin >> newString;
			secondname = newString;
			break;
		case 3:
			cout << setw(INPUT_PADDING) << "" << "������� ����� ��������: ";
			cin >> newString;
			surname = newString;
			break;
		case 4:
			cout << setw(INPUT_PADDING) << "" << "������� ����� ������: ";
			cin >> newInt;
			group = newInt;
			break;
		case 5:
			cout << setw(INPUT_PADDING) << "" << "������� ����� ����: ";
			cin >> newInt;
			course = newInt;
			break;
		case 6:
			cout << setw(INPUT_PADDING) << "" << "������� ����� �����: ";
			cin >> newString;
			login = newString;
			break;
		case 7:
			cout << setw(INPUT_PADDING) << "" << "������� ����� ������: ";
			cin >> newString;
			password = newString;
			break;
		case 0:
			break;
		default:
			cout << setw(INPUT_PADDING) << "" << "������: �������� �����!\n";
			break;
		}

		ClearTerminal();
		RegistratedStudentTable(*this);
	} while (choice != 0);
	
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
	int currentStudentsNum = studentsArray.size();

	int n;
	cout << left << setw(OPTIONS_PADDING) << "������� ���������� ����������� �������: ";
	cin >> n;
	cin.ignore(); // ������� ������ ����� cin >> 

	for (int i = 0; i < n; i++) {
		currentStudentsNum ++; //�������� �������������� � 1

		//������� �������
		cout << "������� ������� ������ (0 - �������, 1 - �������������): ";
		cin >> userLevel;
		cin.ignore();

		// ���� �����
		cout << "������ " << currentStudentsNum << ":\n\n";

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
				currentStudentsNum,
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
			currentStudentsNum,
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

void StudentFileRewrite() {
	fstream outFile(DB_FILE_NAME, ios::out | ios::trunc);

	for (int i = 0; i < studentsArray.size(); i++) {
		outFile << studentsArray[i];
	}
}