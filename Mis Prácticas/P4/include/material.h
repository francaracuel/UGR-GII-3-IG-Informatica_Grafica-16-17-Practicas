////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 4
//
// material.h
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <string>
#include <vector>
#include <GL/glut.h>
#include <GL/gl.h>
#include "texture.h"

using namespace std;

class Material{
    
private:
    
    // Activo
    bool active;
    
    // Emisividad del material
    vector<GLfloat> emission;
    
    // Ambiental
    vector<GLfloat> ambient;
    
    // Difusa
    vector<GLfloat> diffuse;
    
    // Especular
    vector<GLfloat> specular;
    
    // Exponente de brillo
    GLfloat shininess;
    
    // Puntero a la textura
    Texture *texture;
    
    ////////////////////////////////////////////////////////////////////////////
    // Utils
    //
    void init();
    
public:
    
    ////////////////////////////////////////////////////////////////////////////
    // Constructores
    //        
    Material();
    
    Material(string nameTexture, bool generateAutomatic);
    
    ////////////////////////////////////////////////////////////////////////////
    // Getters
    //
    bool getActive();
    
    vector<GLfloat> getEmission();
    
    vector<GLfloat> getAmbient();
    
    vector<GLfloat> getDiffuse();
    
    vector<GLfloat> getSpecular();
    
    GLfloat getShininess();
    
    Texture* getTexture();
    
    ////////////////////////////////////////////////////////////////////////////
    // Setters
    //
    void setActive(bool active);
    
    void setEmission(vector<GLfloat> emission);
    
    void setAmbient(vector<GLfloat> ambient);
    
    void setDiffuse(vector<GLfloat> diffuse);
    
    void setSpecular(vector<GLfloat> specular);
    
    void setShininess(GLfloat shininess);
    
    void setTexture(Texture *texture);
    
    ////////////////////////////////////////////////////////////////////////////
    // Utils
    //
    void apply();
        
};

#endif