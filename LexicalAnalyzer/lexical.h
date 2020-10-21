#ifndef LEXICALANALYZER_LEXICAL_H
#define LEXICALANALYZER_LEXICAL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


using std::cout;
using std::vector;

bool isID(const std::string &str);//
bool isDigit(const std::string &str);//
bool isSymbol(const std::string &str);//
bool isKeyword(const std::string &str);//
bool isReservedName(const std::string &str);//
bool isOperator(const std::string &str);//
bool isSeparator(const std::string &str);
void printRoleOfToken(const vector<std::string>& tokens);
void lexicalAnalyze(const std::string &nameOfFile);


#endif //LEXICALANALYZER_LEXICAL_H
