////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 1
//
// obj3D.cc
//
////////////////////////////////////////////////////////////////////////////////

#include "obj3D.h"

////////////////////////////////////////////////////////////////////////////////
// Constructor
//
Obj3D::Obj3D():axisSize(50), drawMode(GL_TRIANGLES), polygonMode(GL_LINE), chess(false){
 
}

Obj3D::Obj3D(float aS):axisSize(aS), drawMode(GL_TRIANGLES), polygonMode(GL_LINE), chess(false){
    
}

Obj3D::Obj3D(GLenum dMode, GLenum pMode, bool c):axisSize(50), drawMode(dMode), polygonMode(pMode), chess(c){
    
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

////////////////////////////////////////////////////////////////////////////////
// Crea la geometría del objeto que se quiere dibujar
//
void Obj3D::createGeometry(){
    
}

////////////////////////////////////////////////////////////////////////////////
// Dibuja en la pantalla el objeto 3D
//
void Obj3D::draw(){
                    
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