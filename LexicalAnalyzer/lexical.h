#ifndef LEXICALANALYZER_LEXICAL_H
#define LEXICALANALYZER_LEXICAL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool isID(const string &str);
bool isDigit(const string &str);
bool isSymbol(const string &str);
bool isKeyword(const string &str);
bool isReservedName(const string &str);
bool isOperator(const string &str);
bool isSeparator(const string &str);
void printRoleOfToken(const vector<string>& tokens);
void lexicalAnalyze(const string &nameOfFile);


#endif //LEXICALANALYZER_LEXICAL_H
