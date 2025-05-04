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
		n = GetIntegerInput();
		LoadStudentsFromFile();

		ClearTerminal();

		switch (n)
		{
		case 1:
			PrintAccountData();
			break;
		case 2:
			GetStudentByParam();
			break;
		case 3:
			ShowStudentsDataTable();
			break;
		case 4:
			SetCourseWorkLink();
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

	StudentWorkCourseTable(*userAccountLink);

	WaitEnterInput();
}

//Предоставить студенту доступ к редактированию ссылки
void SetCourseWorkLink() {
	const string HEADER = "РЕДАКТИРОВАНИЕ ССЫЛКИ КУРСОВОЙ РАБОТЫ";
	HeaderSecondLevel(HEADER);

	cout << "Текущая ссылка на курсовую работу:\n"<< userAccountLink->getCourseWorkLink()<<endl;
	cout << "Вы хотите изменить ссылку";

	if (!GetUserApprove())
		return;

	string link = GetLinkInput("Введите новую ссылку:");
	userAccountLink->SetCourseWorkStorageLink(link);

	string successMessage = "Ссылка успешно добавлена";

	LogMessage(successMessage);

	WaitEnterInput();
	StudentFileRewrite();
}

void GetStudentByParam() {
	const string HEADER = "ПОИСК СТУДЕНТА";
	HeaderSecondLevel(HEADER);

	vector<int> indexes = FindStudentByParam();

	if (indexes.size() == 1 && indexes[0] == -1)
		return;  //если был выбран выход

	for (int i : indexes) {
		if(studentsArray[i].getId()!=1)
			StudentWorkCourseTable(studentsArray[i]);
	}

	WaitEnterInput();
}