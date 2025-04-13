#pragma once
#include "Header.h"

// table macroses
#define BORDERS_WIDTH 100
#define OPTIONS_PADDING 5
#define HEADER_PADDING 5

// functions prototypes

//base tableFunctions
void ClearTerminal();
ostream& headerBorder(ostream&);
void MenuWithOptionsHeaderCentralized(int, const string[], string);
void SubHeader(const string);

//loginTableFunctions
void LoginFormHeader(bool);
void LoginAutorizationStatus(bool);