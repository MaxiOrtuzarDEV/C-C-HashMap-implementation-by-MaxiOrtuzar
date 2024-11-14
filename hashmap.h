/*
* Universidad de La Frontera
* Ingeniería Civil Electrónica/Telemática
*
* IIE-344 ESTRUCTURA DE DATOS Y ALGORITMOS
*
* Tarea 2
*
* Autor 1: Maximiliano Ortuzar
* Autor 2: Benjamin Fuentes
*
* Fecha: 14-13-2024
*
* Descripción general del programa: Implementacion de hashmap en c/c++
*/

#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>

#define INICIAL_SIZE_HASHMAP10 11
#define LOAD_FACTOR 0.70
#define INCREMENTATION_HASHMAP 17


struct NODO_HM{

    int value = 0;
    std::string key;
    NODO_HM *next = nullptr;
    bool isEmpty() const;
    void set(int, const std::string &);
    void printNodo() const;
    void emptyNodo();

    //PENDINETE


};

struct HASHMAP {
    unsigned size;
    NODO_HM **nodohashmap;
    double ocupado = 0;

    //methods
    unsigned funcion_hash( const std::string&  key) const;
    void insertar(int value, const std::string& key);
    bool eliminar(const std::string &key) const;
    void getPrintNodo(const std::string&  key) const;
    int getValue( const std::string&  key) const;
    void resize();
    std::string serializarNODO(unsigned valorHash) const;
    void guardar_HASHMAP(const std::string& nombreArchivo) const;

    static HASHMAP cargar_HASHMAP(const std::string& nombreArchivo);


    //Constructor
    explicit HASHMAP(unsigned);
    HASHMAP();
    //Destructor
    ~HASHMAP();
};




#endif //HASHMAP_H
