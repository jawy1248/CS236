
#include <fstream>

#include "Token.h"
#include "Parser.h"
#include "Scanner.h"
#include "Interpreter.h"

using namespace std;

int main(int argc, char* argv[]) {
    ifstream infile(argv[1]);
    stringstream buffer;
    buffer << infile.rdbuf();
    infile.close();

    Interpreter interpreter(Parser(Scanner(buffer.str()).scanToken()).datalogProgram());
    interpreter.run();

    return 0;
}