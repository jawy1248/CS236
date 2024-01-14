#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;
int main(int argc, char* argv[]){
	
	// set filename
	string filename = argv[1];
	
	// read in file
	ifstream in;
	in.open(filename);
	stringstream ss;
	ss << in.rdbuf();
	string input = ss.str();
	in.close();
		
	// set counters
	int charCount = 0;
	int lineCount = 0;
	int spaceCount = 0;
	int digitCount = 0;
	int letterCount = 0;

	// count everything (exc new lines)
	for(unsigned long i=0; i<input.length(); i++){
		charCount++;
		if(input[i] == '\n'){
			lineCount++;
			spaceCount++;
		}
		else if(isspace(input[i]))
			spaceCount++;
		else if(isdigit(input[i]))
			digitCount++;
		else if(isalpha(input[i]))
			letterCount++;
	}

	// print results
	cout << "chars: " << charCount << endl;
	cout << "lines: " << lineCount << endl;
	cout << "spaces: " << spaceCount << endl;
	cout << "digits: " << digitCount << endl;
	cout << "letters: " << letterCount << endl;
}
