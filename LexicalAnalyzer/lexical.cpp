#include "lexical.h"

bool lexical_analyzer::isID(const string &str) {
    if (isdigit(str[0]))
        return false;
    int counter = 0;
    if (str[0] == '_')
        counter++;
    for(counter; counter < str.size(); counter++)
        if(!(isalnum(str[counter])) && str[counter] != '_')
            return false;
    return true;
}

bool lexical_analyzer::isDigit(const string &str) {
    bool digit = true;
    for (int i = 0; i < str.length(); i++){
        if (!isdigit(str[i]) && str[i] != '.')
            digit = false;
    }
    return digit;
}

bool lexical_analyzer::isSymbol(const string &str) {
    return str[0] == '\'' && str[2] == '\'';
}

bool lexical_analyzer::isKeyword(const string &str) {
    const vector <string> keywords{"break", "do", "do", "else", "return", "for", "if", "while"};
    for(const auto& keyword : keywords)
        if (keyword == str)
            return true;

    return false;
}

bool lexical_analyzer::isReservedName(const string &str) {
    const vector <string> reserve{"bool", "char", "const", "double", "false", "true", "float", "int", "null", "void"};
    for(const auto& reserve : reserve)
        if (reserve == str)
            return true;
    return false;
}

bool lexical_analyzer::isOperator(const string &str) {
    const vector <string> operators{"<", ">", "<=", ">=", "*", "+", "-", "/", "=", "!=", "&&", "||", "==", "!"};
    for(const auto& op : operators)
        if (op == str)
            return true;
    return false;
}

bool lexical_analyzer::isSeparator(const string &str) {
    const vector <string> Separators{"{", "}", ",", "(", ")", ";"};
    for(const auto& separate : Separators)
        if (separate == str)
            return true;
    return false;
}

bool lexical_analyzer::isNotLegal(const string &str) {
    return str == " " || str == "\n" || str == "\r";
}


void lexical_analyzer::printRoleOfToken(const string& token) {
    count++;
    if (isOperator(token)){
        table[count][0] = "operator";
        table[count][1] = token;
    }
    else if(isSeparator(token)) {
        table[count][0] = "separator";
        table[count][1] = token;
    }
    else if(isKeyword(token)) {
        table[count][0] = "keyword";
        table[count][1] = token;
    }
    else if(isReservedName(token)) {
        table[count][0] = "reserved name";
        table[count][1] = token;
    }
    else if(isDigit(token)) {
        table[count][0] = "digit";
        table[count][1] = token;
    }
    else if(isSymbol(token)) {
        table[count][0] = "symbol";
        table[count][1] = token;
    }
    else if(isID(token)) {
        table[count][0] = "identifier";
        table[count][1] = token;
    }
    else {
        count--;
        cout << "Identifier  " << token << " not found\n";
    }
}

void lexical_analyzer::lexicalAnalyze(const string &nameOfFile) {
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
            if (isOperator(string(1, ch))){
                printRoleOfToken(std::string(1, ch));
                continue;
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