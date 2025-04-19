#include "TableManips.h"
#include "StudentFileManip.h"

extern void AdminFunctionsMenu() {
	const string OPTIONS_TO_CHOOSE[5] = {"����������� ��������� �������� � �������� ��������", "������������ ������ ������� ������ ���������", "���������� ����������� ����� ��� �����", "�������� �������������� �����", "���������� ���� �������� �����"};
	const string HEADER = { "���� ��������������" };
	int n;

	do {
		HeaderFirstLevel(5, OPTIONS_TO_CHOOSE, HEADER);
		cin >> n;
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
		default:
			break;
		}

		ClearTerminal();
	} while (n != 0);

}

void StudentsListOperations() {
	const string OPTIONS_TO_CHOOSE[4] = { "����������� ��� ������� ������","�������� ������� ������/������", "�������� ������� ������/������", "������� ������� ������ / ������"  };
	const string HEADER = { "���� �������� � �������� ��������" };
	int n;

	do {
		HeaderFirstLevel(4, OPTIONS_TO_CHOOSE, HEADER);
		cin >> n;
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
	const string HEADER = "������� ������� �������";
	HeaderSecondLevel(HEADER);

	for (int i = 0; i < studentsArray.size(); i++) {
		RegistratedStudentTable(studentsArray[i]);
	}

	cin.get();
	WaitEnterInput();
}

void AddStudentMenu() {
	const string HEADER = "����������� ��������";
	HeaderSecondLevel(HEADER);

	RegistrateStudentInFile();
}

void EditStudentsFromArrayMenu() {
	const string HEADER = "�������������� ��������";
	HeaderSecondLevel(HEADER);

	vector<int> indexes;

	do {
		indexes = FindStudentByParam();

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
	const string HEADER = "�������� ��������";
	HeaderSecondLevel(HEADER);

	vector<int> indexes;
	int delChoice;

	do {
		indexes = FindStudentByParam();

		for (int i = 0; i < indexes.size(); i++) {
			int index = indexes[i];
			
			
			cout << "�� ������ ������� ��� ������? (1 - ��, 0 - ���)\n";

			RegistratedStudentTable(studentsArray[index]);

			cout <<"����������� ��������" << setw(INPUT_PADDING) << ": ";
			cin >> delChoice;


			if (delChoice == 1) {
				DeleteStudentArray(i);
				RefreshStudentsId();
				StudentFileRewrite();
				cout << "������ ������� �������" << endl;
			}

		}
		ClearTerminal();
		HeaderSecondLevel(HEADER);

	} while (indexes.size() != 0);
}

void ShowStudentsDataTable() {
	const string HEADER = "������� ������ ���������";
	HeaderSecondLevel(HEADER);

	vector<int> indexes = SortIndexes();

	for (int i = 0; i < indexes.size(); i++) {
		int index = indexes[i];
		StudentWorkCourseTable(studentsArray[index]);
	}

	cin.ignore();
	WaitEnterInput();
}


void SetCourseDeadlines() {
	const string HEADER = "��������� ����������� �����";
	HeaderSecondLevel(HEADER);

	ShowDeadLinesList();

	int confirm;

	cout << "�� ������ �������� ����������� �����? (1 - ��; 0 - ���)\n";
	cin >> confirm;

	if (confirm) {
		for (int i = 0; i < NUM_OF_DEADLINES; i++) {
			cout << "���������� ���� ����������� ����� [" << i + 1 << "]" << endl;
			courseDeadLinePoints[i].SetDate();
			cout << endl;
		}

		string message = "����� ������� �������";
		LogMessage(message);
		SaveDeadLinesInFile();
		cin.ignore();
		WaitEnterInput();
	}
	else
		return;
	
}

bool SelectMark(int index) {
	int mark;
	int deadLineIndex;

	cout << "�������� ����������� ����� �� ��������� (0 ��� ������): ";
	cin >> deadLineIndex;

	if (deadLineIndex == 0) return false;

	deadLineIndex--;


	cout << "������� ������ �� ����������� �����: ";
	cin >> mark;
	studentsArray[index].setMark(deadLineIndex, mark);

	return true;
}

void SetStudentsMarks() {
	const string HEADER = "���� ���������� ������ ��������";
	HeaderSecondLevel(HEADER);
	vector<int> indexes;

	do {
		ClearTerminal();
		HeaderSecondLevel(HEADER);

		indexes = FindStudentByParam();

		for (int i = 0; i < indexes.size(); i++) {
			int index = indexes[i];

			if (studentsArray[index].getId() == 1)
			{
				cout << "���������� �������� �������������� �������������";
				WaitEnterInput();
				return;
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
	const string HEADER = "���� ��������� ���� ������ ��������";
	HeaderSecondLevel(HEADER);
	vector<int> indexes;

	do {
		indexes = FindStudentByParam();
		ClearTerminal();
		HeaderSecondLevel(HEADER);

		for (int i = 0; i < indexes.size(); i++) {
			int index = indexes[i];

			if (studentsArray[index].getId() == 1)
			{
				cout << "���������� ���������� ���� �������������";
				WaitEnterInput();
				return;
			}

			StudentWorkCourseTable(studentsArray[index]);
			cin.ignore();

			cout << "�� ������ ���������� ����� ���� ����� ��������? (1- ��; 0 - ���)\n";
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