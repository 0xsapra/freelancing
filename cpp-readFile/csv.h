#include <fstream>
#include <sstream>

using namespace std;

class CSV{
private:
	string filename;
	fstream finStream;
	char delimeter;

public:

	vector< vector<string> > rows;

	CSV(string filename, char delimeter=' '){
		this->filename = filename;
		this->delimeter = delimeter;
		this->finStream.open(filename); // open file

		if(!this->finStream){
			cout << "[-]Invalid Filename. The csv file does not exists\n";
			return;
		}

		this->readCSV(); // read the csv file
	}

	void readCSV(){
		
		string line;
		string word;
		vector<string> row;

		// Read the header. We dont need it
		getline( this->finStream, line);

		// Read body/rows
		while (getline( this->finStream, line, '\n')){ // get each line from file
			row.clear();
			stringstream s(line);
			while(getline(s, word, this->delimeter)){ // split on delimeter
				row.push_back(word);
			}
			getline(s, word, '\n'); // reading last column of row..
			row.push_back(word);

			this->rows.push_back(row);
		}
		cout << "[+]The data is loaded successfully." << endl;
	}

	void printCSV(){

		for(auto row:this->rows){
			cout << row[0] << " " << row[1]<< " "  << row[2]<< " "<< row[3]<< " "  << endl;
		}
	}

};