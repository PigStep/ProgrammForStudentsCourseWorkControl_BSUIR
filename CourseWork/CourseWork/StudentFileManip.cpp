#include "StudentFileManip.h"
#include "TableManips.h";

vector<StudentCourseWork> studentsArray;
Date courseDeadLinePoints[NUM_OF_DEADLINES];

using namespace std;

int StudentEditMenuChoice() {
	int choice;

	// Вывод меню выбора параметра
	cout << setw(OPTIONS_PADDING) << "" << "Выберите параметр для изменения:\n";
	cout << setw(OPTIONS_PADDING) << "" << "1. Имя\n";
	cout << setw(OPTIONS_PADDING) << "" << "2. Фамилия\n";
	cout << setw(OPTIONS_PADDING) << "" << "3. Отчество\n";
	cout << setw(OPTIONS_PADDING) << "" << "4. Группа\n";
	cout << setw(OPTIONS_PADDING) << "" << "5. Курс\n";
	cout << setw(OPTIONS_PADDING) << "" << "6. Логин\n";
	cout << setw(OPTIONS_PADDING) << "" << "7. Пароль\n\n";
	cout << setw(OPTIONS_PADDING) << "" << "0. Выход\n\n";

	// Ввод выбора пользователя
	cout << setw(INPUT_PADDING) << "" << "Ваш выбор: ";
	cin >> choice;

	return choice;

} 

void DeleteStudentArray(int index) {
	studentsArray.erase(studentsArray.begin() + index);
}

void RefreshStudentsId() {
	for (int i = 0; i < studentsArray.size(); i++) {
		studentsArray[i].setId(i + 1);
	}
}

//Получить номер параметра поиска
int FindStudentInFileMenu() {
	int choice;

	// Вывод меню выбора параметра
	cout << setw(OPTIONS_PADDING) << "" << "Выберите параметр для поиска студента:\n";

	cout << setw(OPTIONS_PADDING) << "" << "1. ID пользователя\n";
	cout << setw(OPTIONS_PADDING) << "" << "2. Имя\n";
	cout << setw(OPTIONS_PADDING) << "" << "3. Фамилия\n";
	cout << setw(OPTIONS_PADDING) << "" << "4. Отчество\n";
	cout << setw(OPTIONS_PADDING) << "" << "5. Группа\n";
	cout << setw(OPTIONS_PADDING) << "" << "6. Курс\n";
	cout << setw(OPTIONS_PADDING) << "" << "0. Выход\n\n";

	// Ввод выбора пользователя
	cout << setw(INPUT_PADDING) << "" << "Ваш выбор: ";
	cin >> choice;

	return choice;
}

//Получить вектор студентов из файла
vector<int> FindStudentByParam() {
	vector<int> studentsIndexes;
	string searchValue;
	int intSearchValue;

	int choice = FindStudentInFileMenu();

	if (choice == 0) return studentsIndexes; // Выход

	// Запрос значения для поиска
	cout << setw(INPUT_PADDING) << "" << "Введите значение для поиска: ";
	if (choice == 1 || choice == 5 || choice == 6) {
		cin >> intSearchValue;
	}
	else {
		cin.ignore(); // Очищаем буфер перед чтением строки
		getline(cin, searchValue);
	}

	// Поиск по выбранному параметру
	for (int i = 0; i < studentsArray.size(); i++) {
		
		bool found = false;

		switch (choice) {
		case 1: // ID пользователя
			found = (studentsArray[i].getId() == intSearchValue);
			break;
		case 2: // Имя
			found = (studentsArray[i].getName() == searchValue);
			break;
		case 3: // Фамилия
			found = (studentsArray[i].getSurname() == searchValue);
			break;
		case 4: // Отчество
			found = (studentsArray[i].getSecondName() == searchValue);
			break;
		case 5: // Группа
			found = (studentsArray[i].getGroup() == intSearchValue);
			break;
		case 6: // Курс
			found = (studentsArray[i].getCourse() == intSearchValue);
			break;
		default:
			cout << setw(INPUT_PADDING) << "" << "Неверный выбор!\n";
		}

		if (found) {
			studentsIndexes.push_back(i);
		}
	}

	if (studentsIndexes.size() == 0) {
		cout << setw(INPUT_PADDING) << "" << "Студент не найден!\n";
		cin.ignore();
		WaitEnterInput();
	}

	return studentsIndexes;
}

vector<int> SortIndexes() {
	vector<int> indexes(studentsArray.size());

	// Заполняем вектор индексами от 0 до arraySize-1
	for (int i = 0; i < studentsArray.size(); ++i) {
		indexes[i] = i;
	}

	int sortField = FindStudentInFileMenu();

	// Сортируем индексы по выбранному полю
	sort(indexes.begin(), indexes.end(), [&](int a, int b) {
		switch (sortField) {
		case 1: // ID
			return studentsArray[a].getId() < studentsArray[b].getId();
		case 2: // Имя
			return studentsArray[a].getName() < studentsArray[b].getName();
		case 3: // Фамилия
			return studentsArray[a].getSurname() < studentsArray[b].getSurname();
		case 4: // Отчество
			return studentsArray[a].getSecondName() < studentsArray[b].getSecondName();
		case 5: // Группа
			return studentsArray[a].getGroup() < studentsArray[b].getGroup();
		case 6: // Курс
			return studentsArray[a].getCourse() < studentsArray[b].getCourse();
		default:
			return studentsArray[a].getId() < studentsArray[b].getId(); // По умолчанию сортируем по ID
		}
		});

	return indexes;
}
void LoadStudentsFromFile() {
	studentsArray.clear();

	ifstream regFile(STUD_REG_FILE, ios::in | ios::out);
	ifstream dataFile(STUD_DATA_FILE, ios::in | ios::out);

	// Читаем оба файла построчно одновременно
	string regLine, dataLine;
	while (getline(regFile, regLine) && getline(dataFile, dataLine)) {
		if (regLine.empty() || dataLine.empty()) continue;

		// Обрабатываем строку из регистрационного файла (User данные)
		vector<string> regTokens = SplitString(regLine, ';');
		if (regTokens.size() < 5) continue; // Минимум 5 поля для User

		// Обрабатываем строку из файла данных (Student + CourseWork)
		vector<string> dataTokens = SplitString(dataLine, ';');
		if (dataTokens.size() < 8) continue; // Минимум 8 полей

		// Создаем объект StudentCourseWork
		StudentCourseWork student(
			stoi(regTokens[0]),  // id
			stoi(regTokens[1]),  // userLevel
			regTokens[2],        // login
			regTokens[3],		 // salt
			regTokens[4],        // hashedpassword
			dataTokens[0],       // name
			dataTokens[1],       // secondname
			dataTokens[2],       // surname
			dataTokens[3].empty() ? -1 : stoi(dataTokens[3]),  // group
			dataTokens[4].empty() ? -1 : stoi(dataTokens[4])   // course
		);

		// Устанавливаем дополнительные поля
		if (dataTokens.size() > 5) {
			student.SetCourseWorkTheme(dataTokens[5]);
		}
		if (dataTokens.size() > 6) {
			student.SetCourseWorkStorageLink(dataTokens[6]);
		}
		if (dataTokens.size() > 7) { //обработка оценок
			for (int i = 0; i < NUM_OF_DEADLINES; i++) {
				if (!dataTokens[7 + i].empty()) {
					student.setMark(i, stoi(dataTokens[7 + i]));
					}
				}
			}

		studentsArray.push_back(student);
		
	}

	regFile.close();
	dataFile.close();
}

vector<string> SplitString(const string& str, char delimiter) {
	vector<string> tokens;
	string token;
	istringstream tokenStream(str);
	while (getline(tokenStream, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

void Student::StudentEdit() {
	int choice;
	string newString;
	int newInt;

	do {
		choice = StudentEditMenuChoice();

		// Обработка выбора
		switch (choice) {
		case 1:
			cout << setw(INPUT_PADDING) << "" << "Введите новое имя: ";
			cin >> newString;
			name = newString;
			break;
		case 2:
			cout << setw(INPUT_PADDING) << "" << "Введите новую фамилию: ";
			cin >> newString;
			secondname = newString;
			break;
		case 3:
			cout << setw(INPUT_PADDING) << "" << "Введите новое отчество: ";
			cin >> newString;
			surname = newString;
			break;
		case 4:
			cout << setw(INPUT_PADDING) << "" << "Введите новую группу: ";
			cin >> newInt;
			group = newInt;
			break;
		case 5:
			cout << setw(INPUT_PADDING) << "" << "Введите новый курс: ";
			cin >> newInt;
			course = newInt;
			break;
		case 6:
			cout << setw(INPUT_PADDING) << "" << "Введите новый логин: ";
			cin >> newString;
			login = newString;
			break;
		case 7:
			cout << setw(INPUT_PADDING) << "" << "Введите новый пароль: ";
			cin >> newString;
			this->hashPassword(newString);
			break;
		case 0:
			break;
		default:
			cout << setw(INPUT_PADDING) << "" << "Ошибка: неверный выбор!\n";
			break;
		}

		ClearTerminal();
		RegistratedStudentTable(*this);
	} while (choice != 0);
	
}



void RegistrateStudentInFile() {

	int userLevel;
	string name;
	string secondname;
	string surname;
	int group;
	int course;

	string login;
	string password;
	int currentStudentsNum = studentsArray.size();

	int n;
	cout << left << setw(OPTIONS_PADDING) << "Введите количество добавляемых записей: ";
	cin >> n;
	cin.ignore(); // Очистка буфера после cin >> 

	for (int i = 0; i < n; i++) {
		currentStudentsNum ++; //начинаем индексирование с 1

		//Уровень доступа
		cout << "Уровень доступа записи (0 - студент, 1 - администратор): ";
		cin >> userLevel;
		cin.ignore();

		// Ввод имени
		cout << "Запись " << currentStudentsNum << ":\n\n";

		// Ввод логина
		cout << left << setw(OPTIONS_PADDING) << "Логин: ";
		getline(cin, login);

		// Ввод пароля
		cout << left << setw(OPTIONS_PADDING) << "Пароль: ";
		getline(cin, password);

		cout << left << setw(OPTIONS_PADDING) << "Имя: ";
		getline(cin, name);

		// Ввод фамилии
		cout << left << setw(OPTIONS_PADDING) << "Фамилия: ";
		getline(cin, secondname);

		// Ввод отчества
		cout << left << setw(OPTIONS_PADDING) << "Отчество: ";
		getline(cin, surname);

		if (userLevel == 1) {
			StudentCourseWork StudentCourse(
				currentStudentsNum,
				userLevel,
				password,
				login,
				"",
				name,
				secondname,
				surname);

			StudentCourse.writeInFiles(studentsFileData, studentsFileReg);
			continue;
		}

		// Ввод группы (число)
		cout << left << setw(OPTIONS_PADDING) << "Группа: ";
		cin >> group;
		cin.ignore();  // Очистка буфера после cin >> 

		// Ввод курса (число)
		cout << left << setw(OPTIONS_PADDING) << "Курс: ";
		cin >> course;
		cin.ignore();  // Очистка буфера после cin >>


		StudentCourseWork StudentCourse(
			currentStudentsNum,
			userLevel,
			login,
			"",
			password,
			name,
			secondname,
			surname,
			group,
			course);

		StudentCourse.writeInFiles(studentsFileData,studentsFileReg);
	}
}

void StudentFileRewrite() {
	fstream dataStream;
	fstream regStream;

	dataStream.open(STUD_DATA_FILE,ios::out | ios::trunc);
	regStream.open(STUD_REG_FILE, ios::out | ios::trunc);

	dataStream << flush;
	regStream << flush;

	for (int i = 0; i < studentsArray.size(); i++) {
		studentsArray[i].writeInFiles(dataStream,regStream);
	}

	dataStream.close();
	regStream.close();
}

int AdminArrayCount() {
	int count = 0;

	for (int i = 0; i < studentsArray.size(); i++) {
		if (studentsArray[i].getUserLevel() == 1)
			count++;
	}

	return count;
}
void CreateBaseAdmin() {
	StudentCourseWork admin;

	admin.writeInFiles(studentsFileData,studentsFileReg);
}

//методы Класса User

User::User() {
	userLevel=1;
	id=1;

	login="admin";
	salt = "adminSalt";
	hashedPassword=HashPassword("admin",salt);
}

User::User(int id, int userLevel,
	string login, string salt, string password) {
	this->id = id;

	if (salt.empty()) {
		hashPassword(password);
	}
	else {
		this->salt = salt;
		this->hashedPassword = password;
	}


	
	this->login = login;
	this->userLevel = userLevel;
}

//Фукнкция проверки на существование пароля
bool User::checkPassword(const string& password){
	return HashPassword(password, salt) == hashedPassword;
}

//захэшировать пароль с уникальной солью для записи
void User::hashPassword(const string& password)
{
	salt = GenerateSalt();
	hashedPassword = HashPassword(password, salt);
}

fstream& operator<<(fstream& stream, const User& self){

	stream << self.id << ";"
		<< self.userLevel << ";"
		<< self.login << ";"
		<< self.salt<<";"
		<< self.hashedPassword << ";";

	return stream;
}

//Методы Класса Student
Student::Student() {
	name = "ADMIN";
	secondname = "ADMIN";
	surname = "ADMIN";

	group = -1;
	course = -1;
}
Student::Student(int id, int userLevel,
	string login, string salt, string password, 
	string name, string secondname, string surname,
	int group, int course) : User(id, userLevel, login, salt, password){
	this->name = name;
	this->secondname = secondname;
	this->surname = surname;

	this->course = course;
	this->group = group;
}
Student::Student(int id, int userLevel,
	string login, string salt, string password,
	string name, string secondname, string surname) : User(id, userLevel, login, salt, password) {

	this->name = name;
	this->secondname = secondname;
	this->surname = surname;
}

fstream& operator<<(fstream& stream, const Student& self) {
	stream << self.name << ";"
		<< self.secondname << ";"
		<< self.surname << ";"

		<< self.group << ";"
		<< self.course << ";";
	return stream;
}

//Методы класса StudentCourseWork

StudentCourseWork::StudentCourseWork(int id, int userLevel, 
	string password, string login, string salt,
	string name, string secondname, string surname) : Student(id, userLevel, login, salt, password, name, secondname, surname) {

	courseWorkStorageLink = STORAGE_LINK_DEFAULT;
	courseWorkTheme = THEME_DEFAULT;
	group = -1;
	course = -1;

	setMarksDefault();
}

fstream& operator<<(fstream& stream, const StudentCourseWork& self) {

	stream << self.courseWorkTheme << ';'
		<< self.courseWorkStorageLink << ';';

	for (int i = 0; i < NUM_OF_DEADLINES; i++) {
		stream << self.deadLinePointsMarks[i] << ";";
	}

	return stream;
}

void StudentCourseWork::setCourseWorkTheme() {
	string theme;

	cin.ignore();
	cout << "Введите новую тему курсовой работы\n";
	cout << setw(INPUT_PADDING);
	getline(cin, theme);

	this->courseWorkTheme = theme;
}

void StudentCourseWork::setMark(int deadLineIndex, int mark) {
	deadLinePointsMarks[deadLineIndex] = mark;
}


int StudentCourseWork::getMark(int index) {
	return deadLinePointsMarks[index];
}

void StudentCourseWork::setMarksDefault() {
	for (int i = 0; i < NUM_OF_DEADLINES; i++) {
		deadLinePointsMarks[i] = DEFAULT_MARK;
	}
}

void StudentCourseWork::writeInFiles(fstream& dataStream, fstream& regStream) {
	// 1. Запись данных User в первый файл
	// Явное приведение к базовому классу User для вызова нужной перегрузки
	regStream << static_cast<const User&>(*this);
	regStream << "\n";
	regStream.flush();


	// 2. Запись данных Student и StudentCourseWork во второй файл
	// Сначала записываем Student часть
	dataStream << static_cast<const Student&>(*this);

	// Затем записываем StudentCourseWork часть
	dataStream << *this;
	dataStream << "\n";  // Добавляем перевод строки для разделения записей
	dataStream.flush();  // Принудительная запись
}

//Функции работы с контрольными точками

void SaveDeadLinesInFile() {
	// Закрываем и переоткрываем файл в режиме перезаписи
	studentsFileDeadLines.close();
	studentsFileDeadLines.open(DEAD_LINES_FILE, ios::out | ios::trunc); // перезаписываем файл

	// Записываем даты с разделителями
	for (int i = 0; i < NUM_OF_DEADLINES; i++) {
		studentsFileDeadLines << courseDeadLinePoints[i].getDate();
		if (i < NUM_OF_DEADLINES - 1) {
			studentsFileDeadLines << ";"; // добавляем разделитель
		}
	}
	studentsFileDeadLines << endl; // добавляем перевод строки

	// Возвращаем файл в исходный режим (если нужно)
	studentsFileDeadLines.close();
	studentsFileDeadLines.open(DEAD_LINES_FILE, ios::in | ios::out | ios::app);
}

//Функция загрузки контрольных точек из файла в оперативную память
void LoadDeadlinesFromFile() {
	string line;
	if (getline(studentsFileDeadLines, line) && !line.empty()) { // Считываем строку с датами
		istringstream iss(line);
		string dateStr;
		int index = 0;

		// Разделяем строку по символу ';' и парсим даты
		while (getline(iss, dateStr, ';') && index < NUM_OF_DEADLINES) {
			courseDeadLinePoints[index].parse(dateStr);
			index++;
		}
	}
	else
		cout << EMPTY_DEADLINES_FILE_WARN << endl;
}
//Функция получения всех дат контрольных точек одной строкой
string GetDeadLines() {
	string dates;
	for (int i = 0; i < NUM_OF_DEADLINES; i++) {
		dates += to_string(i + 1) + "- " + courseDeadLinePoints[i].getDate() + '\n';
	}
	return dates;
}

//Функция вывода всех контрльных точек в виде списка
void ShowDeadLinesList() {
	string message = "Текущие контрольные точки:\n";
	message += GetDeadLines();
	LogMessage(message);
}