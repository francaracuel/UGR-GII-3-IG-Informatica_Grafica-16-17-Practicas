////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 3
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
#include <tuple>
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
    
    // Centrar el objeto
    bool center;
    
    // Escala el objeto
    bool scale;
        
    ////////////////////////////////////////////////////////////////////////////
    // Crea la geometría del objeto que se quiere dibujar
    //
    // - virtual permite que el compilador ejecute el método de la clase que
    //   hereda
    //
    virtual void createGeometry();
    
    ////////////////////////////////////////////////////////////////////////////
    // Se centran las coordenadas en el origen
    //
    void centerObject();
    
    ////////////////////////////////////////////////////////////////////////////
    // Se escala el objeto para ocupar la pantalla a buen tamaño
    //
    void scaleObject();
    
    ////////////////////////////////////////////////////////////////////////////
    // Devuelve la malla del objeto
    //
    Mesh getMesh();
    
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
    
    virtual unsigned int getSides();
    
    ////////////////////////////////////////////////////////////////////////////
    // Setters
    //
    
    virtual void setDrawMode(GLenum drawMode);
    
    virtual void setPolygonMode(GLenum polygonMode);
    
    virtual void setChess(bool chess);
    
    void setScale(bool scale);
    
    void setCenter(bool center);
    
    ////////////////////////////////////////////////////////////////////////////
    // Dibuja en la pantalla el objeto 3D
    //
    virtual void draw();
    
    ////////////////////////////////////////////////////////////////////////////
    // Devuelve si un objeto es por revolución o no
    //
    virtual bool isRev();
        
};

#endif