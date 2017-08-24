////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 4
//
// obj3D.cc
//
////////////////////////////////////////////////////////////////////////////////

#include "obj3D.h"

#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Constructor
//
Obj3D::Obj3D():axisSize(50), drawMode(GL_TRIANGLES), polygonMode(GL_LINE), 
        chess(false), center(false), scale(false), normalVertex(false),
        normalIndex(false), shading(0), light(new Light(true)),
        light2(new Light(true, 1)), material(new Material()){
    
}

Obj3D::Obj3D(float aS):axisSize(aS), drawMode(GL_TRIANGLES), 
        polygonMode(GL_LINE), chess(false), center(false), scale(false), 
        normalVertex(false), normalIndex(false), shading(0), 
        light(new Light(true)), light2(new Light(true, 1)), 
        material(new Material()){
   
}

Obj3D::Obj3D(GLenum dMode, GLenum pMode, bool c):axisSize(50), drawMode(dMode), 
        polygonMode(pMode), chess(c), center(false), scale(false), 
        normalVertex(false), normalIndex(false), shading(0), 
        light(new Light(true)), light2(new Light(true, 1)), 
        material(new Material()){
  
}

Obj3D::Obj3D(string nameTexture, bool generateAutomatic): Obj3D(){
        
    material = new Material(nameTexture, generateAutomatic);
    
}

Obj3D::Obj3D(GLenum dMode, GLenum pMode, bool c, string nameTexture, 
        bool generateAutomatic): Obj3D(dMode, pMode, c){
        
    material = new Material(nameTexture, generateAutomatic);
    
}

////////////////////////////////////////////////////////////////////////////////
// Getters
//
    
GLenum Obj3D::getDrawMode(){
    return drawMode;
}

GLenum Obj3D::getPolygonMode(){
    return polygonMode;
}

bool Obj3D::getChess(){
    return chess;
}

Mesh Obj3D::getMesh(){
    return *mesh;
}

bool Obj3D::getNormalVertex(){
    return normalVertex;
}

bool Obj3D::getNormalIndex(){
    return normalIndex;
}

Light* Obj3D::getLight(){
    return light;
}

Light* Obj3D::getLight2(){
    return light2;
}

bool Obj3D::getActiveLight(){
    return light->getActive();
}

bool Obj3D::getShading(){
    return shading;
}

Material* Obj3D::getMaterial(){
    return material;
}
    
////////////////////////////////////////////////////////////////////////////////
// Setters
//
    
void Obj3D::setDrawMode(GLenum drawMode){
    this->drawMode = drawMode;
}

void Obj3D::setPolygonMode(GLenum polygonMode){
    this->polygonMode = polygonMode;
}

void Obj3D::setChess(bool chess){
    this->chess = chess;
}

void Obj3D::setScale(bool s){
    this->scale = s;
}

void Obj3D::setCenter(bool c){
    this->center = c;
}

void Obj3D::setNormalVertex(bool n){
    this->normalVertex = n;
}

void Obj3D::setNormalIndex(bool n){
    this->normalIndex = n;
}

void Obj3D::setLight(Light *l){
    this->light = l;
}

void Obj3D::setLight2(Light *l){
    this->light2 = l;
}

void Obj3D::setActiveLight(bool lightActive){
    light->setActive(lightActive);
    light2->setActive(lightActive);
}

void Obj3D::setShading(bool s){
    this->shading = s;
}

void Obj3D::setMaterial(Material *m){
    this->material = m;
}

////////////////////////////////////////////////////////////////////////////////
// Crea la geometría del objeto que se quiere dibujar
//
void Obj3D::createGeometry(){
    
}

////////////////////////////////////////////////////////////////////////////////
// Dibuja en la pantalla el objeto 3D
//
void Obj3D::draw(){
            
    // Se aplica (o no) la luz
    light->apply();
    
    light2->apply();
    
    // Se le aplica el material y como consecuencia las texturas, si procede
    material->apply();
    
    // Si la generación de coordenadas de textura no es automática, se asignan
    if(!material->getTexture()->getAutomatic()){
        
        // Se asigna el vector de coordenadas
        glTexCoordPointer(2, GL_FLOAT, 0, mesh->getFirstTexture());
    
        // Se habilita el vector de coordenadas
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        
    }
           
    // Se escala el objeto
    if(scale)
        scaleObject();   
    
    // Se centra el objeto en el origen
    if(center)
        centerObject();
                        
    // Se habilita la opción de enviar los vértices como un array
    glEnableClientState(GL_VERTEX_ARRAY);
    
    // Se envía el array de vértices
    glVertexPointer(3, GL_FLOAT, 0, mesh->getFirstVertex());
    
    // Se habilita la opción de enviar los colores como un array
    glEnableClientState(GL_COLOR_ARRAY);
    
    // Se envía el array de colores
    glColorPointer(3, GL_FLOAT, 0, mesh->getFirstColor());
    
    // Se habilita el envío de normales
    glEnableClientState( GL_NORMAL_ARRAY );

    // Sombreado plano
    if(shading==0){
        
        // Se le envían las normales de las caras del objeto
        glNormalPointer(GL_FLOAT, 0, mesh->getFirstNormalIndex());
        
        glShadeModel(GL_FLAT);        
        
    // Sombreado suave
    } else{
        
        // Se le envían las normales de los vértices del objeto
        glNormalPointer(GL_FLOAT, 0, mesh->getFirstNormalVertex());
        
        glShadeModel(GL_SMOOTH);
        
    }
    
    // Se habilita que opengl se encargue de las normales en las 
    // transformaciones
    glEnable(GL_NORMALIZE);
    
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
    
    glPointSize(10);
            
    // Puntos, alambre o caras
    if(!chess){
            
        // Se envía el array de índices a los vértices
        glDrawElements(drawMode, mesh->getNumIndex(), GL_UNSIGNED_INT, mesh->getFirstIndex());
        
    // Ajedrez
    } else{
        
        // Se envía el array de índices a los vértices
        glDrawElements(drawMode, mesh->getNumIndex()/2, GL_UNSIGNED_INT, mesh->getFirstEvenIndex());

        // Se envía el array de colores
        glColorPointer(3, GL_FLOAT, 0, mesh->getSecondColor());

        // Se envía el array de índices a los vértices
        glDrawElements(drawMode, mesh->getNumIndex()/2, GL_UNSIGNED_INT, mesh->getFirstOddIndex());
        
    }    
    
    // Si se pintan las normales de los vértices del objeto
    if(normalVertex){
 
        // Se apagan las luces, porque se quiere pintar de color las normales
        glDisable(GL_LIGHTING);        
        glDisable(GL_TEXTURE_2D);
        
        // Se deshabilita el array de colores, porque en este caso se va a
        // pintar con glColor3ub
        glDisableClientState(GL_COLOR_ARRAY);
        
        glColor3ub(101, 41, 219);
        
        // Se le mandan los vértices de las normales
        glVertexPointer(3, GL_FLOAT, 0, mesh->getFirstColorNormalVertexVertex());
        
        // Se pintan las normales. Al tener solo 2 vértices por línea, el número
        // de vértices será 2/3 del número de índices
        glDrawElements(GL_LINES, mesh->getColorNormalVertexIndex().size(), GL_UNSIGNED_INT, mesh->getFirstColorNormalVertexIndex());
        
        // Se vuelve a habilitar el array de colores
        glEnableClientState(GL_COLOR_ARRAY);
        
        // Se vuelven a encender la luces
        glEnable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        
    }
       
    // Si se pintan las normales de las caras del objeto
    if(normalIndex){
        
        // Se apagan las luces, porque se quiere pintar de color las normales
        glDisable(GL_LIGHTING);  
        glDisable(GL_TEXTURE_2D);
        
        // Se deshabilita el array de colores, porque en este caso se va a
        // pintar con glColor3ub
        glDisableClientState(GL_COLOR_ARRAY);
        
        glColor3ub(159, 219, 41);
        
        // Se le mandan los vértices de las normales
        glVertexPointer(3, GL_FLOAT, 0, mesh->getFirstColorNormalIndexVertex());
        
        // Se pintan las normales. Al tener solo 2 vértices por línea, el número
        // de vértices será 2/3 del número de índices
        glDrawElements(GL_LINES, mesh->getColorNormalIndexIndex().size(), GL_UNSIGNED_INT, mesh->getFirstColorNormalIndexIndex());
        
        // Se vuelve a habilitar el array de colores
        glEnableClientState(GL_COLOR_ARRAY);
        
        // Se vuelven a encender la luces
        glEnable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        
    }
               
}

////////////////////////////////////////////////////////////////////////////
// Se centran las coordenadas en el origen
//
void Obj3D::centerObject(){
        
//    cout << endl << "Las coordenadas son: " << endl;
//    
//    cout << "Máx X: " << get<0>(mesh->getMaxPoints()) << " ; Y: " << get<1>(mesh->getMaxPoints()) << " ; Z: " << get<2>(mesh->getMaxPoints()) << endl;
//    
//    cout << endl;
//    
//    cout << "Mín X: " << get<0>(mesh->getMinPoints()) << " ; Y: " << get<1>(mesh->getMinPoints()) << " ; Z: " << get<2>(mesh->getMinPoints()) << endl;
    
    tuple <float, float, float> diff = mesh->getDiffCenter();
    
//    cout << "La diferencia entre x es: " << get<0>(diff) << endl;
//    
//    cout << "La diferencia entre y es: " << get<1>(diff) << endl;
//    
//    cout << "La diferencia entre z es: " << get<2>(diff) << endl;
        
    glTranslatef(get<0>(diff), get<1>(diff), get<2>(diff));
    
}

////////////////////////////////////////////////////////////////////////////
// Se escala el objeto para ocupar la pantalla a buen tamaño
//
void Obj3D::scaleObject(){
       
    float scale = mesh->getScaleValue();
        
//    cout << "Se debe multiplicar por: " << scale << endl;
    
    glScaled(scale, scale, scale);
                
}

// Devuelve el número de caras que tiene el modelo
unsigned int Obj3D::getSides(){
    return 0;    
}

////////////////////////////////////////////////////////////////////////////
// Devuelve si un objeto es por revolución o no
//
bool Obj3D::isRev(){
    return false;
}

