#include <fstream>
#include <iostream>

#include "Scanner.h"
#include "Token.h"
using namespace std;

int main(int argc, char* argv[]) {
    // Make sure input file was provided
    if (argv[1] == NULL) {
        cout << "Please include an input file on command line" << endl;
        return 0;
    }

    // Open file
    string filename = argv[1];
    ifstream myFile;
    myFile.open(filename);
    stringstream buff;

    // Read through the file
    if (myFile.is_open())
        buff << myFile.rdbuf();

    // Close file
    myFile.close();

    Scanner scan = Scanner(buff.str());
    vector<Token> tokens = scan.scanToken();

    for (Token token : tokens) {
        cout << token.toString() << endl;
    }
    cout << "Total Tokens = " << tokens.size() << endl;

    return 0;
}