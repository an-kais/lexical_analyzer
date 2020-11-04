#include <iostream>
#include <iomanip>
#include "lexical.h"

int main(){
    lexical_analyzer la;
    la.lexicalAnalyze("../example.txt");
    for (int i = 0; i <= la.count; i++){
        for (int j = 0; j < la.len; j++){
            cout << setw(12) << la.table[i][j];
        }
        cout << endl;
    }
    return 0;
}
