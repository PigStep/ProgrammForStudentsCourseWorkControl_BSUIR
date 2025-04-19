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
	cout << "¬ведите число: "<< setw(INPUT_PADDING) <<"";
	cin >> day;

	cout << "¬ведите мес€ц: " << setw(INPUT_PADDING) << "";
	cin >> month;

	cout << "¬ведите год: " << setw(INPUT_PADDING) << "";
	cin >> year;
}

void Date::parse(string str) {
	size_t dot1 = str.find('.');
	size_t dot2 = str.rfind('.');

	// »звлекаем подстроки: день, мес€ц, год
	string dayStr = str.substr(0, dot1);
	string monthStr = str.substr(dot1 + 1, dot2 - dot1 - 1);
	string yearStr = str.substr(dot2 + 1);

	// ѕреобразуем строки в числа
	int day, month, year;

	day = stoi(dayStr);
	month = stoi(monthStr);
	year = stoi(yearStr);
	

	// ”станавливаем значени€
	this->day = day;
	this->month = month;
	this->year = year;
}

fstream& operator<<(fstream& stream, const Date& self) {
	stream << self.getDate();

	return stream;
}