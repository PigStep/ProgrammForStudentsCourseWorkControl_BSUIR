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
		if (line.empty()) continue; // Пропускаем пустые строки

		istringstream iss(line);
		string token;
		vector<string> tokens;

		// Разбиваем строку по разделителю ';'
		while (getline(iss, token, ';')) {
			tokens.push_back(token);
		}

		// Проверяем, что получили все 11 полей (10 ';' в строке)
		if (tokens.size() != 11) {
			continue;
		}

		// Создаем объект StudentCourseWork
		// Преобразуем группу и курс из строки в число
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

		// Устанавливаем дополнительные поля
		student.SetCourseWorkTheme(tokens[7]);
		student.SetCourseWorkStorageLink(tokens[8]);

		students_data.push_back(student);

	}
}