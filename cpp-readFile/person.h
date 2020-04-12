using namespace std;

class Person{
	string fname;
	string lname;
	string nationality;

public:

	Person(string fname, string lname, string nationality){
		this->fname = fname;
		this->lname = lname;
		this->nationality = nationality;
	}

	void setFirstName(string fname){
		this->fname = fname;
	}
	void setNationality(string nationality){
		this->nationality = nationality;
	}

	string getName(){
		return this->fname+" "+this->lname ;
	}
	string getNationality(){
		return this->nationality;
	}
};