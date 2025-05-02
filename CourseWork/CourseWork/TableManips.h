#pragma once
#include "StudentFileManip.h"

// functions prototypes

//Базовые табличные функции

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

// Функция для вывода горизонтальной границы
void printBorder(char);
// Функция для вывода строки таблицы
void printTableRow(const string&, const string&, char);
void RegistratedStudentTable(Student);
void StudentWorkCourseTable(StudentCourseWork);