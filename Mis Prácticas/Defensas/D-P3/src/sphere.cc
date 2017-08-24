////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 3
//
// sphere.cc
//
////////////////////////////////////////////////////////////////////////////////

#include "sphere.h"

////////////////////////////////////////////////////////////////////////////////
// Constructor
//
// Crea la geometría del objeto por revolución con un número de caras dadas
Sphere::Sphere(unsigned int sides) : ObjRev(false, sides){
    
    init();
    
}

// Crea la geometría del objeto por revolución con un número de caras dadas
// y unos colores
Sphere::Sphere(unsigned int sides, vector<float> colors) : ObjRev(false, sides){
    
    init();
    
    mesh->setColors(colors);
    
}

////////////////////////////////////////////////////////////////////////////////
// Inicializa todos los datos necesarios
//
void Sphere::init(){
    
    type = 'x';
    
    createOutline();
                                
    createGeometry();
    
}

////////////////////////////////////////////////////////////////////////////////
// Crea el perfil del objeto por revolución que se quiere dibujar
//
void Sphere::createOutline(){
    
    // Perfil del modelo       
    
    float x = 0;
    float y = 0.5;
    float z = 0;
    
    float auxX = 0;
    
    // Por cada punto del perfil crea los restantes de su mismo eje Y por
    // revolución
    for(unsigned int j=0; j<side; j++){

        listVertexOutline.push_back(x);
        listVertexOutline.push_back(y);
        listVertexOutline.push_back(z);

        auxX = x;

        x = cos(alpha)*x-sin(alpha)*y;                
        y = sin(alpha)*auxX+cos(alpha)*y;

    }
    
}

////////////////////////////////////////////////////////////////////////////////
// Crea la geometría del objeto por revolución que se quiere dibujar
//
void Sphere::createGeometry(){
        
    // Se crea el vector de vértices 
    vector<float> listVertex;
    
    // Se sacan las primeras coordenadas para trabajar con ellas y 
    // transformarlas
    float x;
    float y;
    float z;
    
    float auxX;
    
    // Recorre todo el vector de puntos del perfil    
    for(unsigned int i=0; i<listVertexOutline.size(); i=i+3){
            
        x = listVertexOutline[i];
        y = listVertexOutline[i+1];
        z = listVertexOutline[i+2];
        
        //cout << "Nuevo anillo de puntos\n";
        
        // Por cada punto del perfil crea los restantes de su mismo eje Y por
        // revolución
        for(unsigned int j=0; j<side; j++){

            //std::cout << "X: " << x << " Y: " << y << "Z: " << z << std::endl;
            
            // 1
            listVertex.push_back(x);
            listVertex.push_back(y);
            listVertex.push_back(z);

            auxX = x;

            x = cos(alpha)*x+sin(alpha)*z;                
            z = -sin(alpha)*auxX+cos(alpha)*z;

        }
              
    }
    
    // Se crea el vector de índices
    vector<unsigned int> listIndex;
    
    //std::cout << "Número de vértices en el perfil: " << listVertexOutline.size() << std::endl;
        
    //std::cout << "Vértice perfil * lados: " << side*(listVertexOutline.size()/3)+side << std::endl;
    
    for(unsigned int i=side; i<side*(listVertexOutline.size()/3); i++){
        
        if(i%side==0){
            
            
            listIndex.push_back(i-side);
            listIndex.push_back(i-1);
            listIndex.push_back(i);
            
            
            listIndex.push_back(i-1);
            listIndex.push_back(i+side-1);
            listIndex.push_back(i);
            
        } else{
                        
            listIndex.push_back(i-side);
            listIndex.push_back(i-side-1);
            listIndex.push_back(i);
            
            listIndex.push_back(i-side-1);
            listIndex.push_back(i-1);
            listIndex.push_back(i);
            
        }
        
    }
                
    mesh = new Mesh(listVertex.size()/3, listIndex.size(), listVertex, listIndex, 30, 182, 129, 182, 30, 83, axisSize);
        
}
