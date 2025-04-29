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

	StudentWorkCourseTable(*userAccount);

	WaitEnterInput();
}

//Предоставить студенту доступ к редактированию ссылки
void SetCourseWorkLink() {
	const string HEADER = "РЕДАКТИРОВАНИЕ ССЫЛКИ КУРСОВОЙ РАБОТЫ";
	HeaderSecondLevel(HEADER);

	cout << "Текущая ссылка на курсовую работу:\n"<< userAccount->getCourseWorkLink()<<endl;
	cout << "Вы точно хотите её изменить? (1 - да; 0 - нет)"
		<<setw(INPUT_PADDING)<<"";
	
	int n;
	cin >> n;
	if (!n)
		return;

	cout << "Введите новую ссылку:"
		<< setw(INPUT_PADDING) << "";
	cin.ignore();
	string link;
	getline(cin, link);
	userAccount->SetCourseWorkStorageLink(link);

	string SCCSS_CHNG_MSG = "Ссылка успешно добавлена";

	LogMessage(SCCSS_CHNG_MSG);

	WaitEnterInput();
	StudentFileRewrite();
}

void GetStudentByParam() {
	const string HEADER = "ПОИСК СТУДЕНТА";
	HeaderSecondLevel(HEADER);

	vector<int> indexes = FindStudentByParam();

	for (int i : indexes) {
		if(studentsArray[i].getId()!=1)
			StudentWorkCourseTable(studentsArray[i]);
	}

	cin.ignore();
	WaitEnterInput();
}