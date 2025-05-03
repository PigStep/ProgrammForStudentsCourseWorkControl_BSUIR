#include "TableManips.h"
#include "StudentFileManip.h"

extern void AdminFunctionsMenu() {
	const string OPTIONS_TO_CHOOSE[5] = {"Просмотреть возможные операции с учетными записями", "Предоставить полную таблицу данных студентов", "Установить контрольные точки для работ", "Провести рецензирование работ", "Установить темы курсовых работ"};
	const string HEADER = { "МЕНЮ АДМИНИСТРАТОРА" };
	int n;

	do {
		HeaderFirstLevel(5, OPTIONS_TO_CHOOSE, HEADER);
		n = GetIntegerInput(0, 5);
		LoadStudentsFromFile();

		ClearTerminal();

		switch (n)
		{
		case 1:
			StudentsListOperations();
			break;
		case 2:
			ShowStudentsDataTable();
			break;
		case 3:
			SetCourseDeadlines();
			break;
		case 4:
			SetStudentsMarks();
			break;
		case 5:
			SetStudentCourseTheme();
			break;
		case 0:
			break;
		default:
			break;
		}
	} while (n != 0);

}

void StudentsListOperations() {
	const string OPTIONS_TO_CHOOSE[4] = { "Просмотреть все учетные записи","Добавить учетную запись/записи", "Изменить учетную запись/записи", "Удалить учетную запись / записи"  };
	const string HEADER = { "МЕНЮ ОПЕРАЦИЙ С УЧЕТНЫМИ ЗАПИСЯМИ" };
	int n;

	do {
		HeaderFirstLevel(4, OPTIONS_TO_CHOOSE, HEADER);
		n = GetIntegerInput(0, 4);
		LoadStudentsFromFile();

		ClearTerminal();

		switch (n)
		{
		case 1:
			PrintStudentsFromFile();
			break;
		case 2:
			AddStudentMenu();
			break;
		case 3:
			EditStudentsFromArrayMenu();
			break;
		case 4:
			DeleteStudentsFromArrayMenu();
			break;
		default:
			break;
		}

		ClearTerminal();
	} while (n != 0);

}

void PrintStudentsFromFile() {
	const string HEADER = "ТАБЛИЦА УЧЕТНЫХ ЗАПИСЕЙ";
	HeaderSecondLevel(HEADER);

	for (int i = 0; i < studentsArray.size(); i++) {
		RegistratedStudentTable(studentsArray[i]);
	}
	WaitEnterInput();
}

void AddStudentMenu() {
	const string HEADER = "РЕГИСТРАЦИЯ СТУДЕНТА";
	HeaderSecondLevel(HEADER);

	RegistrateStudentInFile();
}

void EditStudentsFromArrayMenu() {
	const string HEADER = "РЕДАКТИРОВАНИЕ СТУДЕНТА";
	HeaderSecondLevel(HEADER);

	vector<int> indexes;

	do {
		indexes = FindUserByParam();

		if (indexes.size() == 1 && indexes[0] == -1)
			break;  //если был выбран выход

		for (int i = 0; i < indexes.size(); i++) {
			int index = indexes[i];

			RefreshMenu(HEADER,index);

			studentsArray[index].StudentEdit();
		}
		ClearTerminal();
		HeaderSecondLevel(HEADER);
	}while (true);
	StudentFileRewrite();
}

void RefreshMenu(const string HEADER, int index) {
	ClearTerminal();
	HeaderSecondLevel(HEADER);
	RegistratedStudentTable(studentsArray[index]);
}

void DeleteStudentsFromArrayMenu() {
	const string HEADER = "УДАЛЕНИЕ УЧЕТНОЙ ЗАПИСИ";
	HeaderSecondLevel(HEADER);

	vector<int> indexes;
	int delChoice;

	do {
		indexes = FindUserByParam();

		if (indexes.size() == 1 && indexes[0] == -1)
			break;  //если был выбран выход

		for (int i = 0; i < indexes.size(); i++) {
			int index = indexes[i];

			if (studentsArray[index].getLogin() == userAccountLink->getLogin()) {
				cout << "Ошибка, самоудаление невозможно!\n";
				WaitEnterInput();
				break;
			}
			
			cout << "Вы хотите удалить эту запись\n";

			RegistratedStudentTable(studentsArray[index]);

			if (GetUserApprove()) {
				DeleteStudentArray(i);
				RefreshStudentsId();
				cout << "Запись успешно удалена" << endl;
			}
		}
		ClearTerminal();
		HeaderSecondLevel(HEADER);
	} while (true);
	StudentFileRewrite();
}

void ShowStudentsDataTable() {
	const string HEADER = "ТАБЛИЦА ДАННЫХ СТУДЕНТОВ";
	HeaderSecondLevel(HEADER);

	vector<int> indexes = SortIndexes();

	for (int i = 0; i < indexes.size(); i++) {
		int index = indexes[i];
		StudentWorkCourseTable(studentsArray[index]);
	}
	if (indexes.size() != 0)
		WaitEnterInput();
	else
		ClearTerminal();
}


void SetCourseDeadlines() {
	const string HEADER = "УСТАНОВКА КОНТРОЛЬНЫХ ТОЧЕК";
	HeaderSecondLevel(HEADER);

	ShowDeadLinesList();

	cout << "Вы хотите изменить контрольные точки\n";

	if (GetUserApprove()) {
		do {
			for (int i = 0; i < NUM_OF_DEADLINES; i++) {
				cout << "Установите дату контрольной точки [" << i + 1 << "]" << endl;
				courseDeadLinePoints[i].SetDate();
				cout << endl;
			}
		} while (!CheckDates());

		string message = "Точки успешно созданы";
		LogMessage(message);
		SaveDeadLinesInFile();
		WaitEnterInput();
	}
	else
		return;
	
}

bool SelectMark(int index) {
	int mark;
	int deadLineIndex;

	cout << "Выберете контрольную точку на изменение (0 для выхода): ";
	cin >> deadLineIndex;

	if (deadLineIndex == 0) return false;

	deadLineIndex--;


	cout << "Введите оценку за контрольную точку: ";
	cin >> mark;
	studentsArray[index].setMark(deadLineIndex, mark);

	return true;
}

void SetStudentsMarks() {
	const string HEADER = "МЕНЮ ОЦЕНИВАНИЯ РАБОТЫ СТУДЕНТА";
	HeaderSecondLevel(HEADER);
	vector<int> indexes;

	do {
		ClearTerminal();
		HeaderSecondLevel(HEADER);

		indexes = FindUserByParam();

		for (int i = 0; i < indexes.size(); i++) {
			int index = indexes[i];

			if (CheckIsManipulatingAdmin(studentsArray[index])) {
				WaitEnterInput();
			}

			do {
				ClearTerminal();
				HeaderSecondLevel(HEADER);
				StudentWorkCourseTable(studentsArray[index]);
			}while (SelectMark(index));
		}
	} while (indexes.size() != 0);
	StudentFileRewrite();
	LoadStudentsFromFile();
}

void SetStudentCourseTheme() {
	const string HEADER = "МЕНЮ УСТАНОВКИ ТЕМЫ РАБОТЫ СТУДЕНТА";
	HeaderSecondLevel(HEADER);
	vector<int> indexes;

	do {
		indexes = FindUserByParam();
		ClearTerminal();
		HeaderSecondLevel(HEADER);

		for (int i = 0; i < indexes.size(); i++) {
			int index = indexes[i];

			if (studentsArray[index].getId() == 1)
			{
				cout << "Невозможно установить тему преподавателю";
				WaitEnterInput();
				return;
			}

			StudentWorkCourseTable(studentsArray[index]);
			cin.ignore();

			cout << "Вы хотите установить новую тему этому студенту? (1- да; 0 - нет)\n";
			int confirm;
			cin >> confirm;

			if (confirm == 1) {
				
				studentsArray[index].setCourseWorkTheme();

				ClearTerminal();
				StudentWorkCourseTable(studentsArray[index]);
				WaitEnterInput();
			}
			ClearTerminal();
		}
	} while (indexes.size() != 0);
	StudentFileRewrite();
	LoadStudentsFromFile();
}