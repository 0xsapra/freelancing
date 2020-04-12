#include <iostream>
#include "SLinkedList.h"
#include <string.h>

using namespace std;

int main(){

	SLinkedList<int> List;
	List.addFront(23);
	List.addFront(24);
	List.addFront(25);
	List.addFront(26);
	List.addLast(21);
	List.addLast(20);
	List.addLast(19);
	List.addLast(18);
	List.print();
	cout << endl;

	List.removeFront();
	List.removeLast();
	List.print();


	SLinkedList<string> List2;
	List2.addFront("asdf");
	List2.removeFront();
	List2.removeFront();
	List2.removeLast();
	List2.addLast("qwer");
	List2.removeLast();
	List2.addLast("asdf");

	List2.print();

	cout << endl << endl << endl;

	cout << List.front();
	cout << List2.last();
}

// Data -> 26
// Data -> 25
// Data -> 24
// Data -> 23
// Data -> 21
// Data -> 20
// Data -> 19
// Data -> 18

// Data -> 25
// Data -> 24
// Data -> 23
// Data -> 21
// Data -> 20
// Data -> 19
// Cannot delete from empty ListCannot delete from empty List 2Data -> asdf



// 25asdf

