//============================================================================
// Name        : Main.cpp
// Author      : Zach Taylor and Tess McCorkle
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
class User{ //abstract base class
public:
	User();
    string firstName, lastName;
    string idNum;
    virtual void updateFile() = 0;  //pure virtual function
};

User::User(){
    cout << "user created" << endl;
}

class Student : public User{
private:
	double swipes;
	string status;
	double CostEntree;
	double CostDessert;
	double CostDrinks;
public:
	Student(string cardInfo);
	vector <string> Entree;
	vector <string> Dessert;
	vector <string> Drinks;
    vector <string> studentMeal;
	void displayMenu(string menu);
    void createMenus();
    void buyFood(vector<string> menu);
    virtual void updateFile();
};

Student::Student(string cardInfo)
{
	ifstream input;
	cardInfo = cardInfo + ".txt";
	input.open(cardInfo);
	input >> status;
    if(status.compare("Manager") == 0){
        throw "Not a Student";
    }
	cout << "status: " << status << endl;
	input >> swipes;
	cout << "Swipes: " << swipes << endl;
    input >> firstName;
    input >> lastName;
    cout << "Name: " << firstName << " " << lastName << endl;

}

void Student::createMenus(){ //read in menus and save info into vectors
    string placehold;
    ifstream input, input2, input3;
    
    //create Entree menu
    input.open ("Entree.txt");
    input >> CostEntree; //Gets cost of Entree
    cout << "Each Entree is " << CostEntree << " Swipe(s)" << endl;
    while(getline(input,placehold))
    {
        input >> placehold;
        Entree.push_back(placehold);
    }
    input.close();
    
    //create Drink menu
    input2.open ("Drinks.txt");
    input2 >> CostDrinks;
    cout << "Each Drink is " << CostDrinks << " Swipe(s)" << endl;
    while(getline(input2,placehold))
    {
        input2 >> placehold;
        Drinks.push_back(placehold);
    }
    input2.close();
    
    //create Dessert
    input3.open ("Dessert.txt");
    input3 >> CostDessert;
    cout << "Each Dessert is " << CostDessert << " Swipe(s)" << endl;
    while(getline(input3,placehold))
    {
        input3 >> placehold;
        Dessert.push_back(placehold);
    }
    input3.close();
}

void Student::displayMenu(string menu){	//display the food menu for students
    if(menu.compare("Entree") == 0){
        cout << "--ENTREE MENU--" << endl;
        for(int i = 0; i < Entree.size()-1; i++)
        {
            cout << "  " << i << " " << Entree[i] << endl;
        }
        buyFood(Entree);
    }
    else if(menu.compare("Drinks") == 0){
        cout << "\n--DRINK MENU--" << endl;
        for(int i = 0; i < Drinks.size()-1; i++)
        {
            cout << "  " << i-1 << " " << Drinks[i] << endl;
        }
        buyFood(Drinks);
    }
    else if(menu.compare("Dessert") == 0){
        cout << "\n--DESSERT MENU--" << endl;
        for(int i = 0; i < Dessert.size()-1; i++)
        {
            cout << "  " << i << " " << Dessert[i] << endl;
        }
        buyFood(Dessert);
    }
    

}
void Student::buyFood(vector<string> menu){
    int option = 1;
    cout << "You have " << swipes  << " swipes."<< endl;
    while(option !=0){
        
        cout << "What would you like to purchase?" << endl;
        cin >> option;
        swipes--;
        studentMeal.push_back(menu[option]);
    }
    swipes++;   //accounts for the 0 option when exiting the while loop
    //cout << "Updated Swipes: " << swipes << endl << endl;
    cout << "Your Order: " << endl;
    
    for(int i = 0; i < studentMeal.size(); i++)
    {
        cout << studentMeal[i] << ", ";
    }
    
}

void Student::updateFile(){
    
}

class Employee: public User{
    
    virtual void updateFile();
};

void studentMenu(){    //display the option menu for students
    cout << "1) Buy Food\n2) Buy Swipes\n3) Submit feedback\n4) I'm a new Student" << endl;
}
void employeeMenu(){
    cout << "1) Update Menu\n2) Review Feedback\n3) Inventory" << endl;
}

int main() {
	int userLevel; // student or employee?
	int choice;
    int menuChoice;
	string cardInfo;
    string parsedCardInfo;
    
	string input, employeePassword = "1234";


	cout << "1) Student \n2)Employee\n" << endl;
	cin >> userLevel;
	cout << "Swipe card" << endl; // prints
	cin >> cardInfo;
    
    parsedCardInfo = cardInfo.substr(1,9);  //parses the extra characters from the student id
    //cout << parsedCardInfo; //for testing purposes
    
    if(userLevel == 1){
        try{
            Student *s1 = new Student(parsedCardInfo);
            studentMenu();
            cin >> choice;
            
            switch(choice){
                case 1:
                    s1->createMenus();
                    s1->displayMenu("Entree");
                    s1->displayMenu("Drinks");
                    s1->displayMenu("Dessert");
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
            }
        }
        catch(const char* e){
            cout << e << endl;
        }
    }
	else if(userLevel == 2){
        try{    //try making a manager object
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
        catch(int e){
            cout << "ERROR " << e << ": You don't have acces to this" << endl;
        }
	}

	return 0;
}
