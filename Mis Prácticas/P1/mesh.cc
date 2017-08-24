////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 1
//
// mesh.cc
//
////////////////////////////////////////////////////////////////////////////////

#include "mesh.h"

////////////////////////////////////////////////////////////////////////////////
// Constructor
//
Mesh::Mesh(unsigned int numV, unsigned int numI, 
            vector<float> listV, vector<unsigned int> listI) : 
    numVertex(numV), 
    numIndex(numI),
    listVertex(listV),
    listIndex(listI){
        
    for(unsigned int i=0; i<listIndex.size(); i=i+6){
        listEvenIndex.push_back(listIndex[i]);
        listEvenIndex.push_back(listIndex[i+1]);
        listEvenIndex.push_back(listIndex[i+2]);
        listOddIndex.push_back(listIndex[i+3]);
        listOddIndex.push_back(listIndex[i+4]);
        listOddIndex.push_back(listIndex[i+5]);
    }
        
}

Mesh::Mesh(unsigned int numV, unsigned int numI, 
            vector<float> listV, vector<unsigned int> listI,
            float c11, float c12, float c13, float c21, float c22, float c23) : 
    numVertex(numV), 
    numIndex(numI),
    listVertex(listV),
    listIndex(listI){
    
    for(unsigned int i=0; i<listIndex.size(); i=i+6){
        listEvenIndex.push_back(listIndex[i]);
        listEvenIndex.push_back(listIndex[i+1]);
        listEvenIndex.push_back(listIndex[i+2]);
        listOddIndex.push_back(listIndex[i+3]);
        listOddIndex.push_back(listIndex[i+4]);
        listOddIndex.push_back(listIndex[i+5]);
    }
    
    for(unsigned int i = 0; i<listIndex.size(); i=i+3){
        listColors.push_back(c11/255);
        listColors.push_back(c12/255);
        listColors.push_back(c13/255);        
    }
    
    for(unsigned int i = 0; i<listIndex.size(); i=i+3){
        listSecondColors.push_back(c21/255);
        listSecondColors.push_back(c22/255);
        listSecondColors.push_back(c23/255);        
    }
    
}

////////////////////////////////////////////////////////////////////////////////
// Getters
//

// Devuelve el número de vértices
unsigned int Mesh::getNumVertex(){
    return numVertex;
}

// Devuelve el número de índices
unsigned int Mesh::getNumIndex(){
    return numIndex;
}

// Devuelve el vector con los vértices
vector<float> Mesh::getVertex(){
    return listVertex;
}

// Devuelve el vector con los índices
vector<unsigned int> Mesh::getIndex(){
    return listIndex;
}

// Devuelve el primer vértice como un puntero
float* Mesh::getFirstVertex(){
    return &listVertex.front();
}

// Devuelve el primer índice de los vértices como un puntero
unsigned int* Mesh::getFirstIndex(){
    return &listIndex.front();
}

// Devuelve la lista par de los índices de los vértices
vector<unsigned int> Mesh::getEvenIndex(){
    return listEvenIndex;
}

// Devuelve la lista impar de los índices de los vértices
vector<unsigned int> Mesh::getOddIndex(){
    return listOddIndex;
}

// Devuelve el primer índice de la lista par de los índices de los vértices
unsigned int* Mesh::getFirstEvenIndex(){
    return &listEvenIndex.front();
}

// Devuelve el primer índice de la lista impar de los índices de los vértices
unsigned int* Mesh::getFirstOddIndex(){
    return &listOddIndex.front();
}

// Devuelve el primer índice de los colores como un puntero
float* Mesh::getFirstColor(){
    return &listColors.front();
}

// Devuelve el primer índice del segundo color como un puntero
float* Mesh::getSecondColor(){
    return &listSecondColors.front();
}