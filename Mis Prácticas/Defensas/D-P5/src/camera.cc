////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 5
//
// camera.cc
//
////////////////////////////////////////////////////////////////////////////////

#include "camera.h"

////////////////////////////////////////////////////////////////////////////////
// Constructores
//
Camera::Camera(int UI_window_width, int UI_window_height) :  
    Camera(4*50, 0, 0, 50, 2000, UI_window_width / 10, UI_window_height / 10, 0){
    
}

Camera::Camera(GLfloat d, GLfloat aX, GLfloat aY, GLfloat f,
        GLfloat b, GLfloat w, GLfloat h, int t) :  angleX(aX), 
                                            angleY(aY), 
                                            frontPlane(f), 
                                            backPlane(b),
                                            distance(d),
                                            width(w),
                                            height(h),
                                            type(t)
            {
    
    eye.push_back(0);
    eye.push_back(0);
    eye.push_back(100);
    
    at.push_back(0);
    at.push_back(0);
    at.push_back(0);
    
    incdec = 10;
    
}

////////////////////////////////////////////////////////////////////////////////
// Getters
//
GLfloat Camera::getDistance(){
    return distance;
}

GLfloat Camera::getAngleX(){
    return angleX;
}

GLfloat Camera::getAngleY(){
    return angleY;
}

GLfloat Camera::getWidth(){
    return width;
}

GLfloat Camera::getFrontPlane(){
    return frontPlane;
}

GLfloat Camera::getBackPlane(){
    return backPlane;
}

GLfloat Camera::getHeight(){
    return height;
}

int Camera::getType(){
    return type;
}

vector<GLfloat> Camera::getEye(){
    return eye;
}
    
vector<GLfloat> Camera::getAt(){
    return at;
}

////////////////////////////////////////////////////////////////////////////////
// Setters
//
void Camera::setDistance(GLfloat d){
    distance = d;
}    

void Camera::setAngleX(GLfloat aX){
    angleX = aX;
}

void Camera::setAngleY(GLfloat aY){
    angleY = aY;
}

void Camera::setFrontPlane(GLfloat fp){
    frontPlane = fp;
}

void Camera::setBackPlane(GLfloat bp){
    backPlane = bp;
}

void Camera::setWidth(GLfloat w){
    width = w;
}

void Camera::setHeight(GLfloat h){
    height = h;
}

void Camera::setType(int t){
    type = t;
}

void Camera::setEye(GLfloat x, GLfloat y, GLfloat z){
    eye[0] = x;
    eye[1] = y;
    eye[2] = z;
}

void Camera::setEyeX(GLfloat x){
    eye[0] = x;
}

void Camera::setEyeY(GLfloat y){
    eye[1] = y;
}

void Camera::setEyeZ(GLfloat z){
    eye[2] = z;
}
    
void Camera::setAt(GLfloat x, GLfloat y, GLfloat z){
    at[0] = x;
    at[1] = y;
    at[2] = z;
}

void Camera::setAtX(GLfloat x){
    at[0] = x;
}

void Camera::setAtY(GLfloat y){
    at[1] = y;
}

void Camera::setAtZ(GLfloat z){
    at[2] = z;
}

////////////////////////////////////////////////////////////////////////////////
// Utils
//
void Camera::increaseDistance(){
    distance *= 1.2;
}
    
void Camera::increaseAngleX(){
    angleX++;
}

void Camera::increaseAngleY(){
    angleY++;
}

void Camera::increaseEyeX(){
    eye[0] += incdec;
}

void Camera::increaseEyeY(){
    eye[1] += incdec;
}

void Camera::increaseEyeZ(){
    eye[2] += incdec;
}

void Camera::increaseAtX(){
    at[0] += incdec;
}

void Camera::increaseAtY(){
    at[1] += incdec;
}

void Camera::increaseAtZ(){
    at[2] += incdec;
}

void Camera::decreaseDistance(){
    distance /= 1.2;
}

void Camera::decreaseAngleX(){
    angleX--;
}

void Camera::decreaseAngleY(){
    angleY--;
}

void Camera::decreaseEyeX(){
    eye[0] -= incdec;
}

void Camera::decreaseEyeY(){
    eye[1] -= incdec;
}

void Camera::decreaseEyeZ(){
    eye[2] -= incdec;
}

void Camera::decreaseAtX(){
    at[0] -= incdec;
}

void Camera::decreaseAtY(){
    at[1] -= incdec;
}

void Camera::decreaseAtZ(){
    at[2] -= incdec;
}

void Camera::setObserver(){
    gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], 0, 1, 0);
    //gluLookAt(eye[0], eye[1], eye[2], eye[0]+at[0], eye[1]+at[1], eye[2]+at[2], 0, 1, 0);
}