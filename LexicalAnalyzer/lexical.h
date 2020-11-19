#ifndef LEXICALANALYZER_LEXICAL_H
#define LEXICALANALYZER_LEXICAL_H

using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


class lexical_analyzer {

    bool isID(const string &str);
    bool isDigit(const string &str);
    bool isSymbol(const string &str);
    bool isKeyword(const string &str);
    bool isReservedName(const string &str);
    bool isOperator(const string &str);
    bool isSeparator(const string &str);
    bool isNotLegal(const string &str);

public:
    void lexicalAnalyze(const string &nameOfFile);
    void printRoleOfToken(const string &token);
    static const int len = 3;
    static const int height = 1000;
    string table[height][len];
    int count = -1;
    int pos = 1;
};

#endif //LEXICALANALYZER_LEXICAL_H
