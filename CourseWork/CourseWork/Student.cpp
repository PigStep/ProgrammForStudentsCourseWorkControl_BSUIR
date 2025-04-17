#include "Student.h"
#include "TableManips.h";

vector<StudentCourseWork> students_data;

void Student::StudentEdit(const int bordersWidth, const int optionsPadding, const int inputPadding) {
	int choice;
	string newString;
	int newInt;

	do {
		// Вывод меню выбора параметра
		cout << setw(optionsPadding) << "" << "Выберите параметр для изменения:\n";
		cout << setw(optionsPadding) << "" << "1. Имя\n";
		cout << setw(optionsPadding) << "" << "2. Фамилия\n";
		cout << setw(optionsPadding) << "" << "3. Отчество\n";
		cout << setw(optionsPadding) << "" << "4. Группа\n";
		cout << setw(optionsPadding) << "" << "5. Курс\n";
		cout << setw(optionsPadding) << "" << "6. Логин\n";
		cout << setw(optionsPadding) << "" << "7. Пароль\n\n";
		cout << setw(optionsPadding) << "" << "0. Выход\n\n";

		// Ввод выбора пользователя
		cout << setw(inputPadding) << "" << "Ваш выбор: ";
		cin >> choice;

		// Обработка выбора
		switch (choice) {
		case 1:
			cout << setw(inputPadding) << "" << "Введите новое имя: ";
			cin >> newString;
			name = newString;
			break;
		case 2:
			cout << setw(inputPadding) << "" << "Введите новую фамилию: ";
			cin >> newString;
			secondname = newString;
			break;
		case 3:
			cout << setw(inputPadding) << "" << "Введите новое отчество: ";
			cin >> newString;
			surname = newString;
			break;
		case 4:
			cout << setw(inputPadding) << "" << "Введите новую группу: ";
			cin >> newInt;
			group = newInt;
			break;
		case 5:
			cout << setw(inputPadding) << "" << "Введите новый курс: ";
			cin >> newInt;
			course = newInt;
			break;
		case 6:
			cout << setw(inputPadding) << "" << "Введите новый логин: ";
			cin >> newString;
			login = newString;
			break;
		case 7:
			cout << setw(inputPadding) << "" << "Введите новый пароль: ";
			cin >> newString;
			password = newString;
			break;
		case 0:
			break;
		default:
			cout << setw(inputPadding) << "" << "Ошибка: неверный выбор!\n";
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
	cout << left << setw(OPTIONS_PADDING) << "Введите количество добавляемых записей: ";
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
		cout << left << setw(OPTIONS_PADDING) << "Логин: ";
		getline(cin, login);

		// Ввод пароля
		cout << left << setw(OPTIONS_PADDING) << "Пароль: ";
		getline(cin, password);

		cout << left << setw(OPTIONS_PADDING) << "Имя: ";
		getline(cin, name);

		// Ввод фамилии
		cout << left << setw(OPTIONS_PADDING) << "Фамилия: ";
		getline(cin, secondname);

		// Ввод отчества
		cout << left << setw(OPTIONS_PADDING) << "Отчество: ";
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
		cout << left << setw(OPTIONS_PADDING) << "Группа: ";
		cin >> group;
		cin.ignore();  // Очистка буфера после cin >> 

		// Ввод курса (число)
		cout << left << setw(OPTIONS_PADDING) << "Курс: ";
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

void EditStudents() {

}