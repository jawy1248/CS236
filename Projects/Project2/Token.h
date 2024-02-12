#include <stdio.h>
#include <sstream>
#include <string>

#pragma once

using namespace std;

enum TokenType {
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    myEOF
};

class Token {
   private:
    TokenType type;
    string value;
    int line;

   public:
    Token(TokenType type, string value, int line) : type(type), value(value), line(line) {}

    string toString() const {
        stringstream out;
        out << "(" << typeName(type) << ","
            << "\"" << value << "\"," << line << ")";
        return out.str();
    }

    TokenType getType() const { return type; }

    string typeName(TokenType type) const {
        switch (type) {
            case 0:
                return "COMMA";
            case 1:
                return "PERIOD";
            case 2:
                return "Q_MARK";
            case 3:
                return "LEFT_PAREN";
            case 4:
                return "RIGHT_PAREN";
            case 5:
                return "COLON";
            case 6:
                return "COLON_DASH";
            case 7:
                return "MULTIPLY";
            case 8:
                return "ADD";
            case 9:
                return "SCHEMES";
            case 10:
                return "FACTS";
            case 11:
                return "RULES";
            case 12:
                return "QUERIES";
            case 13:
                return "ID";
            case 14:
                return "STRING";
            case 15:
                return "COMMENT";
            case 16:
                return "UNDEFINED";
            case 17:
                return "EOF";
            default:
                return "NULL";
        }
    }
};
