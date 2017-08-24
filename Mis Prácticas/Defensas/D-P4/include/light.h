////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 4
//
// light.h
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _LIGHT_H
#define _LIGHT_H

#include <tuple>
#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

class Light{
    
private:
    
    // Guarda si está activa o no la fuente de luz
    bool active;
    
    // Número de la luz
    int number;
    
    // Color de la fuente de luz
    tuple<float, float, float> rgb;
    
    // Tipo: 0 -> posicional, 1 -> direccional
    int type;
    
    // Coordenadas de la posicional
    tuple<float, float, float> pos;
    
    // Coordenadas de la direccional
    tuple<float, float, float> dir;
    
    // Si la fuente es direccional tendrá los ñangulos para el vector de
    // dirección
    float alpha;
    float beta;
    
    bool defensa4;
    
    // Ambiental
    vector<GLfloat> ambient;
    
    // Difusa
    vector<GLfloat> diffuse;
    
    // Especular
    vector<GLfloat> specular1;
    vector<GLfloat> specular2;
    vector<GLfloat> specular;
    
public:
    
    ////////////////////////////////////////////////////////////////////////////
    // Constructores
    //
    Light(bool active);
    
    Light(bool active, int n);
    
    ////////////////////////////////////////////////////////////////////////////
    // Operadores
    //
    Light& operator=(const Light& l);
    
    ////////////////////////////////////////////////////////////////////////////
    // Getters
    //
    bool getActive();
    
    tuple<float, float, float> getRgb();
    
    int getType();
    
    tuple<float, float, float> getPos();
    
    tuple<float, float, float> getDir();
    
    float getAlpha();
    
    float getBeta();
    
    bool getDefensa4();
    
    ////////////////////////////////////////////////////////////////////////////
    // Setters
    //
    void setActive(bool active);
    
    void setRgb(float r, float g, float b);
    
    void setType(int type);
    
    void setPos(float x, float y, float z);
    
    void setDir(float x, float y, float z);
    
    void setAlpha(float alpha);
    
    void setBeta(float beta);
    
    void setAmbient(vector<GLfloat> ambient);
    
    void setDiffuse(vector<GLfloat> diffuse);
    
    void setSpecular(vector<GLfloat> specular);
    
    void setDefensa4(bool d);
    
    ////////////////////////////////////////////////////////////////////////////
    // Utils
    //
    void apply();
    
};

#endif