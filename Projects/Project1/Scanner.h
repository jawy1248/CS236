#include <stdio.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "Token.h"
#pragma once

using namespace std;

class Scanner {
   private:
    string input;
    string output;
    int line = 1;

   public:
    Scanner(const string input) : input(input) {}

    vector<Token> scanToken() {
        // Declare parameters
        vector<Token> tokens;
        TokenType type;
        int size;
        int newLine = 0;
        string value;

        // Repeat until the input is empty
        while (!input.empty()) {
            // Increase line count if needed
            line = (newLine) ? newLine : line;
            newLine = 0;

            // Remove whitespace
            char temp = input.at(0);
            while (isspace(temp)) {
                // Move the input until we get to some sort of char
                input = input.substr(1);
                temp = input.at(0);
            }

            // Get the input tokens
            switch (temp) {
                case '\n': {
                    line += 1;
                    input = input.substr(1);
                    continue;
                }

                case ',': {
                    type = COMMA;
                    size = 1;
                    break;
                }

                case '.': {
                    type = PERIOD;
                    size = 1;
                    break;
                }

                case '?': {
                    type = Q_MARK;
                    size = 1;
                    break;
                }

                case '(': {
                    type = LEFT_PAREN;
                    size = 1;
                    break;
                }

                case ')': {
                    type = RIGHT_PAREN;
                    size = 1;
                    break;
                }

                case ':': {
                    if (input.size() > 1 && input.at(1) == '-') {
                        type = COLON_DASH;
                        size = 2;
                    } else {
                        type = COLON;
                        size = 1;
                    }
                    break;
                }

                case '*': {
                    type = MULTIPLY;
                    size = 1;
                    break;
                }

                case '+': {
                    type = ADD;
                    size = 1;
                    break;
                }

                case '\'': {
                    int pos = input.size();
                    for (int i = 1; i < pos; i++) {
                        if (input.at(i) == '\n')
                            newLine = (newLine == 0) ? line + 1 : newLine + 1;
                        else if (i != pos - 1) {
                            if (input.at(i) == '\'' && input.at(i + 1) == '\'' && i + 2 < pos)
                                i++;
                        } else
                            type = UNDEFINED;
                    }
                    if (type != STRING && type != UNDEFINED)
                        type = UNDEFINED;
                    size = input.substr(0, pos).size();
                    break;
                }

                case '#': {
                    bool err = false;
                    int pos = 0;
                    if (input.at(1) == '|') {
                        err = true;
                        for (int i = 0; i < input.size(); i++) {
                            if (input.at(i) == '\n')
                                (newLine == 0) ? newLine = line + 1 : newLine++;
                            if (input.at(i) == '|' && i != input.size() - 1 && input.at(i + 1) == '#') {
                                err = false;
                                pos = i + 2;
                                break;
                            }
                        }
                    }
                    type = (!err) ? COMMENT : UNDEFINED;
                    size = (pos != 0) ? input.substr(0, pos).size() : input.substr(0, input.find('\n')).size();
                    break;
                }

                default: {
                    string subString5 = input.substr(0, 5);
                    string subString7 = input.substr(0, 7);

                    if (subString7 == "Schemes" && !isalpha(input.at(7))) {
                        type = SCHEMES;
                        size = 7;
                    } else if (subString5 == "Facts" && !isalpha(input.at(5))) {
                        type = FACTS;
                        size = 5;
                    } else if (subString5 == "Rules" && !isalpha(input.at(5))) {
                        type = RULES;
                        size = 5;
                    } else if (subString7 == "Queries" && !isalpha(input.at(7))) {
                        type = QUERIES;
                        size = 7;
                    } else if (isalpha(input.at(0))) {
                        type = ID;
                        int pos = 0;
                        for (int i = 0; i < input.size(); i++) {
                            if (!isalpha(input.at(i) && !isdigit(input.at(i)))) {
                                pos = i;
                                break;
                            }
                        }
                        size = input.substr(0, pos).size();
                    } else if (!input.empty()) {
                        type = UNDEFINED;
                        size = 1;
                    } else {
                        type = myEOF;
                        size = 0;
                    }
                    break;
                }
            }
            value = input.substr(0, size);
            input = input.substr(size);

            tokens.emplace_back(type, value, line);
        }
        if (input.empty()) {
            line = (newLine != 0) ? newLine : line;
            tokens.emplace_back(myEOF, "", line);
        } else
            throw invalid_argument("Buffer is still not empty, Line " + to_string(__LINE__));

        return tokens;
    }
};