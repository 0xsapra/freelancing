#include <iostream>
#include <string> // string library
#include <ctime> // for timing operation

using namespace std;


void print_banner_app(){
	// this function just prints the main app banner
	cout << "FoP4CS Mini Application\n";
	cout << "-----------------------\n";
	cout << "Please select an option:\n";
	cout << "1) Keep counting game\n";
	cout << "2) Number Conversion tool\n";
	cout << "3) Universal Product Code(UPC) Calculator\n";
	cout << "4) Universal Product Code(UPC) Checker\n";
	cout << "9) Quit\n";
	cout << "Please Enter option: ";
}
void print_banner_countapp(){
	// this function just prints count mini app banner
	cout << "Keep counting\n";
	cout << "-----------------------\n";
	cout << "You will be presented with 8 addition questions.\n";
	cout << "After the first question, the left-hand operand is\n";
	cout << "the result of previous addition.\n";
	cout << "Press enter to start...\n\n";
}
void print_banner_upccalc(){
	// this function just prints upc calculator app banner
	cout << "Universal Product Code (UPC) Calculator\n";
	cout << "-----------------------\n";
	cout << "This Calculator will take a 6-digit product code\n";
	cout << "and generate a trailing 7th check digit to produce\n";
	cout << "the final 7 digit UPC\n";
}
void print_banner_upcchecker(){
	// this function just prints upc checker app banner
	cout << "Universal Product Code (UPC) Checker\n";
	cout << "-----------------------\n";
	cout << "This Checker will take a 7-digit product code\n";
	cout << "and Validate if its correct UPC code or not\n";
}


void print_banner_numberconvert(){
	// this function just prints number conversion app banner
	cout << "Number Conversion Tool\n";
}

int input_int(){
	// helper function to take Integer input from user
	int value;
	cin >> value;
	return value;
}

string input_string(){
	// helper function to take String input from user
	string value;
	cin >> value;
	return value;
}

int get_random_int() {
	// get 1 digit random number 
	// the actual rand function gives 7-8 digit number , we can modulo 10 to limit it to single digit
	return rand() % 10;
}

void wait_for_input(){
	// hold program and wait for user key press to continue
	cout << "Press any key to continue...\n";
	cin.ignore();
	cin.get();

}

int countapp_solution(int a, int b){
	// evaluating response for count app .
	// in future we can add a subtract operator and make this function also return a-b and so on
	return a + b;
}

string decToHex(int decimal){
	// helper function to convert decimal to hexadecimal
	string hexdec_num="";
	int remainder;
	char hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}; // These are all the possible hexvalue according
	// to hexadecimal convention. i.e from 0-f

	while(decimal>0) {
		 // if decimal is 10, 10%16 is 10 and hex[10] is 'a' which is actual hex refresentation
		// this is base extraction method and can be applied on dec to binary or dec to anyBase

        remainder = decimal % 16;
        hexdec_num = hex[remainder] + hexdec_num;
        decimal = decimal/16;
    }
    return hexdec_num;
}

string decToBin(int decimal) {
	// helper function to convert decimal to binary

	string bindex_num = "";
	int remainder;
	char bin[]= {'0' , '1'}; // all possible binary values. i.e 0 or 1
	while(decimal>0) {
		// 		bindex_num 				  => ""
		// so if decimal value is 8, 
		// 8 % 2  remainder = 0, bin[0] is 0, => 0    => bindex_num = "0"       			& decimal = 8 / 2 = 4
		// 4 % 2  remainder = 0, bin[0] is 0, => 0    => bindex_num = "0" + "0" = "00"   	& decimal = 4/2 = 2
		// 2 % 2  remainder = 0, bin[0] is 0, => 0    => bindex_num = "0" + "00" = "000"   	& decimal = 2/2 = 1
		// 1 % 2  remainder = 1, bin[1] is 1, => 1    => bindex_num = "1" + "000" = "1000" 	& decimal = 1/2 = 0
		// decimal is now 0, loop breaks with bindex_num = "1000" which is binary of 8
        remainder = decimal % 2;
        bindex_num = bin[remainder] + bindex_num;
        decimal = decimal/2;
    }
    return bindex_num;
}

string pad_zero(string orignal, int count){
	// This function adjust zeros. count is the number of digits required in orignal string
	// if required digits are less than count, it will pad zeros to left
	int str_length = orignal.length();
	string new_string = {""};
	
	for(int i = str_length; i < count; i++){ // make a string with required number of zeros
		new_string += "0";
	}
	return new_string + orignal; // append zeros to orignal string and return
}

void counting_app(){
	// Counting mini App
	print_banner_countapp();

	int solution;
	int respone;
	int wait;
	int begin = get_random_int(); // get a new random integer
	int begin2 = get_random_int(); // get a new random integer
	time_t begin_time, end_time ;
	time(&begin_time); // function is used to time the function

	for(int i=1; i <= 7; i++){
		solution = countapp_solution(begin, begin2); // find the expected output with begin and begin2 
		cout << "Question "<< (i) <<": " << begin << " + " << begin2 << " = "; // Ask user what should output be
		respone =  input_int(); // get user response
		if (respone != solution){ // is user response is not same as expected ouput, display error and return
			cout << "OOPS!! Wrong answer. Correct answer is " << solution << "\n";
			return;
		}
		begin = solution ; // if above if doesnt success, it means user enterd correct solution. In that case, replace 1st argument with prev solution
		begin2 = get_random_int(); // get a new random integer for next term
	}
	time(&end_time);
	cout << "Questions Completed in " << double(end_time - begin_time) << " seconds.\n"; // find time difference
	wait_for_input(); // wait for user to press any key
	return;
}

void number_conversion(){
	// mini app for app conversion 
	print_banner_numberconvert(); // print banner
	int response;

	cout << "Please enter positive decimal number : ";
	response = input_int(); // take user input

	cout << "Binary : " << decToBin(response) << "\n"; // display binary representation
	cout << "Hex : " << decToHex(response) << "\n"; // display hex representation
	wait_for_input(); // wait for user to press any key
	return;
}

int toInt(char p){
	// convert a char like '0', '1', '2' etc into Int values 0, 1, 2
	int asciiInt = (int)p ; // for '0', (int)'0' is 48 which is ascii representation of 0
	return asciiInt - 48; // subtracted ascii from 48 to get orignal Integer value. so ascii('4') = 52, return 52-48 = 4, that is actual int
}

int get_upc_7th_index(string six_digit_input){


	// helper function to find 7th UPC index
	// six_digit_input is string refresentation of user input
	// example, six_digit_input = "123456"

	int addOdd = 0;
	int addEven = 0;
	int intAtIndex;

	for(int i=0; i < 6; i++){ 
		// The code is 6 digit so i < 6 to loop to every element in padded input
		
		intAtIndex = toInt(six_digit_input[i]);  // six_digit_input[i] is 1, 2, 3, 4, 5, 6 in loop
		if ( i % 2 == 0 ){ 
			// Odd index here
			addOdd += intAtIndex; 
		} else {
			// EVEN index here
			addEven += intAtIndex;
		}
	}
	int result = ((3 * addOdd) + addEven) % 10; // calculation to find 7th index (3 * (1+3+5) + 2+4+6) % 10
	result = result == 0 ? result : 10 - result ; // find the 7th index
	return result;
}

void upc_calculator(){

	//  UPC calculator mini app
	print_banner_upccalc();	 // print banner

	string response;
	int result;

	cout << "Please Enter 6 digit code \n";
	response = pad_zero(input_string(), 6); // pad user input with 6 zeros
	result = get_upc_7th_index(response); // get the value of 7th index
	cout << "The 7 digit final UPC is : " << response << result << "\n"; // disaply value
	wait_for_input(); // wait for user input
	return;

}

void upc_checker(){

	// UPC checker app to check intigrity of UPC number
	print_banner_upcchecker(); // print banner
	string response;
	int result;

	cout << "Please Enter 7 digit UPC code \n";
	response = pad_zero(input_string(), 7); // pad user input with 7 zeros. 7 because UPC number are 7 digit long
	result = get_upc_7th_index(response); // get what 7th index value should be for the input
	int sevent_index_value = toInt(response[6]); // get value at 7th index from user input
	if (sevent_index_value == result) { // if the values are same, Its valid UPC
		cout << "It's a valid UPC code : " << response << "\n";
	} else { // else not
		cout << "Invalid UPC code : " << response << "\n";
	}
	wait_for_input();// wait for user input
	return;

}


int main(int argc, char** argv){
	
	int choice;
	srand(time(0)); // initializing random library with random seed. time(0) gives current timestamp
	// and because this cannot be duplicate, we use this as seed 

	do { // do while loop to loop foreever and asks for user input foreever in loop
		// break out of loop is when user input choice is 9(line 246).

		print_banner_app(); // print App welcome message
		choice = input_int(); // get user choice (1, 2,3 , 4 or 9)

		// switch to specific IF statement based on user input
		// the last else drops in if none of user input matches to available choices
		if (choice == 1){
			counting_app();
		} else if(choice == 2) {
			number_conversion();
		} else if(choice == 3) {
			upc_calculator();
		}else if(choice == 4) {
			upc_checker();
		}else if(choice == 9) {
			break;
		}else { 
			cout << "Invalid input\n";
		}

	}while(true);

	return 0;
}