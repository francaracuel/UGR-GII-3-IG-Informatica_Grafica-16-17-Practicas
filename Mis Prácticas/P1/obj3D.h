////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 1
//
// obj3D.h
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _OBJ3D_H
#define _OBJ3D_H

#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "mesh.h"

class Obj3D{
    
protected:
    
    // Clase malla (mesh) donde estará la estructura de los objetos
    Mesh *mesh;
    
    // Tamaño de los segmentos de rectas
    float axisSize;
    
    // Modo de visualización del objeto 3D para glDrawElements
    GLenum drawMode;
    
    // Modo de visualización del objeto 3D para glPolygonMode
    GLenum polygonMode;
    
    // Controla si se dibuja en modo ajedrez o no
    bool chess;
    
public:
    
    ////////////////////////////////////////////////////////////////////////////
    // Constructor
    //
    Obj3D();
    
    Obj3D(float size);
    
    Obj3D(GLenum dMode, GLenum pMode, bool c);
    
    ////////////////////////////////////////////////////////////////////////////
    // Getters
    //
    
    GLenum getDrawMode();
    
    GLenum getPolygonMode();
    
    bool getChess();
    
    ////////////////////////////////////////////////////////////////////////////
    // Setters
    //
    
    void setDrawMode(GLenum drawMode);
    
    void setPolygonMode(GLenum polygonMode);
    
    void setChess(bool chess);
    
    ////////////////////////////////////////////////////////////////////////////
    // Crea la geometría del objeto que se quiere dibujar
    //
    // - virtual permite que el compilador ejecute el método de la clase que
    //   hereda
    //
    virtual void createGeometry();
    
    ////////////////////////////////////////////////////////////////////////////
    // Dibuja en la pantalla el objeto 3D
    //
    void draw();
        
};

#endif