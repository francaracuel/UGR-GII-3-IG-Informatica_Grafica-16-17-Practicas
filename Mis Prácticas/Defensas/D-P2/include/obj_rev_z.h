////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 2
//
// obj_rev_z.h
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _OBJREVZ_H
#define _OBJREVZ_H

#include "obj_rev.h"

class ObjRevZ : public ObjRev {
    
private:
    
    ////////////////////////////////////////////////////////////////////////////
    // Inicializa todos los datos necesarios
    //
    void init();
            
    // A partir del vector que se recibe con el perfil, obtiene la tapa, la base
    // y borra esos elementos del propio vector, para contener solo los puntos
    // que se revolucionan.
    // Si no tiene que dibujarse la tapa, top y bottom serán null
    void setPoints();
       
public:
    
    ////////////////////////////////////////////////////////////////////////////
    // Constructor
    //
    // Crea la geometría del objeto por revolución con los parámetros por 
    // defecto
    //
    ObjRevZ(bool ask);
    
    // Crea la geometría del objeto por revolución con un número de caras dadas
    ObjRevZ(bool ask, unsigned int sides);
    
    // Crea la geometría del objeto por revolución con un número de caras dadas
    // y un fichero
    ObjRevZ(string file, unsigned int sides);
    
    // Crea la geometría del objeto por revolución con un número de caras dadas
    // y un fichero, indicando si se muestran las tapas o no
    ObjRevZ(string file, unsigned int sides, bool top, bool bottom);
    
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