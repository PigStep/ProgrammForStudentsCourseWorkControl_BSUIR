#include "TableManips.h"
#include "Student.h"

extern void AdminFunctionsMenu() {
	const string OPTIONS_TO_CHOOSE[4] = {"����������� ��������� �������� � �������� ��������", "������������ ������ ������� ���������", "���������� ����������� ����� ��� �����", "�������� �������������� �����"};
	const string HEADER = { "���� ��������������" };
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
	const string OPTIONS_TO_CHOOSE[4] = { "����������� ��� ������� ������","�������� ������� ������/������", "�������� ������� ������/������", "������� ������� ������ / ������"  };
	const string HEADER = { "���� �������� � �������� ��������" };
	int n;

	do {
		MenuWithOptionsHeaderCentralized(4, OPTIONS_TO_CHOOSE, HEADER);
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
		}
		ClearTerminal();
		HeaderSecondLevel(HEADER);

	} while (indexes.size() != 0);
}

