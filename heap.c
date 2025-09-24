#include "heap.h"

void modificar_dato(int arr[], int nro_agregar, int posc_agregar){
    arr[posc_agregar] = nro_agregar;

    if (posc_agregar <= 1)
        return;
    
    if (posc_agregar % 2 == 1){
        posc_agregar = (posc_agregar - 1) / 2;
    } else{
        posc_agregar = posc_agregar / 2;
    }
    
    arr[posc_agregar] = arr[posc_agregar * 2] * arr[posc_agregar * 2 + 1];
    
    modificar_dato(arr, arr[posc_agregar], posc_agregar);
    return; 
}
