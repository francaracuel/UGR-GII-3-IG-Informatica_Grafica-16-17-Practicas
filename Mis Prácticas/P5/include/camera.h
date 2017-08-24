////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 5
//
// camera.h
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _CAMERA_H
#define _CAMERA_H

#include <vector>
#include <GL/glut.h>
#include <GL/gl.h>
using namespace std;

class Camera{
    
private:
    
    // Coordenadas polare de la camara
    GLfloat distance;
    GLfloat angleX;
    GLfloat angleY;
    
    // Transformación de la perspectiva
    GLfloat frontPlane;
    GLfloat backPlane;
    GLfloat width;
    GLfloat height;
    
    // Vector para la visualización
    vector<GLfloat> eye;
    vector<GLfloat> at;
    
    int type;
    
    int incdec;
    
public:
    
    ////////////////////////////////////////////////////////////////////////////
    // Constructores
    //
    Camera(int UI_window_width, int UI_window_height);
    
    Camera(GLfloat distance, GLfloat angleX, GLfloat angleY, GLfloat frontPlane,
        GLfloat backPlane, GLfloat width, GLfloat height, int type);
    
    ////////////////////////////////////////////////////////////////////////////
    // Getters
    //
    GLfloat getDistance();
    
    GLfloat getAngleX();
    
    GLfloat getAngleY();
    
    GLfloat getFrontPlane();
    
    GLfloat getBackPlane();
    
    GLfloat getWidth();
    
    GLfloat getHeight();
    
    int getType();
    
    vector<GLfloat> getEye();
    
    vector<GLfloat> getAt();
    
    ////////////////////////////////////////////////////////////////////////////
    // Setters
    //
    void setDistance(GLfloat distance);    
    
    void setAngleX(GLfloat angleX);
    
    void setAngleY(GLfloat angleY);
    
    void setFrontPlane(GLfloat frontPlane);
    
    void setBackPlane(GLfloat backPlane);
    
    void setWidth(GLfloat width);
    
    void setHeight(GLfloat height);
    
    void setType(int type);
    
    void setEye(GLfloat x, GLfloat y, GLfloat z);
    void setEyeX(GLfloat x);
    void setEyeY(GLfloat y);
    void setEyeZ(GLfloat z);
    
    void setAt(GLfloat x, GLfloat y, GLfloat z);    
    void setAtX(GLfloat x);
    void setAtY(GLfloat y);
    void setAtZ(GLfloat z);
    
    ////////////////////////////////////////////////////////////////////////////
    // Utils
    //
    void increaseDistance();
    
    void increaseAngleX();
    
    void increaseAngleY();
    
    void increaseEyeX();
    void increaseEyeY();
    void increaseEyeZ();
    
    void increaseAtX();
    void increaseAtY();
    void increaseAtZ();
    
    void decreaseDistance();
    
    void decreaseAngleX();
    
    void decreaseAngleY();
    
    void decreaseEyeX();
    void decreaseEyeY();
    void decreaseEyeZ();
    
    void decreaseAtX();
    void decreaseAtY();
    void decreaseAtZ();
    
    void setObserver();
        
};

#endif