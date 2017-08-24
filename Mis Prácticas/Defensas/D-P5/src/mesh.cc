////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 5
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
    listIndex(listI),
    generateTexture(true){
        
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
    
    // Se crean las normales
    createNormalVertex();
    
    if(generateTexture)
        // Se crean las coordenadas de textura
        createTextureCoord();
        
}

Mesh::Mesh(unsigned int numV, unsigned int numI, 
            vector<float> listV, vector<unsigned int> listI,
            float c11, float c12, float c13, float c21, float c22, float c23, 
            float axisSize) : 
    numVertex(numV), 
    numIndex(numI),
    listVertex(listV),
    listIndex(listI),
    generateTexture(true){
    
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
    
    // Se crean las normales
    createNormalVertex();
    
    // Se crean las coordenadas de textura
    createTextureCoord();
    
}

Mesh::Mesh(unsigned int numV, unsigned int numI, 
            vector<float> listV, vector<unsigned int> listI,
            float c11, float c12, float c13, float c21, float c22, float c23, 
            float axisSize, bool gT, int side, int numOutline, 
            vector<float> listVertexOutline) : 
    numVertex(numV), 
    numIndex(numI),
    listVertex(listV),
    listIndex(listI),
    generateTexture(gT){
    
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
    
    // Se crean las normales
    createNormalVertex();
    
    // Para los objetos por revolución se debería utilizar un método alternativo
    // en el cual, por más que reviso la función, no veo que está mal, pero
    // no consigo hacer que el cuerpo coja la textura correctamente.
    // Con el método normal, la textura funciona correctamente, y debido a la
    // falta de tiempo, utilizo este método para aplicarle la textura a los 
    // objetos por revolción.
    //if(generateTexture)
        // Se crean las coordenadas de textura
        createTextureCoord();
    //else
        // Se crean las coordenadas de textura para objetos por revolución
        //createTextureCoordRev(side, numOutline, listVertexOutline);
    
}

////////////////////////////////////////////////////////////////////////////////
// Create
//

// Crea el vector con las normales de los vértices del objeto
void Mesh::createNormalVertex(){    
    
    // Se inicializa el vector de normales de vértices a 0
    listNormalVertex = vector<float>(numVertex*3, 0);
            
    // Se crean las normales de las caras
    createNormalIndex();
        
    // Se recorre el vector de vértices para hacerlos unitarios
    for(unsigned int i=0; i<listNormalVertex.size(); i=i+3){
        
        // Se consigue el módulo del vector
        float mm = sqrt(listNormalVertex[i]*listNormalVertex[i] + listNormalVertex[i+1]*listNormalVertex[i+1] + listNormalVertex[i+2]*listNormalVertex[i+2]);
        
        // Se normaliza el vector
        listNormalVertex[i] = listNormalVertex[i]/mm;
        listNormalVertex[i+1] = listNormalVertex[i+1]/mm;
        listNormalVertex[i+2] = listNormalVertex[i+2]/mm;
        
        // Se va a utilizar GL_LINES para pintar y solo es necesario añadir
        // 2 vectores
        listColorNormalVertexVertex.push_back(listVertex[i]);
        listColorNormalVertexVertex.push_back(listVertex[i+1]);
        listColorNormalVertexVertex.push_back(listVertex[i+2]);
        
        listColorNormalVertexVertex.push_back(listVertex[i] + listNormalVertex[i]*100);
        listColorNormalVertexVertex.push_back(listVertex[i+1] + listNormalVertex[i+1]*100);
        listColorNormalVertexVertex.push_back(listVertex[i+2] + listNormalVertex[i+2]*100);
        
    }
    
    // Se añaden los índices a los vectores de las normales.
    for(unsigned int i=0; i<listColorNormalVertexVertex.size(); i++){
        listColorNormalVertexIndex.push_back(i);
    }
    
}

// Crea el vector con las normales de los índices/caras del objeto
void Mesh::createNormalIndex(){
         
    // Se recorre el vector de índices/caras
    for(unsigned int i=0; i<listIndex.size(); i=i+3){
        
        // Coordenadas que crean la cara
        
        // Primer vértice de la cara
        // x, y, z
        tuple<float, float, float> p;
        
        // x
        get<0>(p) = listVertex[listIndex[i]*3];
        
        // y
        get<1>(p) = listVertex[listIndex[i]*3+1];
        
        // z
        get<2>(p) = listVertex[listIndex[i]*3+2];
        
        // Segundo vértice de la cara
        // x, y, z
        tuple<float, float, float> q;
        
        // x
        get<0>(q) = listVertex[listIndex[i+1]*3];
        
        // y
        get<1>(q) = listVertex[listIndex[i+1]*3+1];
        
        // z
        get<2>(q) = listVertex[listIndex[i+1]*3+2];
        
        // Tercer vértice de la cara
        // x, y, z
        tuple<float, float, float> r;
        
        // x
        get<0>(r) = listVertex[listIndex[i+2]*3];
        
        // y
        get<1>(r) = listVertex[listIndex[i+2]*3+1];
        
        // z
        get<2>(r) = listVertex[listIndex[i+2]*3+2];
                
        // Vector a
        // x, y, z
        tuple<float, float, float> a;
        
        // x
        get<0>(a) = get<0>(q) - get<0>(p);
        
        // y
        get<1>(a) = get<1>(q) - get<1>(p);
        
        // z
        get<2>(a) = get<2>(q) - get<2>(p);
        
        // Vector b
        // x, y, z
        tuple<float, float, float> b;
        
        // x
        get<0>(b) = get<0>(r) - get<0>(p);
        
        // y
        get<1>(b) = get<1>(r) - get<1>(p);
        
        // z
        get<2>(b) = get<2>(r) - get<2>(p);
        
        // Vector m
        // x, y, z
        tuple<float, float, float> m;
        
        // x
        get<0>(m) = get<1>(a) * get<2>(b) - get<2>(a) * get<1>(b);
        
        // y
        get<1>(m) = get<2>(a) * get<0>(b) - get<0>(a) * get<2>(b);
        
        // z
        get<2>(m) = get<0>(a) * get<1>(b) - get<1>(a) * get<0>(b);
        
        // Módulo de m
        float mm = sqrt(get<0>(m)*get<0>(m) + get<1>(m)*get<1>(m) + get<2>(m)*get<2>(m));
        
        // Vector normal (unitario) n
        // x, y, z
        tuple<float, float, float> n;
        
        // x
        get<0>(n) = get<0>(m) / mm;
        
        // y
        get<1>(n) = get<1>(m) / mm;
        
        // z
        get<2>(n) = get<2>(m) / mm;
        
        ////////////////////////////////////////////////////////////////////////
        // Se añade la normal de la cara correspondiente a su vector        
        // x
        listNormalIndex.push_back(get<0>(n));
        
        // y
        listNormalIndex.push_back(get<1>(n));
        
        // z
        listNormalIndex.push_back(get<2>(n));
        
        //
        ////////////////////////////////////////////////////////////////////////
        
        ////////////////////////////////////////////////////////////////////////
        // Se añade al vector de normales de vértices, el vector n de cada
        // vértice. Después se modificará para hacerlo unitario.
        
        // x
        listNormalVertex[listIndex[i]*3] += get<0>(n);
        
        // y
        listNormalVertex[listIndex[i]*3+1] += get<1>(n);
        
        // z
        listNormalVertex[listIndex[i]*3+2] += get<2>(n);
        
        
        // x
        listNormalVertex[listIndex[i+1]*3] += get<0>(n);
        
        // y
        listNormalVertex[listIndex[i+1]*3+1] += get<1>(n);
        
        // z
        listNormalVertex[listIndex[i+1]*3+2] += get<2>(n);
        
        
        // x
        listNormalVertex[listIndex[i+2]*3] += get<0>(n);
        
        // y
        listNormalVertex[listIndex[i+2]*3+1] += get<1>(n);
        
        // z
        listNormalVertex[listIndex[i+2]*3+2] += get<2>(n);
        
        //
        ////////////////////////////////////////////////////////////////////////
        
        ////////////////////////////////////////////////////////////////////////
        // Se crean los vértices para la visualización de las normales de cara      
        float n1 = (listVertex[listIndex[i]*3]+listVertex[listIndex[i+1]*3]+listVertex[listIndex[i+2]*3])/3;
        float n2 = (listVertex[listIndex[i]*3+1]+listVertex[listIndex[i+1]*3+1]+listVertex[listIndex[i+2]*3+1])/3;
        float n3 = (listVertex[listIndex[i]*3+2]+listVertex[listIndex[i+1]*3+2]+listVertex[listIndex[i+2]*3+2])/3;
              
        // Se va a utilizar GL_LINES para pintar y solo es necesario añadir
        // 2 vectores
        listColorNormalIndexVertex.push_back(n1);
        listColorNormalIndexVertex.push_back(n2);
        listColorNormalIndexVertex.push_back(n3);
        
        listColorNormalIndexVertex.push_back(n1 + get<0>(n)*100);
        listColorNormalIndexVertex.push_back(n2 + get<1>(n)*100);
        listColorNormalIndexVertex.push_back(n3 + get<2>(n)*100);
                          
    }
     
    // Se añaden los índices a los vectores de las normales. Como solo se 
    // utilizan 2 vértices por cada línea, el número de índices de las normales
    // será 2/3 del número de índices del objeto
    for(unsigned int i=0; i<numIndex/3*2; i++){
        listColorNormalIndexIndex.push_back(i);
    }
    
}

// Crea las coordenadas de textura del objeto
void Mesh::createTextureCoord(){
 
    // Se consiguen las coordenadas máximas y mínimas de la altura
    float yMax = get<1>(pMax);
    float yMin = get<1>(pMin);
    
    // Se recorren todos los vértices y por cada tupla de 3 valores(x,y,z) se
    // guardan una tupla de 2 valores (u,v), por lo que el tamaño del vector
    // de texturas será 2/3 el tamaño del de vértices
    for(unsigned int i=0; i<numVertex*3; i=i+3){
        
        // Se consiguen las coordenadas de cada vector
        float x = listVertex[i];
        float y = listVertex[i+1];
        float z = listVertex[i+2];
        
        // Se crea alfa
        float alpha = atan2(z, x);
        
        // u = 1/2 + alpha/2PI
        float u = (1/2) + (alpha/(2*3.14159265358979323846));
        
        // v = altura - altura mínima / altura máxima - altura mínima
        float v = (y - yMin) / (yMax - yMin);
        
        // Se guardan los valores en el vector
        listTexture.push_back(u);
        listTexture.push_back(v);
        
    }
    
    /*for(int i=0; i<listTexture.size(); i=i+2){
        printf("\nCoordenada %d: (%f,%f)\n", i/2, listTexture[i], listTexture[i+1]);
    }*/
    
}

// Crea las coordenadas de textura del objeto por revolución
void Mesh::createTextureCoordRev(int side, int numOutline, 
        vector<float> listVertexOutline){
    
    // Vector con las distancias que se van calculando
    vector<float> distances(numOutline, 0);
    distances[0] = 0.0;

    for(unsigned int i=1; i<numOutline; i++){
        
        float x = (listVertexOutline[i*3] - listVertexOutline[(i*3)-3]) * (listVertexOutline[i*3] - listVertexOutline[(i*3)-3]);
        float y = (listVertexOutline[(i*3)+1] - listVertexOutline[(i*3)-2]) * (listVertexOutline[(i*3)+1] - listVertexOutline[(i*3)-2]);
        float z = (listVertexOutline[(i*3)+2] - listVertexOutline[(i*3)-1]) * (listVertexOutline[(i*3)+2] - listVertexOutline[(i*3)-1]);
        printf("\n\nCoordenada %d: (%f, %f, %f)", i, x, y, z);
        distances[i] = distances[i-1] + sqrt(x+y+z);
        
    }
                
    // Se calculan sus correspondientes coordenadas en 2 partes.
    for(unsigned int i=0; i<side; i++){
        
        float si = ((float)i)/(float)(side-1);
        
        for(unsigned int j=0; j<numOutline; j++){
            
            float tj = distances[j]/distances[numOutline-1];
            
            listTexture.push_back(si);
            listTexture.push_back(tj);
            
        }
        
    }
    
    for(int i=0; i<listTexture.size(); i=i+2){
        printf("\nREV Coordenada %d: (%f,%f)\n", i/2, listTexture[i], listTexture[i+1]);
    }
    
}

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

// Devuelve el vector de normales de los vértices
vector<float> Mesh::getNormalVertex(){
    return listNormalVertex;    
}

// Devuelve el vector de normales de los índices
vector<float> Mesh::getNormalIndex(){
    return listNormalIndex;
}

// Devuelve la primera normal del vector de normales de los vértices
float* Mesh::getFirstNormalVertex(){
    return &listNormalVertex.front();
}

// Devuelve la primera normal del vector de normales de caras
float* Mesh::getFirstNormalIndex(){
    return &listNormalIndex.front();
}

// Devuelve el vector de vértices de normales de los vértices para pintarlas 
// como líneas
vector<float> Mesh::getColorNormalVertexVertex(){
    return listColorNormalVertexVertex;    
}

// Devuelve el vector de índices de normales de los vértices para pintarlas 
// como líneas
vector<unsigned int> Mesh::getColorNormalVertexIndex(){
    return listColorNormalVertexIndex;    
}

// Devuelve el vector de vértices de normales de los índices para pintarlas 
// como líneas
vector<float> Mesh::getColorNormalIndexVertex(){
    return listColorNormalIndexVertex;
}

// Devuelve el vector de índices de normales de los índices para pintarlas como 
// líneas
vector<unsigned int> Mesh::getColorNormalIndexIndex(){
    return listColorNormalIndexIndex;
}

// Devuelve el primer vértice del vector de normales de los vértices para 
// pintarlas como líneas
float* Mesh::getFirstColorNormalVertexVertex(){
    return &listColorNormalVertexVertex.front();
}

// Devuelve el primer índice del vector de normales de los vértices para 
// pintarlas como líneas
unsigned int* Mesh::getFirstColorNormalVertexIndex(){
    return &listColorNormalVertexIndex.front();
}

// Devuelve el primer vértice del vector de normales de caras para pintarlas 
// como líneas
float* Mesh::getFirstColorNormalIndexVertex(){
    return &listColorNormalIndexVertex.front();
}

// Devuelve el primer índice del vector de normales de caras para pintarlas 
// como líneas
unsigned int* Mesh::getFirstColorNormalIndexIndex(){
    return &listColorNormalIndexIndex.front();
}

// Devuelve el primer índice de los colores como un puntero
float* Mesh::getFirstColor(){
    return &listColors.front();
}

// Devuelve el primer índice del segundo color como un puntero
float* Mesh::getSecondColor(){
    return &listSecondColors.front();
}

// Devuelve el vector de texturas
vector<float> Mesh::getTexture(){
    return listTexture;
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

// Devuelve el puntero al primer elemento de las texturas
float* Mesh::getFirstTexture(){
    return &listTexture.front();
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

// Establece el vector de texturas
void Mesh::setTexture(vector<float> t){
    this->listTexture = t;
}
