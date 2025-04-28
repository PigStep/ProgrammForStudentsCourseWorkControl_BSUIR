#include "TableManips.h"
#include "StudentFileManip.h"

//Вывести меню взаимодействия системы с пользователем
extern void UserFunctionsMenu() {
	const string OPTIONS_TO_CHOOSE[4] = {"Просмотреть данные", 
		"Поиск студента", "Сортировка студентов", "Предоставить ссылку на курсовую работу"};
	const string HEADER = { "МЕНЮ ПОЛЬЗОВАТЕЛЯ" };
	int n;

	do {
		HeaderFirstLevel(4, OPTIONS_TO_CHOOSE, HEADER);
		cin >> n;
		LoadStudentsFromFile();

		ClearTerminal();
		cin.ignore();

		switch (n)
		{
		case 1:
			PrintAccountData();
			break;
		case 2:
			
			break;
		case 3:
			ShowStudentsDataTable();
			break;
		case 4:

			break;
		case 5:

			break;
		default:
			break;
		}

		ClearTerminal();
	} while (n != 0);

}

//Вывести информацию о текщей учетной записи
void PrintAccountData() {
	const string HEADER = "ТЕКУЩАЯ УЧЕТНАЯ ЗАПИСЬ";
	HeaderSecondLevel(HEADER);

	StudentWorkCourseTable(*userAccount);

	WaitEnterInput();
}
