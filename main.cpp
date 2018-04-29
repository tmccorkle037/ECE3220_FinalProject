//============================================================================
// Name        : Main.cpp
// Author      : Zach Taylor
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>

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
private:
	int swipes;
	string name;
	string status;
	int CostEntree;
	int CostDessert;
	int CostDrinks;
public:
	Student(string cardInfo);
	vector <string> Entree;
	vector <string> Dessert;
	vector <string> Drinks;
	void displayMenu();
};

Student::Student(string cardInfo)
{
	ifstream input;
	cardInfo = cardInfo + ".txt";
	input.open(cardInfo);
	input >> status;
	cout << "status: " << status << endl;
	input >> swipes;
	cout << "Swipes: " << swipes << endl;
	while(getline(input,name))
	{
		//gets the Whole line
	}
	cout << "Name: " << name << endl;


}
User::User(){
	cout << "user created" << endl;
}

void studentMenu(){	//display the option menu for students
	cout << "1) Buy Food\n2) Buy Swipes\n3) Submit feedback\n4) I'm a new Student" << endl;
}
void employeeMenu(){
	cout << "1) Update Menu\n2) Review Feedback\n3) Inventory" << endl;
}
void Student::displayMenu(){	//display the food menu for students
//open the menu file, save the data into vectors in the menu class

	string placehold;
	cout << endl << "MENU" << endl;
	ifstream input;
	input.open ("Entree.txt");
	input >> CostEntree; //Gets cost of Entree
	cout << "Each Entree is " << CostEntree << " Swipe(s)" << endl;
	while(getline(input,placehold))
	{
		input >> placehold;
		// cout << placehold << endl; This was for testing purposes only
		Entree.push_back(placehold);
	}

	for(int i = 0; i < Entree.size(); i++)
	{
		cout << "\t" << i+1 << " " << Entree[i] << endl;
	}
	input.close();

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
		Student S1(cardInfo);


		switch(choice){
		case 1:
			S1.displayMenu();
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
