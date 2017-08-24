////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 4
//
// light.cpp
//
////////////////////////////////////////////////////////////////////////////////

#include "light.h"

////////////////////////////////////////////////////////////////////////////
// Constructores
//
Light::Light(bool a) : active(a), number(0), type(1), alpha(0), beta(0), defensa4(true){
    
    setRgb(1.0, 1.0, 1.0);
    setPos(0, 0, 0);
    setDir(-1, 1, 1);
    
    // Ambiental
    ambient.push_back(0.0);
    ambient.push_back(0.0);
    ambient.push_back(0.0);
    ambient.push_back(1.0);
    
    // Difusa
    diffuse.push_back(1.0);
    diffuse.push_back(1.0);
    diffuse.push_back(1.0);
    diffuse.push_back(1.0);
    
    // Especular
    specular.push_back(1.0);
    specular.push_back(1.0);
    specular.push_back(1.0);
    specular.push_back(1.0);
    
    specular1.push_back(1.0);
    specular1.push_back(1.0);
    specular1.push_back(1.0);
    specular1.push_back(1.0);
    
}

Light::Light(bool a, int n) : Light(a){
    
    number = n;
    
}

////////////////////////////////////////////////////////////////////////////
// Operadores
//
Light& Light::operator=(const Light& l){
    
    if(this != &l){
        
        this->active = l.active;
        this->rgb = l.rgb;
        this->type = l.type;
        this->pos = l.pos;
        this->dir = l.dir;
        this->alpha = l.alpha;
        this->beta = l.beta;
        
    }
    
}

////////////////////////////////////////////////////////////////////////////
// Getters
//
bool Light::getActive(){
    return active;
}

tuple<float, float, float> Light::getRgb(){
    return rgb;
}

int Light::getType(){
    return type;
}

tuple<float, float, float> Light::getPos(){
    return pos;
}

tuple<float, float, float> Light::getDir(){
    return dir;
}

float Light::getAlpha(){
    return alpha;
}

float Light::getBeta(){
    return beta;
}

bool Light::getDefensa4(){
    return defensa4;
}

////////////////////////////////////////////////////////////////////////////
// Setters
//
void Light::setActive(bool a){
    active = a;
}

void Light::setRgb(float r, float g, float b){
    this->rgb = tuple<float, float, float>(r, g, b);
}

void Light::setType(int t){
    this->type = t;
}

void Light::setPos(float x, float y, float z){
    this->pos = tuple<float, float, float>(x, y, z);
}
    
void Light::setDir(float x, float y, float z){
    this->dir = tuple<float, float, float>(x, y, z);
}

void Light::setAlpha(float a){
    this->alpha = a;
}

void Light::setBeta(float b){
    this->beta = b;
}

void Light::setAmbient(vector<GLfloat> a){
    ambient = a;
}

void Light::setDiffuse(vector<GLfloat> d){
    diffuse = d;
}

void Light::setSpecular(vector<GLfloat> s){
    specular = s;
}

void Light::setDefensa4(bool a){
    defensa4 = a;
}

////////////////////////////////////////////////////////////////////////////
// Utils
//
void Light::apply(){
    
    if(active){
        
        glEnable(GL_LIGHTING);

        GLfloat lmodel_ambient[] = {get<0>(rgb), get<1>(rgb), get<2>(rgb), 1.0};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
                
        if(defensa4){
           
            glEnable(GL_LIGHT5);

            setDir(-1, 1, 1);
            
            // Especular
            
            specular[0] = 1.0;
            specular[1] = 1.0;
            specular[2] = 1.0;
            specular[3] = 1.0;
            
            
            GLfloat dirf0[4] = {get<0>(dir), get<1>(dir), get<2>(dir), 0.0};
            
            glLightfv(GL_LIGHT5, GL_POSITION, dirf0);                    
            glLightfv(GL_LIGHT5, GL_AMBIENT, &ambient.front());
            glLightfv(GL_LIGHT5, GL_DIFFUSE, &diffuse.front());
            glLightfv(GL_LIGHT5, GL_SPECULAR, &specular.front());
            
            
            glDisable(GL_LIGHT3) ;

        } else{
                        
            glEnable(GL_LIGHT5);
            glEnable(GL_LIGHT3);
            
            setDir(0, 80, 0);
            
            // Especular
            specular[0] = 1.0;
            specular[1] = 0.0;
            specular[2] = 0.0;
            specular[3] = 1.0;
            
            GLfloat dirf1[4] = {get<0>(dir), get<1>(dir), get<2>(dir), 0.0};
            
            glLightfv(GL_LIGHT5, GL_POSITION, dirf1);                    
            glLightfv(GL_LIGHT5, GL_AMBIENT, &ambient.front());
            glLightfv(GL_LIGHT5, GL_DIFFUSE, &diffuse.front());
            glLightfv(GL_LIGHT5, GL_SPECULAR, &specular.front());
            
            //setDir(0, -10, 0);
            
            
            glEnable(GL_LIGHT3);
            
            
            GLfloat dirf2[4] = {0, -10, 0};
            
            // Especular
            specular1[0] = 0.0;
            specular1[1] = 0.0;
            specular1[2] = 1.0;
            specular1[3] = 1.0;
                        
            glLightfv(GL_LIGHT3, GL_POSITION, dirf2);                    
            glLightfv(GL_LIGHT3, GL_AMBIENT, &ambient.front());
            glLightfv(GL_LIGHT3, GL_DIFFUSE, &diffuse.front());
            glLightfv(GL_LIGHT3, GL_SPECULAR, &specular1.front());
            
        }
        
        
        
        
        const GLfloat posf[4] = {get<0>(pos), get<1>(pos), get<2>(pos), 1.0}; // (x,y,z,w)
        const GLfloat dirf[4] = {get<0>(dir), get<1>(dir), get<2>(dir), 0.0}; // (x,y,z,w)

        switch(number){
            
            case 0:
                
                glEnable(GL_LIGHT0);
                
                // Posicional
                if(type==0){                    
                    glLightfv(GL_LIGHT0, GL_POSITION, posf);
                // Direccional
                } else if(type==1){  
                                                                            
                    /*glMatrixMode(GL_MODELVIEW);
                    
                    glPushMatrix();
                    
                    glLoadIdentity();
                    
                    GLfloat fMatrizM[16];
                    glLoadMatrixf(fMatrizM);
                    
                    glMultMatrixf(fMatrizM);
                    
                    glRotatef(alpha, 0.0, 1.0, 0.0);
                    
                    glRotatef(beta, -1.0, 0.0, 0.0);
                                        
                    glLightfv(GL_LIGHT0, GL_POSITION, dirf);
                    
                    glPopMatrix();*/
                    
                    
                    
                    
                    glLightfv(GL_LIGHT0, GL_POSITION, dirf);
                    
                }
                
                
                
                glLightfv(GL_LIGHT0, GL_AMBIENT, &ambient.front());
                glLightfv(GL_LIGHT0, GL_DIFFUSE, &diffuse.front());
                glLightfv(GL_LIGHT0, GL_SPECULAR, &specular.front());
                
                break;
                
            case 1:
                
                glEnable(GL_LIGHT1) ;
                
                // Posicional
                if(type==0){                    
                    glLightfv(GL_LIGHT1, GL_POSITION, posf);
                // Direccional
                } else if(type==1){            
                    
                    glLightfv(GL_LIGHT1, GL_POSITION, dirf);
                    
                }
                    
                glLightfv(GL_LIGHT1, GL_AMBIENT, &ambient.front());
                glLightfv(GL_LIGHT1, GL_DIFFUSE, &diffuse.front());
                glLightfv(GL_LIGHT1, GL_SPECULAR, &specular.front());
                
                break;
                
            case 2:
                
                glEnable(GL_LIGHT2) ;
                
                // Posicional
                if(type==0){                    
                    glLightfv(GL_LIGHT2, GL_POSITION, posf);
                // Direccional
                } else if(type==1){            
                    
                    glLightfv(GL_LIGHT2, GL_POSITION, dirf);
                    
                }
                    
                glLightfv(GL_LIGHT2, GL_AMBIENT, &ambient.front());
                glLightfv(GL_LIGHT2, GL_DIFFUSE, &diffuse.front());
                glLightfv(GL_LIGHT2, GL_SPECULAR, &specular.front());
                
                break;
                
            /*case 3:
                
                glEnable(GL_LIGHT3) ;
                
                // Posicional
                if(type==0){                    
                    glLightfv(GL_LIGHT3, GL_POSITION, posf);
                // Direccional
                } else if(type==1){            
                    
                    glLightfv(GL_LIGHT3, GL_POSITION, dirf);
                    
                }
                    
                glLightfv(GL_LIGHT3, GL_AMBIENT, &ambient.front());
                glLightfv(GL_LIGHT3, GL_DIFFUSE, &diffuse.front());
                glLightfv(GL_LIGHT3, GL_SPECULAR, &specular.front());
                
                break;
                
            case 4:
                
                glEnable(GL_LIGHT4) ;
                
                // Posicional
                if(type==0){                    
                    glLightfv(GL_LIGHT4, GL_POSITION, posf);
                // Direccional
                } else if(type==1){            
                    
                    glLightfv(GL_LIGHT4, GL_POSITION, dirf);
                    
                }
                    
                glLightfv(GL_LIGHT4, GL_AMBIENT, &ambient.front());
                glLightfv(GL_LIGHT4, GL_DIFFUSE, &diffuse.front());
                glLightfv(GL_LIGHT4, GL_SPECULAR, &specular.front());
                
                break;
                
            case 5:
                
                glEnable(GL_LIGHT5) ;
                
                // Posicional
                if(type==0){                    
                    glLightfv(GL_LIGHT5, GL_POSITION, posf);
                // Direccional
                } else if(type==1){            
                    
                    glLightfv(GL_LIGHT5, GL_POSITION, dirf);
                    
                }
                    
                glLightfv(GL_LIGHT5, GL_AMBIENT, &ambient.front());
                glLightfv(GL_LIGHT5, GL_DIFFUSE, &diffuse.front());
                glLightfv(GL_LIGHT5, GL_SPECULAR, &specular.front());
                
                break;
                
            case 6:
                
                glEnable(GL_LIGHT6) ;
                
                // Posicional
                if(type==0){                    
                    glLightfv(GL_LIGHT6, GL_POSITION, posf);
                // Direccional
                } else if(type==1){            
                    
                    glLightfv(GL_LIGHT6, GL_POSITION, dirf);
                    
                }
                    
                glLightfv(GL_LIGHT6, GL_AMBIENT, &ambient.front());
                glLightfv(GL_LIGHT6, GL_DIFFUSE, &diffuse.front());
                glLightfv(GL_LIGHT6, GL_SPECULAR, &specular.front());
                
                break;
                
            case 7:
                
                glEnable(GL_LIGHT7) ;
                
                // Posicional
                if(type==0){                    
                    glLightfv(GL_LIGHT7, GL_POSITION, posf);
                // Direccional
                } else if(type==1){            
                    
                    glLightfv(GL_LIGHT7, GL_POSITION, dirf);
                    
                }
                    
                glLightfv(GL_LIGHT7, GL_AMBIENT, &ambient.front());
                glLightfv(GL_LIGHT7, GL_DIFFUSE, &diffuse.front());
                glLightfv(GL_LIGHT7, GL_SPECULAR, &specular.front());
                
                break;  */              
            
            
        }
        
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
        
    } else{
        
        glDisable(GL_LIGHTING);
        
    }
    
}
