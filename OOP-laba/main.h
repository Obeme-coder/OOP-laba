#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <chrono>

using namespace std;
using namespace std::filesystem;

void cls();
void input_teacher();
void input_student();
vector<path> get_files(string prefix);
void read_teacher();
void read_student();
void show_teachers();
void show_students();

class person {
private:
	int phone_number;
public:
	static int count;
	int code;
	string name;
	int age;
	int gender;
	person();
	person(int code, string name, int age, int phone_number, int gender);
	person(person& p);
	~person();
};

class teacher {
public:
	int code;
	string name;
	int gender;
	int phone_num;
	string pulpit;
	string post;
	teacher();
	teacher(int code, string name, int gender, int phone_num, string pulpit, string post);
	static teacher user_input();
	void save();
	static teacher load(string path);
	void print();
};

class student {
public:
	int code;
	string name;
	int gender;
	int phone_num;
	int group;
	int grades[3];
	student();
	student(int code, string name, int gender, int phone_num, int group, int grades[3]);
	static student user_input();
	void save();
	static student load(string path);
	void print();
};