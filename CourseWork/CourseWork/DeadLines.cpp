#include "StudentFileManip.h"
#include "TableManips.h"

//методы класса
string Date::getDate() const{
	string ret = "";

	if (day < 10)
		ret += "0";
	ret += to_string(day);
	ret += ".";

	if (month < 10)
		ret += "0";
	ret += to_string(month);
	ret += ".";

	ret += to_string(year);

	return ret;
}

void Date::SetDate() {
	while (true) {
		cout << "Введите число: " << setw(INPUT_PADDING) << "";
		day = GetIntegerInput(1, 31);

		cout << "Введите месяц: " << setw(INPUT_PADDING) << "";
		month = GetIntegerInput(1, 12);

		cout << "Введите год: " << setw(INPUT_PADDING) << "";
		year = GetIntegerInput(1);

		if (IsValidDate(day, month, year)) {
			break;
		}

		cout << "Ошибка: введена некорректная дата. Пожалуйста, повторите ввод.\n";
	}
}

void Date::parse(string str) {
	size_t dot1 = str.find('.');
	size_t dot2 = str.rfind('.');

	// Извлекаем подстроки: день, месяц, год
	string dayStr = str.substr(0, dot1);
	string monthStr = str.substr(dot1 + 1, dot2 - dot1 - 1);
	string yearStr = str.substr(dot2 + 1);

	// Преобразуем строки в числа
	int day, month, year;

	day = stoi(dayStr);
	month = stoi(monthStr);
	year = stoi(yearStr);
	

	// Устанавливаем значения
	this->day = day;
	this->month = month;
	this->year = year;
}

//Является ли год високосным
bool Date::IsLeapYear(int y) const {
	return (y % 400 == 0) || (y % 100 != 0 && y % 4 == 0);
}
//Узнать количество дней в месяце
int Date::DaysInMonth(int m, int y) const {
	switch (m) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 4: case 6: case 9: case 11:
		return 30;
	case 2:
		return IsLeapYear(y) ? 29 : 28;
	default:
		return 0;
	}
}

//Проверка на корректность даты
bool Date::IsValidDate(int d, int m, int y) const {
	// Получаем текущую дату (безопасно, через localtime_s)
	time_t now = time(nullptr);
	tm currentTime;
	if (localtime_s(&currentTime, &now) != 0) {
		return false; // Ошибка получения времени
	}

	int currentYear = currentTime.tm_year + 1900;
	int currentMonth = currentTime.tm_mon + 1;
	int currentDay = currentTime.tm_mday;

	// Проверка, что дата не раньше текущей
	if (y < currentYear) return false;
	if (y == currentYear && m < currentMonth) return false;
	if (y == currentYear && m == currentMonth && d < currentDay) return false;

	// Проверка на допустимые границы месяца и дня
	if (m < 1 || m > 12) return false;
	if (d < 1 || d > DaysInMonth(m, y)) return false;

	return true;
}

bool Date::operator>(const Date& other) const {
	if (year != other.year)
		return year > other.year;
	if (month != other.month)
		return month > other.month;
	return day > other.day;
}


fstream& operator<<(fstream& stream, const Date& self) {
	stream << self.getDate();

	return stream;
}