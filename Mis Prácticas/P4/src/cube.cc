////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 4
//
// cube.cc
//
////////////////////////////////////////////////////////////////////////////////

#include "cube.h"

////////////////////////////////////////////////////////////////////////////////
// Constructor
//
// Crea la geometría el cubo
//
Cube::Cube(){
    
    createGeometry();
    
}

Cube::Cube(string nameTexture, bool generateAutomatic): Cube(){
        
    material = new Material(nameTexture, generateAutomatic);
    
}

////////////////////////////////////////////////////////////////////////////////
// Crea la geometría del cubo que se quiere dibujar
//
void Cube::createGeometry(){
    
    // Se crea el vector de vértices
    vector<float> listVertex;
    
    // 0
    listVertex.push_back(-axisSize);
    listVertex.push_back(-axisSize);
    listVertex.push_back(axisSize);
    
    // 1
    listVertex.push_back(axisSize);
    listVertex.push_back(-axisSize);
    listVertex.push_back(axisSize);   
    
    // 2
    listVertex.push_back(axisSize);
    listVertex.push_back(axisSize);
    listVertex.push_back(axisSize);
    
    // 3
    listVertex.push_back(-axisSize);
    listVertex.push_back(axisSize);
    listVertex.push_back(axisSize);
    
    // 4
    listVertex.push_back(-axisSize);
    listVertex.push_back(-axisSize);
    listVertex.push_back(-axisSize);
    
    // 5
    listVertex.push_back(axisSize);
    listVertex.push_back(-axisSize);
    listVertex.push_back(-axisSize);   
    
    // 6
    listVertex.push_back(axisSize);
    listVertex.push_back(axisSize);
    listVertex.push_back(-axisSize);
    
    // 7
    listVertex.push_back(-axisSize);
    listVertex.push_back(axisSize);
    listVertex.push_back(-axisSize);
                
    // Se crea el vector de índices
    vector<unsigned int> listIndex;
        
    // 0
    listIndex.push_back(0);
    listIndex.push_back(2);
    listIndex.push_back(3);
    
    // 1
    listIndex.push_back(0);
    listIndex.push_back(1);
    listIndex.push_back(2);
    
    // 2
    listIndex.push_back(1);
    listIndex.push_back(6);
    listIndex.push_back(2);
    
    // 3
    listIndex.push_back(1);
    listIndex.push_back(5);
    listIndex.push_back(6);
    
    // 4
    listIndex.push_back(5);
    listIndex.push_back(7);
    listIndex.push_back(6);
    
    // 5
    listIndex.push_back(5);
    listIndex.push_back(4);
    listIndex.push_back(7);
    
    // 6
    listIndex.push_back(4);
    listIndex.push_back(3);
    listIndex.push_back(7);
    
    // 7
    listIndex.push_back(4);
    listIndex.push_back(0);
    listIndex.push_back(3);
    
    // 8
    listIndex.push_back(3);
    listIndex.push_back(6);
    listIndex.push_back(7);
    
    // 9
    listIndex.push_back(3);
    listIndex.push_back(2);
    listIndex.push_back(6);
    
    // 10
    listIndex.push_back(4);
    listIndex.push_back(5);
    listIndex.push_back(0);
    
    // 11
    listIndex.push_back(5);
    listIndex.push_back(1);
    listIndex.push_back(0);    
    
    mesh = new Mesh(listVertex.size()/3, listIndex.size(), listVertex, listIndex, 30, 182, 129, 182, 30, 83, axisSize);
            
}