#include "main.h"

void cls() {
	cout << "\x1B[2J\x1B[H";
}

void stf(ofstream& file, int x) {
	string str = to_string(x);
	file.write(str.data(), str.size());
	file.write(";", 1);
}

#pragma region person

int person::count = 0;

person::person() {
	count++;
}

person::person(int code, string name, int age, int phone_number, int gender) {
	count++;
	cout << "person count: " << count << endl;
	this->code = code;
	this->name = name;
	this->age = age;
	this->phone_number = phone_number;
	this->gender = gender;
}

person::person(person& p) {
	this->code = code;
	this->name = name;
	this->age = age;
	this->phone_number = phone_number;
	this->gender = gender;
}

person::~person() {
	count--;
	cout << "person count: " << count << endl;
}

#pragma endregion

#pragma region teacher

teacher::teacher() {}

teacher::teacher(int code, string name, int gender, int phone_num, string pulpit, string post) {
	this->code = code;
	this->name = name;
	this->gender = gender;
	this->phone_num = phone_num;
	this->pulpit = pulpit;
	this->post = post;
}

teacher teacher::user_input() {
	teacher t;

	cout << "input code ";
	cin >> t.code;

	cout << "input name ";
	cin.get();
	getline(cin, t.name);

	cout << "input gender (1-male 2-female) ";
	cin >> t.gender;

	cout << "input phone number ";
	cin >> t.phone_num;

	cout << "input pulpit ";
	cin.get();
	getline(cin, t.pulpit);

	cout << "input post ";
	cin.get();
	getline(cin, t.post);

	return t;
}

void teacher::save() {
	ofstream file("data\\FT_" + name + ".txt", ios::binary);

	stf(file, code);
	file.write(name.data(), name.size());
	file.write(";", 1);
	stf(file, gender);
	stf(file, phone_num);
	file.write(pulpit.data(), pulpit.size());
	file.write(";", 1);
	file.write(post.data(), post.size());
	file.write(";", 1);
	file.write("#", 1);

	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	char buf[100] = { 0 };
	std::strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&now));

	file.write(buf, strlen(buf));

	file.close();
}

teacher teacher::load(string path) {
	teacher t;

	ifstream file(path, ios::binary);

	string input;
	getline(file, input, ';');
	t.code = stoi(input);

	getline(file, t.name, ';');

	getline(file, input, ';');
	t.gender = stoi(input);

	getline(file, input, ';');
	t.phone_num = stoi(input);

	getline(file, t.pulpit, ';');

	getline(file, t.post, ';');

	file.close();

	return t;
}

void teacher::print() {
	cout << "teacher num " << code << endl;
	cout << "\tname: " << name << endl;
	cout << "\tgender: " << gender << endl;
	cout << "\tphone number: " << phone_num << endl;
	cout << "\tpulpit: " << pulpit << endl;
	cout << "\tpost: " << post << endl;
}

#pragma endregion

#pragma region student

student::student() { }

student::student(int code, string name, int gender, int phone_num, int group, int grades[3]) {
	this->code = code;
	this->name = name;
	this->gender = gender;
	this->phone_num = phone_num;
	this->group = group;
	this->grades[0] = grades[0];
	this->grades[1] = grades[1];
	this->grades[2] = grades[2];
}

student student::user_input() {
	student s;

	cout << "input code ";
	cin >> s.code;

	cout << "input name ";
	cin.get();
	getline(cin, s.name);

	cout << "input gender (1-male 2-female) ";
	cin >> s.gender;

	cout << "input phone number ";
	cin >> s.phone_num;

	cout << "input group ";
	cin >> s.group;

	cout << "input physics grade ";
	cin >> s.grades[0];

	cout << "input math grade ";
	cin >> s.grades[1];

	cout << "input cs grade ";
	cin >> s.grades[2];

	return s;
}

void student::save() {
	ofstream file("data\\FS_" + name + ".txt", ios::binary);

	stf(file, code);
	file.write(name.data(), name.size());
	file.write(";", 1);
	stf(file, gender);
	stf(file, phone_num);
	stf(file, group);
	stf(file, grades[0]);
	stf(file, grades[1]);
	stf(file, grades[2]);
	file.write("#", 1);

	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	char buf[100] = { 0 };
	std::strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&now));

	file.write(buf, strlen(buf));

	file.close();
}

student student::load(string path) {
	student s;

	ifstream file(path, ios::binary);

	string input;
	getline(file, input, ';');
	s.code = stoi(input);

	getline(file, s.name, ';');

	getline(file, input, ';');
	s.gender = stoi(input);

	getline(file, input, ';');
	s.phone_num = stoi(input);

	getline(file, input, ';');
	s.group = stoi(input);

	getline(file, input, ';');
	s.grades[0] = stoi(input);

	getline(file, input, ';');
	s.grades[1] = stoi(input);

	getline(file, input, ';');
	s.grades[2] = stoi(input);

	file.close();

	return s;
}

void student::print() {
	cout << "student num " << code << endl;
	cout << "\tname: " << name << endl;
	cout << "\tgender: " << gender << endl;
	cout << "\tphone number: " << phone_num << endl;
	cout << "\group: " << group << endl;
	cout << "\grades: " << grades[0] << ", " << grades[1] << ", " << grades[2] << endl;
}

#pragma endregion

int main() {

	person people[] = { person(1, "John", 17, 123123, 1), person(2, "Ana", 17, 12341243, 2), person() };

	/*while (true) {
		cls();
		cout << "1 - interactive data entry about the teacher" << endl;
		cout << "2 - interactive data entry about the student" << endl;
		cout << "3 - reading from the teacher data file" << endl;
		cout << "4 - reading from the student data file" << endl;
		cout << "5 - show teacher files" << endl;
		cout << "6 - show students files" << endl;
		cout << "0 - Exit" << endl;

		int input;
		cin >> input;
		switch (input)
		{
		case 0: {
			exit(0);
		}break;
		case 1: {
			input_teacher();
		}break;
		case 2: {
			input_student();
		}break;
		case 3: {
			read_teacher();
		}break;
		case 4: {
			read_student();
		}break;
		case 5: {
			show_teachers();
		}break;
		case 6: {
			show_students();
		}break;
		}
	}*/
}

void input_teacher() {
	cls();

	teacher t = teacher::user_input();

	t.save();
}

void input_student() {
	cls();

	student s = student::user_input();

	s.save();
}

vector<path> get_files(string prefix) {
	vector<path> files;

	for (const auto& file : directory_iterator("data")) {
		if (is_regular_file(file) && !file.path().filename().string().find(prefix)) {
			files.push_back(file.path());
		}
	}

	return files;
}

void read_teacher() {
	cls();

	vector<path> files = get_files("FS_");

	if (!files.size()) {
		cout << "no files" << endl;
		cin.get();
		cin.get();
		return;
	}

	for (size_t i = 0; i < files.size(); i++)
	{
		cout << i << " - \"" << files[i].string() << "\"" << endl;
	}

	int i;
	cout << "choose file: ";
	cin >> i;

	cls();

	if (i < 0 || i >= files.size()) return;

	teacher t = teacher::load(files[i].string());

	t.print();

	cin.get();
	cin.get();
}

void read_student() {
	cls();

	vector<path> files = get_files("FS_");

	if (!files.size()) {
		cout << "no files" << endl;
		cin.get();
		cin.get();
		return;
	}

	for (size_t i = 0; i < files.size(); i++)
	{
		cout << i << " - \"" << files[i].string() << "\"" << endl;
	}

	int i;
	cout << "choose file: ";
	cin >> i;

	cls();

	if (i < 0 || i >= files.size()) return;

	student t = student::load(files[i].string());

	t.print();

	cin.get();
	cin.get();
}

void show_teachers() {
	cls();

	vector<path> files = get_files("FT_");

	if (!files.size()) {
		cout << "no files" << endl;
		cin.get();
		cin.get();
		return;
	}

	vector<teacher> teachers;
	for (size_t i = 0; i < files.size(); i++) {
		teachers.push_back(teacher::load(files[i].string()));
	}

	bool sorted = false;
	while (!sorted) {
		sorted = true;

		for (size_t i = 0; i < teachers.size() - 1; i++) {
			if (teachers[i].phone_num < teachers[i + 1].phone_num) {
				swap(teachers[i], teachers[i + 1]);
				sorted = false;
			}
		}
	}

	for (size_t i = 0; i < teachers.size(); i++)
	{
		teachers[i].print();
		cout << endl;
	}

	cin.get();
	cin.get();
}

void show_students() {
	cls();

	vector<path> files = get_files("FS_");

	if (!files.size()) {
		cout << "no files" << endl;
		cin.get();
		cin.get();
		return;
	}

	vector<student> students;
	for (size_t i = 0; i < files.size(); i++) {
		students.push_back(student::load(files[i].string()));
	}

	bool sorted = false;
	while (!sorted) {
		sorted = true;

		for (size_t i = 0; i < students.size() - 1; i++) {
			if (students[i].phone_num < students[i + 1].phone_num) {
				swap(students[i], students[i + 1]);
				sorted = false;
			}
		}
	}

	for (size_t i = 0; i < students.size(); i++)
	{
		students[i].print();
		cout << endl;
	}

	cin.get();
	cin.get();
}