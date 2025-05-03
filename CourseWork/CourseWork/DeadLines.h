#pragma once
#include "Header.h"

using namespace std;

class Date {
	int day;
	int month;
	int year;

public:
	Date() {
		day = 0;
		month = 0;
		year = 2000;
	}
	void parse(string);
	void SetDate();
	string getDate() const;

	bool IsLeapYear(int y) const;
	int DaysInMonth(int m, int y) const;
	bool IsValidDate(int d, int m, int y) const;

	bool operator>(const Date& other) const;

	friend fstream& operator<<(fstream&, const Date&);

};