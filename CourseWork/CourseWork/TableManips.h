#pragma once
#include "Student.h"

// табличные константы
const int BORDERS_WIDTH = 100;
const int OPTIONS_PADDING = 5;
const int HEADER_PADDING = 5;
const int INPUT_PADDING = 10;

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

// Функция для вывода горизонтальной границы
void printBorder(char);
// Функция для вывода строки таблицы
void printTableRow(const string&, const string&, char);
void RegistratedStudentTable(Student);
void StudentWorkCourseTable(StudentCourseWork);