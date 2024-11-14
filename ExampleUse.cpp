#include <iostream>
#include "hashmap.h"

int main() {
    HASHMAP XD;


    std::cout<< XD.funcion_hash("maxi"); XD.insertar(12, "maxi");

    std::cout<< XD.funcion_hash("ixam")<<std::endl; XD.insertar(1, "ixam");
    std::cout<< XD.funcion_hash("iaxm")<<std::endl; XD.insertar(7272727, "iaxm");


    std::cout<< XD.serializarNODO(1) << std::endl;

    XD.guardar_HASHMAP("aaaaaa.txt");

    HASHMAP nuevo = nuevo.cargar_HASHMAP("aaaaaa.txt");

    std::cout<<nuevo.getValue("maxi")<<std::endl;
    std::cout << "Valor de 'maxi': " << nuevo.getValue("maxi") << std::endl;
    std::cout << "Valor de 'ixam': " << nuevo.getValue("ixam") << std::endl;
    std::cout << "Valor de 'iaxm': " << nuevo.getValue("iaxm") << std::endl;
    std::cout<< XD.funcion_hash("iaxm")<<std::endl; XD.insertar(7272727, "hfgdhdhh");
}
