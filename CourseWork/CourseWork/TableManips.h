#pragma once
#include "StudentFileManip.h"

// ��������� ���������
const int BORDERS_WIDTH = 80;   // ����� ������ �������
const int OPTIONS_PADDING = 5; // ������ ��� ��������
const int HEADER_WIDTH = 10;  // ������ ����� �������
const int INPUT_PADDING = 10;   // ������ ��� ����� �����

// functions prototypes

//������� ��������� �������

void ClearTerminal();
void WaitEnterInput();
ostream& headerBorder(ostream&);
void HeaderFirstLevel(int, const string[], string);
void HeaderSecondLevel(const string);
void LogMessage(string&);

//loginTableFunctions
void LoginFormHeader(bool);
void LoginAutorizationStatus(bool);

//studentTableFunctions

// ������� ��� ������ �������������� �������
void printBorder(char);
// ������� ��� ������ ������ �������
void printTableRow(const string&, const string&, char);
void RegistratedStudentTable(Student);
void StudentWorkCourseTable(StudentCourseWork);