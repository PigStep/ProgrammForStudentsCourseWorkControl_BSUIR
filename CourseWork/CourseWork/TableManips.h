#pragma once
#include "Header.h"

// Макросы табличных данных
#define BORDERS_WIDTH 100
#define OPTIONS_PADDING 5
#define HEADER_PADDING 5

// Объявления функций
void ClearTerminal();
ostream& headerBorder(ostream& stream);
void PrintMenuWithOptionsHeaderCentralized(int optionsCount, const string optionsArray[], string header);
