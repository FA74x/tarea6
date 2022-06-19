/* 5088530 */

#include "../include/mapping.h"
#include "../include/cadena.h"
#include <math.h>

struct _rep_mapping {
    TCadena *arr;
    nat cant;
    nat tam;
};

nat hash(nat clave, nat tam) {
    int res = fabs(cos(clave+7) * clave + 13);
    return res % tam;
}

TMapping crearMap(nat M) {
    TMapping map = new _rep_mapping;
    TCadena *arreglo = new TCadena[M];
    map->arr = arreglo;
    map->tam = M;
    map->cant = 0;
    for (nat i = 0; i < M; i++) {
        map->arr[i] = crearCadena();
    }
    return map;
}

void liberarMap(TMapping map) {
    for (nat i = 0; i < map->tam; i++) {
        liberarCadena(map->arr[i]);
    }
    delete[] map->arr;
    delete map;
}

TMapping asociarEnMap(nat clave, double valor, TMapping map) {
    int pos = hash(clave,map->tam);
    map->cant = map->cant + 1;
    map->arr[pos] = insertarAlInicio(clave,valor,map->arr[pos]);
    return map;
}

TMapping desasociarEnMap(nat clave, TMapping map) {
    int pos = hash(clave,map->tam);
    map->arr[pos] = removerDeCadena(clave,map->arr[pos]);
    map->cant = map->cant - 1;
    return map;
}

bool esClaveEnMap(nat clave, TMapping map) {
    int pos = hash(clave,map->tam);
    return estaEnCadena(clave,map->arr[pos]);
}

double valorEnMap(nat clave, TMapping map) {
    int pos = hash(clave,map->tam);
    TCadena aux = map->arr[pos];
    while (clave != natInfo(primeroEnCadena(aux))) {
        aux = cadenaSiguiente(aux);
    }
    return realInfo(primeroEnCadena(aux));
}

bool estaLlenoMap(TMapping map) {
    return map->cant == map->tam;
}