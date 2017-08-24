////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 5
//
// texture.cc
//
////////////////////////////////////////////////////////////////////////////////

#include "texture.h"

////////////////////////////////////////////////////////////////////////////
// Constructor
//
Texture::Texture() : active(false){
        
}

Texture::Texture(string name, bool generateAutomatic) : active(true), 
        automatic(generateAutomatic){
      
    image = new jpg::Imagen("./data/"+name);
                
    // Se genera el identificador    
    glGenTextures(1, &idTex);
        
}

////////////////////////////////////////////////////////////////////////////
// Getters
//
bool Texture::getActive(){
    return active;
}

unsigned char* Texture::getPixels(){
    return pixels;
}

unsigned int Texture::getIdTex(){
    return idTex;
}

bool Texture::getAutomatic(){
    return automatic;
}

float* Texture::getAut1(){
    return aut1;
}

float* Texture::getAut2(){
    return aut2;
}

////////////////////////////////////////////////////////////////////////////////
// Setters
//
void Texture::setActive(bool a){
    active = a;
}

////////////////////////////////////////////////////////////////////////////////
// Utils
//
void Texture::apply(){
    
    if(active){
    
        if(!automatic){

            // Se deshabilitan las texturas automáticas por si se encuentran 
            // habilitadas
            glDisable(GL_TEXTURE_GEN_S);
            glDisable(GL_TEXTURE_GEN_T);

        } else{

            // Se habilita el vector de coordenadas
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);

            // Se habilitan las texturas automáticas
            glEnable(GL_TEXTURE_GEN_S);
            glEnable(GL_TEXTURE_GEN_T);

            // Se generan las coordenadas automáticas
            glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
            glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

        }

        // Se habilitan las texturas
        glEnable(GL_TEXTURE_2D);

        // Se activa esta textura en concreto
        glBindTexture(GL_TEXTURE_2D, idTex);

        // Cómo se usa el color de los texels con la iluminación activada
        glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

        // Cómo se selecciona el texel a partir de una coordenada de textura
        // Magnificación
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Minificación
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Cuando las coordenadas de textura no están en el rango [0,1][0,1]
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Se construye la textura
        gluBuild2DMipmaps(GL_TEXTURE_2D,
                            GL_RGB,
                            image->tamX(),
                            image->tamY(),
                            GL_RGB,
                            GL_UNSIGNED_BYTE,
                            image->leerPixels());
        
    } else{
        
        // Se deshabilitan las texturas
        glDisable(GL_TEXTURE_2D);
        
    }
    
}