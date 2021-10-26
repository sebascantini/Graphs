#include "busquedaLocal.h"

pair<vector<int>, int> busquedaLocal(vector<vector<int> > &incidencias){
    pair<vector<int>, int> ciclo = hagm(incidencias);
    int costo_viejo = ciclo.second;
    int costo_nuevo = 0;

    while(costo_viejo > costo_nuevo){
        costo_viejo = ciclo.second;
        for(int i = 0; i < ciclo.first.size(); ++i){
            for(int j = i+2; j < ciclo.first.size(); ++j){
                pair<int, int> aristaA = make_pair(ciclo.first[i], (ciclo.first[(i+1)%ciclo.first.size()]));
                pair<int, int> aristaB = make_pair(ciclo.first[j], (ciclo.first[(j+1)%ciclo.first.size()]));
                //calculamos el hipotetico nuevo costo
                if(aristaA.first != aristaB.second)
                    costo_nuevo = costo_viejo - incidencias[aristaA.first-1][aristaA.second-1] - incidencias[aristaB.first-1][aristaB.second-1] + incidencias[aristaA.first-1][aristaB.second-1] + incidencias[aristaB.first-1][aristaA.second-1];
                    if(costo_nuevo < costo_viejo){
                    //actualizar
                    ciclo.second = costo_nuevo;
                    swap(ciclo.first, i, j);
                }
            }
        }
    }

    return ciclo;
}