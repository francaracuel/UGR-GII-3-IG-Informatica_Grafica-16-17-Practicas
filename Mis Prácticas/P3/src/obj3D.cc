////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 3
//
// obj3D.cc
//
////////////////////////////////////////////////////////////////////////////////

#include "obj3D.h"

#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Constructor
//
Obj3D::Obj3D():axisSize(50), drawMode(GL_TRIANGLES), polygonMode(GL_LINE), chess(false), center(false), scale(false){
 
}

Obj3D::Obj3D(float aS):axisSize(aS), drawMode(GL_TRIANGLES), polygonMode(GL_LINE), chess(false), center(false), scale(false){
    
}

Obj3D::Obj3D(GLenum dMode, GLenum pMode, bool c):axisSize(50), drawMode(dMode), polygonMode(pMode), chess(c), center(false), scale(false){
    
}

////////////////////////////////////////////////////////////////////////////////
// Getters
//
    
GLenum Obj3D::getDrawMode(){
    return drawMode;
}

GLenum Obj3D::getPolygonMode(){
    return polygonMode;
}

bool Obj3D::getChess(){
    return chess;
}

Mesh Obj3D::getMesh(){
    return *mesh;
}
    
////////////////////////////////////////////////////////////////////////////////
// Setters
//
    
void Obj3D::setDrawMode(GLenum drawMode){
    this->drawMode = drawMode;
}

void Obj3D::setPolygonMode(GLenum polygonMode){
    this->polygonMode = polygonMode;
}

void Obj3D::setChess(bool chess){
    this->chess = chess;
}

void Obj3D::setScale(bool s){
    this->scale = s;
}

void Obj3D::setCenter(bool c){
    this->center = c;
}

////////////////////////////////////////////////////////////////////////////////
// Crea la geometría del objeto que se quiere dibujar
//
void Obj3D::createGeometry(){
    
}

////////////////////////////////////////////////////////////////////////////////
// Dibuja en la pantalla el objeto 3D
//
void Obj3D::draw(){
           
    // Se escala el objeto
    if(scale)
        scaleObject();   
    
    // Se centra el objeto en el origen
    if(center)
        centerObject();
                        
    // Se habilita la opción de enviar los vértices como un array
    glEnableClientState(GL_VERTEX_ARRAY);
    
    // Se envía el array de vértices
    glVertexPointer(3, GL_FLOAT, 0, mesh->getFirstVertex());
    
    // Se habilita la opción de enviar los colores como un array
    glEnableClientState(GL_COLOR_ARRAY);
    
    // Se envía el array de colores
    glColorPointer(3, GL_FLOAT, 0, mesh->getFirstColor());
    
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
    
    glPointSize(10);
    
    // Puntos, alambre o caras
    if(!chess){
            
        // Se envía el array de índices a los vértices
        glDrawElements(drawMode, mesh->getNumIndex(), GL_UNSIGNED_INT, mesh->getFirstIndex());
        
    // Ajedrez
    } else{
        
        // Se envía el array de índices a los vértices
        glDrawElements(drawMode, mesh->getNumIndex()/2, GL_UNSIGNED_INT, mesh->getFirstEvenIndex());

        // Se envía el array de colores
        glColorPointer(3, GL_FLOAT, 0, mesh->getSecondColor());

        // Se envía el array de índices a los vértices
        glDrawElements(drawMode, mesh->getNumIndex()/2, GL_UNSIGNED_INT, mesh->getFirstOddIndex());
        
    }
           
}

////////////////////////////////////////////////////////////////////////////
// Se centran las coordenadas en el origen
//
void Obj3D::centerObject(){
        
//    cout << endl << "Las coordenadas son: " << endl;
//    
//    cout << "Máx X: " << get<0>(mesh->getMaxPoints()) << " ; Y: " << get<1>(mesh->getMaxPoints()) << " ; Z: " << get<2>(mesh->getMaxPoints()) << endl;
//    
//    cout << endl;
//    
//    cout << "Mín X: " << get<0>(mesh->getMinPoints()) << " ; Y: " << get<1>(mesh->getMinPoints()) << " ; Z: " << get<2>(mesh->getMinPoints()) << endl;
    
    tuple <float, float, float> diff = mesh->getDiffCenter();
    
//    cout << "La diferencia entre x es: " << get<0>(diff) << endl;
//    
//    cout << "La diferencia entre y es: " << get<1>(diff) << endl;
//    
//    cout << "La diferencia entre z es: " << get<2>(diff) << endl;
        
    glTranslatef(get<0>(diff), get<1>(diff), get<2>(diff));
    
}

////////////////////////////////////////////////////////////////////////////
// Se escala el objeto para ocupar la pantalla a buen tamaño
//
void Obj3D::scaleObject(){
       
    float scale = mesh->getScaleValue();
        
//    cout << "Se debe multiplicar por: " << scale << endl;
    
    glScaled(scale, scale, scale);
                
}

// Devuelve el número de caras que tiene el modelo
unsigned int Obj3D::getSides(){
    return 0;    
}

////////////////////////////////////////////////////////////////////////////
// Devuelve si un objeto es por revolución o no
//
bool Obj3D::isRev(){
    return false;
}
