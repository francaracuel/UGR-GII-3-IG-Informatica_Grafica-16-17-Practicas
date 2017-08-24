////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 4
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
#include "light.h"
#include "material.h"

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
    
    // Visualización de las normales
    bool normalVertex, normalIndex;
    
    // Visualización con luces
    Light *light;
    
    // Visualización con luces
    Light *light2;
    
    // Tipo de sombreado -> plano: 0, suave: 1
    int shading;
    
    // Material del objeto
    Material *material;
    
        
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
    
private:
    
    
    
public:
    
    ////////////////////////////////////////////////////////////////////////////
    // Constructor
    //
    Obj3D();
    
    Obj3D(float size);
    
    Obj3D(GLenum dMode, GLenum pMode, bool c);
    
    Obj3D(string nameTexture, bool generateAutomatic);
    
    Obj3D(GLenum dMode, GLenum pMode, bool c, string nameTexture, 
        bool generateAutomatic);
    
    ////////////////////////////////////////////////////////////////////////////
    // Getters
    //
    
    GLenum getDrawMode();
    
    GLenum getPolygonMode();
    
    bool getChess();
    
    virtual unsigned int getSides();
        
    bool getNormalVertex();
    
    bool getNormalIndex();
    
    Light* getLight();
    
    Light* getLight2();
    
    bool getActiveLight();
    
    bool getShading();
    
    Material* getMaterial();
    
    ////////////////////////////////////////////////////////////////////////////
    // Setters
    //
    
    virtual void setDrawMode(GLenum drawMode);
    
    virtual void setPolygonMode(GLenum polygonMode);
    
    virtual void setChess(bool chess);
    
    void setScale(bool scale);
    
    void setCenter(bool center);
    
    virtual void setNormalVertex(bool normal);
        
    virtual void setNormalIndex(bool normal);
    
    virtual void setLight(Light *light);
    
    virtual void setLight2(Light *light);
    
    void setActiveLight(bool lightActive);
    
    virtual void setShading(bool shading);
    
    void setMaterial(Material *material);
    
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