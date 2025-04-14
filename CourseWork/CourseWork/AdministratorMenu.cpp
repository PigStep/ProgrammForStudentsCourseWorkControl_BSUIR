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

void RegistrateStudents() {
	const string HEADER = "ДОБАВЛЕНИЕ УЧЕТНОЙ ЗАПИСИ СТУДЕНТА";

	HeaderSecondLevel(HEADER);

	cin.get();
	cout << "Нажмите Enter для продолжения" << endl;
	cin.get();
	
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
			readStudentsFromFile(studentsFileDB);
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
void readStudentsFromFile(fstream& file) {
	// Перемещаем указатель чтения в начало файла
	file.seekg(0, ios::beg);

	string line;
	while (getline(file, line)) {  // Читаем построчно до конца файла
		cout << line << endl;      // Выводим прочитанную строку (можно парсить)
	}

	// После чтения возвращаем указатель записи в конец файла (если нужно дописывать)
	file.seekp(0, ios::end);
}

void AddStudent() {
	const string HEADER = "РЕГИСТРАЦИЯ СТУДЕНТА";
	HeaderSecondLevel(HEADER);

	string name;
	string secondname;
	string surname;
	int group;
	int course;

	int n;
	cout << left << setw(ENTER_PADDING) << "Введите количество добавляемых студентов: ";
	cin >> n;
	cin.ignore(); // Очистка буфера после cin >> 

	for (int i = 0; i < n; i++) {
		// Ввод имени
		cout << "Студент " << i + 1<<":\n";
		cout << left << setw(ENTER_PADDING) << "Имя: ";
		getline(cin, name);

		// Ввод фамилии
		cout << left << setw(ENTER_PADDING) << "Фамилия: ";
		getline(cin, secondname);

		// Ввод отчества
		cout << left << setw(ENTER_PADDING) << "Отчество: ";
		getline(cin, surname);

		// Ввод группы (число)
		cout << left << setw(ENTER_PADDING) << "Группа: ";
		cin >> group;
		cin.ignore();  // Очистка буфера после cin >> 

		// Ввод курса (число)
		cout << left << setw(ENTER_PADDING) << "Курс: ";
		cin >> course;
		cin.ignore();  // Очистка буфера после cin >>


		StudentCourseWork StudentCourse(name, secondname, surname, group, course);

		studentsFileDB << StudentCourse;
	}
}