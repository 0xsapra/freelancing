#include<iostream>
#include<string>
#include<vector>

#include "csv.h"
#include "athlete.h"

using namespace std;

#define FILENAME "file.txt"

int main(){


	CSV *csv = new CSV(FILENAME);
	vector<Athlete*> athletes; // saving pointers of athletes
	float distanceThreshold;

	for(auto row: csv->rows){
		Athlete *athlete = new Athlete(row[0], row[1], row[2], row[3]);
		athletes.push_back(athlete);
	}
	cout << "Please enter the distance threshold: ";
	cin >> distanceThreshold;

	cout << "The athletes exceeded " << distanceThreshold << "m are :\n";

	for(auto athlete: athletes ){
		if(athlete->hasJumpedOverThreshold(distanceThreshold)){
			cout << *athlete;
		}
	}


	return 0;
}