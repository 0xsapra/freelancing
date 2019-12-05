#include<iostream>
#include <string> // string library
#include <vector>
#include <list> 
#include <bits/stdc++.h> 

using namespace std;

# define MAX_CUSTOMER 1000
#define MAX_CALL 1000


int random(int, int);


class Call {
	long phone_number; // callee phone number
	int duration; // call duration in seconds
public:
	Call (long phone_number, int duration ){
		this->phone_number = phone_number;
		this->duration = duration;
	}
	int getduration(){
		return this->duration;
	}

};

class Customer {
public:

	string name;
	float balance; // initial balance is 0
	list<Call*> call_list;

	// setter to set customer name
	void setName( string name ) {
		this-> name = name;
	}

	// getter to retrieve customers name ("firstname lastname")
	string getName() {
		return this-> name;
	}
		
	// to add the phone call to the list of calls, where the arguments are:
	// phone number called and duration of the call (in seconds)
	void addCall (long phone_number, int duration) {
		Call *call = new Call(phone_number, duration);
		this->call_list.push_back(call);
	}
	
	// setter to set customer balance
	void setBalance( float balance) {
		this-> balance = balance;
	}
	
	// getter to retrieve user customer balance
	float getBalance() {
		return this-> balance;
	}

	// Get customer average call duration (rounder up).
	int getAverageCallDuration() {
		int duration = 0;
		for(auto call: this->call_list){
			duration += call->getduration();
		}
		int avg_duration_in_sec = duration / this->call_list.size();
		int avg_duration_in_min = avg_duration_in_sec / 60 + (avg_duration_in_sec % 60 != 0); 
		return avg_duration_in_min;
	}

	// To compute the balance based on the list of calls.
	virtual void computeBalance() = 0;
};

class RegularCustomer : public Customer {
	int monthlyfee = 5;
	int percallrate = 1; 
public:
	// Overriding compute balance virtual function to compute balance for Regular customer according to its formula
	void computeBalance(){
		int num_calls = this->call_list.size();
		float balance = this->monthlyfee + this->percallrate * num_calls ;
		this->setBalance(balance);
	}
};

class PremiumCustomer : public Customer {
	int monthlyfee = 40;
	float persecrate = 0.02 / 60;
public:
	// Overriding compute balance virtual function to compute balance for Premium customer according to its formula
	void computeBalance(){
		int num_secs = 0;
		for(auto each: this->call_list){
			num_secs += each->getduration();
		}
		float balance = this->monthlyfee + this->persecrate * num_secs;
		this->setBalance(balance);
	}
};

bool sort_Regularcustomer(RegularCustomer*, RegularCustomer*);
bool sort_Premiumcustomer(PremiumCustomer*, PremiumCustomer*);


class Simulation {
	vector<RegularCustomer*> regularcustomerVector;
	vector<PremiumCustomer*> premiumcustomerVector;
	int customer_count;
	int call_count;
public:	

	// constructor to generate new customer for each Customer type and assign them random value
	Simulation(){
		srand(time(0)); // For randomness
		this-> customer_count 	= MAX_CUSTOMER;
		this-> call_count 		= random(20, 500);

		for(int i=0; i < MAX_CUSTOMER; i++){
			RegularCustomer *rc = dynamic_cast<RegularCustomer*>(this-> generateCustomer("regular"));
			PremiumCustomer *pc = dynamic_cast<PremiumCustomer*>(this-> generateCustomer("premium"));
			
			this-> regularcustomerVector.push_back( rc );
			this-> premiumcustomerVector.push_back( pc );

		}
		sort(this->regularcustomerVector.begin(), this-> regularcustomerVector.end(), sort_Regularcustomer);
		sort(this->premiumcustomerVector.begin(), this-> premiumcustomerVector.end(), sort_Premiumcustomer);
	}

	// Generate 4-8 character customer name (firstname lastname) [ the first letter in the first and last name must be in upper case ]
	string generateName() {
		string alphabet("abcdefghijklmnopqrstuvwxyz");
    	string firstname = "";
    	string lastname  = "";
    	int fn_name_length = random(4, 8);
    	int ln_name_length = random(4, 8);

    	for (int i=0; i<fn_name_length; i++){
    		char chr = alphabet.at( random(0,25) );
    		if (i==0) chr -= 32; // convert to UPPER Case
    		firstname += chr;
    	}
    	for (int i=0; i<ln_name_length; i++){
    		char chr = alphabet.at( random(0,25) );
    		if (i==0) chr -= 32; // convert to UPPER Case
    		lastname += chr;
    	}
    	return firstname + " " + lastname;
	}
	
	// generate 10 digit random phone number
	long generatePhoneNumber() {
		return random(10000, 99999)*10000 + random(10000, 99999);
	}

	// randomly generate call duration from 20sec to 10800 sec(3hours)
	int generateCallDuration() {
		return random(20, 9800) + random(15, 1000);
	}

	// Generate a new customer and assign name, balance and Calls to him according to customer type(Premium/Regular)
	Customer* generateCustomer(string customer_type) {
		// generate a random customer

		string name = this-> generateName();
		Customer *customer;
		if( customer_type == "regular"){
			 customer = new RegularCustomer();	
		} else {
			 customer = new PremiumCustomer();
		}
		customer -> setName(name);
		customer -> setBalance(0);

		for (int i = 0; i < this->call_count; i++) {
			long phone_number = this->generatePhoneNumber();
			int duration = this->generateCallDuration();
			customer->addCall(phone_number, duration);
		}
		customer->computeBalance();
		return customer;
	}

	// Calculate Average Duration of total users in simulation according to customer type(Premium/Regular)
	float getAverageDuration(string customer_type) {
		int duration_sum = 0;
		int total_elements = MAX_CUSTOMER;
		if(customer_type == "regular"){
			for(auto each: this->regularcustomerVector){
				duration_sum += each->getAverageCallDuration();
			}
		}else{
			for(auto each: this->premiumcustomerVector){
				duration_sum += each->getAverageCallDuration();
			}
		}
		return duration_sum / total_elements;
	}

	// Calculate Average Balance of total users in simulation according to customer type(Premium/Regular)
	float getAveragebalance(string customer_type){
		float balance_sum = 0.0;
		int total_elements = MAX_CUSTOMER;
		if( customer_type == "regular" ){
			for(auto each: this->regularcustomerVector){
				// cout << each->getBalance() << ",";
				balance_sum += each->getBalance();
			}
		}else{
			for(auto each: this->premiumcustomerVector){
				// cout << each->getBalance() << ",";
				balance_sum += each->getBalance();
			}
		}
		return balance_sum / total_elements;
	}

	// Print the result of Simulation 
	void printResult() {
		string largestRegular = this->regularcustomerVector.back()->name;
		string largestPremium = this->premiumcustomerVector.back()->name;
		string smallestRegular = this->regularcustomerVector.front()->name;
		string smallestPremium = this->premiumcustomerVector.front()->name;

		float largestPremium_balace = this->premiumcustomerVector.back()->getBalance();
		float largestRegular_balance = this->regularcustomerVector.back()->getBalance();
		float smallestPremium_balace = this->premiumcustomerVector.front()->getBalance();
		float smallestRegular_balance = this->regularcustomerVector.front()->getBalance();

		double result_regular = this->getAveragebalance("regular") * MAX_CUSTOMER;

		cout << "Simulation run:" << endl;
		cout << "--------------------" << endl;
		cout << "  Number of customers in each group:\t" << MAX_CUSTOMER << endl;
		cout << "  Number of calls/per customer:\t\t" << this->call_count << endl;
		cout << endl;
		cout << "Regular Customers:" << endl;
		cout << "  Average duration of the call:\t\t" << this->getAverageDuration("regular") << " min" << endl;
		cout << "  Average balance/per customer:\t\t$" << this->getAveragebalance("regular") << endl;
		cout << "  Customer with largest balace:\t\t" << largestRegular << " ($" << largestRegular_balance << ")" << endl;
		cout << "  Customer with smallest balace:\t" << smallestRegular << " ($" << smallestRegular_balance << ")" << endl;
		cout << endl;
		cout << "Premiums Customers:" << endl;
		cout << "  Average duration of the call:\t\t" << this->getAverageDuration("premium") << " min" << endl;
		cout << "  Average balance/per customer:\t\t$" << this->getAveragebalance("premium") << endl;
		cout << "  Customer with largest balace:\t\t" << largestPremium << " ($" << largestPremium_balace << ")" << endl;
		cout << "  Customer with smallest balace:\t" << smallestPremium << " ($" << smallestPremium_balace << ")" << endl;
		cout << endl;
		cout << " With " << MAX_CUSTOMER << " regular customer the company will make $ " << abs(result_regular) << " more."<<endl;
	}
};


int main(int argc, char** argv){

	Simulation *sim = new Simulation();
	sim->printResult();
	delete sim;
	return 0;
}


int random(int begin, int end){
	return ( rand() % (end - begin + 1) ) + begin;
}

bool sort_Regularcustomer(RegularCustomer* r1, RegularCustomer* r2){
	return (r1->getBalance() < r2->getBalance());
}

bool sort_Premiumcustomer(PremiumCustomer* r1, PremiumCustomer* r2){
	return (r1->getBalance() < r2->getBalance());
}

