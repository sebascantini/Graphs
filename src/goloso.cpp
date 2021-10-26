#include "goloso.h"

pair<vector<int>, int> goloso(vector<vector<int> > &incidencias){

    vector<int> visitados;
    vector<int> camino = vector<int>(1, 1);
    int n = incidencias.size();
    int costo_minimo = 0;
    int j = 0;
    int minimo;

    visitados.assign(n, 0);
    visitados[0] = 1;

    // Tomo el minimo de todos los nodos no visitados.
    int nodo = 1;
    while(1){
        nodo = j;
        // calculamos el minimo de la fila i-esima.
        for(int k = 0; k < n; ++k)
            if(visitados[k] == 0 && incidencias[nodo][k] < incidencias[nodo][j]){
                j = k;
            }
        // ya tenemos el minimo y el su nodo j
        visitados[j] = 1; // marcamos j como visitado
        if ( j == nodo)
            break;
        costo_minimo += incidencias[nodo][j]; // lo sumamos al costo minimo
        camino.push_back(j+1); // agregamos j al camino
    }
    costo_minimo += incidencias[0][j];
    return make_pair(camino, costo_minimo);
}




