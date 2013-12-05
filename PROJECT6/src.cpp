/* ========================================================================== */
/*      PROGRAM : Soft Drink Vending Machine 
Simulation

AUTHOR: <Helen Parker>
FSU MAIL NAME: <hdp12>
RECITATION SECTION NUMBER: <009>
RECITATION INSTRUCTOR NAME: <Danny>
COP 3014 - Fall 2013    
PROJECT NUMBER: 6
DUE DATE: Wednesday 12/04/2013
PLATFORM: Windows OS / C++ 11 / Microsoft Visual C++ Express 2012 IDE

SUMMARY

This program simulates a soft drink vending machine. The program will work with drink names, 
their prices, and the current number available in the machine.
Each time the program runs, it will enter a loop that performs the following steps: 
a list of drinks and their prices is displayed on the screen. 
The user is then allowed to either quit the program or pick a drink. 
If the user selects a drink, the program will notify the user that $1.00 must be entered for payment. 
The program will then display the amount of change that would be returned and subtract one from the number of drinks left in the machine for that drink. 
If the user selects a drink that is sold out, a message to that effect will be displayed. 
The loop then repeats. 

When the user chooses to quit the program, the program will display the total amount of profit the machine earned during the current run. The profit on each can is calculated as $0.25 per can, for all drinks. After the user has quit and the program has printed out the total profit, it will then sort the array of structs containing the drinks into descending numeric order according to the number of cans of each drink which are available. Then, print out a summary table of the machine's final state, which includes the drink names, prices, and cans available in the machine at that point.



INPUT

machine.txt
The user can either pick a drink or quit the program
choice of drink (1 through 6), or the command to quit (0)

OUTPUT

a list of drinks and their prices is displayed on the screen. 
If the user selects a drink, the program will notify the user that $1.00 must be entered for payment. 
The program will then display the amount of change that would be returned and subtract one from the number of drinks left in the machine for that drink. 
If the user selects a drink that is sold out, a message to that effect will be displayed.
It will print out a summary table of the machine's final state, which includes the drink names, prices, and cans available in the machine at that point.


*/

/* ========================================================================== */

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct sodaStruct
{
	string drinkName;
	double price;
	int numAvailableCans;
};

typedef sodaStruct listSodas[6];

int header();

int sodas(ifstream&, listSodas);

int sodaChoice(listSodas);
int payTheMachine(int, listSodas);
int sodaCanPrint(int, listSodas);
int leaver(double, listSodas);


int main(){
	//header file
	header();
	
	listSodas drinks;
	double profit;
	char leaveConfirm;
	
	

	//input file
	ifstream inFile;


	// import the txt file of answers
	inFile.open("machine.txt");


	//implement a check to see if the file specified does open, and if it does not, terminate the run //using either return in main or exit in another function

	// gets the line from the txt
	sodas(inFile, drinks);
	
	cout << setprecision(2) << fixed;


do{
	//allow user to choose their desired drink and returns that number
	int userSoda = sodaChoice(drinks);
	// cout <<	userSoda << endl;
					
	// exit if user selected to exit (input was 0)
	if (userSoda < 0){ 
		break;
	}
	
	cout << endl;
	//"so you chose " << drinks[userSoda].drinkName << endl;

	// Ask for payment
	cout << payTheMachine(userSoda, drinks) << endl;
	//subtract one from the number of drinks left in the machine for that drink.
	drinks[userSoda].numAvailableCans -= 1;
	profit += 0.25;
	sodaCanPrint(userSoda, drinks);
	
	cout << "WOULD YOU LIKE TO EXIT? (Y)ES OR (N)O..." << endl;
	cin >> leaveConfirm;
} while (leaveConfirm == 'n' || leaveConfirm == 'N');

	// exit 
	leaver(profit, drinks);
	
}

int header(){
	cout << "  WELCOME TO THE SOFT DRINK VENDING MACHINE SIMULATOR" 
		<< endl << " **~~>>-----------------====****====-----------------<<~~**"
		<< endl << endl << endl;
	return 0;
}

int sodas(ifstream& inFile, listSodas drinks){
	for (int i=0; i<6; i++){
		getline(inFile, drinks[i].drinkName);
		inFile >> drinks[i].price;
		inFile >> drinks[i].numAvailableCans;
		inFile.ignore();
	}
	return 0;
}


int sodaChoice(listSodas drinks){
	int choice;
	int k=1;

		//print out soda choices	

			cout << "#   PRICE      STOCK        DRINK NAME" << endl
			 	 << "~===~~~~~======~~~~~=====~~~~~~~~~~~~~~~~ " << endl;
			 	 
		for (int i=0; i<6; i++){							  		   
			cout << k << "   " << drinks[i].price << "        "
				 << drinks[i].numAvailableCans << "         "
				 << drinks[i].drinkName << endl;
			k++;
		}
		cout <<  endl;
	//prompt user for their choice of drink (1 through 6), or the command to quit (0)
	cout << "If you would like to purchase a soda," << endl << "please" 
		<< " enter the soda number (1 through 6)"
		<< endl << "or enter (0) to quit" << endl;
	cin >> choice;

	while (choice >=7 || choice < 0){
		//if user doesn’t input integer check for the 
		//fail state and recover as needed.
		//perform bad data checking on the value of this user input item, 
		//and re-prompt the user until a valid menu choice is entered. 
		cout << "Please enter a valid number, '" << choice 
		<< "' is not a valid number" << endl;
		cin >> choice;
	}
	
	int realChoice = choice-1;
	//WHILE LOOP THAT If the user selects a drink that is sold out, 
	//a message to that effect will be displayed and allows them
	// to try again.
	
	while (drinks[realChoice].numAvailableCans == 0){
		cout << "I'm embarrassed to admit that " 
		<< drinks[realChoice].drinkName
		<< "' is completely SOLD OUT!" << endl
		<< "Please enter a different soda number (1 through 6), " 
		<< "or (0) to quit" << endl;
		cin >> choice; 
		realChoice = choice-1;
	}
	
	return realChoice;
}

int payTheMachine(int a,listSodas drinks){
	double oneDollar = 1.00;
	double change;
	
	//notify the user that $1.00 must be entered 
	cout << "PLEASE ENTER $1.00 FOR YOUR DRINK" << endl;
	
	//display the amount of change that would be returned 
	change = oneDollar - drinks[a].price;
	cout << "YOUR CHANGE IS PRECISELY $" << change;
	
	return change;
}

int sodaCanPrint(int a, listSodas drinks){
	
	//print out actual soda can ascii art because why not.. i got distracted
	cout << "HERE IS YOUR DRINK!!!" << endl
	<<"   .-'``--``'-." << endl
	<<" /`.  * C(#O)/`\\ " << endl
	<<" |   ````````  |"<< endl
	<<" |             |"<< endl
	<< " |" <<drinks[a].drinkName<< endl
	<<" |             |"<< endl
	<<" |             |"<< endl
	<<"  \\           / "<< endl
	<<"   `._______.'"<< endl << endl
	<< "ENJOY!!" <<endl << endl;
	
	return 1;
}

int leaver(double profit, listSodas drinks){

	// print out profit
	cout << "THE TOTAL PROFIT WAS $" << profit << "." << endl;
	
	// sort the array of structs containing the drinks into descending 
	//numeric order according to the number of cans of each 
	//drink which are available
		cout << "PRICE      REMAINING STOCK        DRINK NAME" << endl
		 	<< "~~~~~======~~~~~~~~~~~~~~~=====~~~~~~~~~~~~~~~~ "
		<< endl;
	for (int i = 0; i<21; i++){
		for (int k=0; k<7; k++){
			if (drinks[k].numAvailableCans == 20-i){
		cout << "$" << drinks[k].price 					 
					 <<"            " << drinks[k].numAvailableCans
					 <<"              "<< drinks[k].drinkName << endl;

		}
	}
}
		cout << endl << endl 
		<< " **~~>>-----------------====****====-----------------<<~~**" 
		<< endl << " THANK YOU FOR USING THE SOFT DRINK VENDING MACHINE SIMULATOR"
		<< endl << " GOODBYE" << endl;
	return 0;
}





