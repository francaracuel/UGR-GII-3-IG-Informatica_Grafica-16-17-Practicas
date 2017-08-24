////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 4
//
// mesh.h
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MESH_H
#define _MESH_H

#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>

using namespace std;

class Mesh{
    
private:
       
    // Número de vértices
    unsigned int numVertex;
    
    // Número de índices
    unsigned int numIndex;
    
    // Vector con los vértices
    vector<float> listVertex;
    
    // Vector con los índices
    vector<unsigned int> listIndex;
    
    // Vector con los índices pares
    vector<unsigned int> listEvenIndex;
    
    // Vector con los índices impares
    vector<unsigned int> listOddIndex;
    
    // Vector con las normales de los vértices
    vector<float> listNormalVertex;
    
    // Vector con las normales de los índices/caras
    vector<float> listNormalIndex;
    
    // Vector con los vértices de las normales de los vértices para mostrarlas 
    // como líneas
    vector<float> listColorNormalVertexVertex;
    
    // Vector con los índices de las normales de los vértices para mostrarlas 
    // como líneas
    vector<unsigned int> listColorNormalVertexIndex;
    
    // Vector con los vértices de las normales de los índices/caras para 
    // mostrarlas como líneas
    vector<float> listColorNormalIndexVertex;
    
    // Vector con los índices de las normales de los índices/caras para 
    // mostrarlas como líneas
    vector<unsigned int> listColorNormalIndexIndex;
    
    // Vector con los colores
    vector<float> listColors;
    
    // Vector con los colores
    vector<float> listSecondColors;
    
    // Vector con las coordenadas de textura
    vector<float> listTexture;
    
    // Condición para saber si se generan las texturas o no
    bool generateTexture;
    
    // Tupla de 3 con los máximos puntos del modelo
    tuple <float, float, float> pMax;
    
    // Tupla de 3 con los mínimos puntos del modelo
    tuple <float, float, float> pMin;
    
    // Tupla de 3 con lo que hay que mover el modelo
    tuple <float, float, float> diff;
    
    // Tamaño que hay que escalar el modelo
    float scale;
    
    ////////////////////////////////////////////////////////////////////////////
    // Coordenadas
    
    // Crea el vector con las normales de los vértices del objeto
    void createNormalVertex();
    
    // Crea el vector con las normales de los índices/caras del objeto
    void createNormalIndex();
    
    // Crea las coordenadas de textura del objeto
    void createTextureCoord();
    
    // Crea las coordenadas de textura para los objetos por revolución
    void createTextureCoordRev(int side, int numOutline, 
        vector<float> listVertexOutline);
    
    // Crea una tupla de 3 elementos con las máximas coordenadas
    void createMaxPoints();
    
    // Crea una tupla de 3 elementos con las mínimas coordenadas
    void createMinPoints();
    
    // Crea una tupla de 3 elementos con el valor por el que hay que 
    // trasladar el modelo para centrarlo en el origen
    void createDiffCenter();
    
    // Crea el factor por el que hay que multiplicar las coordenadas del
    // modelo para que se redimensione al tamaño máximo establecido por axisSize
    void createScaleValue(float axisSize);
    
public:
    
    ////////////////////////////////////////////////////////////////////////////
    // Constructor
    //
    Mesh(unsigned int numVertex, unsigned int numIndex, 
            vector<float> listVertex, vector<unsigned int> listIndex, 
            float axisSize);
    
    Mesh(unsigned int numVertex, unsigned int numIndex, 
            vector<float> listVertex, vector<unsigned int> listIndex,
            float c11, float c12, float c13, float c21, float c22, float c23, 
            float axisSize);
    
    Mesh(unsigned int numVertex, unsigned int numIndex, 
            vector<float> listVertex, vector<unsigned int> listIndex,
            float c11, float c12, float c13, float c21, float c22, float c23, 
            float axisSize, bool generateTextures, int side, int numOutline,
            vector<float> listVertexOutline);
    
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
    
    // Devuelve el vector de normales de los vértices
    vector<float> getNormalVertex();
        
    // Devuelve el vector de normales de los índices
    vector<float> getNormalIndex();
    
    // Devuelve la primera normal del vector de normales de los vértices
    float* getFirstNormalVertex();
    
    // Devuelve la primera normal del vector de normales de caras
    float* getFirstNormalIndex();
    
    // Devuelve el vector de vértices de normales de los vértices para 
    // pintarlas como líneas
    vector<float> getColorNormalVertexVertex();
    
    // Devuelve el vector de índices de normales de los vértices para 
    // pintarlas como líneas
    vector<unsigned int> getColorNormalVertexIndex();
        
    // Devuelve el vector de vértices de normales de los índices para pintarlas 
    // como líneas
    vector<float> getColorNormalIndexVertex();
    
    // Devuelve el vector de índices de normales de los índices para pintarlas 
    // como líneas
    vector<unsigned int> getColorNormalIndexIndex();
    
    // Devuelve el primer vértice del vector de normales de los vértices para
    // pintarla
    float* getFirstColorNormalVertexVertex();
    
    // Devuelve el primer índice del vector de normales de los vértices para
    // pintarla
    unsigned int* getFirstColorNormalVertexIndex();
    
    // Devuelve el primer vértice del vector de normales de caras para
    // pintarla
    float* getFirstColorNormalIndexVertex();
    
    // Devuelve el primer vértice del vector de normales de caras para
    // pintarla
    unsigned int* getFirstColorNormalIndexIndex();
    
    // Devuelve el primer índice de los colores como un puntero
    float* getFirstColor();
    
    // Devuelve el primer índice del segundo color como un puntero
    float* getSecondColor();
    
    // Devuelve el vector de texturas
    vector<float> getTexture();
    
    // Devuelve el puntero al primer elemento de las texturas
    float* getFirstTexture();
    
    ////////////////////////////////////////////////////////////////////////////
    // Setters
    //
    
    // Establece los colores que tendrá el objeto
    void setColors(vector<float> colors);
    
    // Establece el vector de texturas
    void setTexture(vector<float> texture);
    
    ////////////////////////////////////////////////////////////////////////////
    // Coordenadas
    
    // Devuelve una tupla de 3 elementos con las máximas coordenadas
    tuple<float, float, float> getMaxPoints();
    
    // Devuelve una tupla de 3 elementos con las mínimas coordenadas
    tuple<float, float, float> getMinPoints();
    
    // Devuelve una tupla de 3 elementos con el valor por el que hay que 
    // trasladar el modelo para centrarlo en el origen
    tuple<float, float, float> getDiffCenter();
    
    // Devuelve el factor por el que hay que multiplicar las coordenadas del
    // modelo para que se redimensione al tamaño máximo establecido por axisSize
    float getScaleValue();
    
};

#endif