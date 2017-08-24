////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 5
//
// can.cc
//
////////////////////////////////////////////////////////////////////////////////

#include "can.h"

////////////////////////////////////////////////////////////////////////////////
// Constructor
//
Can::Can(){
    
    init();
    
}

Can::Can(string name, bool generateAutomatic) : Can(){
    
    listObj[1]->getMaterial()->setTexture(new Texture(name, generateAutomatic));
    
}

////////////////////////////////////////////////////////////////////////////////
// Inicializa todos los valores necesarios
//
void Can::init(){
   
    // 0 Tapa superior
    listObj.push_back(new ObjRevX("lata-s.ply", 50, true, true));
    
    // 1 Cuerpo
    listObj.push_back(new ObjRevX(50, "lata.ply", false, false, "lata.jpg", false));
    
    // 2 Tapa inferior
    listObj.push_back(new ObjRevX("lata-i.ply", 50, true, true));
        
}

////////////////////////////////////////////////////////////////////////////////
// Getters
//
vector<Obj3D*> Can::getListObj(){
    return listObj;
}

////////////////////////////////////////////////////////////////////////////////
// Setters
//

void Can::setDrawMode(GLenum drawMode){
    
    this->drawMode = drawMode;
    
    for(unsigned int i=0; i<listObj.size(); i++){
        listObj[i]->setDrawMode(drawMode);
    }
    
}

void Can::setPolygonMode(GLenum polygonMode){
    
    this->polygonMode = polygonMode;
    
    for(unsigned int i=0; i<listObj.size(); i++){
        listObj[i]->setPolygonMode(polygonMode);
    }
    
}

void Can::setChess(bool chess){
    
    this->chess = chess;
    
    for(unsigned int i=0; i<listObj.size(); i++){
        listObj[i]->setChess(chess);
    }
    
}

void Can::setNormalVertex(bool n){
    
    this->normalVertex = n;
    
    for(unsigned int i=0; i<listObj.size(); i++){
        listObj[i]->setNormalVertex(n);
    }
    
}

void Can::setNormalIndex(bool n){
    
    this->normalIndex = n;
    
    for(unsigned int i=0; i<listObj.size(); i++){
        listObj[i]->setNormalIndex(n);
    }
    
}

void Can::setLight(Light *l){
    
    this->light = l;
    
    for(unsigned int i=0; i<listObj.size(); i++){
            listObj[i]->setLight(l);
    }
    
}

void Can::setLight2(Light *l){
    
    this->light2 = l;
    
    for(unsigned int i=0; i<listObj.size(); i++){
            listObj[i]->setLight2(l);
    }
    
}

void Can::setShading(bool s){
    
    this->shading = s;
    
    for(unsigned int i=0; i<listObj.size(); i++){
        listObj[i]->setShading(s);
    }
    
}

////////////////////////////////////////////////////////////////////////////////
// Dibuja el objeto completo
//
void Can::draw(){
        
    glScaled(axisSize*3, axisSize*3, axisSize*3);
    
    // Tapa superior
    glPushMatrix();
        
        listObj[0]->draw();
        
    glPopMatrix();
    
    // Cuerpo
    glPushMatrix();
            
        listObj[1]->draw();
        
    glPopMatrix();
    
    // Tapa inferior
    glPushMatrix();
    
                
        listObj[2]->draw();
        
    glPopMatrix();
    
    
}

// Asigna una textura a todos los objetos por igual (menos a los ojos)
void Can::setTexture(string name, bool generateAutomatic){
    
    for(unsigned int i=0; i<listObj.size(); i++){
            listObj[i]->getMaterial()->setTexture(new Texture(name, generateAutomatic));
    }
    
}