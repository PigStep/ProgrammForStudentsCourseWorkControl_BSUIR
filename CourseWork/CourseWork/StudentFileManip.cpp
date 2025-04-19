#include "StudentFileManip.h"
#include "TableManips.h";

vector<StudentCourseWork> studentsArray;
Date courseDeadLinePoints[NUM_OF_DEADLINES];

using namespace std;

int StudentEditMenuChoice() {
	int choice;

	// ����� ���� ������ ���������
	cout << setw(OPTIONS_PADDING) << "" << "�������� �������� ��� ���������:\n";
	cout << setw(OPTIONS_PADDING) << "" << "1. ���\n";
	cout << setw(OPTIONS_PADDING) << "" << "2. �������\n";
	cout << setw(OPTIONS_PADDING) << "" << "3. ��������\n";
	cout << setw(OPTIONS_PADDING) << "" << "4. ������\n";
	cout << setw(OPTIONS_PADDING) << "" << "5. ����\n";
	cout << setw(OPTIONS_PADDING) << "" << "6. �����\n";
	cout << setw(OPTIONS_PADDING) << "" << "7. ������\n\n";
	cout << setw(OPTIONS_PADDING) << "" << "0. �����\n\n";

	// ���� ������ ������������
	cout << setw(INPUT_PADDING) << "" << "��� �����: ";
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

//�������� ����� ��������� ������
int FindStudentInFileMenu() {
	int choice;

	// ����� ���� ������ ���������
	cout << setw(OPTIONS_PADDING) << "" << "�������� �������� ��� ������:\n";

	cout << setw(OPTIONS_PADDING) << "" << "1. ID ������������\n";
	cout << setw(OPTIONS_PADDING) << "" << "2. ���\n";
	cout << setw(OPTIONS_PADDING) << "" << "3. �������\n";
	cout << setw(OPTIONS_PADDING) << "" << "4. ��������\n";
	cout << setw(OPTIONS_PADDING) << "" << "5. ������\n";
	cout << setw(OPTIONS_PADDING) << "" << "6. ����\n";
	cout << setw(OPTIONS_PADDING) << "" << "0. �����\n\n";

	// ���� ������ ������������
	cout << setw(INPUT_PADDING) << "" << "��� �����: ";
	cin >> choice;

	return choice;

}

//�������� ������ ��������� �� �����
vector<int> FindStudentByParam() {
	vector<int> studentsIndexes;
	string searchValue;
	int intSearchValue;

	int choice = FindStudentInFileMenu();

	if (choice == 0) return studentsIndexes; // �����

	// ������ �������� ��� ������
	cout << setw(INPUT_PADDING) << "" << "������� �������� ��� ������: ";
	if (choice == 1 || choice == 5 || choice == 6) {
		cin >> intSearchValue;
	}
	else {
		cin.ignore(); // ������� ����� ����� ������� ������
		getline(cin, searchValue);
	}

	// ����� �� ���������� ���������
	for (int i = 0; i < studentsArray.size(); i++) {
		
		bool found = false;

		switch (choice) {
		case 1: // ID ������������
			found = (studentsArray[i].getId() == intSearchValue);
			break;
		case 2: // ���
			found = (studentsArray[i].getName() == searchValue);
			break;
		case 3: // �������
			found = (studentsArray[i].getSurname() == searchValue);
			break;
		case 4: // ��������
			found = (studentsArray[i].getSecondName() == searchValue);
			break;
		case 5: // ������
			found = (studentsArray[i].getGroup() == intSearchValue);
			break;
		case 6: // ����
			found = (studentsArray[i].getCourse() == intSearchValue);
			break;
		default:
			cout << setw(INPUT_PADDING) << "" << "�������� �����!\n";
		}

		if (found) {
			studentsIndexes.push_back(i);
		}
	}

	if (studentsIndexes.size() == 0) {
		cout << setw(INPUT_PADDING) << "" << "������� �� ������!\n";
		cin.ignore();
		WaitEnterInput();
	}

	return studentsIndexes;
}

void LoadStudentsFromFile() {
	studentsArray.clear();

	ifstream regFile(STUD_REG_FILE, ios::in | ios::out);
	ifstream dataFile(STUD_DATA_FILE, ios::in | ios::out);

	// ������ ��� ����� ��������� ������������
	string regLine, dataLine;
	while (getline(regFile, regLine) && getline(dataFile, dataLine)) {
		if (regLine.empty() || dataLine.empty()) continue;

		// ������������ ������ �� ���������������� ����� (User ������)
		vector<string> regTokens = SplitString(regLine, ';');
		if (regTokens.size() < 5) continue; // ������� 5 ���� ��� User

		// ������������ ������ �� ����� ������ (Student + CourseWork)
		vector<string> dataTokens = SplitString(dataLine, ';');
		if (dataTokens.size() < 8) continue; // ������� 8 �����

		// ������� ������ StudentCourseWork
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

		// ������������� �������������� ����
		if (dataTokens.size() > 5) {
			student.SetCourseWorkTheme(dataTokens[5]);
		}
		if (dataTokens.size() > 6) {
			student.SetCourseWorkStorageLink(dataTokens[6]);
		}
		if (dataTokens.size() > 7) { //��������� ������
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

		// ��������� ������
		switch (choice) {
		case 1:
			cout << setw(INPUT_PADDING) << "" << "������� ����� ���: ";
			cin >> newString;
			name = newString;
			break;
		case 2:
			cout << setw(INPUT_PADDING) << "" << "������� ����� �������: ";
			cin >> newString;
			secondname = newString;
			break;
		case 3:
			cout << setw(INPUT_PADDING) << "" << "������� ����� ��������: ";
			cin >> newString;
			surname = newString;
			break;
		case 4:
			cout << setw(INPUT_PADDING) << "" << "������� ����� ������: ";
			cin >> newInt;
			group = newInt;
			break;
		case 5:
			cout << setw(INPUT_PADDING) << "" << "������� ����� ����: ";
			cin >> newInt;
			course = newInt;
			break;
		case 6:
			cout << setw(INPUT_PADDING) << "" << "������� ����� �����: ";
			cin >> newString;
			login = newString;
			break;
		case 7:
			cout << setw(INPUT_PADDING) << "" << "������� ����� ������: ";
			cin >> newString;
			hashedPassword = newString;
			break;
		case 0:
			break;
		default:
			cout << setw(INPUT_PADDING) << "" << "������: �������� �����!\n";
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
	cout << left << setw(OPTIONS_PADDING) << "������� ���������� ����������� �������: ";
	cin >> n;
	cin.ignore(); // ������� ������ ����� cin >> 

	for (int i = 0; i < n; i++) {
		currentStudentsNum ++; //�������� �������������� � 1

		//������� �������
		cout << "������� ������� ������ (0 - �������, 1 - �������������): ";
		cin >> userLevel;
		cin.ignore();

		// ���� �����
		cout << "������ " << currentStudentsNum << ":\n\n";

		// ���� ������
		cout << left << setw(OPTIONS_PADDING) << "�����: ";
		getline(cin, login);

		// ���� ������
		cout << left << setw(OPTIONS_PADDING) << "������: ";
		getline(cin, password);

		cout << left << setw(OPTIONS_PADDING) << "���: ";
		getline(cin, name);

		// ���� �������
		cout << left << setw(OPTIONS_PADDING) << "�������: ";
		getline(cin, secondname);

		// ���� ��������
		cout << left << setw(OPTIONS_PADDING) << "��������: ";
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

		// ���� ������ (�����)
		cout << left << setw(OPTIONS_PADDING) << "������: ";
		cin >> group;
		cin.ignore();  // ������� ������ ����� cin >> 

		// ���� ����� (�����)
		cout << left << setw(OPTIONS_PADDING) << "����: ";
		cin >> course;
		cin.ignore();  // ������� ������ ����� cin >>


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

//������ ������ User

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

//�������� �������� �� ������������� ������
bool User::checkPassword(const string& password){
	return HashPassword(password, salt) == hashedPassword;
}

//������������ ������ � ���������� ����� ��� ������
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

//������ ������ Student
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

//������ ������ StudentCourseWork

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
	// 1. ������ ������ User � ������ ����
	// ����� ���������� � �������� ������ User ��� ������ ������ ����������
	regStream << static_cast<const User&>(*this);
	regStream << "\n";
	regStream.flush();


	// 2. ������ ������ Student � StudentCourseWork �� ������ ����
	// ������� ���������� Student �����
	dataStream << static_cast<const Student&>(*this);

	// ����� ���������� StudentCourseWork �����
	dataStream << *this;
	dataStream << "\n";  // ��������� ������� ������ ��� ���������� �������
	dataStream.flush();  // �������������� ������
}

//������� ������ � ������������ �������

void SaveDeadLinesInFile() {
	// ��������� � ������������� ���� � ������ ����������
	studentsFileDeadLines.close();
	studentsFileDeadLines.open(DEAD_LINES_FILE, ios::out | ios::trunc); // �������������� ����

	// ���������� ���� � �������������
	for (int i = 0; i < NUM_OF_DEADLINES; i++) {
		studentsFileDeadLines << courseDeadLinePoints[i].getDate();
		if (i < NUM_OF_DEADLINES - 1) {
			studentsFileDeadLines << ";"; // ��������� �����������
		}
	}
	studentsFileDeadLines << endl; // ��������� ������� ������

	// ���������� ���� � �������� ����� (���� �����)
	studentsFileDeadLines.close();
	studentsFileDeadLines.open(DEAD_LINES_FILE, ios::in | ios::out | ios::app);
}

void LoadDeadlinesFromFile() {
	string line;
	if (getline(studentsFileDeadLines, line) && !line.empty()) { // ��������� ������ � ������
		istringstream iss(line);
		string dateStr;
		int index = 0;

		// ��������� ������ �� ������� ';' � ������ ����
		while (getline(iss, dateStr, ';') && index < NUM_OF_DEADLINES) {
			courseDeadLinePoints[index].parse(dateStr);
			index++;
		}
	}
	else
		cout << EMPTY_DEADLINES_FILE_WARN << endl;
}

string GetDeadLines() {
	string dates;
	for (int i = 0; i < NUM_OF_DEADLINES; i++) {
		dates += to_string(i + 1) + "- " + courseDeadLinePoints[i].getDate() + '\n';
	}
	return dates;
}

void ShowDeadLinesList() {
	string message = "������� ����������� �����:\n";
	message += GetDeadLines();
	LogMessage(message);
}