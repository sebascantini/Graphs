#include "adicional.h"

void imprimir(int c, vector<int> &camino){
    cout << (camino.size()-1)+1 << " " << c << endl;

    for(int elm: camino){
        cout << elm << ' ';
    }
    cout << endl;
    return;
}

void swap(vector<int> &ciclo, int i, int j){
    for(int k = 0; k < ((j-i)/2) ; ++k){
        int temp = ciclo[i+1+k];
        ciclo[i+1+k] = ciclo[j-k];
        ciclo[j-k] = temp;
    }
}