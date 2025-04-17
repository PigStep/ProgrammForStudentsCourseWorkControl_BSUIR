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
	cout << left << setw(padding) << "Введите количество добавляемых записей: ";
	cin >> n;
	cin.ignore(); // Очистка буфера после cin >> 

	for (int i = 0; i < n; i++) {
		currentStudentsNum += i;

		//Уровень доступа
		cout << "Уровень доступа записи (0 - студент, 1 - администратор): ";
		cin >> userLevel;
		cin.ignore();

		// Ввод имени
		cout << "Запись " << i + 1 << ":\n\n";

		// Ввод логина
		cout << left << setw(padding) << "Логин: ";
		getline(cin, login);

		// Ввод пароля
		cout << left << setw(padding) << "Пароль: ";
		getline(cin, password);

		cout << left << setw(padding) << "Имя: ";
		getline(cin, name);

		// Ввод фамилии
		cout << left << setw(padding) << "Фамилия: ";
		getline(cin, secondname);

		// Ввод отчества
		cout << left << setw(padding) << "Отчество: ";
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

		// Ввод группы (число)
		cout << left << setw(padding) << "Группа: ";
		cin >> group;
		cin.ignore();  // Очистка буфера после cin >> 

		// Ввод курса (число)
		cout << left << setw(padding) << "Курс: ";
		cin >> course;
		cin.ignore();  // Очистка буфера после cin >>


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