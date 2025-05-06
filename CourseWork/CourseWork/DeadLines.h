#pragma once
#include "Header.h"

using namespace std;

class Date {
	int day;
	int month;
	int year;

	bool IsLeapYear(int y) const;
	int DaysInMonth(int m, int y) const;
	bool IsValidDate(int d, int m, int y) const;

public:
	Date() {
		day = 0;
		month = 0;
		year = 2000;
	}
	void parse(string);
	void SetDate();
	string getDate() const;

	bool operator>(const Date& other) const;
	bool operator==(const Date& other) const;

	friend fstream& operator<<(fstream&, const Date&);

};