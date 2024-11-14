

#include "hashmap.h"
#include <iostream>
#include <ostream>
#include <sstream>

//Set de Nodo
void NODO_HM::set(const int value, const std::string &key) {
    this->value = value;
    this->key = key;
}

bool NODO_HM::isEmpty() const {

    return key.empty();  // Si la clave está vacía, el nodo se considera vacío

}

//Imprimir clave/valor Nodo
void NODO_HM::printNodo() const {

    if (this->isEmpty()==true) {
        std::cout << "Vacio......" << std::endl;
    }else {
        std::cout<< " Key: "<< this->key << " ; " << "Value: " << this->value <<std::endl;
    }


}

void NODO_HM::emptyNodo() {
    this->key.clear();
    this->value = 0;

}


//CONSTRUCTORES DE HASHMAP
HASHMAP::HASHMAP(const unsigned _size) : size(_size), ocupado(0.0) {
    nodohashmap = new NODO_HM*[this->size];
    for (int i = 0; i < this->size; ++i) {
        nodohashmap[i] = new NODO_HM();
        nodohashmap[i]->emptyNodo();
    }
}
HASHMAP::HASHMAP() : size(INICIAL_SIZE_HASHMAP10), ocupado(0.0) {
    nodohashmap = new NODO_HM*[this->size];
    for (int i = 0; i < this->size; ++i) {
        nodohashmap[i] = new NODO_HM();
        nodohashmap[i]->emptyNodo();
    }
}

//DESTRUCTOR
HASHMAP::~HASHMAP() {
    for (int i = 0; i < size; ++i) {
        delete nodohashmap[i];  // Libera cada objeto NODO_HM
    }
    delete[] nodohashmap;  // Libera el arreglo de punteros
}

//Funcion Hash
unsigned HASHMAP::funcion_hash( const std::string&  key) const {
    size_t hash = 0;

    for(const char c : key) {
        constexpr size_t primo = 31;
        hash = (hash * primo + c) % size;
    }
    return hash;
}

void HASHMAP::getPrintNodo(const std::string &key) const {
    const unsigned hashindex = funcion_hash(key);
    const NODO_HM *nodo = this->nodohashmap[hashindex];
    if (nodo->key == key){
        nodo->printNodo();
    }else {
        while (nodo->key != key) {
            nodo = nodo->next;
        }
        nodo->printNodo();
    }

}



//Metodo de insertar
void HASHMAP::insertar(const int value, const std::string& key) {

    const unsigned hashindex = funcion_hash(key);

    if( this->nodohashmap[hashindex]->key.empty()) {

        this->nodohashmap[hashindex]->set(value, key);
        this->nodohashmap[hashindex]->printNodo();

        //Control del loadFactor PENDIENTE
        const double elementSpacePorcentaje = 1.0 / this->size;
        this->ocupado += elementSpacePorcentaje;

        std::cout<<"no colision"<<std::endl;

        if(this->ocupado >= LOAD_FACTOR) {
            this->resize();
        }
    }else {

        NODO_HM *ptr = this->nodohashmap[hashindex];


        while (ptr != nullptr) {
            if (ptr->key == key) {
                // Clave existente, actualizamos el valor
                ptr->set(value, key);
                std::cout << "Actualizacion NODO. " << hashindex << std::endl;
                ptr->printNodo();
                return;
            }

            if (ptr->next == nullptr) break;
            ptr = ptr->next;
        }

        // Clave no existe, agregar nuevo nodo al final de la lista
        auto *newNode = new NODO_HM;
        newNode->set(value, key);
        ptr->next = newNode;
        newNode->printNodo();
        std::cout << "Colision resuelta, nuevo nodo enlazado " << std::endl;

    }

}

bool HASHMAP::eliminar(const std::string &key) const {

    const unsigned hashindex = funcion_hash(key);
    NODO_HM *editor = this->nodohashmap[hashindex];
    NODO_HM *otro = nullptr;

    if(editor->key == key && editor->next == nullptr) {
        editor->emptyNodo();
        return true;
    }
    if (editor->key == key && editor->next != nullptr){
        otro = editor->next;
        editor->emptyNodo();
        this->nodohashmap[hashindex] = otro;
        return true;
    }
    if (editor->isEmpty()) {
        std::cout<<"El nodo esta vacio."<<std::endl;
        return false;
    }
    while (editor->key != key) {
        otro = editor;
        editor = editor->next;
    }
    otro->next = editor->next;
    editor->emptyNodo();
    return true;
}


int HASHMAP::getValue(const std::string &key) const {

    int value;
    const unsigned hashindex = funcion_hash(key);

    const NODO_HM *nodo = this->nodohashmap[hashindex];
    if (nodo->key == key){
        value = nodo->value;
    }else {
        while (nodo->key != key) {
            nodo = nodo->next;
        }
        value = nodo->value;
    }
    return value;
}

//Redimenciona el tamaño
void HASHMAP::resize() {
    // Guardar el tamaño actual
    unsigned oldSize = size;
    size = size + INCREMENTATION_HASHMAP; // Incrementar el tamaño de acuerdo con la constante definida
    auto** newHashmap = new NODO_HM*[size];

    // Inicializar nuevo arreglo de nodos
    for (unsigned i = 0; i < size; ++i) {
        newHashmap[i] = new NODO_HM();
        newHashmap[i]->emptyNodo();
    }

    // Rehashing: transferir los elementos al nuevo arreglo
    for (unsigned i = 0; i < oldSize; ++i) {
        NODO_HM* current = nodohashmap[i];

        while (current != nullptr && !current->isEmpty()) {
            unsigned newIndex = funcion_hash(current->key); // Calcular nuevo índice para cada clave

            // Insertar el nodo en la nueva posición
            if (newHashmap[newIndex]->isEmpty()) {
                newHashmap[newIndex]->set(current->value, current->key);
            } else {
                // Resolver colisiones en el nuevo arreglo
                NODO_HM* temp = newHashmap[newIndex];
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = new NODO_HM();
                temp->next->set(current->value, current->key);
            }

            current = current->next;
        }
    }

    // Liberar memoria del arreglo antiguo
    for (unsigned i = 0; i < oldSize; ++i) {
        delete nodohashmap[i];
    }
    delete[] nodohashmap;

    // Reemplazar con el nuevo arreglo
    nodohashmap = newHashmap;

    // Ajustar el factor de carga
    ocupado = static_cast<double>(oldSize) / size;
}

std::string HASHMAP::serializarNODO(const unsigned valorHash) const {
    std::ostringstream oss;
    auto current = this->nodohashmap[valorHash];


    // Iniciar con el valor del hash
    oss << valorHash << "|";

    // Serializar el nodo actual y los nodos enlazados en caso de colisión
    while (current != nullptr && !current->isEmpty()) {
        oss << current->key << ":" << current->value;
        
        // Si hay más nodos enlazados, agregamos el separador "->"
        current = current->next;
        if (current != nullptr && !current->isEmpty()) {
            oss << "->";
        }
    }

    // Retornar la cadena serializada
    return oss.str();
}


void HASHMAP::guardar_HASHMAP(const std::string& nombreArchivo) const {
    FILE *archivo = fopen(nombreArchivo.c_str(), "w");

    if (archivo == nullptr) {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    // Recorrer todos los índices de la tabla hash
    for (unsigned i = 0; i < this->size; ++i) {  // Asegúrate de que SIZE sea el tamaño de la tabla
        // Obtener la cadena serializada del nodo en la posición 'i'
        std::string serializado = serializarNODO(i);

        // Si la posición no está vacía (es decir, tiene nodos), escribir la serialización en el archivo
        if (!serializado.empty()) {
            // Escribir en el archivo con printf o fputs
            fprintf(archivo, "%s\n", serializado.c_str());
        }
    }

    // Cerrar el archivo
    fclose(archivo);
}
HASHMAP HASHMAP::cargar_HASHMAP(const std::string& nombreArchivo) {
    HASHMAP hashmapCargado;  // Creamos un nuevo objeto HASHMAP vacío

    FILE* archivo = fopen(nombreArchivo.c_str(), "r");
    if (archivo == nullptr) {
        std::cerr << "No se pudo abrir el archivo para cargar el HashMap." << std::endl;
        return hashmapCargado;  // Si no se pudo abrir el archivo, devolvemos el HashMap vacío
    }

    char linea[1024];
    while (fgets(linea, sizeof(linea), archivo)) {
        std::string lineaStr(linea);
        std::stringstream ss(lineaStr);

        unsigned hashValue;
        char separador;
        ss >> hashValue >> separador;  // Leer el valor hash y '|'

        if (separador != '|') {
            std::cerr << "Formato incorrecto en la línea: " << lineaStr << std::endl;
            continue;  // Si el formato es incorrecto, continuamos con la siguiente línea
        }

        // Leer claves y valores, separados por "->"
        std::string claveValor;
        while (std::getline(ss, claveValor, '-')) {
            if (claveValor.empty()) continue;

            // Procesamos la clave y el valor
            size_t pos = claveValor.find(":");
            if (pos != std::string::npos) {
                std::string key = claveValor.substr(0, pos);
                int value = std::stoi(claveValor.substr(pos + 1));

                // Insertar el par clave-valor en el HashMap cargado
                hashmapCargado.insertar(value, key);
            }
        }
    }

    fclose(archivo);
    return hashmapCargado;
}

