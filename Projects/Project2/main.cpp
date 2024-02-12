#include <fstream>
#include <iostream>
#include <vector>

#include "Token.h"
#include "Parser.h"
#include "Scanner.h"

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

    // Scan and store tokens
    Scanner scan = Scanner(buff.str());
    vector<Token> tokens = scan.scanToken();

    // Parse tokens
    Parser p = Parser(tokens);
    p.datalogProgram();

    return 0;
}