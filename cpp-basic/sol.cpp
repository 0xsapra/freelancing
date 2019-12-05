#include <iostream> 
#include <string> 
#include <time.h>  
using namespace std;

void menu();

void countingGame();

void number_conversion();

int main() { 
	srand(time(0));
	menu();
 } 

void menu() { 
	cout << "Please select an option\n";
	cout << "1. Keep Counting Game\n";
	cout << "2. Number Conversion Tool \n";
	cout << "3. Universal Product Code (UPC) Calculator\n";
	cout << "4. Universal Product Code (UPC) Checker\n";
	cout << "9. Quit";

	int userinput;
	bool menuDone = false;
	do { 
		cout << "Please enter an option: \n";
		cin >> userinput;

  		switch (userinput) { 
	  		case 1: 
	  			countingGame();
	  			break;
	   		case 2: 
	   			number_conversion();
	  			break;
	   		case 3: 
	   			cout << "Universal Product Code (UPC) Calculator\n";
	  			break;
	   		case 4: 
	   			cout << "Universal Product Code(UPC) Checker\n";
	  			break;
	  		default:
	  			cout << "Invalid Input";
	  			exit(0);
	  			break;	
  		}
  	}while (menuDone == false);

 	menuDone = false;
}

void number_conversion(){
	// mini app for app conversion 
	cout << "Number Conversion Tool\n";
	cout << "Please enter positive decimal number : ";

	int decimal, decimal1, decimal2;
	string hexdec_num="", bindex_num = "";
	int remainder;

	char bin[]= {'0' , '1'};
	char hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}; // These are all the possible hexvalue according
	
	cin >> decimal; // take user input
	decimal1 = decimal;
	decimal2 = decimal;

	while(decimal1>0) {
		
        remainder = decimal1 % 16;
        hexdec_num = hex[remainder] + hexdec_num;
        decimal1 = decimal1/16;
    }

    while(decimal2>0) {
		remainder = decimal2 % 2;
        bindex_num = bin[remainder] + bindex_num;
        decimal2 = decimal2/2;
    }

	cout << "Binary : " << bindex_num << "\n"; // display binary representation
	cout << "Hex : " << hexdec_num << "\n"; // display hex representation
	
	cout << "Press any key to continue...\n";
	cin.ignore();
	cin.get();
	return;
}

void countingGame() { 
	cout << "Keep Counting Game\n";
 	cout << "-------------------\n";
	cout << "You will be presented with 8 addition questions.\n";
 	cout << "After the first question, the left - hand operand is\n";
 	cout << "the result of the previous addition.\n";
 	cout << "Press enter to start...\n";
 	int solution;
	int respone;
	int wait;
	int begin = rand() % 10; // get a new random integer
	int begin2 = rand() % 10;
	time_t begin_time, end_time ;
	time(&begin_time);

	for(int i=1; i <= 7; i++){
		solution = begin+ begin2; // find the expected output with begin and begin2 
		cout << "Question "<< (i) <<": " << begin << " + " << begin2 << " = "; // Ask user what should output be
		cin >> respone ;
		if (respone != solution){ // is user response is not same as expected ouput, display error and return
			cout << "OOPS!! Wrong answer. Correct answer is " << solution << "\n";
			return;
		}
		begin = solution ; // if above if doesnt success, it means user enterd correct solution. In that case, replace 1st argument with prev solution
		begin2 = rand() % 10; // get a new random integer for next term
	}
	time(&end_time);
	cout << "Questions Completed in " << double(end_time - begin_time) << " seconds.\n"; // find time difference
 	cout << "Press any key to continue...\n";
	cin.ignore();
	cin.get();
 }





