////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 2
//
// diamond.cc
//
////////////////////////////////////////////////////////////////////////////////

#include "diamond.h"

////////////////////////////////////////////////////////////////////////////////
// Constructor
//
// Crea la geometría del diamante
//
Diamond::Diamond(){
    
    createGeometry();
    
}

////////////////////////////////////////////////////////////////////////////////
// Crea la geometría del diamante que se quiere dibujar
//
void Diamond::createGeometry(){
    
    // Se crea el vector de vértices
    vector<float> listVertex;
    
    // 
    listVertex.push_back(-axisSize/2);
    listVertex.push_back(0);
    listVertex.push_back(axisSize/2);
    
    // 
    listVertex.push_back(axisSize/2);
    listVertex.push_back(0);
    listVertex.push_back(axisSize/2);  
    
    // 
    listVertex.push_back(axisSize/2);
    listVertex.push_back(0);
    listVertex.push_back(-axisSize/2);
    
    // 
    listVertex.push_back(-axisSize/2);
    listVertex.push_back(0);
    listVertex.push_back(-axisSize/2);
    
    listVertex.push_back(0);
    listVertex.push_back(axisSize);
    listVertex.push_back(0);
    
    listVertex.push_back(0);
    listVertex.push_back(-axisSize*2);
    listVertex.push_back(0);
        
    // Se crea el vector de índices
    vector<unsigned int> listIndex;
    
    listIndex.push_back(5);
    listIndex.push_back(1);
    listIndex.push_back(0);
    
    listIndex.push_back(0);
    listIndex.push_back(1);
    listIndex.push_back(4);
    
    listIndex.push_back(1);
    listIndex.push_back(2);
    listIndex.push_back(4);
    
    listIndex.push_back(5);
    listIndex.push_back(2);
    listIndex.push_back(1);
    
    listIndex.push_back(5);
    listIndex.push_back(3);
    listIndex.push_back(2);
    
    listIndex.push_back(2);
    listIndex.push_back(3);
    listIndex.push_back(4);
    
    listIndex.push_back(3);
    listIndex.push_back(0);
    listIndex.push_back(4);
        
    listIndex.push_back(5);
    listIndex.push_back(0);
    listIndex.push_back(3);
        
    mesh = new Mesh(listVertex.size()/3, listIndex.size(), listVertex, listIndex, 30, 182, 129, 182, 30, 83, axisSize);
        
}