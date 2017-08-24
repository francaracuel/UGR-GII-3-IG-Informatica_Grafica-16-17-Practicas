////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 3
//
// dog_head.h
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _DOGHEAD_H
#define _DOGHEAD_H

#include <vector>
#include <tuple>
#include "obj3D.h"
#include "obj_ply.h"
#include "sphere.h"

class DogHead : public Obj3D {
    
private:
    
    vector<Obj3D*> listObj;
    
    // Vector con los grados de libertad
    vector<float> listL;
    
    // Vector con la velocidad de los grados de libertad
    vector<float> listS;
    
    // Constantes de configuración de los grados de libertad
    // 0 -> Lengua -> Max, min, growth, MaxSpeed, minSpeed, growthSpeed
    // 1 -> Boca -> Max, min, growth, MaxSpeed, minSpeed, growthSpeed 
    // 2 -> Orejas -> Max, min, growth, MaxSpeed, minSpeed, growthSpeed
    // 3 -> Ojos -> Max, min, growth, MaxSpeed, minSpeed, growthSpeed
    // 4 -> Cabeza -> Max, min, growth, MaxSpeed, minSpeed, growthSpeed
    vector<tuple<float, float, float, float, float, float> > listConstant;    
    
public:
    
    ////////////////////////////////////////////////////////////////////////////
    // Constructor
    //
    DogHead();   
    
    ////////////////////////////////////////////////////////////////////////////
    // Setters
    //
    
    void setDrawMode(GLenum drawMode);
    
    void setPolygonMode(GLenum polygonMode);
    
    void setChess(bool chess);
    
    void setNormalVertex(bool normal);
        
    void setNormalIndex(bool normal);
    
    void setLight(bool light);
        
    ////////////////////////////////////////////////////////////////////////////
    // Dibuja todo el objeto
    //
    void draw();
    
    ////////////////////////////////////////////////////////////////////////////
    // Aumenta el valor de la lengua
    bool increaseTongue();
    
    // Disminuye el valor de la lengua
    bool decreaseTongue();
    
    // Aumenta el valor de la velocidad de la lengua
    bool increaseTongueSpeed();
    
    // Disminuye el valor de la velocidad de la lengua
    bool decreaseTongueSpeed();
    
    // Aumenta el valor de la boca
    bool increaseMouth();
    
    // Disminuye el valor de la boca
    bool decreaseMouth();
    
    // Aumenta el valor de la velocidad de la boca
    bool increaseMouthSpeed();
    
    // Disminuye el valor de la velocidad de la boca
    bool decreaseMouthSpeed();
    
    // Aumenta el valor de las orejas
    bool increaseEars();
    
    // Disminuye el valor de las orejas
    bool decreaseEars();
    
    // Aumenta el valor de la velocidad de las orejas
    bool increaseEarsSpeed();
    
    // Disminuye el valor de la velocidad de las orejas
    bool decreaseEarsSpeed();
    
    // Aumenta el valor de los ojos
    bool increaseEyes();
    
    // Disminuye el valor de los ojos
    bool decreaseEyes();
    
    // Aumenta el tamaño de los ojos
    bool increaseEyesSize();
    
    // Disminuye el tamaño de los ojos
    bool decreaseEyesSize();
    
    // Aumenta el valor de la velocidad de los ojos
    bool increaseEyesSpeed();
    
    // Disminuye el valor de la velocidad de los ojos
    bool decreaseEyesSpeed();
    
    // Aumenta el valor de la cabeza
    bool increaseHead();
    
    // Disminuye el valor de la cabeza
    bool decreaseHead();
    
    // Aumenta el valor de la velocidad de la cabeza
    bool increaseHeadSpeed();
    
    // Disminuye el valor de la velocidad de la cabeza
    bool decreaseHeadSpeed();
    
    // Aumenta la velocidad de todos los grados de libertad
    void increaseSpeedAll();
    
    // Disminuye la velocidad de todos los grados de libertad
    void decreaseSpeedAll();
    
private:
    
    ////////////////////////////////////////////////////////////////////////////
    // Inicializa todos los valores necesarios
    //
    void init(); 
        
    // Dibuja la nariz, boca y lengua
    void drawNMT();
    
    // Dibuja la cabeza y las orejas
    void drawHE();
    
    // Dibuja los ojos
    void drawEyes();
    
    // Aumenta un valor del vector de grados de libertad
    bool increaseValue(int element);
    
    // Disminuye un valor del vector de grados de libertad
    bool decreaseValue(int element);
    
    // Aumenta la velocidad de un valor del vector de grados de libertad
    bool increaseSpeed(int element);
    
    // Disminuye la velocidad de un valor del vector de grados de libertad
    bool decreaseSpeed(int element);

};

#endif
