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
    void newStudent(string cardInfo);
    void purchaseSwipes();
	void displayMenu(string menu);
    void createMenus();
    void buyFood(vector<string> menu,double cost);
    virtual void updateFile();
    void feedback();
    int error; //error for if a new profile
};
void Student::newStudent(string cardInfo)
{
	ofstream output;
	idNum = cardInfo;
	cout << "Please enter your first name" << endl;
	cin >> firstName;
	cout << "Please enter your last name" << endl;
	cin >> lastName;
	status = "Student";
	purchaseSwipes();
	output.open(idNum + ".txt");
	output << status << "\n" << swipes << "\n" << firstName << " " << lastName;
	output.close();
	error = 0;
}
void Student::feedback()
{
	ifstream myfile;
	string placehold;
	string placehold1;
	vector <string> hold;
	myfile.open("Feedback.txt");
	while(getline(myfile,placehold))
	{
	        myfile >> placehold;
	        hold.push_back(placehold);
	}
	myfile.close();
	ofstream output;
	output.open("Feedback.txt");
	cout << "Please enter your feedback" << endl;
	cin.ignore();
	getline(cin,placehold1);
	hold.push_back(placehold1);
	for(int i=0; i < hold.size(); i++)
	{
		//cout << i << hold[i] << endl; For testing purposes
		output << hold[i] << "\n";
	}
	output.close();
	cout << endl << "We value your opinion and thank you for submitting feedback" << endl;


}
void Student::purchaseSwipes()
{
	double MoreSwipes = 0;
	cout << "How many swipes would you like to purchase" << endl;
	cin >> MoreSwipes;
	while(MoreSwipes <=0)
	{
		cout << "Please enter a positive amount of swipes you'd like to purchase" << endl;
		cin >> MoreSwipes;
	}
	swipes = swipes + MoreSwipes;
	cout << "Your new balance is " << swipes << endl;

}
Student::Student(string cardInfo)
{
	idNum = cardInfo;
	ifstream input;
	cardInfo = cardInfo + ".txt";
	input.open(cardInfo);
	if(!input.is_open())
	{
		error = 1;
		cout << "You are a new student please create a new profile" << endl;
		swipes = 0;
		firstName = "New";
		lastName = "Student";

	}
	else
	{
		error = 0;
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
	input.close();
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
        for(int i = 0; i < Entree.size(); i++)
        {
            cout << "  " << i << " " << Entree[i] << endl;
        }
        cout << "  " <<Entree.size() << " To move to Drinks" << endl;
        buyFood(Entree,CostEntree);
    }
    else if(menu.compare("Drinks") == 0){
        cout << "\n--DRINK MENU--" << endl;
        for(int i = 0; i < Drinks.size(); i++)
        {
            cout << "  " << i << " " << Drinks[i] << endl;
        }
        cout << "  " << Drinks.size() << " To move to Dessert" << endl;
        buyFood(Drinks,CostDrinks);
    }
    else if(menu.compare("Dessert") == 0){
        cout << "\n--DESSERT MENU--" << endl;
        for(int i = 0; i < Dessert.size(); i++)
        {
            cout << "  " << i << " " << Dessert[i] << endl;
        }
        cout << "  " << Dessert.size() << " To end order" << endl;
        buyFood(Dessert,CostDessert);
    }


}
void Student::buyFood(vector<string> menu, double cost){
    int option = 1;
    cout << "You have " << swipes  << " swipes."<< endl;
    while(option !=menu.size()){

        cout << "What would you like to purchase?" << endl;
        cin >> option;
        while(option < 0 || option > menu.size()) // error check for option
        {
        	cout << "You have chosen a wrong menu item\nPlease enter a correct item" << endl;
        	cin >> option;
        }
        if(option == menu.size()){
        	//cout << "Moving onto next menu" << endl;
        }
        else{
        swipes = swipes - cost;
        studentMeal.push_back(menu[option]);
        }
    }
    //cout << "Updated Swipes: " << swipes << endl << endl;
    cout << "Your Order: " << endl;

    for(int i = 0; i < studentMeal.size(); i++)
    {
        cout << studentMeal[i] << ", ";
    }

}

void Student::updateFile(){
	ofstream output;
	output.open( idNum + ".txt");
	output << status << "\n" << swipes << "\n" << firstName << " " << lastName;
	output.close();
}

class Employee: public User{

    virtual void updateFile();
};

void studentMenu(){    //display the option menu for students
    cout << endl << "1) Buy Food\n2) Buy Swipes\n3) Submit feedback\n4) I'm a new Student" << endl;
    cout << "5) To EXIT the program" << endl;
}
void employeeMenu(){
    cout << "1) Update Menu\n2) Review Feedback\n3) Inventory" << endl;
}

int main() {
	int userLevel; // student or employee?
	int choice = 0;
    int menuChoice;
	string cardInfo;
    string parsedCardInfo;

	string input, employeePassword = "1234";


	cout << "1)Student \n2)Employee\n" << endl;
	cin >> userLevel;
	cout << "Swipe card" << endl; // prints
	cin >> cardInfo;

    parsedCardInfo = cardInfo.substr(1,9);  //parses the extra characters from the student id
    //cout << parsedCardInfo; //for testing purposes

    if(userLevel == 1){
        try{
            Student *s1 = new Student(parsedCardInfo);
            //cout << parsedCardInfo; testing purposes

            while(choice !=5)
            {
            	if(s1->error == 1)
            	{
            		choice = 4;
            	}
            	else{
            		studentMenu();
            		cin >> choice;
            	}

            	switch(choice){
            	case 1: // Buy food
            		s1->createMenus();
            		s1->displayMenu("Entree");
            		s1->displayMenu("Drinks");
            		s1->displayMenu("Dessert");
            		s1->updateFile();
            		break;
            	case 2: // Buying swipes
            		s1->purchaseSwipes();
            		s1->updateFile();
            		break;
            	case 3: // Feedback
            		s1->feedback();
            		break;
            	case 4: //New student
            		if(s1->error != 1)
            		{
            			cout << "You have already created a profile" << endl;
            			cout << "Please select a valid option" << endl;
            			break;
            		}
            		cout << "Thanks for creating a new profile" << endl;
            		s1->newStudent(parsedCardInfo);
            		break;
            	case 5:
            		cout << "Thank you for choosing Mizzou Dining Halls" << endl;
            		break;
            	}
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
    		cout << "ERROR " << e << ": You don't have access to this" << endl;
    	}
    }

    return 0;
}
