#include "TableManips.h"
#include "StudentFileManip.h"

extern void AdminFunctionsMenu() {
	const string OPTIONS_TO_CHOOSE[4] = {"����������� ��������� �������� � �������� ��������", "������������ ������ ������� ������ ���������", "���������� ����������� ����� ��� �����", "�������� �������������� �����"};
	const string HEADER = { "���� ��������������" };
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
	const string OPTIONS_TO_CHOOSE[4] = { "����������� ��� ������� ������","�������� ������� ������/������", "�������� ������� ������/������", "������� ������� ������ / ������"  };
	const string HEADER = { "���� �������� � �������� ��������" };
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
	const string HEADER = "������� ���������";
	HeaderSecondLevel(HEADER);

	for (int i = 0; i < studentsArray.size(); i++) {
		RegistratedStudentTable(studentsArray[i]);
	}

	cin.get();
	WaitEnterInput();
}

void AddStudentFromArrayMenu() {
	const string HEADER = "����������� ��������";
	HeaderSecondLevel(HEADER);

	RegistrateStudentInFile();
}

void EditStudentsFromArrayMenu() {
	const string HEADER = "�������������� ��������";
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
	const string HEADER = "�������� ��������";
	HeaderSecondLevel(HEADER);

	vector<int> indexes;
	int delChoice;

	do {
		indexes = FindStudentInFile();

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
			}

			cout << "������ ������� �������"<<endl;
		}
		ClearTerminal();
		HeaderSecondLevel(HEADER);

	} while (indexes.size() != 0);
}

void ShowStudentsDataTable() {
	const string HEADER = "������� ������ ���������";
	HeaderSecondLevel(HEADER);

	for (int i = 0; i < studentsArray.size(); i++) {
		StudentWorkCourseTable(studentsArray[i]);
	}
	cin.ignore();
	WaitEnterInput();
}


void SetCourseDeadlines() {
	const string HEADER = "��������� ����������� �����";
	HeaderSecondLevel(HEADER);

	string message = "������� ����������� �����:\n";
	message += GetDeadLines();
	LogMessage(message);

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

void SetStudentsMarks() {
	const string HEADER = "���� ���������� ������ ��������";
	HeaderSecondLevel(HEADER);
	vector<int> indexes;

	do {
		indexes = FindStudentInFile();

		for (int i = 0; i < indexes.size(); i++) {
			int index = indexes[i];

			RefreshMenu(HEADER, index);

			cout << "�������� ����������� ����� �� ���������: ";

			StudentFileRewrite();
		}

		ClearTerminal();
		HeaderSecondLevel(HEADER);
	} while (indexes.size() != 0);
}
