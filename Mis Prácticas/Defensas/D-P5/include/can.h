////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 5
//
// can.h
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _CAN_H
#define _CAN_H

#include <vector>
#include <tuple>
#include "obj_rev_x.h"
#include "obj_rev_y.h"
#include "obj_rev_z.h"

class Can : public Obj3D {
    
private:
    
    vector<Obj3D*> listObj;  
    
public:
    
    ////////////////////////////////////////////////////////////////////////////
    // Constructor
    //
    Can();   
    
    Can(string name, bool generateAutomatic);
    
    ////////////////////////////////////////////////////////////////////////////
    // Getters
    //
    vector<Obj3D*> getListObj();
    
    ////////////////////////////////////////////////////////////////////////////
    // Setters
    //
    
    void setDrawMode(GLenum drawMode);
    
    void setPolygonMode(GLenum polygonMode);
    
    void setChess(bool chess);
    
    void setNormalVertex(bool normal);
        
    void setNormalIndex(bool normal);
    
    void setLight(Light *light);
    
    void setLight2(Light *light);
    
    virtual void setShading(bool shading);    
        
    ////////////////////////////////////////////////////////////////////////////
    // Dibuja todo el objeto
    //
    void draw();
        
private:
    
    ////////////////////////////////////////////////////////////////////////////
    // Inicializa todos los valores necesarios
    //
    void init(); 
    
    void init(string name, bool generateAutomatic);            
    
    ////////////////////////////////////////////////////////////////////////////
    // Setters 
    // 
    
    // Asigna una textura a todos los objetos por igual (menos a los ojos)
    void setTexture(string name, bool generateAutomatic);

};

#endif