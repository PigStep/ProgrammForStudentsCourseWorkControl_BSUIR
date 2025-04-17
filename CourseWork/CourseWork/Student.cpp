#include "Student.h"

vector<StudentCourseWork> students_data;

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

void RegistrateStudentInFile(int padding) {

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
	cout << left << setw(padding) << "������� ���������� ����������� �������: ";
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
		cout << left << setw(padding) << "�����: ";
		getline(cin, login);

		// ���� ������
		cout << left << setw(padding) << "������: ";
		getline(cin, password);

		cout << left << setw(padding) << "���: ";
		getline(cin, name);

		// ���� �������
		cout << left << setw(padding) << "�������: ";
		getline(cin, secondname);

		// ���� ��������
		cout << left << setw(padding) << "��������: ";
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
		cout << left << setw(padding) << "������: ";
		cin >> group;
		cin.ignore();  // ������� ������ ����� cin >> 

		// ���� ����� (�����)
		cout << left << setw(padding) << "����: ";
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