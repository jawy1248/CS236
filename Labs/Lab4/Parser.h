#include <iostream>
#include <utility>
#include <vector>
#include "Token.h"
#include "Predicate.h"
#include "DatalogProgram.h"
#include "Rule.h"

#pragma once

using namespace std;

class Parser {
private:
    vector<Token> tokens;
    DatalogProgram datalog;

public:
    Parser(vector<Token> tokens) : tokens(tokens) { }

    TokenType tokenType() const {return tokens.at(0).getType();}

    string tokenValue() const {return tokens.at(0).getValue();}

    void advanceToken() {tokens.erase(tokens.begin());}

    void throwError() {
        cout << "Failure!" << endl;
        cout << "  " << tokens.at(0).toString() << endl;
        exit(1);
    }

    string match(TokenType t) {
        while (tokenType() == COMMENT)
            advanceToken();
        if (tokenType() == t) {
            string returnVal = tokenValue();
            advanceToken();
            return returnVal;
        } else throwError();
        return "";
    }

    Predicate headPredicate() {
        Predicate head(match(ID));
        match(LEFT_PAREN);
        head.addValue(match(ID));
        idList(head);
        match(RIGHT_PAREN);
        return head;
    }

    void parameter(Predicate& p) {
        if (tokenType() == STRING)
            p.addValue(match(STRING));
        else if (tokenType() == ID)
            p.addValue(match(ID));
    }

    void predicate(Predicate& p) {
        if (tokenType() == ID) {
            p = Predicate(match(ID));
            match(LEFT_PAREN);
            parameter(p);
            parameterList(p);
            match(RIGHT_PAREN);
        }
    }

    void idList(Predicate& p) {
        if (tokenType() == COMMA) {
            match(COMMA);
            p.addValue(match(ID)); // B, C, D
            idList(p);
        }
    }

    void stringList(Predicate& p) {
        if (tokenType() == COMMA) {
            match(COMMA);
            p.addValue(match(STRING));
            datalog.addToDomain(p.getParameters().back().getParameters());
            stringList(p);
        }
    }

    void parameterList(Predicate& p) {
        if (tokenType() == COMMA) {
            match(COMMA);
            parameter(p);
            parameterList(p);
        }
    }

    void predicateList(Predicate& p, Rule& rule) {
        if (tokenType() == COMMA) {
            match(COMMA);
            predicate(p);
            rule.addPredicate(p);
            predicateList(p, rule);
        }
    }

    void scheme() {
        if (tokenType() == ID) {
            Predicate p(match(ID));
            match(LEFT_PAREN);
            p.addValue(match(ID));
            idList(p);
            match(RIGHT_PAREN);
            datalog.addToSchemes(p);
        } else throwError();
    }

    void fact() {
        if (tokenType() == ID) {
            Predicate p(match(ID));
            match(LEFT_PAREN);
            p.addValue(match(STRING));
            datalog.addToDomain(p.getParameters().back().getParameters());
            stringList(p);
            match(RIGHT_PAREN);
            match(PERIOD);
            datalog.addToFacts(p);
        } else throwError();
    }

    void rule() {
        Rule rule(headPredicate());
        match(COLON_DASH);
        Predicate p("");
        predicate(p);
        rule.addPredicate(p);
        predicateList(p, rule);
        match(PERIOD);
        datalog.addToRules(rule);
    }

    void query() {
        Predicate p("");
        predicate(p);
        match(Q_MARK);
        datalog.addToQueries(p);
    }

    void schemeList() {
        if (tokenType() == ID) {
            scheme();
            schemeList();
        }
    }

    void factList() {
        if (tokenType() == ID) {
            fact();
            factList();
        }
    }

    void ruleList() {
        if (tokenType() == ID) {
            rule();
            ruleList();
        }
    }

    void queryList() {
        if (tokenType() == ID) {
            query();
            queryList();
        }
    }

    DatalogProgram datalogProgram() {
        match(SCHEMES);
        match(COLON);
        scheme();
        schemeList();
        match(FACTS);
        match(COLON);
        factList();
        match(RULES);
        match(COLON);
        ruleList();
        match(QUERIES);
        match(COLON);
        query();
        queryList();
        match(myEOF);
        return datalog;
    }
};