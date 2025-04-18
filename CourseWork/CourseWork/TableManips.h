#pragma once
#include "Header.h"
#include "Student.h"

// table macroses
#define BORDERS_WIDTH 100
#define OPTIONS_PADDING 5
#define HEADER_PADDING 5
#define INPUT_PADDING 10

// functions prototypes

//base tableFunctions
void ClearTerminal();
void WaitEnterInput();
ostream& headerBorder(ostream&);
void MenuWithOptionsHeaderCentralized(int, const string[], string);
void HeaderSecondLevel(const string);

//loginTableFunctions
void LoginFormHeader(bool);
void LoginAutorizationStatus(bool);

//studentTableFunctions

// ������� ��� ������ �������������� �������
void printBorder(char);
// ������� ��� ������ ������ �������
void printTableRow(const string&, const string&, char);
void RegistratedStudentTable(Student);