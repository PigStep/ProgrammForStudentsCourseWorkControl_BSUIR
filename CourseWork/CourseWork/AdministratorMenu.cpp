#include "TableManips.h"

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

void RegistrateStudents() {
	const string HEADER = "���������� ������� ������ ��������";

	SubHeader(HEADER);

	cin.get();
	cout << "������� Enter ��� �����������" << endl;
	cin.get();
	
}

void StudentsListOperations() {
	const string OPTIONS_TO_CHOOSE[4] = { "����������� ��� ������� ������","�������� ������� ������/������", "������� ������� ������/������", "�������� ������� ������/������" };
	const string HEADER = { "���� �������� � �������� ��������" };
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