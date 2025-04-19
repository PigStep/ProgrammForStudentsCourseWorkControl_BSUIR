#include "TableManips.h"
#include "StudentFileManip.h"

extern void AdminFunctionsMenu() {
	const string OPTIONS_TO_CHOOSE[4] = {"Просмотреть возможные операции с учетными записями", "Предоставить полную таблицу данных студентов", "Установить контрольные точки для работ", "Провести рецензирование работ"};
	const string HEADER = { "МЕНЮ АДМИНИСТРАТОРА" };
	int n;

	do {
		HeaderFirstLevel(4, OPTIONS_TO_CHOOSE, HEADER);
		cin >> n;
		GetStudentsFromFile();

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
		default:
			break;
		}

		ClearTerminal();
	} while (n != 0);

}

void StudentsListOperations() {
	const string OPTIONS_TO_CHOOSE[4] = { "Просмотреть все учетные записи","Добавить учетную запись/записи", "Изменить учетную запись/записи", "Удалить учетную запись / записи"  };
	const string HEADER = { "МЕНЮ ОПЕРАЦИЙ С УЧЕТНЫМИ ЗАПИСЯМИ" };
	int n;

	do {
		HeaderFirstLevel(4, OPTIONS_TO_CHOOSE, HEADER);
		cin >> n;
		GetStudentsFromFile();

		ClearTerminal();

		switch (n)
		{
		case 1:
			PrintStudentsFromFile();
			break;
		case 2:
			AddStudentFromArrayMenu();
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
	const string HEADER = "ТАБЛИЦА СТУДЕНТОВ";
	HeaderSecondLevel(HEADER);

	for (int i = 0; i < studentsArray.size(); i++) {
		RegistratedStudentTable(studentsArray[i]);
	}

	cin.get();
	WaitEnterInput();
}

void AddStudentFromArrayMenu() {
	const string HEADER = "РЕГИСТРАЦИЯ СТУДЕНТА";
	HeaderSecondLevel(HEADER);

	RegistrateStudentInFile();
}

void EditStudentsFromArrayMenu() {
	const string HEADER = "РЕДАКТИРОВАНИЕ СТУДЕНТА";
	HeaderSecondLevel(HEADER);

	vector<int> indexes;

	do {
		indexes = FindStudentInFile();

		for (int i = 0; i < indexes.size(); i++) {
			int index = indexes[i];

			RefreshMenu(HEADER,index);

			studentsArray[index].StudentEdit();

			StudentFileRewrite();
		}

		ClearTerminal();
		HeaderSecondLevel(HEADER);
	}while (indexes.size() != 0);
}

void RefreshMenu(const string HEADER, int index) {
	ClearTerminal();
	HeaderSecondLevel(HEADER);
	RegistratedStudentTable(studentsArray[index]);
}

void DeleteStudentsFromArrayMenu() {
	const string HEADER = "УДАЛЕНИЕ СТУДЕНТА";
	HeaderSecondLevel(HEADER);

	vector<int> indexes;
	int delChoice;

	do {
		indexes = FindStudentInFile();

		for (int i = 0; i < indexes.size(); i++) {
			int index = indexes[i];
			
			
			cout << "Вы хотите удалить эту запись? (1 - да, 0 - нет)\n";

			RegistratedStudentTable(studentsArray[index]);

			cout <<"Подтвердите удаление" << setw(INPUT_PADDING) << ": ";
			cin >> delChoice;


			if (delChoice == 1) {
				DeleteStudentArray(i);
				RefreshStudentsId();
				StudentFileRewrite();
			}

			cout << "Запись успешно удалена"<<endl;
		}
		ClearTerminal();
		HeaderSecondLevel(HEADER);

	} while (indexes.size() != 0);
}

void ShowStudentsDataTable() {
	const string HEADER = "ТАБЛИЦА ДАННЫХ СТУДЕНТОВ";
	HeaderSecondLevel(HEADER);

	for (int i = 0; i < studentsArray.size(); i++) {
		StudentWorkCourseTable(studentsArray[i]);
	}
	cin.ignore();
	WaitEnterInput();
}


void SetCourseDeadlines() {
	const string HEADER = "УСТАНОВКА КОНТРОЛЬНЫХ ТОЧЕК";
	HeaderSecondLevel(HEADER);

	string message = "Текущие контрольные точки:\n";
	message += GetDeadLines();
	LogMessage(message);

	int confirm;

	cout << "Вы хотите изменить контрольные точки? (1 - да; 0 - нет)\n";
	cin >> confirm;

	if (confirm) {
		for (int i = 0; i < NUM_OF_DEADLINES; i++) {
			cout << "Установите дату контрольной точки [" << i + 1 << "]" << endl;
			courseDeadLinePoints[i].SetDate();
			cout << endl;
		}

		string message = "Точки успешно созданы";
		LogMessage(message);
		SaveDeadLinesInFile();
		cin.ignore();
		WaitEnterInput();
	}
	else
		return;
	
}

void SetStudentsMarks() {
	const string HEADER = "МЕНЮ ОЦЕНИВАНИЯ РАБОТЫ СТУДЕНТА";
	HeaderSecondLevel(HEADER);
	vector<int> indexes;

	do {
		indexes = FindStudentInFile();

		for (int i = 0; i < indexes.size(); i++) {
			int index = indexes[i];

			RefreshMenu(HEADER, index);

			cout << "Выберете контрольную точку на изменение: ";

			StudentFileRewrite();
		}

		ClearTerminal();
		HeaderSecondLevel(HEADER);
	} while (indexes.size() != 0);
}
