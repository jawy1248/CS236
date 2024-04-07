#include <fstream>

#include "Token.h"
#include "Parser.h"
#include "Scanner.h"
#include "Interpreter.h"

using namespace std;

int main(int argc, char* argv[]) {
    stringstream buffer;
    string input = argv[1];
    buffer << ifstream(input).rdbuf();

    Interpreter(Parser(Scanner(buffer.str()).scanToken()).datalogProgram()).run();
    return 0;
}