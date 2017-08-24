////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 1
//
// mesh.h
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MESH_H
#define _MESH_H

#include <vector>

using namespace std;

class Mesh{
    
private:
       
    // Número de vértices
    unsigned int numVertex;
    
    // Número de índices
    unsigned int numIndex;
    
    // Vector con los índices
    vector<float> listVertex;
    
    // Vector con los índices
    vector<unsigned int> listIndex;
    
    // Vector con los índices pares
    vector<unsigned int> listEvenIndex;
    
    // Vector con los índices impares
    vector<unsigned int> listOddIndex;
    
    // Vector con los colores
    vector<float> listColors;
    
    // Vector con los colores
    vector<float> listSecondColors;
    
public:
    
    ////////////////////////////////////////////////////////////////////////////
    // Constructor
    //
    Mesh(unsigned int numVertex, unsigned int numIndex, 
            vector<float> listVertex, vector<unsigned int> listIndex);
    
    Mesh(unsigned int numVertex, unsigned int numIndex, 
            vector<float> listVertex, vector<unsigned int> listIndex,
            float c11, float c12, float c13, float c21, float c22, float c23);
    
    ////////////////////////////////////////////////////////////////////////////
    // Getters
    //
    
    // Devuelve el número de vértices
    unsigned int getNumVertex();
        
    // Devuelve el número de índices
    unsigned int getNumIndex();
            
    // Devuelve el vector con los vértices
    vector<float> getVertex();
        
    // Devuelve el vector con los índices
    vector<unsigned int> getIndex();
    
    // Devuelve el primer vértice como un puntero
    float* getFirstVertex();
    
    // Devuelve el primer índice de los vértices como un puntero
    unsigned int* getFirstIndex();
    
    // Devuelve la lista par de los índices de los vértices
    vector<unsigned int> getEvenIndex();
    
    // Devuelve la lista impar de los índices de los vértices
    vector<unsigned int> getOddIndex();
    
    // Devuelve el primer índice de la lista par de los índices de los vértices
    unsigned int* getFirstEvenIndex();
    
    // Devuelve el primer índice de la lista impar de los índices de los vértices
    unsigned int* getFirstOddIndex();
    
    // Devuelve el primer índice de los colores como un puntero
    float* getFirstColor();
    
    // Devuelve el primer índice del segundo color como un puntero
    float* getSecondColor();
    
};

#endif