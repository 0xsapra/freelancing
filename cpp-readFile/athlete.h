#include "person.h"

using namespace std;

class Athlete: public Person {
	float distance;
public:
	Athlete(string fname, string lname, string nationality, string distance)
	:Person(fname, lname, nationality){
		this->distance = atof(distance.c_str()); // convert cpp string to float
	}

	bool hasJumpedOverThreshold(float threshold){
		return threshold < this->distance;
	}

	friend ostream &operator<<( ostream &output, Athlete &athlete ) { 
        output << athlete.getName() << " " << athlete.getNationality() << " " << athlete.distance << endl;
        return output;            
	}

};