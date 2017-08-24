////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 4
//
// sphere.h
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _SPHERE_H
#define _SPHERE_H

#include "obj_rev.h"
#include <vector>

class Sphere : public ObjRev {
    
private:
    
    ////////////////////////////////////////////////////////////////////////////
    // Inicializa todos los datos necesarios
    //
    void init();
                   
public:
    
    ////////////////////////////////////////////////////////////////////////////
    // Constructor
    //    
    // Crea la geometría del objeto por revolución con un número de caras dadas
    Sphere(unsigned int sides);
    
    // Crea la geometría del objeto por revolución con un número de caras dadas
    // y unos colores
    Sphere(unsigned int sides, vector<float> colors);
    
    // Crea la geometría del objeto por revolución con un número de caras dadas
    Sphere(unsigned int sides, string nameTexture, bool generateAutomatic);
   
    ////////////////////////////////////////////////////////////////////////////
    // Crea el perfil del objeto por revolución que se quiere dibujar
    //
    void createOutline();
            
    ////////////////////////////////////////////////////////////////////////////
    // Crea la geometría del objeto por revolución que se quiere dibujar
    //
    void createGeometry();  

};

#endif