#include "lexical.h"

using namespace std;

bool isID(const string &str){
    if (isdigit(str[0]))
        return false;
    int counter = 0;
    if (str[0] == '_')
        counter++;
    for(counter; counter < str.size(); counter++)
        if(!(isalnum(str[counter])))
            return false;
    return true;
}


bool isDigit(const string &str){
    bool digit = true;
    for (int i = 0; i < str.length(); i++){
        if (!isdigit(str[i]) && str[i] != '.')
                digit = false;
    }
    return digit;
}

bool isSymbol(const string &str){
    return str[0] == '\'' && str[2] == '\'';
}


bool isKeyword(const string &str){
    const vector <string> keywords{"break", "do", "do", "else", "return", "for", "if", "while"};
    for(const auto& keyword : keywords)
        if (keyword == str)
            return true;

    return false;
}

bool isReservedName(const string &str){
    const vector <string> reserve{"bool", "char", "const", "double", "false", "true", "float", "int", "null", "void"};
    for(const auto& reserve : reserve)
        if (reserve == str)
            return true;
    return false;
}


bool isOperator(const string &str){
    const vector <string> operators{"<", ">", "<=", ">=", "*", "+", "-", "/", "=", "!=", "&&", "||", "==", "!"};
    for(const auto& op : operators)
        if (op == str)
            return true;
    return false;
}

bool isSeparator(const string &str){
    const vector <string> Separators{"{", "}", ",", "(", ")", ";"};
    for(const auto& separate : Separators)
        if (separate == str)
            return true;

    return false;
}

bool isNotLegal(const string &str){
    return str == " " || str == "\n" || str == "\r";
}

void printRoleOfToken(const string& token){
    if(isOperator(token))
        cout << "(operator, " << token << ")\n";
    else if(isSeparator(token))
        cout << "(separator, " << token << ")\n";
    else if(isKeyword(token))
        cout << "(keyword, " << token << ")\n";
    else if(isReservedName(token))
        cout << "(reserved name, " << token << ")\n";
    else if(isDigit(token))
        cout << "(digit, " << token << ")\n";
    else if(isSymbol(token))
        cout << "(symbol, " << token << ")\n";
    else if(isID(token))
        cout << "(identifier, " << token << ")\n";
    else
        cout << "Identifier  " << token << " not found\n";
}

void lexicalAnalyze(const string &nameOfFile){
    char ch;
    string buffer;
    fstream file(nameOfFile, fstream::in);

    if (!file.is_open()){
        cout << "error while opening the file\n";
        exit(0);
    }

    bool miltiCm = false, singleCm = false;
    while (file >> noskipws >> ch){
        if (singleCm || miltiCm){
            if (singleCm && ch == '\n')
                singleCm = false;

            if (miltiCm && ch == '*'){
                file >> ch;
                if (ch == EOF)
                    break;
                if (ch == '/')
                    miltiCm = false;
            }
            continue;
        }
        if (ch == '/'){
            string comm(1, ch);
            file >> ch;
            if(ch == EOF){
                printRoleOfToken(comm);
                break;
            }
            if(ch == '*'){
                miltiCm = true;
                comm += ch;
            }
            else if(ch == '/'){
                singleCm = true;
                comm += ch;
            }
            if(miltiCm || singleCm){
                printRoleOfToken(comm);
                continue;
            }
        }

        if (isNotLegal(string(1, ch))){
            if (!buffer.empty()){
                printRoleOfToken(buffer);
                buffer = "";
            }
            continue;
        }

        if(isOperator(string(1, ch))){
            if (!buffer.empty() && !isOperator(buffer)){
                printRoleOfToken(buffer);
                buffer = "";
            }
        }

        if (isSeparator(string(1, ch))){
            if (!buffer.empty()){
                printRoleOfToken(buffer);
                buffer = "";
            }
            if (isSeparator(string(1, ch))){
                printRoleOfToken(std::string(1, ch));
                continue;
            }
        }
        buffer += ch;
    }
    file.close();
}
