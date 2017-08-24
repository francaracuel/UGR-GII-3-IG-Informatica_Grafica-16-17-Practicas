////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 3
//
// obj_rev.h
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _OBJREV_H
#define _OBJREV_H

#include "obj_ply.h"

class ObjRev : public ObjPLY {
       
public:
               
    ////////////////////////////////////////////////////////////////////////////
    // Getters
    //
    
    // Devuelve el número de caras que tiene el modelo
    unsigned int getSides();
    
    // Devuelve si se está mostrando la cara superior
    bool getTopCover();
    
    // Devuelve si se está mostrando la cara inferior
    bool getBottomCover();
    
    ////////////////////////////////////////////////////////////////////////////
    // Devuelve si un objeto es por revolución o no
    //
    bool isRev();    
    
    // Devuelve el tipo de objeto que es
    char getType();
    
protected:
       
    // Vector que recibe con el perfil
    vector<float> listVertexOutline;
    
    // Tupla de 3 elementos que contiene las coordenadas de la tapa del modelo
    tuple<float, float, float> top;
    
    // Tupla de 3 elementos que contiene las coordenadas de la base del modelo
    tuple<float, float, float> bottom;
    
    // Número de lados que tiene el modelo
    unsigned int side;
    
    // Ángulo en radianes que hay que aplicar a las transformaciones
    float alpha;
    
    // Indica si debe dibujarse la tapa superior del modelo
    bool topCover;
    
    // Indica si debe dibujarse la tapa inferior del modelo
    bool bottomCover;
    
    // Indica el tipo de objeto que es: x,y,z
    char type;
    
    ////////////////////////////////////////////////////////////////////////////
    // Constructor
    //
    // Crea la geometría del objeto por revolución con los parámetros por 
    // defecto
    //
    ObjRev(bool ask);
    
    // Crea la geometría del objeto por revolución con un número de caras dadas
    ObjRev(bool ask, unsigned int sides);
    
    // Crea la geometría del objeto por revolución con un número de caras dadas
    // y un fichero
    ObjRev(string file, unsigned int sides);
    
    // Crea la geometría del objeto por revolución con un número de caras dadas
    // y un fichero, indicando si se muestran las tapas o no
    ObjRev(string file, unsigned int sides, bool top, bool bottom);
    
    ////////////////////////////////////////////////////////////////////////////
    // Crea el perfil del objeto por revolución que se quiere dibujar
    //
    virtual void createOutline();
    
    ////////////////////////////////////////////////////////////////////////////
    // Crea el perfil del objeto por revolución que se quiere dibujar
    // cogiendo los datos de un fichero PLY
    //
    void createOutlinePly();
        
    ////////////////////////////////////////////////////////////////////////////
    // Crea la geometría del objeto por revolución que se quiere dibujar
    //
    virtual void createGeometry();
    
    // A partir del vector que se recibe con el perfil, obtiene la tapa, la base
    // y borra esos elementos del propio vector, para contener solo los puntos
    // que se revolucionan.
    // Si no tiene que dibujarse la tapa, top y bottom serán null
    virtual void setPoints();

};

#endif