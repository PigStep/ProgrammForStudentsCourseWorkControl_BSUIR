#include "Student.h"

vector<StudentCourseWork> students_data;

void getStudentsFromFile(const string& filename) {
	students_data;
	ifstream file(filename);

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