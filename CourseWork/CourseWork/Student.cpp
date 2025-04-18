#include "Student.h"
#include "TableManips.h";

vector<StudentCourseWork> studentsArray;

using namespace std;

int StudentEditMenuChoice() {
	int choice;

	// Вывод меню выбора параметра
	cout << setw(OPTIONS_PADDING) << "" << "Выберите параметр для изменения:\n";
	cout << setw(OPTIONS_PADDING) << "" << "1. Имя\n";
	cout << setw(OPTIONS_PADDING) << "" << "2. Фамилия\n";
	cout << setw(OPTIONS_PADDING) << "" << "3. Отчество\n";
	cout << setw(OPTIONS_PADDING) << "" << "4. Группа\n";
	cout << setw(OPTIONS_PADDING) << "" << "5. Курс\n";
	cout << setw(OPTIONS_PADDING) << "" << "6. Логин\n";
	cout << setw(OPTIONS_PADDING) << "" << "7. Пароль\n\n";
	cout << setw(OPTIONS_PADDING) << "" << "0. Выход\n\n";

	// Ввод выбора пользователя
	cout << setw(INPUT_PADDING) << "" << "Ваш выбор: ";
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

//Получить номер параметра поиска
int FindStudentInFileMenu() {
	int choice;

	// Вывод меню выбора параметра
	cout << setw(OPTIONS_PADDING) << "" << "Выберите параметр для поиска:\n";

	cout << setw(OPTIONS_PADDING) << "" << "1. ID пользователя\n";
	cout << setw(OPTIONS_PADDING) << "" << "2. Имя\n";
	cout << setw(OPTIONS_PADDING) << "" << "3. Фамилия\n";
	cout << setw(OPTIONS_PADDING) << "" << "4. Отчество\n";
	cout << setw(OPTIONS_PADDING) << "" << "5. Группа\n";
	cout << setw(OPTIONS_PADDING) << "" << "6. Курс\n";
	cout << setw(OPTIONS_PADDING) << "" << "7. Логин\n";
	cout << setw(OPTIONS_PADDING) << "" << "8. Пароль\n\n";
	cout << setw(OPTIONS_PADDING) << "" << "0. Выход\n\n";

	// Ввод выбора пользователя
	cout << setw(INPUT_PADDING) << "" << "Ваш выбор: ";
	cin >> choice;

	return choice;

}

//Получить вектор студентов из файла
vector<int> FindStudentInFile() {
	vector<int> studentsIndexes;
	string searchValue;
	int intSearchValue;

	int choice = FindStudentInFileMenu();

	if (choice == 0) return studentsIndexes; // Выход

	// Запрос значения для поиска
	cout << setw(INPUT_PADDING) << "" << "Введите значение для поиска: ";
	if (choice == 1 || choice == 5 || choice == 6) {
		cin >> intSearchValue;
	}
	else {
		cin.ignore(); // Очищаем буфер перед чтением строки
		getline(cin, searchValue);
	}

	// Поиск по выбранному параметру
	for (int i = 0; i < studentsArray.size(); i++) {
		
		bool found = false;

		switch (choice) {
		case 1: // ID пользователя
			found = (studentsArray[i].getId() == intSearchValue);
			break;
		case 2: // Имя
			found = (studentsArray[i].getName() == searchValue);
			break;
		case 3: // Фамилия
			found = (studentsArray[i].getSurname() == searchValue);
			break;
		case 4: // Отчество
			found = (studentsArray[i].getSecondName() == searchValue);
			break;
		case 5: // Группа
			found = (studentsArray[i].getGroup() == intSearchValue);
			break;
		case 6: // Курс
			found = (studentsArray[i].getCourse() == intSearchValue);
			break;
		case 7: // Логин
			found = (studentsArray[i].getLogin() == searchValue);
			break;
		case 8: // Пароль
			found = (studentsArray[i].getPassword() == searchValue);
			break;
		default:
			cout << setw(INPUT_PADDING) << "" << "Неверный выбор!\n";
		}

		if (found) {
			studentsIndexes.push_back(i);
		}
	}

	if (studentsIndexes.size() == 0) {
		cout << setw(INPUT_PADDING) << "" << "Студент не найден!\n";
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

		// Устанавливаем дополнительные поля
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

		// Обработка выбора
		switch (choice) {
		case 1:
			cout << setw(INPUT_PADDING) << "" << "Введите новое имя: ";
			cin >> newString;
			name = newString;
			break;
		case 2:
			cout << setw(INPUT_PADDING) << "" << "Введите новую фамилию: ";
			cin >> newString;
			secondname = newString;
			break;
		case 3:
			cout << setw(INPUT_PADDING) << "" << "Введите новое отчество: ";
			cin >> newString;
			surname = newString;
			break;
		case 4:
			cout << setw(INPUT_PADDING) << "" << "Введите новую группу: ";
			cin >> newInt;
			group = newInt;
			break;
		case 5:
			cout << setw(INPUT_PADDING) << "" << "Введите новый курс: ";
			cin >> newInt;
			course = newInt;
			break;
		case 6:
			cout << setw(INPUT_PADDING) << "" << "Введите новый логин: ";
			cin >> newString;
			login = newString;
			break;
		case 7:
			cout << setw(INPUT_PADDING) << "" << "Введите новый пароль: ";
			cin >> newString;
			password = newString;
			break;
		case 0:
			break;
		default:
			cout << setw(INPUT_PADDING) << "" << "Ошибка: неверный выбор!\n";
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
	cout << left << setw(OPTIONS_PADDING) << "Введите количество добавляемых записей: ";
	cin >> n;
	cin.ignore(); // Очистка буфера после cin >> 

	for (int i = 0; i < n; i++) {
		currentStudentsNum ++; //начинаем индексирование с 1

		//Уровень доступа
		cout << "Уровень доступа записи (0 - студент, 1 - администратор): ";
		cin >> userLevel;
		cin.ignore();

		// Ввод имени
		cout << "Запись " << currentStudentsNum << ":\n\n";

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

		// Ввод группы (число)
		cout << left << setw(OPTIONS_PADDING) << "Группа: ";
		cin >> group;
		cin.ignore();  // Очистка буфера после cin >> 

		// Ввод курса (число)
		cout << left << setw(OPTIONS_PADDING) << "Курс: ";
		cin >> course;
		cin.ignore();  // Очистка буфера после cin >>


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