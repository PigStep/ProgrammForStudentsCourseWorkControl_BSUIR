#pragma once
#include "Header.h"

// ������� ��������� ������
#define BORDERS_WIDTH 100
#define OPTIONS_PADDING 5
#define HEADER_PADDING 5

// ���������� �������
void ClearTerminal();
ostream& headerBorder(ostream& stream);
void PrintMenuWithOptionsHeaderCentralized(int optionsCount, const string optionsArray[], string header);
