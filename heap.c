#include "heap.h"

void modificar_dato(long long tree[], long long nro_agregar, int posc_agregar){
    tree[posc_agregar] = nro_agregar;

    if (posc_agregar <= 1)
        return;
    
    if (posc_agregar % 2 == 1){
        posc_agregar = (posc_agregar - 1) / 2;
    } else{
        posc_agregar = posc_agregar / 2;
    }
    
    tree[posc_agregar] = tree[posc_agregar * 2] * tree[posc_agregar * 2 + 1];
    
    modificar_dato(tree, tree[posc_agregar], posc_agregar);
    return; 
}
