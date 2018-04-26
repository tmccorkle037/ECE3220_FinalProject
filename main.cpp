#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;
class User{
private:
	string name;
	string idNum;
public:
	User();
	User(string name, string id){ this->name = name; this->idNum = id; };
	void setName();
	void setIdNum();
	string getName();
	string getIdNum();
};

class Student{

};


User::User(){
	cout << "user created" << endl;
}

void studentMenu(){	//display the option menu for students
	cout << "1) Buy Food\n2) Buy Swipes\n3) Submit feedback\n4) I'm a new Student" << endl;
}
void employeeMenu(){
	cout << "1) Update Menu\n2) Review Feedback\n3) Inventory" << endl;
}
void displayMenu(){	//display the food menu for students
//open the menu file, save the data into vectors in the menu class
	cout << "MENU" << endl;
}

int main() {
	int userLevel; // student or employee?
	int choice;
	string cardInfo;
	string input, employeePassword = "1234";


	cout << "1) Student \n2)Employee\n" << endl;
	cin >> userLevel;

	cout << "Swipe card" << endl; // prints
	cin >> cardInfo;

	if(userLevel == 1){
		studentMenu();
		cin >> choice;

		switch(choice){
		case 1:
			displayMenu();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		}
	}
	else if(userLevel == 2){
		cout << "Enter Password: ";
		cin >> input;

		while( input.compare(employeePassword)!= 0){
			cout << "Wrong password. Try again" << endl;
			cin >> input;
		}
		employeeMenu();
		cin >> choice;

		switch(choice){
		case 1:
			break;
		case 2:
			break;
		}

	}

	return 0;
}