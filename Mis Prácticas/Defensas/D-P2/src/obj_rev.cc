////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 2
//
// obj_rev.cc
//
////////////////////////////////////////////////////////////////////////////////

#include "obj_rev.h"

////////////////////////////////////////////////////////////////////////////////
// Constructor
//
// Crea la geometría del objeto por revolución
//
ObjRev::ObjRev(bool ask) : ObjPLY(false), side(4), topCover(true), bottomCover(true){
        
    if(ask){                
        setFile();        
    }
                        
    // Ángulo en radianes que hay que aplicar a las transformaciones
    alpha = (360 * 3.141592) / (180.0 * side);
        
}

// Crea la geometría del objeto por revolución con un número de caras dadas
ObjRev::ObjRev(bool ask, unsigned int sides) : ObjRev(ask){
        
    // sides debe ser >= 3
    if(sides<3){
        sides = 3;
    }
    
    side = sides;
    
    // Ángulo en radianes que hay que aplicar a las transformaciones
    alpha = (360 * 3.141592) / (180.0 * side);
    
}

// Crea la geometría del objeto por revolución con un número de caras dadas
// y un fichero
ObjRev::ObjRev(string f, unsigned int sides) : ObjRev(false, sides){
    
    setFile(f);
                
}

// Crea la geometría del objeto por revolución con un número de caras dadas
// y un fichero, indicando si se muestran las tapas o no
ObjRev::ObjRev(string f, unsigned int sides, bool top, bool bottom) : 
                ObjRev(f, sides){
    
    topCover = top;
    bottomCover = bottom;
        
}

////////////////////////////////////////////////////////////////////////////
// Crea el perfil del objeto por revolución que se quiere dibujar
//
void ObjRev::createOutline(){
          
}

////////////////////////////////////////////////////////////////////////////////
// Crea el perfil del objeto por revolución que se quiere dibujar
// cogiendo los datos de un fichero PLY
//
void ObjRev::createOutlinePly(){
        
    _file_ply *ply = new _file_ply();
    
    // Si da un error al abrir el fichero
    if(ply->open(getFileChar())==-1){
                
        file = "data/"+file;
        
        if(ply->open(getFileChar())!=-1){
            success();
        }
        
    } else{
        success();
    }
    
    ply->read(listVertexOutline);
            
}

////////////////////////////////////////////////////////////////////////////////
// Crea la geometría del objeto por revolución que se quiere dibujar
//
void ObjRev::createGeometry(){
        
}

// A partir del vector que se recibe con el perfil, obtiene la tapa, la base
// y borra esos elementos del propio vector, para contener solo los puntos
// que se revolucionan.
// Si no tiene que dibujarse la tapa, top y bottom serán null
void ObjRev::setPoints(){
    
}

// Devuelve el número de caras que tiene el modelo
unsigned int ObjRev::getSides(){
    return side;    
}

// Devuelve si se está mostrando la cara superior
bool ObjRev::getTopCover(){
    return topCover;
}
    
// Devuelve si se está mostrando la cara inferior
bool ObjRev::getBottomCover(){
    return bottomCover;
}

////////////////////////////////////////////////////////////////////////////
// Devuelve si un objeto es por revolución o no
//
bool ObjRev::isRev(){
    return true;
}

// Devuelve el tipo de objeto que es
char ObjRev::getType(){
    return type;
}