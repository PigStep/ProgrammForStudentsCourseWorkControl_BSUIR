#pragma once
#include "StudentFileManip.h"

// табличные константы
const int BORDERS_WIDTH = 80;   // Общая ширина таблицы
const int OPTIONS_PADDING = 5; // Отступ для значений
const int HEADER_WIDTH = 10;  // Ширина левой колонки
const int INPUT_PADDING = 10;   // Отступ для полей ввода

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