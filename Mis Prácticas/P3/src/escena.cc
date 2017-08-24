////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 3
//
// escena.cc
//
////////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <typeinfo>
#include "escena.h"

Escena::Escena() {
    
    Front_plane = 50;
    Back_plane = 2000;
    Observer_distance = 4 * Front_plane;
    Observer_angle_x = Observer_angle_y = 0;
    ejes.changeAxisSize(5000);
    
    //obj = new ObjPLY(false, "tongue.ply");
    obj = new DogHead();
    //obj = new Cube();
        
}

void Escena::inicializar(int UI_window_width, int UI_window_height) {

    glClearColor(1, 1, 1, 1); // se indica cual sera el color para limpiar la ventana	(r,v,a,al)

    glEnable(GL_DEPTH_TEST); // se habilita el z-bufer

    this->change_projection();
    Width = UI_window_width / 10;
    Height = UI_window_height / 10;
    glViewport(0, 0, UI_window_width, UI_window_height);
    
    // Inicialización de las variables
    // -1 -> deshabilitado, 0 -> disminuye, 1 -> aumenta
    listIncDec.push_back(-1);
    listIncDec.push_back(-1);
    listIncDec.push_back(-1);
    listIncDec.push_back(-1);
    listIncDec.push_back(-1);   
    
    type = 2;

}


//**************************************************************************
// Funcion que dibuja objetos en la escena
//***************************************************************************

void Escena::draw_objects() {
    
    obj->draw();

}

void Escena::dibujar() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
    change_observer();
    draw_axis();
    draw_objects();
    
}

int Escena::teclaPulsada(unsigned char Tecla1, int x, int y) {

    std::cout << "Tecla" << Tecla1 << std::endl;
    
    GLenum polygonMode;
    bool chess;
        
    // En caso de comenzar con ObjPLY
    /*if(file.empty())
        file = dynamic_cast<ObjPLY*>(obj)->getFile();*/
        
    ////////////////////////////////////////////////////////////////////////////
    // Teclas para la práctica 3
    //
    
    switch(Tecla1){
        
        case 'q':
            return 1;
            break;
        
        // points
        case 'p':
            obj->setPolygonMode(GL_POINT);
            obj->setChess(false);
            break;
            
        // lines
        case 'l':            
            obj->setPolygonMode(GL_LINE);
            obj->setChess(false);
            break;
            
        // side
        case 's':
            obj->setPolygonMode(GL_FILL);
            obj->setChess(false);
            break;
            
        // chess
        case 'a':
            obj->setPolygonMode(GL_FILL);
            obj->setChess(true);
            break;
            
        // Activa el tipo 1
        case '1':
        case '2':
        case '!':
            type = 1;
            
            for(unsigned int i=0; i<listIncDec.size(); i++){
                listIncDec[i] = -1;
            }
            
            break;
            
        // Activa el tipo 2
        case '3':
        case '"':
            type = 2;
            polygonMode = obj->getPolygonMode();
            chess = obj->getChess();

            obj = new DogHead();

            obj->setPolygonMode(polygonMode);
            obj->setChess(chess);
            break;
            
    }
    
    // Práctica 1, 2
    if(type == 1){
        
        switch(Tecla1){
        
            case 'q':
                return 1;
                break;

            // points
            case 'p':
                obj->setPolygonMode(GL_POINT);
                obj->setChess(false);
                break;

            // lines
            case 'l':            
                obj->setPolygonMode(GL_LINE);
                obj->setChess(false);
                break;

            // side
            case 's':
                obj->setPolygonMode(GL_FILL);
                obj->setChess(false);
                break;

            // chess
            case 'a':
                obj->setPolygonMode(GL_FILL);
                obj->setChess(true);
                break;

            // tetraedro
            case 't':

                polygonMode = obj->getPolygonMode();
                chess = obj->getChess();

                obj = new Tetrahedron();
                
                obj->setCenter(true);

                obj->setPolygonMode(polygonMode);
                obj->setChess(chess);

                break;

            // cubo
            case 'c':

                polygonMode = obj->getPolygonMode();
                chess = obj->getChess();

                obj = new Cube();
                
                obj->setCenter(true);

                obj->setPolygonMode(polygonMode);
                obj->setChess(chess);

                break;

            // diamond
            case 'd':

                polygonMode = obj->getPolygonMode();
                chess = obj->getChess();

                obj = new Diamond();
                
                obj->setCenter(true);

                obj->setPolygonMode(polygonMode);
                obj->setChess(chess);

                break;

            // objeto PLY pidiendo el nombre del fichero ply
            case '1':
            case 'o':

                polygonMode = obj->getPolygonMode();
                chess = obj->getChess();

                obj = new ObjPLY(true);
                
                obj->setCenter(true);
                obj->setScale(true);

                obj->setPolygonMode(polygonMode);
                obj->setChess(chess);

                file = dynamic_cast<ObjPLY*>(obj)->getFile();

                break;

            // Carga el modelo por revolución con el perfil preestablecido
            case 'x':

                polygonMode = obj->getPolygonMode();
                chess = obj->getChess();

                obj = new ObjRevX(false);
                
                obj->setCenter(true);
                obj->setScale(true);

                obj->setPolygonMode(polygonMode);
                obj->setChess(chess);

                break;

            // Carga el modelo por revolución con el perfil cargado por PLY
            case '2':
            case 'X':

                polygonMode = obj->getPolygonMode();
                chess = obj->getChess();

                obj = new ObjRevX(true);
                
                obj->setCenter(true);
                obj->setScale(true);

                obj->setPolygonMode(polygonMode);
                obj->setChess(chess);

                break;

            // Carga el modelo por revolución con el perfil preestablecido
            case 'y':

                polygonMode = obj->getPolygonMode();
                chess = obj->getChess();

                obj = new ObjRevY(false);
                
                obj->setCenter(true);
                obj->setScale(true);

                obj->setPolygonMode(polygonMode);
                obj->setChess(chess);

                break;

            // Carga el modelo por revolución con el perfil cargado por PLY
            case 'Y':

                polygonMode = obj->getPolygonMode();
                chess = obj->getChess();

                obj = new ObjRevY(true);
                
                obj->setCenter(true);
                obj->setScale(true);

                obj->setPolygonMode(polygonMode);
                obj->setChess(chess);

                break;

            // Carga el modelo por revolución con el perfil preestablecido
            case 'z':

                polygonMode = obj->getPolygonMode();
                chess = obj->getChess();

                obj = new ObjRevZ(false);
                
                obj->setCenter(true);
                obj->setScale(true);

                obj->setPolygonMode(polygonMode);
                obj->setChess(chess);

                break;

            // Carga el modelo por revolución con el perfil cargado por PLY
            case 'Z':

                polygonMode = obj->getPolygonMode();
                chess = obj->getChess();

                obj = new ObjRevZ(true);
                
                obj->setCenter(true);
                obj->setScale(true);

                obj->setPolygonMode(polygonMode);
                obj->setChess(chess);

                break;

            // Aumenta 1 cara el modelo por revolución
            case '+':

                if(obj->isRev()){

                    string file = dynamic_cast<ObjPLY*>(obj)->getFile();

                    polygonMode = obj->getPolygonMode();
                    chess = obj->getChess();

                    unsigned int sides = obj->getSides()+1;

                    switch(dynamic_cast<ObjRev*>(obj)->getType()){

                        case 'x':                        
                            obj = new ObjRevX(file, sides);
                            break;

                        case 'y':                        
                            obj = new ObjRevY(file, sides);
                            break;  

                        case 'z':                        
                            obj = new ObjRevZ(file, sides);
                            break;  

                    }                    
                
                    obj->setCenter(true);
                    obj->setScale(true);

                    obj->setPolygonMode(polygonMode);
                    obj->setChess(chess);

                }

                break;

            // Aumenta 1 cara el modelo por revolución
            case '-':

                if(obj->isRev()){

                    string file = dynamic_cast<ObjPLY*>(obj)->getFile();

                    polygonMode = obj->getPolygonMode();
                    chess = obj->getChess();

                    unsigned int sides = obj->getSides()-1;

                    switch(dynamic_cast<ObjRev*>(obj)->getType()){

                        case 'x':                        
                            obj = new ObjRevX(file, sides);
                            break;

                        case 'y':                        
                            obj = new ObjRevY(file, sides);
                            break;  

                        case 'z':                        
                            obj = new ObjRevZ(file, sides);
                            break;  

                    }
                
                    obj->setCenter(true);
                    obj->setScale(true);

                    obj->setPolygonMode(polygonMode);
                    obj->setChess(chess);

                }

                break;

            // Pone o quita la tapa superior
            case '/':

                if(obj->isRev()){

                    string file = dynamic_cast<ObjPLY*>(obj)->getFile();

                    polygonMode = obj->getPolygonMode();
                    chess = obj->getChess();

                    unsigned int sides = obj->getSides();

                    switch(dynamic_cast<ObjRev*>(obj)->getType()){

                        case 'x':                        
                            obj = new ObjRevX(file, sides, !dynamic_cast<ObjRevX*>(obj)->getTopCover(), dynamic_cast<ObjRevX*>(obj)->getBottomCover());
                            break;

                        case 'y':                        
                            obj = new ObjRevY(file, sides, !dynamic_cast<ObjRevY*>(obj)->getTopCover(), dynamic_cast<ObjRevY*>(obj)->getBottomCover());
                            break;  

                        case 'z':                        
                            obj = new ObjRevZ(file, sides, !dynamic_cast<ObjRevZ*>(obj)->getTopCover(), dynamic_cast<ObjRevZ*>(obj)->getBottomCover());
                            break;  

                    }
                
                    obj->setCenter(true);
                    obj->setScale(true);

                    obj->setPolygonMode(polygonMode);
                    obj->setChess(chess);

                }

                break;

            // Pone o quita la tapa inferior
            case '*':

                if(obj->isRev()){

                    string file = dynamic_cast<ObjPLY*>(obj)->getFile();

                    polygonMode = obj->getPolygonMode();
                    chess = obj->getChess();

                    unsigned int sides = obj->getSides();

                    switch(dynamic_cast<ObjRev*>(obj)->getType()){

                        case 'x':                        
                            obj = new ObjRevX(file, sides, dynamic_cast<ObjRevX*>(obj)->getTopCover(), !dynamic_cast<ObjRevX*>(obj)->getBottomCover());
                            break;

                        case 'y':                        
                            obj = new ObjRevY(file, sides, dynamic_cast<ObjRevY*>(obj)->getTopCover(), !dynamic_cast<ObjRevY*>(obj)->getBottomCover());
                            break;  

                        case 'z':                        
                            obj = new ObjRevZ(file, sides, dynamic_cast<ObjRevZ*>(obj)->getTopCover(), !dynamic_cast<ObjRevZ*>(obj)->getBottomCover());
                            break;  

                    }
                
                    obj->setCenter(true);
                    obj->setScale(true);

                    obj->setPolygonMode(polygonMode);
                    obj->setChess(chess);

                }

                break;

        }
    
    // Práctica 3
    }else if(type == 2){
    
        switch(Tecla1){

            // Activa o cancela el movimiento de la lengua
            case '6':
                if(listIncDec[0] == -1)
                    listIncDec[0] = 1;
                else
                    listIncDec[0] = -1;
                break;

            // Aumenta la lengua
            case 'Z':
                dynamic_cast<DogHead*>(obj)->increaseTongue();
                break;

            // Disminuye la lengua
            case 'z':
                dynamic_cast<DogHead*>(obj)->decreaseTongue();
                break;

            // Aumenta la velocidad de la lengua
            case 'B':
                dynamic_cast<DogHead*>(obj)->increaseTongueSpeed();
                break;

            // Disminuye la velocidad de la lengua
            case 'b':
                dynamic_cast<DogHead*>(obj)->decreaseTongueSpeed();
                break;

            // Activa o cancela el movimiento de la boca
            case '7':
                if(listIncDec[1] == -1)
                    listIncDec[1] = 1;
                else
                    listIncDec[1] = -1;
                break;

            // Aumenta la boca
            case 'X':
                dynamic_cast<DogHead*>(obj)->increaseMouth();
                break;

            // Disminuye la boca
            case 'x':
                dynamic_cast<DogHead*>(obj)->decreaseMouth();
                break;

            // Aumenta la velocidad de la boca
            case 'N':
                dynamic_cast<DogHead*>(obj)->increaseMouthSpeed();
                break;

            // Disminuye la velocidad de la boca
            case 'n':
                dynamic_cast<DogHead*>(obj)->decreaseMouthSpeed();
                break;

            // Activa o cancela el movimiento de las orejas
            case '8':
                if(listIncDec[2] == -1)
                    listIncDec[2] = 1;
                else
                    listIncDec[2] = -1;
                break;

            // Aumenta las orejas
            case 'C':
                dynamic_cast<DogHead*>(obj)->increaseEars();
                break;

            // Disminuye las orejas
            case 'c':
                dynamic_cast<DogHead*>(obj)->decreaseEars();
                break;

            // Aumenta la velocidad de las orejas
            case 'M':
                dynamic_cast<DogHead*>(obj)->increaseEarsSpeed();
                break;

            // Disminuye la velocidad de las orejas
            case 'm':
                dynamic_cast<DogHead*>(obj)->decreaseEarsSpeed();
                break;

            // Activa o cancela el movimiento de los ojos
            case '9':
                if(listIncDec[3] == -1)
                    listIncDec[3] = 1;
                else
                    listIncDec[3] = -1;
                break;

            // Aumenta los ojos
            case 'W':
                dynamic_cast<DogHead*>(obj)->increaseEyes();
                break;

            // Disminuye los ojos
            case 'w':
                dynamic_cast<DogHead*>(obj)->decreaseEyes();
                break;

            // Aumenta la velocidad de los ojos
            case 'R':
                dynamic_cast<DogHead*>(obj)->increaseEyesSpeed();
                break;

            // Disminuye la velocidad de los ojos
            case 'r':
                dynamic_cast<DogHead*>(obj)->decreaseEyesSpeed();
                break;

            // Activa o cancela el movimiento de la cabeza
            case '0':
                if(listIncDec[4] == -1)
                    listIncDec[4] = 1;
                else
                    listIncDec[4] = -1;
                break;

            // Aumenta la cabeza
            case 'E':
                dynamic_cast<DogHead*>(obj)->increaseHead();
                break;

            // Disminuye la cabeza
            case 'e':
                dynamic_cast<DogHead*>(obj)->decreaseHead();
                break;

            // Aumenta la velocidad de la cabeza
            case 'T':
                dynamic_cast<DogHead*>(obj)->increaseHeadSpeed();
                break;

            // Disminuye la velocidad de la cabeza
            case 't':
                dynamic_cast<DogHead*>(obj)->decreaseHeadSpeed();
                break;
                
            // Aumenta la velocidad de todo
            case '+':
                dynamic_cast<DogHead*>(obj)->increaseSpeedAll();
                break;

            // Disminuye la velocidad de todo
            case '-':
                dynamic_cast<DogHead*>(obj)->decreaseSpeedAll();
                break;

        }
    
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // Teclas para la práctica 1 y práctica 2
    //
    
    /**/
    
    //
    ////////////////////////////////////////////////////////////////////////////
    
    return 0;
    
}

void Escena::teclaEspecial(int Tecla1, int x, int y) {
    switch (Tecla1) {
        case GLUT_KEY_LEFT:Observer_angle_y--;
            break;
        case GLUT_KEY_RIGHT:Observer_angle_y++;
            break;
        case GLUT_KEY_UP:Observer_angle_x--;
            break;
        case GLUT_KEY_DOWN:Observer_angle_x++;
            break;
        case GLUT_KEY_PAGE_UP:Observer_distance *= 1.2;
            break;
        case GLUT_KEY_PAGE_DOWN:Observer_distance /= 1.2;
            break;
    }

    std::cout << Observer_distance << std::endl;
}


//**************************************************************************
// Funcion para definir la transformaci�n de proyeccion
//***************************************************************************

void Escena::change_projection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-Width, Width, -Height, Height, Front_plane, Back_plane);
}

void Escena::redimensionar(int newWidth, int newHeight) {
    change_projection();
    Width = newWidth / 10;
    Height = newHeight / 10;
    glViewport(0, 0, newWidth, newHeight);
}


//**************************************************************************
// Funcion para definir la transformaci�n de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer() {

    // posicion del observador
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -Observer_distance);
    glRotatef(Observer_angle_x, 1, 0, 0);
    glRotatef(Observer_angle_y, 0, 1, 0);
}


//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void Escena::draw_axis() {
    ejes.draw();
}

// Función que se ejecuta cuando no pasa nada y donde se le da movimiento
// al objeto
void Escena::idle(){
    
    // Lengua
    if(listIncDec[0] != -1){
    
        if(listIncDec[0] == 1){

            if(dynamic_cast<DogHead*>(obj)->increaseTongue()){
                listIncDec[0] = 0;
            }

        } else{

            if(dynamic_cast<DogHead*>(obj)->decreaseTongue()){
                listIncDec[0] = 1;
            }

        }
    
    }
    
    // Boca
    if(listIncDec[1] != -1){
        
        if(listIncDec[1] == 1){

            if(dynamic_cast<DogHead*>(obj)->increaseMouth()){
                listIncDec[1] = 0;
            }

        } else{

            if(dynamic_cast<DogHead*>(obj)->decreaseMouth()){
                listIncDec[1] = 1;
            }

        }
    
    }
    
    // Orejas
    if(listIncDec[2] != -1){
    
        if(listIncDec[2] == 1){

            if(dynamic_cast<DogHead*>(obj)->increaseEars()){
                listIncDec[2] = 0;
            }

        } else{

            if(dynamic_cast<DogHead*>(obj)->decreaseEars()){
                listIncDec[2] = 1;
            }

        }
        
    }

    // Ojos
    if(listIncDec[3] != -1){
    
        if(listIncDec[3] == 1){

            if(dynamic_cast<DogHead*>(obj)->increaseEyes()){
                listIncDec[3] = 0;
            }

        } else{

            if(dynamic_cast<DogHead*>(obj)->decreaseEyes()){
                listIncDec[3] = 1;
            }

        }
        
    }

    // Cabeza
    if(listIncDec[4] != -1){
    
        if(listIncDec[4] == 1){

            if(dynamic_cast<DogHead*>(obj)->increaseHead()){
                listIncDec[4] = 0;
            }

        } else{

            if(dynamic_cast<DogHead*>(obj)->decreaseHead()){
                listIncDec[4] = 1;
            }

        }
        
    }
    
}




