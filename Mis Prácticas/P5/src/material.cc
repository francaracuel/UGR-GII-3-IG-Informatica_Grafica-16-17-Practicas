////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 5
//
// material.cc
//
////////////////////////////////////////////////////////////////////////////////

#include "material.h"

////////////////////////////////////////////////////////////////////////////////
// Constructores
//
Material::Material() : active(true), texture(new Texture()){
    
    init();
    
}

Material::Material(string nameTexture, bool generateAutomatic) : active(true),
    texture(new Texture(nameTexture, generateAutomatic)){
    
    init();
        
}

////////////////////////////////////////////////////////////////////////////////
// Getters
//
bool Material::getActive(){
    return active;
}

vector<GLfloat> Material::getAmbient(){
    return ambient;
}

vector<GLfloat> Material::getDiffuse(){
    return diffuse;
}

vector<GLfloat> Material::getSpecular(){
    return specular;
}

GLfloat Material::getShininess(){
    return shininess;
}

Texture* Material::getTexture(){
    return texture;
}

////////////////////////////////////////////////////////////////////////////
// Utils
//
void Material::init(){
    
    // Emisividad
    emission.push_back(0.0);
    emission.push_back(0.0);
    emission.push_back(0.0);
    emission.push_back(1.0);
    
    // Ambiental
    ambient.push_back(0.2);
    ambient.push_back(0.2);
    ambient.push_back(0.2);
    ambient.push_back(1.0);
    
    // Difusa
    diffuse.push_back(0.8);
    diffuse.push_back(0.8);
    diffuse.push_back(0.8);
    diffuse.push_back(1.0);
    
    // Especular
    specular.push_back(0.0);
    specular.push_back(0.0);
    specular.push_back(0.0);
    specular.push_back(1.0);
    
    // Exponente de brillo
    shininess = 0.0;
    
}

////////////////////////////////////////////////////////////////////////////
// Setters
//
void Material::setActive(bool a){
    active = a;
}

void Material::setEmission(vector<GLfloat> e){
    emission = e;
}
    
void Material::setAmbient(vector<GLfloat> a){
    ambient = a;
}

void Material::setDiffuse(vector<GLfloat> d){
    diffuse = d;
}

void Material::setSpecular(vector<GLfloat> s){
    specular = s;
}

void Material::setShininess(GLfloat s){
    shininess = s;
}

void Material::setTexture(Texture *t){
    texture = t;
}

void Material::apply(){
            
    // Si está activo se le aplican los materiales
    if(true){
                
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &emission.front());
        
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &ambient.front());
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &diffuse.front());
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &specular.front());
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
        
        glEnable(GL_SMOOTH);
        
	glShadeModel(GL_SMOOTH);
        
    }
    
    // Se le aplica las texturas
    texture->apply();
        
}