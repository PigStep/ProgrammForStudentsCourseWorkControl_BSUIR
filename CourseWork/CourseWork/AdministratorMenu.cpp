#include "TableManips.h"

extern void AdminFunctionsMenu() {
	const string OPTIONS_TO_CHOOSE[5] = { "���������� ����� ��������","����� �����","��� ���� ����", "�����","��"};
	const string HEADER = { "���� ��������������" };

	PrintMenuWithOptionsHeaderCentralized(5, OPTIONS_TO_CHOOSE, HEADER);

	int n;
	cin >> n;
}