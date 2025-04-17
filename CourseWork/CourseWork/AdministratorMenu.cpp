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
		getStudentsFromFile(DB_FILE_NAME);

		ClearTerminal();

		switch (n)
		{
		case(1):
			PrintStudentsFromFile();
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

void PrintStudentsFromFile() {
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

	RegistrateStudentInFile(INPUT_PADDING);
}