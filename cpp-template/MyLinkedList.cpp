#include <iostream>
#include "SLinkedList.h"
#include <string.h>
#include <time.h> 

using namespace std;

int main(){

	int i, temp_random_number;
	string temp_random_str;

	srand(time(0)); 
	SLinkedList<int> List;
	for(i=0; i<50; i++){
		temp_random_number = (rand() % 100);
		List.addLast(temp_random_number);
	}
	List.print();

	SLinkedList<string> List2;
	for(i=1; i<=100; i++){
		temp_random_str = "Customer " + to_string(i);
		List2.addLast(temp_random_str);
	}
	List2.print();

	return 0;
}