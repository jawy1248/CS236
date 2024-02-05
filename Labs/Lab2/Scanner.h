#include <stdio.h>

#include <cctype>
#include <sstream>
#include <string>

#include "Token.h"
#pragma once

using namespace std;

class Scanner {
   private:
    string input;
    string output;

   public:
    Scanner(const string input) : input(input) {}

    Token scanToken() {
        // Remove whitespace
        char temp = input.at(0);
        while (isspace(temp)) {
            input = input.substr(1);
            temp = input.at(0);
        }

        if (input.at(0) == ',') {
            TokenType type = COMMA;
            string value = ",";
            int line = 4;
            return Token(type, value, line);
        } else {
            return Token(COMMA, "BAD", 23);
        }
    }
};