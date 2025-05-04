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

void printBorder(char);
void printTableRow(const string&, const string&, char);
void AccoutTable(Student);
void StudentWorkCourseTable(StudentCourseWork);