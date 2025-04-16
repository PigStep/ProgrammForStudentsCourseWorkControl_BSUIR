#include "TableManips.h"
#include "Student.h"

extern void AdminFunctionsMenu() {
	const string OPTIONS_TO_CHOOSE[4] = {"Просмотреть возможные операции с учетными записями", "Предоставить полную таблицу студентов", "Установить контрольные точки для работ", "Провести рецензирование работ"};
	const string HEADER = { "МЕНЮ АДМИНИСТРАТОРА" };
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
	const string OPTIONS_TO_CHOOSE[4] = { "Просмотреть все учетные записи","Добавить учетную запись/записи", "Удалить учетную запись/записи", "Изменить учетную запись/записи" };
	const string HEADER = { "МЕНЮ ОПЕРАЦИЙ С УЧЕТНЫМИ ЗАПИСЯМИ" };
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

	const string HEADER = "ТАБЛИЦА СТУДЕНТОВ";
	HeaderSecondLevel(HEADER);

	for (int i = 0; i < students_data.size(); i++) {
		RegistratedStudentTable(students_data[i]);
	}

	cin.get();
	WaitEnter();
}

void AddStudent() {
	const string HEADER = "РЕГИСТРАЦИЯ СТУДЕНТА";
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
	cout << left << setw(INPUT_PADDING) << "Введите количество добавляемых записей: ";
	cin >> n;
	cin.ignore(); // Очистка буфера после cin >> 

	for (int i = 0; i < n; i++) {

		//Уровень доступа
		cout << "Уровень доступа записи (0 - студент, 1 - администратор): ";
		cin >> userLevel;
		cin.ignore();

		// Ввод имени
		cout << "Запись " << i + 1<<":\n\n";

		// Ввод логина
		cout << left << setw(INPUT_PADDING) << "Логин: ";
		getline(cin, login);

		// Ввод пароля
		cout << left << setw(INPUT_PADDING) << "Пароль: ";
		getline(cin, password);

		cout << left << setw(INPUT_PADDING) << "Имя: ";
		getline(cin, name);

		// Ввод фамилии
		cout << left << setw(INPUT_PADDING) << "Фамилия: ";
		getline(cin, secondname);

		// Ввод отчества
		cout << left << setw(INPUT_PADDING) << "Отчество: ";
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
		// Ввод группы (число)
		cout << left << setw(INPUT_PADDING) << "Группа: ";
		cin >> group;
		cin.ignore();  // Очистка буфера после cin >> 

		// Ввод курса (число)
		cout << left << setw(INPUT_PADDING) << "Курс: ";
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