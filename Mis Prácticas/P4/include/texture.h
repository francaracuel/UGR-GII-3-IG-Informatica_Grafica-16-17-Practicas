////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 4
//
// texture.h
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <string>
#include <GL/glut.h>
#include <GL/gl.h>
#include "jpg_imagen.hpp"

using namespace std;

class Texture{
    
private:
    
    // Si se encuentra activada la textura
    bool active;
           
    // Puntero a los pixels en memoria dinámica
    unsigned char* pixels;
    
    jpg::Imagen *image;
    
    // Identificador de textura en OpenGL
    GLuint idTex;
    
    // Indica si hay generación automática de coordenadas de textura
    bool automatic;
    
    // Dos arrays de 4 flotantes para la generación automática de texturas
    float aut1[4];
    float aut2[4];
        
public:
    
    ////////////////////////////////////////////////////////////////////////////
    // Constructor
    //
    Texture();
    
    Texture(string name, bool generateAutomatic);
    
    ////////////////////////////////////////////////////////////////////////////
    // Getters
    //
    bool getActive();
    
    unsigned char* getPixels();
    
    GLuint getIdTex();
    
    bool getAutomatic();
    
    float* getAut1();
    
    float* getAut2();
    
    ////////////////////////////////////////////////////////////////////////////
    // Setters
    //
    void setActive(bool active);
    
    ////////////////////////////////////////////////////////////////////////////
    // Utils
    //
    void apply();
        
};

#endif