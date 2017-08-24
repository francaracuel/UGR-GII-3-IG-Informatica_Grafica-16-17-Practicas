////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 3
//
// mesh.cc
//
////////////////////////////////////////////////////////////////////////////////

#include "mesh.h"

////////////////////////////////////////////////////////////////////////////////
// Constructor
//
Mesh::Mesh(unsigned int numV, unsigned int numI, 
            vector<float> listV, vector<unsigned int> listI, 
            float axisSize) : 
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
    
    createMaxPoints();
    createMinPoints();
    createDiffCenter();
    createScaleValue(axisSize);
        
}

Mesh::Mesh(unsigned int numV, unsigned int numI, 
            vector<float> listV, vector<unsigned int> listI,
            float c11, float c12, float c13, float c21, float c22, float c23, 
            float axisSize) : 
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
    
    createMaxPoints();
    createMinPoints();
    createDiffCenter();
    createScaleValue(axisSize);
    
}

////////////////////////////////////////////////////////////////////////////////
// Create
//

// Crea una tupla de 3 elementos con las máximas coordenadas
void Mesh::createMaxPoints(){
    
    get<0>(pMax) = listVertex[0];
    get<1>(pMax) = listVertex[1];
    get<2>(pMax) = listVertex[2];
    
    // Se recorren todos los vértices
    for(unsigned int i=3; i<listVertex.size(); i=i+3){
        
        // x
        if(listVertex[i]>get<0>(pMax)){
            get<0>(pMax) = listVertex[i];
        }
        
        // y
        if(listVertex[i+1]>get<1>(pMax)){
            get<1>(pMax) = listVertex[i+1];
        }
        
        // z
        if(listVertex[i+2]>get<2>(pMax)){
            get<2>(pMax) = listVertex[i+2];
        }
        
    }
        
}

// Crea una tupla de 3 elementos con las mínimas coordenadas
void Mesh::createMinPoints(){
    
    get<0>(pMin) = listVertex[0];
    get<1>(pMin) = listVertex[1];
    get<2>(pMin) = listVertex[2];
    
    // Se recorren todos los vértices
    for(unsigned int i=3; i<listVertex.size(); i=i+3){
        
        // x
        if(listVertex[i]<get<0>(pMin)){
            get<0>(pMin) = listVertex[i];
        }
        
        // y
        if(listVertex[i+1]<get<1>(pMin)){
            get<1>(pMin) = listVertex[i+1];
        }
        
        // z
        if(listVertex[i+2]<get<2>(pMin)){
            get<2>(pMin) = listVertex[i+2];
        }
        
    }
        
}

// Crea una tupla de 3 elementos con el valor por el que hay que 
// trasladar el modelo para centrarlo en el origen
void Mesh::createDiffCenter(){
        
    // Hay que restarle la media entre los dos puntos
    get<0>(diff) = -(get<0>(pMax) + get<0>(pMin))/2;
    get<1>(diff) = -(get<1>(pMax) + get<1>(pMin))/2;
    get<2>(diff) = -(get<2>(pMax) + get<2>(pMin))/2;
        
}

// Crea el factor por el que hay que multiplicar las coordenadas del
// modelo para que se redimensione al tamaño máximo establecido por axisSize
void Mesh::createScaleValue(float axisSize){
        
    // Se obtiene el factor de escala de x
    float x = get<0>(pMax) + get<0>(diff);
    
    float scaleX = (axisSize+axisSize) / x;
    
    // Se obtiene el factor de escala de y
    float y = get<1>(pMax) + get<1>(diff);
    
    float scaleY = (axisSize+axisSize) / y;
    
    // Se obtiene el factor de escala de z
    float z = get<2>(pMax) + get<2>(diff);
    
    float scaleZ = (axisSize+axisSize) / z;
    
    // Se devuelve el menor de todos para que no salga de la pantalla
    scale = min({scaleX, scaleY, scaleZ});
    
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

// Devuelve una tupla de 3 elementos con las máximas coordenadas
tuple<float, float, float> Mesh::getMaxPoints(){
    
    return pMax;
    
}

// Devuelve una tupla de 3 elementos con las mínimas coordenadas
tuple<float, float, float> Mesh::getMinPoints(){
    
    return pMin;
    
}

// Devuelve una tupla de 3 elementos con el valor por el que hay que 
// trasladar el modelo para centrarlo en el origen
tuple<float, float, float> Mesh::getDiffCenter(){
    
    return diff;
    
}

// Devuelve el factor por el que hay que multiplicar las coordenadas del
// modelo para que se redimensione al tamaño máximo establecido por axisSize
float Mesh::getScaleValue(){
    
    return scale;
    
}

////////////////////////////////////////////////////////////////////////////////
// Setters
//

// Establece los colores que tendrá el objeto
void Mesh::setColors(vector<float> colors){
    
    vector<float> listColorsAux;
    vector<float> listSecondColorsAux;

    for(unsigned int i = 0; i<listIndex.size(); i=i+3){
        listColorsAux.push_back(colors[0]/255);
        listColorsAux.push_back(colors[1]/255);
        listColorsAux.push_back(colors[2]/255);    
    }
    
    for(unsigned int i = 0; i<listIndex.size(); i=i+3){
        listSecondColorsAux.push_back(colors[3]/255);
        listSecondColorsAux.push_back(colors[4]/255);
        listSecondColorsAux.push_back(colors[5]/255);        
    }
    
    listColors = listColorsAux;
    listSecondColors = listSecondColorsAux;
    
}
