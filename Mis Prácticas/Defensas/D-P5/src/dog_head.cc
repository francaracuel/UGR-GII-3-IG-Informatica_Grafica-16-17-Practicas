////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 5
//
// dog_head.cc
//
////////////////////////////////////////////////////////////////////////////////

#include "dog_head.h"

////////////////////////////////////////////////////////////////////////////////
// Constructor
//
DogHead::DogHead(){
    
    init();
    
}

DogHead::DogHead(string name, bool generateAutomatic) : DogHead(){
    
    setTexture(name, generateAutomatic);
    
}

////////////////////////////////////////////////////////////////////////////////
// Inicializa todos los valores necesarios
//
void DogHead::init(){
    
    // Colores con los que se pinta el objeto
    vector<float> listColors;
    
    listColors.push_back(104);
    listColors.push_back(66);
    listColors.push_back(26);
    
    listColors.push_back(43);
    listColors.push_back(27);
    listColors.push_back(11);
    
    // Colores con los que se pinta la lengua
    vector<float> listColorsT;
    
    listColorsT.push_back(255);
    listColorsT.push_back(116);
    listColorsT.push_back(140);
    
    listColorsT.push_back(255);
    listColorsT.push_back(65);
    listColorsT.push_back(98);
    
    // Colores con los que se pintan los ojos
    vector<float> listColorsB;
    
    listColorsB.push_back(0);
    listColorsB.push_back(0);
    listColorsB.push_back(0);
    
    listColorsB.push_back(100);
    listColorsB.push_back(100);
    listColorsB.push_back(100);
    
    vector<float> listColorsW;
    
    listColorsW.push_back(255);
    listColorsW.push_back(255);
    listColorsW.push_back(255);
    
    listColorsW.push_back(150);
    listColorsW.push_back(150);
    listColorsW.push_back(150);
    
    // 0 Cabeza
    listObj.push_back(new ObjPLY(false, "../data/head.ply", listColors));
    
    // 1 Nariz
    listObj.push_back(new ObjPLY(false, "../data/nose.ply", listColors));
    
    // 2 Boca
    listObj.push_back(new ObjPLY(false, "../data/mouth.ply", listColors));
    
    // 3 Lengua
    listObj.push_back(new ObjPLY(false, "../data/tongue.ply", listColorsT));
    listObj[3]->setActiveLight(false);
    listObj[3]->getMaterial()->setActive(false);
    listObj[3]->getMaterial()->setActive(false);
    
    // 4 Ojos -> blanco
    listObj.push_back(new Sphere(50, listColorsW));
    listObj[4]->setActiveLight(false);
    listObj[4]->getMaterial()->setActive(false);
    listObj[4]->getMaterial()->setActive(false);
    
    // 5 Ojos -> negro
    listObj.push_back(new Sphere(50, listColorsB));
    listObj[5]->getMaterial()->setActive(false);
    listObj[5]->getMaterial()->setActive(false);
    
    // 6 Oreja
    listObj.push_back(new ObjPLY(false, "../data/ear.ply", listColors));
    
    ////////////////////////////////////////////////////////////////////////////
    // Se establecen los valores máximos y mínimos de los grados de libertad
    //
    
    // 0 -> Lengua -> Max, min, growth, MaxSpeed, minSpeed, growthSpeed
    listConstant.push_back(tuple<float, float, float, float, float, float>(0.5, 0, 0.01, 5, 1, 0.1)); 
    
    // 1 -> Boca -> Max, min, growth, MaxSpeed, minSpeed, growthSpeed
    listConstant.push_back(tuple<float, float, float, float, float, float>(35, 0, 1, 5, 1, 0.1)); 
    
    // 2 -> Orejas -> Max, min, growth, MaxSpeed, minSpeed, growthSpeed
    listConstant.push_back(tuple<float, float, float, float, float, float>(75, 0, 1, 5, 1, 0.1)); 
    
    // 3 -> Ojos -> Max, min, growth, MaxSpeed, minSpeed, growthSpeed
    listConstant.push_back(tuple<float, float, float, float, float, float>(45, -45, 1, 5, 1, 0.1)); 
    
    // 4 -> Cabeza -> Max, min, growth, MaxSpeed, minSpeed, growthSpeed
    listConstant.push_back(tuple<float, float, float, float, float, float>(30, -30, 1, 5, 1, 0.1)); 
    
    // 5 -> Cabeza -> Max, min, growth, MaxSpeed, minSpeed, growthSpeed
    listConstant.push_back(tuple<float, float, float, float, float, float>(0.4, 0.2, 0.05, 5, 1, 0.05)); 
    
    // Se añaden los grados de libertad
    // 0 -> Lengua
    listL.push_back(0);
    // 1 -> Boca
    listL.push_back(0);
    // 2 -> Orejas
    listL.push_back(0);
    // 3 -> Ojos
    listL.push_back(0);
    // 4 -> Cabeza
    listL.push_back(0);
    
    
    listL.push_back(0.2);
    
    // Se añade la velocidad de los grados de velocidad
    // 0 -> Lengua
    listS.push_back(1);
    // 1 -> Boca
    listS.push_back(1);
    // 2 -> Orejas
    listS.push_back(1);
    // 3 -> Ojos
    listS.push_back(1);
    // 4 -> Cabeza
    listS.push_back(1);
    
    listS.push_back(0.5);
    
}

////////////////////////////////////////////////////////////////////////////////
// Setters
//

void DogHead::setDrawMode(GLenum drawMode){
    
    this->drawMode = drawMode;
    
    for(unsigned int i=0; i<listObj.size(); i++){
        listObj[i]->setDrawMode(drawMode);
    }
    
}

void DogHead::setPolygonMode(GLenum polygonMode){
    
    this->polygonMode = polygonMode;
    
    for(unsigned int i=0; i<listObj.size(); i++){
        listObj[i]->setPolygonMode(polygonMode);
    }
    
}

void DogHead::setChess(bool chess){
    
    this->chess = chess;
    
    for(unsigned int i=0; i<listObj.size(); i++){
        listObj[i]->setChess(chess);
    }
    
}

void DogHead::setNormalVertex(bool n){
    
    this->normalVertex = n;
    
    for(unsigned int i=0; i<listObj.size(); i++){
        listObj[i]->setNormalVertex(n);
    }
    
}

void DogHead::setNormalIndex(bool n){
    
    this->normalIndex = n;
    
    for(unsigned int i=0; i<listObj.size(); i++){
        listObj[i]->setNormalIndex(n);
    }
    
}

void DogHead::setLight(Light *l){
    
    this->light = l;
    
    for(unsigned int i=0; i<listObj.size(); i++){
            listObj[i]->setLight(l);
    }
    
}

void DogHead::setShading(bool s){
    
    this->shading = s;
    
    for(unsigned int i=0; i<listObj.size(); i++){
        listObj[i]->setShading(s);
    }
    
}

////////////////////////////////////////////////////////////////////////////////
// Dibuja el objeto completo
//
void DogHead::draw(){
    
    glScaled(150,150,150);
    
    glRotatef(listL[4], 0, 0, 1);
    
    drawHE();
    
    drawNMT();
    
    drawEyes();
    
}

// Dibuja la cabeza y las orejas
void DogHead::drawHE(){
    
    glPushMatrix();
    
        // Se dibuja la cabeza
        glPushMatrix();

            listObj[0]->draw();

        glPopMatrix();
    
        // Se dibujan las orejas
        glPushMatrix();

            glTranslatef(0, 0.8, -0.6);
            
            glScaled(0.8, 0.8, 0.8);

                glPushMatrix();
                
                    glTranslatef(0.5, 0, 0);
                
                    glRotatef(listL[2], 0, 1, 0);

                    listObj[6]->draw();

                glPopMatrix();
                
                glPushMatrix();
                
                    glTranslatef(-0.5, 0, 0);
                
                    glRotatef(-listL[2], 0, 1, 0);

                    listObj[6]->draw();

                glPopMatrix();

        glPopMatrix();
    
    
    
    glPopMatrix();
    
    
}

// Dibuja la nariz, boca y lengua
void DogHead::drawNMT(){
    
    glPushMatrix();
    
    glTranslatef(0, 0.2, 0);
        
        // Se dibuja la nariz
        glPushMatrix();
        
            glRotatef(-listL[1], 1, 0, 0);

            listObj[1]->draw();

        glPopMatrix();

        // Se dibuja la boca
        glPushMatrix();
        
            glRotatef(listL[1]/3, 1, 0, 0);

            listObj[2]->draw();

        glPopMatrix();
        
        // Se dibuja la lengua
        glPushMatrix();
        
            glTranslatef(0, 0, listL[0]);

            listObj[3]->draw();

        glPopMatrix();
    
    glPopMatrix();
    
}

// Dibuja los ojos
void DogHead::drawEyes(){
    
    // Se crean los ojos
    glPushMatrix();
    
            glTranslatef(0, 0.75, -0.15);
            
            glScaled(listL[5], listL[5], listL[5]);
            
            glPushMatrix();
                
                glTranslatef(0.7, 0, 0);
            
                listObj[4]->draw();
                
                glPushMatrix();
                
                    glScaled(0.5, 0.5, 0.5);
                    
                    // Movimiento de los ojos
                    glRotatef(listL[3], 0, 1, 0);
                    
                    glTranslatef(0, -0.1, 0.6);
                    
                    listObj[5]->draw();
                
                glPopMatrix();
            
            glPopMatrix();
            
            glPushMatrix();
            
                glTranslatef(-0.7, 0, 0);
            
                listObj[4]->draw();
                
                glPushMatrix();
                
                    glScaled(0.5, 0.5, 0.5);
                    
                    // Movimiento de los ojos
                    glRotatef(listL[3], 0, 1, 0);
                    
                    glTranslatef(0, -0.1, 0.6);
                    
                    listObj[5]->draw();
                
                glPopMatrix();
            
            glPopMatrix();
    
    glPopMatrix();
    
}

////////////////////////////////////////////////////////////////////////////
// Aumenta el valor de la lengua
bool DogHead::increaseTongue(){
    
    return increaseValue(0);
    
}

// Disminuye el valor de la lengua
bool DogHead::decreaseTongue(){
    
    return decreaseValue(0);
    
}

// Aumenta el valor de la velocidad de la lengua
bool DogHead::increaseTongueSpeed(){
    
    return increaseSpeed(0);
    
}

// Disminuye el valor de la velocidad de la lengua
bool DogHead::decreaseTongueSpeed(){
    
    return decreaseSpeed(0);
    
}

// Aumenta el valor de la boca
bool DogHead::increaseMouth(){
    
    return increaseValue(1);
    
}

// Disminuye el valor de la boca
bool DogHead::decreaseMouth(){
    
    return decreaseValue(1);
    
}

// Aumenta el valor de la velocidad de la boca
bool DogHead::increaseMouthSpeed(){
    
    return increaseSpeed(1);
    
}

// Disminuye el valor de la velocidad de la boca
bool DogHead::decreaseMouthSpeed(){
    
    return decreaseSpeed(1);
    
}

// Aumenta el valor de las orejas
bool DogHead::increaseEars(){
    
    return increaseValue(2);
    
}

// Disminuye el valor de las orejas
bool DogHead::decreaseEars(){
    
    return decreaseValue(2);
    
}

// Aumenta el valor de la velocidad de las orejas
bool DogHead::increaseEarsSpeed(){
    
    return increaseSpeed(2);
    
}

// Disminuye el valor de la velocidad de las orejas
bool DogHead::decreaseEarsSpeed(){
    
    return decreaseSpeed(2);
    
}

// Aumenta el valor de los ojos
bool DogHead::increaseEyes(){
    
    return increaseValue(3);
    
}

// Disminuye el valor de los ojos
bool DogHead::decreaseEyes(){
    
    return decreaseValue(3);
    
}

// Aumenta el tamaño de los ojos
bool DogHead::increaseEyesSize(){
    
    return increaseValue(5);
    
}

// Disminuye el tamaño de los ojos
bool DogHead::decreaseEyesSize(){
    
    return decreaseValue(5);
    
}

// Aumenta el valor de la velocidad de los ojos
bool DogHead::increaseEyesSpeed(){
    
    return increaseSpeed(3);
    
}

// Disminuye el valor de la velocidad de los ojos
bool DogHead::decreaseEyesSpeed(){
    
    return decreaseSpeed(3);
    
}

// Aumenta el valor de la cabeza
bool DogHead::increaseHead(){
    
    return increaseValue(4);
    
}

// Disminuye el valor de la cabeza
bool DogHead::decreaseHead(){
    
    return decreaseValue(4);
    
}

// Aumenta el valor de la velocidad de la cabeza
bool DogHead::increaseHeadSpeed(){
    
    return increaseSpeed(4);
    
}

// Disminuye el valor de la velocidad de la cabeza
bool DogHead::decreaseHeadSpeed(){
    
    return decreaseSpeed(4);
    
}

// Aumenta un valor del vector de grados de libertad
bool DogHead::increaseValue(int element){
    
    bool max = false;
    
    if(listL[element] < get<0>(listConstant[element])) // máx
        listL[element] += (get<2>(listConstant[element])*listS[element]); // growth*speed
    
    if(listL[element] >= get<0>(listConstant[element])){
        listL[element] = get<0>(listConstant[element]);  
        max = true;
    }
    
    return max;
    
}

// Disminuye un valor del vector de grados de libertad
bool DogHead::decreaseValue(int element){
    
    bool min = false;
    
    if(listL[element] > get<1>(listConstant[element])) // mín
        listL[element] -= (get<2>(listConstant[element])*listS[element]); // growth*speed
    
    if(listL[element] <= get<1>(listConstant[element])){
        listL[element] = get<1>(listConstant[element]);
        min = true;
    }   
    
    return min;
    
}

// Aumenta la velocidad de un valor del vector de grados de libertad
bool DogHead::increaseSpeed(int element){
    
    bool increase = false;
    
    if(listS[element] < get<3>(listConstant[element])){ // máxSpeed
        listS[element] += get<5>(listConstant[element]); // growthSpeed
        increase = true;
    }
    
    return increase;
    
}

// Disminuye la velocidad de un valor del vector de grados de libertad
bool DogHead::decreaseSpeed(int element){
    
    bool decrease = false;
    
    if(listS[element] > get<4>(listConstant[element])){ // minSpeed
        listS[element] -= get<5>(listConstant[element]); // growthSpeed
        decrease = true;
    }
    
    return decrease;
    
}

// Aumenta la velocidad de todos los grados de libertad
void DogHead::increaseSpeedAll(){
    
    for(int i=0; i<listS.size(); i++){
        increaseSpeed(i);
    }
    
}

// Disminuye la velocidad de todos los grados de libertad
void DogHead::decreaseSpeedAll(){
    
    for(int i=0; i<listS.size(); i++){
        decreaseSpeed(i);
    }
    
}

// Asigna una textura a todos los objetos por igual (menos a los ojos)
void DogHead::setTexture(string name, bool generateAutomatic){
    
    for(unsigned int i=0; i<listObj.size(); i++){
        if(i!=3 && i!=4 && i!=5)
            listObj[i]->getMaterial()->setTexture(new Texture(name, generateAutomatic));
    }
    
}