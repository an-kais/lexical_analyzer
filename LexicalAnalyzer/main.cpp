#include <iostream>
#include <iomanip>
#include "lexical.h"

int main(){
    lexical_analyzer la;
    la.lexicalAnalyze("../example.txt");
    for (int i = 0; i <= la.count; i++){
            cout << setw(12) << la.table[i][1];
        cout << endl;
    }
    return 0;
}
