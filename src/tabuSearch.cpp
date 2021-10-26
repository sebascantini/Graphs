#include "tabuSearch.h"

vector<pair<vector<int>, int>> obtenerSubVecindad(vector<vector<int> > &incidencias, pair<vector<int>, int> ciclo, int vecinos){
    vector<pair<vector<int>, int>> res;
    //hacemos vecinos swaps
    int costo_viejo = ciclo.second;
    int n = ciclo.first.size();
    int c = 0;
    for(int i = 0; i < n; ++i){
        for(int j = i + 2; j < n; ++j){
            if((j+1)%n != i){
                ciclo.second = costo_viejo - incidencias[ciclo.first[i]-1][ciclo.first[(i+1)%n]-1] - incidencias[ciclo.first[j]-1][ciclo.first[(j+1)%n]-1] + incidencias[ciclo.first[i]-1][ciclo.first[(j+1)%n]-1] + incidencias[ciclo.first[j]-1][ciclo.first[(i+1)%n]-1];
                swap(ciclo.first, i, j);
                res.push_back(ciclo);
                swap(ciclo.first, i, j);
                c++;
                if(c == vecinos)
                    break;  
            }     
        }
        if(c == vecinos)
            break;
    }

    //tomamos un 10% random
    for(int i = 0; i < vecinos/10; ++i){
        random_shuffle (ciclo.first.begin(), ciclo.first.end());
        //editas costo
        ciclo.second = 0;
        for(int j = 0; j < n ; ++j){
            int sig = (j + 1) % n;
            ciclo.second += incidencias[ciclo.first[j]][ciclo.first[sig]]; 
        }
        res.push_back(ciclo);
    }
    
    //elegir los mejores
    int cant_mejores = min((int) res.size(), 10);
    for(int i = 0; i < cant_mejores; ++i){
        int mejor_indice = 0;
        for(int j = i; j < res.size(); ++j){
            if(res[j].second < res[mejor_indice].second)
                mejor_indice = j;
        }
        pair<vector<int>, int> temp = res[i];
        res[i] = res[mejor_indice];
        res[mejor_indice] = temp;
    }
    return res;
}


pair<vector<int>, int> obtenerMejor(vector<pair<vector<int>, int>>& vecinos, vector<vector<int>>& memoria){
    // vector<int> ans = 
    int costo = INT_MAX;
    pair<vector<int>, int> ans;
    for(int i = 0 ; i<vecinos.size() ; ++i){
        //primero vemos si es mejor
        if(costo > vecinos[i].second){
            bool cond = true; 
            //luego si no esta en memoria
            for(int j = 0; j < memoria.size() ; ++j){
                cond &= vecinos[i].first != memoria[j]; 
            }
            if(cond){
                ans.first = vecinos[i].first;
                costo = vecinos[i].second;
            }
        }

    }
    ans.second = costo;
    return ans;

}

pair<vector<int>, int> tabuSearch(vector<vector<int> > &incidencias, int n, int k, int v){
    pair<vector<int>, int> ciclo = hagm(incidencias);
    vector<vector<int>> memoria;
    int it = 0;
    int mem_i = 0;

    while(it < n){
        //precalculamos vecinos
        vector<pair<vector<int>, int>> vecinos = obtenerSubVecindad(incidencias, ciclo, v);
        pair<vector<int>, int> nuevo = obtenerMejor(vecinos, memoria);
        
        if(memoria.size() < k)
            memoria.push_back(nuevo.first);
        else
            memoria[mem_i%k] = nuevo.first;
        mem_i++;
        if(nuevo.second < ciclo.second){
            it = 0;
            ciclo.first = nuevo.first;
            ciclo.second = nuevo.second;
        }
        else
            it++;
    }

    return ciclo;
}
       