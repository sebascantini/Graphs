#include "agm.h"

vector<int> grado;

vector<vector<int>*> conjuntos;

vector<pair<int, int>> aristas;

vector<int> ordenarAristas(vector<pair<int, int>>& aristas){
    vector<int> ans;

    vector<vector<int>> caminos = vector<vector<int>>(aristas.size());
    for(int i = 0; i < aristas.size(); ++i){
        caminos[aristas[i].first].push_back(aristas[i].second);
        caminos[aristas[i].second].push_back(aristas[i].first);
    }

    ans.push_back(0);
    ans.push_back(caminos[0][0]);
    for(int i = 2; i < aristas.size(); ++i)
        (caminos[ans[ans.size()-1]][0] == ans[ans.size()-2]) ? ans.push_back(caminos[ans[ans.size()-1]][1]) : ans.push_back(caminos[ans[ans.size()-1]][0]);

    for(int i = 0; i < caminos.size(); ++i)
        ans[i]++;

    return ans;
}

pair<vector<int>, int> hagm(vector<vector<int>> &incidencias){
    int costo_minimo = 0;
    grado = vector<int> (incidencias.size(), 0);
    
    for(int i = 0; i < incidencias.size(); ++i){
        vector<int>* temp = new vector<int>();
        conjuntos.push_back(temp);
        (*conjuntos[i]).push_back(i);
    }

    for(int e = 0; e < incidencias.size()-1; ++e){
        pair<int, int> arista = make_pair(0, 0);
        for(int i = 0; i < incidencias.size(); ++i){
            for(int j = 0; j < incidencias.size(); ++j){
                if(incidencias[i][j] < incidencias[arista.first][arista.second]){
                    if(grado[i] + grado[j] < 2){
                        arista.first = i;
                        arista.second = j;
                    }
                    else if (grado[i] == 1 && grado[j] == 1 && conjuntos[i] != conjuntos[j]){
                        arista.first = i;
                        arista.second = j;
                    }
                }
            }
        }

        //aumentamos grados de vertices en agm
        grado[arista.first]++;
        grado[arista.second]++;

        aristas.push_back(arista);
        costo_minimo += incidencias[arista.first][arista.second];

        //guardar + update
        vector<int>* temp =  conjuntos[arista.second];
        
        for(int i = 0; i < (*temp).size(); ++i){
            (*conjuntos[arista.first]).push_back((*temp)[i]);
            conjuntos[(*temp)[i]] = conjuntos[arista.first];
        }

        delete(temp);
        temp = NULL;
    }
    int j, i = -1;
    for(int k = 0; k < grado.size(); k++)
        if(grado[k] == 1)
            (i == -1) ? i = k : j = k;

    costo_minimo += incidencias[i][j];
    aristas.push_back(make_pair(i,j));

    vector<int> camino = ordenarAristas(aristas);
    return make_pair(camino, costo_minimo);
}