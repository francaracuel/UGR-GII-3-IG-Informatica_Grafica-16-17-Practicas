////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 2
//
// tetrahedron.cc
//
////////////////////////////////////////////////////////////////////////////////

#include "tetrahedron.h"

////////////////////////////////////////////////////////////////////////////////
// Constructor
//
// Crea la geometría el tetraedro
//
Tetrahedron::Tetrahedron(){
    
    createGeometry();
    
}

////////////////////////////////////////////////////////////////////////////////
// Crea la geometría del tetraedro que se quiere dibujar
//
void Tetrahedron::createGeometry(){
    
    // Se crea el vector de vértices
    vector<float> listVertex;
    
    // Vértice 2 (-50,-50,50)
    listVertex.push_back(-axisSize);
    listVertex.push_back(-axisSize);
    listVertex.push_back(axisSize);
    
    // Vértice 1 (50,-50,-50)
    listVertex.push_back(axisSize);
    listVertex.push_back(-axisSize);
    listVertex.push_back(-axisSize);  
    
    // Vértice 3 (50,50,50)
    listVertex.push_back(axisSize);
    listVertex.push_back(axisSize);
    listVertex.push_back(axisSize);
    
    // Vértice 0 (-50,50,-50)
    listVertex.push_back(-axisSize);
    listVertex.push_back(axisSize);
    listVertex.push_back(-axisSize);
        
    // Se crea el vector de índices
    vector<unsigned int> listIndex;
    
    listIndex.push_back(0);
    listIndex.push_back(1);
    listIndex.push_back(2);
    
    listIndex.push_back(0);
    listIndex.push_back(2);
    listIndex.push_back(3);
    
    listIndex.push_back(3);
    listIndex.push_back(1);
    listIndex.push_back(0);
    
    listIndex.push_back(3);
    listIndex.push_back(2);
    listIndex.push_back(1);
    
    // Con una punta en el origen 0,0,0 -> Para la primera defensa
    // Se crea el vector de vértices
    /*vector<float> listVertex;
    
    // Vértice 2 (-50,-50,50)
    listVertex.push_back(0);
    listVertex.push_back(axisSize);
    listVertex.push_back(-axisSize);
    
    // Vértice 1 (50,-50,-50)
    listVertex.push_back(axisSize);
    listVertex.push_back(axisSize);
    listVertex.push_back(axisSize);  
    
    // Vértice 3 (50,50,50)
    listVertex.push_back(0);
    listVertex.push_back(0);
    listVertex.push_back(0);
    
    // Vértice 0 (-50,50,-50)
    listVertex.push_back(-axisSize);
    listVertex.push_back(axisSize);
    listVertex.push_back(axisSize);
        
    // Se crea el vector de índices
    vector<unsigned int> listIndex;
    
    listIndex.push_back(0);
    listIndex.push_back(1);
    listIndex.push_back(2);
    
    listIndex.push_back(0);
    listIndex.push_back(2);
    listIndex.push_back(3);
    
    listIndex.push_back(3);
    listIndex.push_back(1);
    listIndex.push_back(0);
    
    listIndex.push_back(3);
    listIndex.push_back(2);
    listIndex.push_back(1);*/
    
    mesh = new Mesh(listVertex.size()/3, listIndex.size(), listVertex, listIndex, 30, 182, 129, 182, 30, 83, axisSize);
        
}
