#include "TableManips.h"

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

	SubHeader(HEADER);

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

			break;
		default:
			break;
		}

		ClearTerminal();
	} while (n != 0);

}