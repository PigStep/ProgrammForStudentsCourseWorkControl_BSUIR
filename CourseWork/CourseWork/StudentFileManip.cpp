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
	choice = GetIntegerInput(0, 7);

	return choice;

} 

void DeleteStudentArray(int index) {
	studentsArray.erase(studentsArray.begin() + index);
}

void RefreshStudentsId() {
	int userId = userAccountLink->getId();
	for (int i = 0; i < studentsArray.size(); i++) {
		studentsArray[i].setId(i + 1);
	}

	// Проверяем, что userId всё ещё в допустимых пределах
	if (userId > 1 && userId <= studentsArray.size()+1) {
		userAccountLink = &studentsArray[userId-2];
	}
}

//Получить номер параметра поиска
int FindStudentInFileMenu(string message) {
	int choice;

	// Вывод меню выбора параметра
	cout << setw(OPTIONS_PADDING) << "" << message<<endl;

	cout << setw(OPTIONS_PADDING) << "" << "1. ID пользователя\n";
	cout << setw(OPTIONS_PADDING) << "" << "2. Имя\n";
	cout << setw(OPTIONS_PADDING) << "" << "3. Фамилия\n";
	cout << setw(OPTIONS_PADDING) << "" << "4. Отчество\n";
	cout << setw(OPTIONS_PADDING) << "" << "5. Группа\n";
	cout << setw(OPTIONS_PADDING) << "" << "6. Курс\n";
	cout << setw(OPTIONS_PADDING) << "" << "0. Выход\n\n";

	// Ввод выбора пользователя
	cout << setw(INPUT_PADDING) << "" << "Ваш выбор: ";
	choice = GetIntegerInput(0, 6);

	return choice;
}

//Получить вектор студентов из файла по значению
vector<int> FindStudentByParam() {
	vector<int> studentsIndexes;
	string searchValue;
	int intSearchValue;

	int choice = FindStudentInFileMenu("Выберете параметр поиска записи");

	if (choice == 0){
		studentsIndexes.push_back(-1);
		return studentsIndexes; // Выход
	}

	// Запрос значения для поиска
	cout << setw(INPUT_PADDING) << "" << "Введите значение для поиска: ";
	if (choice == 1 || choice == 5 || choice == 6) {
		intSearchValue = GetIntegerInput(0);
	}
	else {
		searchValue = GetStringInput("");
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
		cout << setw(INPUT_PADDING) << "" << "Запись не найдена!\n";
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

	int sortField = FindStudentInFileMenu("Введите параметр сортировки студентов (по убыванию):");

	if (sortField == 0) {
		return vector<int>(0); //заглушка на 0
	}

	// Функция пузырьковой сортировки индексов по выбранному полю
	if (studentsArray.empty()) {
		indexes.clear(); // Если массив студентов пуст, возвращаем пустой вектор индексов
	}
	else {
		// Пузырьковая сортировка
		for (size_t i = 0; i < indexes.size(); ++i) {
			for (size_t j = 0; j < indexes.size() - i - 1; ++j) {
				bool needSwap = false;

				// Определяем нужно ли менять элементы местами
				switch (sortField) {
				case 1: // ID
					needSwap = studentsArray[indexes[j]].getId() > studentsArray[indexes[j + 1]].getId();
					break;
				case 2: // Имя
					needSwap = studentsArray[indexes[j]].getName() > studentsArray[indexes[j + 1]].getName();
					break;
				case 3: // Фамилия
					needSwap = studentsArray[indexes[j]].getSurname() > studentsArray[indexes[j + 1]].getSurname();
					break;
				case 4: // Отчество
					needSwap = studentsArray[indexes[j]].getSecondName() > studentsArray[indexes[j + 1]].getSecondName();
					break;
				case 5: // Группа
					needSwap = studentsArray[indexes[j]].getGroup() > studentsArray[indexes[j + 1]].getGroup();
					break;
				case 6: // Курс
					needSwap = studentsArray[indexes[j]].getCourse() > studentsArray[indexes[j + 1]].getCourse();
					break;
				default:
					break;
				}

				// Если нужно, меняем элементы местами
				if (needSwap) {
					swap(indexes[j], indexes[j + 1]);
				}
			}
		}
	}

	return indexes;
}

vector<int> GetStudentsWithoutAcces() {
	vector<int> indexes;

	for (int i = 0; i < studentsArray.size(); i++) {
		if (!studentsArray[i].getAcces())
			indexes.push_back(i);
	}

	return indexes;
}

//Функция загрузки студентов из файла в оперативную память
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
		if (regTokens.size() < 6) continue; // Минимум 5 поля для User

		// Обрабатываем строку из файла данных (Student + CourseWork)
		vector<string> dataTokens = SplitString(dataLine, ';');
		if (dataTokens.size() < 8) continue; // Минимум 8 полей

		// Создаем объект StudentCourseWork
		StudentCourseWork student(
			stoi(regTokens[0]),  // id
			stoi(regTokens[1]),  // userLevel
			stoi(regTokens[2]),  // acces
			regTokens[3],        // login
			regTokens[4],		 // salt
			regTokens[5],        // hashedpassword
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
			name = GetStringInput("Введите новое имя: ", false,true);
			break;
		case 2:
			secondname = GetStringInput("Введите новую фамилию: ", false, true);
			break;
		case 3:
			surname = GetStringInput("Введите новое отчество: ", false, true);
			break;
		case 4:
			cout << setw(INPUT_PADDING) << "" << "Введите новую группу: ";
			group = GetIntegerInput(MIN_COURSE);
			break;
		case 5:
			cout << setw(INPUT_PADDING) << "" << "Введите новый курс: ";
			course = GetIntegerInput(1,4);
			break;
		case 6:
			do {
				newString = GetStringInput("Введите новый логин: ");
			} while (IsLoginExist(newString));
			login = newString;
			break;
		case 7:
			newString = GetPasswordInput("Введите новый пароль: ");;
			this->hashPassword(newString);
			break;
		case 0:
			break;
		default:
			break;
		}

		ClearTerminal();
		AccoutTable(*this);
	} while (choice != 0);
	
}



void RegistrateStudentInFile(bool haveAcces, string login) {

	int userLevel = 0;
	string name;
	string secondname;
	string surname;
	int group;
	int course;

	string password;
	int currentStudentsNum = studentsArray.size();

	int n = 1;
	if (haveAcces) { //если регистрирует администратор

		cout << left << setw(OPTIONS_PADDING) << "Введите количество добавляемых записей (0 для выхода): ";
		n = GetIntegerInput(0);
	}


	for (int i = 0; i < n; i++) {
		currentStudentsNum ++; //начинаем индексирование с 1
		
		//Уровень доступа (только при добавлени админом
		if (haveAcces) {
			cout << "Уровень доступа записи (0 - студент, 1 - администратор): ";
			userLevel = GetIntegerInput(0, 1);
		}

		// Вывод индекса
		cout << "Запись[" << currentStudentsNum << "]:\n\n";

		if (login.empty()) {
			do {
				// Ввод логина
				login = GetStringInput("Логин: ");
			} while (IsLoginExist(login));
		}

		// Ввод пароля
		password =  GetPasswordInput("Пароль: ");

		//Ввод имени
		name = GetStringInput("Имя: ", false, true);

		// Ввод фамилии
		secondname = GetStringInput("Фамилия: ", false, true);

		// Ввод отчества
		surname = GetStringInput("Отчество: ", false, true);

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
		group = GetIntegerInput(MIN_COURSE, INT_MAX,"Группа: ");

		// Ввод курса (число)
		course = GetIntegerInput(0,4,"Курс: ");


		StudentCourseWork StudentCourse(
			currentStudentsNum,
			userLevel,
			haveAcces, //пользователь подтвержден по уолчанию при регистрации админом
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
	id=studentsArray.size()+1;
	acces = 1;

	login="admin";
	salt = "adminSalt";
	hashedPassword=HashPassword("admin",salt);
}

User::User(int id, int userLevel,
	string login, string salt, string password, int acces) {
	this->id = id;

	if (salt.empty()) {
		hashPassword(password);
	}
	else {
		this->salt = salt;
		this->hashedPassword = password;
	}


	this->acces = acces;
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
		<< self.acces << ";"
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
Student::Student(int id, int userLevel, int acces,
	string login, string salt, string password, 
	string name, string secondname, string surname,
	int group, int course) : User(id, userLevel, login, salt, password, acces){

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
		cout << "ВНИМАНИЕ, ФАЙЛ С КОНТРОЛЬНЫМИ ТОЧКАМИ ОТСУТСВТУЕТ, ДОБАВЛЕНЫ КОНТРОЛЬНЫЕ ТОЧКИ ПО УМОЛЧАНИЮ" << endl;
}
//Функция вывода всех дат контрольных точек одной строкой
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