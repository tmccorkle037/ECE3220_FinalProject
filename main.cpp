//============================================================================
// Name        : main.cpp
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
#include <cstdlib>

using namespace std;
class User{ //abstract base class
public:
	User();
	string firstName, lastName;
	string idNum;
	string status;
	string swipes;
	virtual void updateFile() = 0;  //pure virtual function
	virtual void feedback() = 0;
};

User::User(){

	//ut << "user created" << endl;
}

class Student : public User{
private:
	double swipes;
	string status;
public:
	Student(string cardInfo);
	vector <string> studentMeal;
	void newStudent(string cardInfo);
	void purchaseSwipes();
	void buyFood(vector<string> menu,double cost);
	void updateFile();
	virtual void feedback();
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
	while(MoreSwipes <=0
			)
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
		error = 0;system("clear");
		input >> status;
		if(status.compare("Student") != 0){
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

void Student::buyFood(vector<string> menu, double cost){
	int option = 1;
	cout << "You have " << swipes  << " swipes."<< endl;
	while(option !=menu.size()){

		cout << "Enter the number of the item you would like to purchase:" << endl;
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
	cout << "Your Current Order: " << endl;

	for(int i = 0; i < studentMeal.size(); i++)
	{
		cout << studentMeal[i] << endl;
	}

}

void Student::updateFile(){
	ofstream output;
	output.open( idNum + ".txt");
	output << status << "\n" << swipes << "\n" << firstName << " " << lastName;
	output.close();
}

class Employee: public User{
private:
	double wage = 8.50;
	double totalIncome;
	double hours;
public:
	string password;
	Employee(string cardInfo);
	void updateMenu();
	virtual void updateFile();
	virtual void feedback();
	void updateHours(double time);
	void calculateIncome();
};

Employee::Employee(string cardInfo){
    idNum = cardInfo;
    ifstream input;
    cardInfo = cardInfo + ".txt";
    input.open(cardInfo);
    
    input >> status;
    if(status.compare("Manager") != 0){
        throw 1;
    }
    cout << "status: " << status << endl;
    input >> swipes;
    cout << "Swipes: " << swipes << endl;
    input >> firstName;
    input >> lastName;
    cout << "Name: " << firstName << " " << lastName << endl;
    input >> password;
    input >> hours;
    cout << "Hours worked: " << hours << endl;
    
    input.close();
}

void Employee::updateFile(){
    ofstream outFile;
    outFile.open(idNum + ".txt");
    
    outFile << status << "\n";
    outFile << swipes << "\n";
    outFile << firstName << "\n";
    outFile << lastName << "\n";
    outFile << password << "\n";
    outFile << hours << "\n";
    cout << "File Updated" << endl;
    
    outFile.close();
}

void Employee::feedback(){
    string message;
    ifstream inFile;
    int i = 0;
    inFile.open("Feedback.txt");
    cout << endl;
    while(getline(inFile,message))
    {
        i++;
        cout << i << ":\t";
        cout << message << endl;
    }
    
    inFile.close();
    cout <<  endl;
}

void Employee::updateHours(double time){
    hours = hours + time;
    cout << "Your hours have been documented" << endl;
    updateFile();
    
}

void Employee::calculateIncome(){
    totalIncome = wage*hours;
    cout << "Total earned: $" << totalIncome << endl;
}


class Menu{
public:
    string menuName;
    double cost;
    vector<string> menu;
    Menu(string menuType);
    void displayMenu();
    void editMenu();
    void updateMenu();
};

Menu::Menu(string menuType){ //read in menus and save info into vectors
    menuName = menuType;
    string item;
    ifstream input;
    
    input.open (menuType + ".txt");
    input >> cost;
    //cout << "Each item is " << cost << " Swipe(s)" << endl;
    while(getline(input,item))
    {
        input >> item;
        menu.push_back(item);
    }
    input.close();
    //    cout << menuType << " menu created." << endl;
}

void Menu::displayMenu(){    //display the food menu for students
    cout << "---" << menuName << " Menu---" << endl;
    for( int i = 0; i < menu.size(); i++){
        cout << "  " << i << " " << menu[i] << endl;
    }
    cout <<"  " << menu.size() << " to go to next menu" << endl << endl;
}

void Menu::editMenu(){
    int option;
    string item;
    int dItem;
    
    cout << "1) Add item 2) Delete item" << endl;
    cin >> option;
    
    switch(option){
        case 1:
            cout << "Enter item to be added to the " << menuName << " Menu: " << endl;
            cin >> item;
            menu.push_back(item);
            updateMenu();
            displayMenu();
            
            break;
        case 2:
            cout << "Enter item to be deleted from the " << menuName << " Menu: ";
            cin >> dItem;
            menu.erase(menu.begin() + dItem);
            cout << "item was added" << endl;
            displayMenu();
            updateMenu();
            
    }
}

void Menu::updateMenu(){
    ofstream output;
    output.open( menuName + ".txt");
    output << cost;
    output << "\n";
    
    for( int i = 0; i < menu.size(); i++)
    {
        if(i == menu.size()-1)
        {
            output<< menu[i];
        }
        else
        {
            output << menu[i] << "\n";
        }
    }
    output.close();
}

void studentMenu(){    //display the option menu for students
    cout << endl << "1) Buy Food\n2) Buy Swipes\n3) Submit feedback" << endl;
    cout << "4) To EXIT the program" << endl;
}
void employeeMenu(){
    cout << "***EMPLOYEE MENU***\n\n1) Update Menu\n2) Review Feedback\n3) Enter hours worked\n4) To EXIT the program" << endl;
}

void mainMenu(){
    cout << "---WELCOME TO THE MIZZOU DINING KIOSK---\n" << endl;
    cout << "Are you a student or Employee?" << endl;
    
    cout << "1)Student \n2)Employee\n"<< endl;
    cout << "3)Learn how to use the kiosk" << endl;
}
void help(){
    system("clear");
    cout << "--HELP MENU--" << endl;
    cout << "If you're a student:\nLet us know your a student, then swipe your card so we can access your account information. Next you will be able to buy food, buy swipes, or leave feedback about your dining experience. Follow the on screen commands to make your menu options." << endl;
    cout << "\nIf you're an employee:\nLet us know you're an employee then swipe your card so we can access your account information. Next enter your employee password to access the employee menu. Once you get to the menu, follow the on screen commands to update the menu, view student feedback, or update your hours." << endl;
}

int main() {
    int userLevel; // student or employee
    int choice = 0;
    int i = 1;
    double hours;
    string cardInfo;
    string parsedCardInfo;
    string input;
    
    system("clear");
    
    //creates food menus for the students to select from
    Menu entreeMenu("Entree");
    Menu drinkMenu("Drinks");
    Menu dessertMenu("Dessert");
    
    mainMenu();
    cin >> userLevel;
    
    while(cin.fail()){	//error checks for a character
        cin.clear();
        cin.ignore();
        cout << "Enter a numerical value from 1-3: ";
        cin >> userLevel;
    }
    
    while(userLevel >3 || userLevel < 0){
        cout << "ERROR: must be a number between 1-3. Try again: ";
        cin >> userLevel;
    }
      //parses the extra characters from the student id
    //system("clear");    //clear the screens so card info is not seen
    if(userLevel == 1){ //student user
        cout << "Swipe card" << endl; // prints
        cin >> cardInfo;
        parsedCardInfo = cardInfo.substr(1,9);
        
        try{
            Student *s1 = new Student(parsedCardInfo);
            studentMenu();
            while(choice !=4)
            {
                if(s1->error == 1)
                {
                    choice = 5;
                }
                else{
                    cin >> choice;
                }
                
                switch(choice){
                    case 1: // Buy food
                        entreeMenu.displayMenu();
                        s1->buyFood(entreeMenu.menu, entreeMenu.cost);
                        drinkMenu.displayMenu();
                        s1->buyFood(drinkMenu.menu, drinkMenu.cost);
                        dessertMenu.displayMenu();
                        s1->buyFood(dessertMenu.menu, dessertMenu.cost);
                        s1->updateFile();
                        break;
                    case 2: // Buying swipes
                        s1->purchaseSwipes();
                        s1->updateFile();
                        break;
                    case 3: // Feedback
                        s1->feedback();
                        break;
                    case 4:
                        cout << "Thank you for choosing Mizzou Dining Halls" << endl;
                        break;
                    case 5: //New student
                        if(s1->error != 1)
                        {
                            cout << "You have already created a profile" << endl;
                            cout << "Please select a valid option" << endl;
                            break;
                        }
                        cout << "Thanks for creating a new profile" << endl;
                        s1->newStudent(parsedCardInfo);
                        break;
                }
            }
            delete s1;
        }
        catch(const char* e){
            cout << e << endl;
        }
    }
    else if(userLevel == 2){    //Employee user
        cout << "Swipe card" << endl; // prints
        cin >> cardInfo;
        parsedCardInfo = cardInfo.substr(1,9);
        system("clear");
        
        try{    //try making a manager object
            Employee *manager = new Employee(parsedCardInfo);
            
            cout << "Enter Password: ";
            cin >> input;
            system("clear");
            //error check for wrong password
            while( input.compare(manager->password)!= 0){
                cout << "Wrong password. Try again" << endl;
                cin >> input;
            }
            system("clear");
            while(choice != 4){
                
                employeeMenu();
                cin >> choice;
                
                while(choice > 4 || choice < 1){
                    cout << "Enter a number between 1 and 4" << endl;
                    cin >> choice;
                }
                
                switch(choice){
                    case 1: //Update Menu
                        entreeMenu.displayMenu();
                        drinkMenu.displayMenu();
                        dessertMenu.displayMenu();
                        cout << "Which menu would you like to update? (Entree, Dessert, or Drink)" << endl;
                        cin >> input;
                        
                        //system("clear")
                        while(i == 1){
                            if(input.compare("Entree") == 0){
                                entreeMenu.editMenu();
                                i=0;
                            }
                            else if(input.compare("Dessert") == 0){
                                dessertMenu.editMenu();
                                i=0;
                            }
                            else if(input.compare("Drink") == 0){
                                drinkMenu.editMenu();
                                i=0;
                            }
                            else{
                                cout << "Invalid Menu option. Try again." << endl;
                                cin >> input;
                            }
                        }
                        break;
                    case 2: //Review feedback
                        manager->feedback();
                        break;
                    case 3: //Hours worked
                        cout << "Enter number of hours: " << endl;
                        cin >> hours;
                        while(hours <= 0)
                        {
                            cout << "Please enter a valid number of hours" << endl;
                            cout << "Input should be above 0 hours" << endl;
                            cin >> hours;
                        }
                        manager->updateHours(hours);
                        system("clear");
                        manager->calculateIncome();
                        break;
                    case 4:
                        cout << "Thank you for choosing Mizzou Dining Halls" << endl;
                        break;
                }
            }
            delete manager;
        }
        catch(int e){
            cout << "ERROR " << e << ": Must be an employee of Mizzou Dining Halls to access this information" << endl;
        }
    }
    else if(userLevel == 3){
        help();
    }
return 0;
}
