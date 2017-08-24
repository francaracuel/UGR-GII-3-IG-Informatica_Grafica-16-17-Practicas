////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 5
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
    Back_plane = 2000;    Back_plane = 2000;

    Observer_distance = 4 * Front_plane;
    Observer_angle_x = Observer_angle_y = 0;
    ejes.changeAxisSize(5000);
    
    type = 4;
    
    switch(type){
        
        case 1: 
            obj = new Diamond("madera.jpg", false);
            obj->setPolygonMode(GL_FILL);
            obj->setChess(true);
            obj->setShading(1);
            break;
            
        case 2: 
            obj = new ObjPLY(false, "b", "madera.jpg", false);
            obj->setPolygonMode(GL_FILL);
            obj->setChess(true);
            obj->setShading(1);
            obj->setScale(true);
            break;
            
        case 3: 
            obj = new DogHead("dog.jpg", false);
            obj->setPolygonMode(GL_FILL);
            obj->setChess(true);
            obj->setShading(1);
            break;
            
        case 4: 
            
            Observer_distance *= 2;
            
            setP4();
            
            break;
            
    }
            
}

void Escena::inicializar(int UI_window_width, int UI_window_height) {

    glClearColor(1, 1, 1, 1); // se indica cual sera el color para limpiar la ventana	(r,v,a,al)

    glEnable(GL_DEPTH_TEST); // se habilita el z-bufer
    
    Width = UI_window_width / 10;
    Height = UI_window_height / 10;
    
    // Se inicializa el vector de cámaras
    listCamera.push_back(new Camera(Observer_distance, 0, 
            0, Front_plane, Back_plane, Width, Height, 
            0));
    
    listCamera.push_back(new Camera(Observer_distance, 0, 
            -100, Front_plane, Back_plane, Width, Height, 
            1));
    
    listCamera.push_back(new Camera(Observer_distance, 100, 
            0, Front_plane, Back_plane, Width, Height, 
            0));
        
    numCamera = 0;
    
    moving = false;
    
    examine = -1;

    this->change_projection();
    glViewport(0, 0, UI_window_width, UI_window_height);
           
    // Inicialización de las variables
    // -1 -> deshabilitado, 0 -> disminuye, 1 -> aumenta
    listIncDec.push_back(-1);
    listIncDec.push_back(-1);
    listIncDec.push_back(-1);
    listIncDec.push_back(-1);
    listIncDec.push_back(-1);   
    
}


//**************************************************************************
// Funcion que dibuja objetos en la escena
//***************************************************************************

void Escena::draw_objects() {
        
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    change_observer();
    draw_axis();
    
    if(type!=4){
        
        glPushMatrix();
            obj->draw();
        glPopMatrix();
        
    }else{
        
        glInitNames();
        glPushName(1);
        
        
        glPushMatrix();
            glTranslatef(-150, -100, 0);
            obj->draw();
        glPopMatrix();
        
        glPopName();
        glPushName(2);
        
        glPushMatrix();
            glTranslatef(0, 0, 150);
            obj2->draw();
        glPopMatrix();
        
        glPopName();
        glPushName(3);
        
        glPushMatrix();
            glTranslatef(0, 0, -150);
            obj3->draw();
        glPopMatrix();
        
        glPopName();
        glPushName(4);
        
        glPushMatrix();
            glTranslatef(150, 0, 0);
            obj4->draw();
        glPopMatrix();
        
        glPopName();
        
    }
    
    glutSwapBuffers();

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
    bool normal;
        
    // En caso de comenzar con ObjPLY
    /*if(file.empty())
        file = dynamic_cast<ObjPLY*>(obj)->getFile();*/
        
    switch(Tecla1){
        
        case 'q':
            return 1;
            break;
        
        // points
        case 'p':
            
            obj->setPolygonMode(GL_POINT);
            obj->setChess(false);
            
            if(type==4){
                obj2->setPolygonMode(GL_POINT);
                obj2->setChess(false);
                obj3->setPolygonMode(GL_POINT);
                obj3->setChess(false);
                obj4->setPolygonMode(GL_POINT);
                obj4->setChess(false);                
            }
            
            break;
            
        // lines
        case 'l':  
            
            obj->setPolygonMode(GL_LINE);
            obj->setChess(false);
            
            if(type==4){
                obj2->setPolygonMode(GL_LINE);
                obj2->setChess(false);
                obj3->setPolygonMode(GL_LINE);
                obj3->setChess(false);
                obj4->setPolygonMode(GL_LINE);
                obj4->setChess(false);                
            }
            
            break;
            
        // side
        case 's':
            
            obj->setPolygonMode(GL_FILL);
            obj->setChess(false);
            
            if(type==4){
                obj2->setPolygonMode(GL_FILL);
                obj2->setChess(false);
                obj3->setPolygonMode(GL_FILL);
                obj3->setChess(false);
                obj4->setPolygonMode(GL_FILL);
                obj4->setChess(false);                
            }
            
            break;
            
        // chess
        case 'a':
            
            obj->setPolygonMode(GL_FILL);
            obj->setChess(true);
            
            if(type==4){
                obj2->setPolygonMode(GL_FILL);
                obj2->setChess(false);
                obj3->setPolygonMode(GL_FILL);
                obj3->setChess(false);
                obj4->setPolygonMode(GL_FILL);
                obj4->setChess(false);                
            }            
            
            break;
            
        // normales de vértices
        case '<':
            
            obj->setNormalVertex(!obj->getNormalVertex());
            
            if(type==4){
                obj2->setNormalVertex(!obj2->getNormalVertex());
                obj3->setNormalVertex(!obj3->getNormalVertex());
                obj4->setNormalVertex(!obj4->getNormalVertex());
            }  
            
            break;
            
        // normales de caras
        case '>':
            
            obj->setNormalIndex(!obj->getNormalIndex());
            
            if(type==4){
                obj2->setNormalVertex(!obj2->getNormalIndex());
                obj3->setNormalVertex(!obj3->getNormalIndex());
                obj4->setNormalVertex(!obj4->getNormalIndex());
            }  
            
            break;
            
        // light
        case ',':
            
            obj->setActiveLight(!obj->getActiveLight());
            
            if(type==4){
                obj2->setActiveLight(!obj2->getActiveLight());
                obj3->setActiveLight(!obj3->getActiveLight());
                obj4->setActiveLight(!obj4->getActiveLight());
            }  
            
            break;
            
        // sombreado
        case ';':
            
            obj->setShading((obj->getShading()==0) ? 1 : 0);
            
            if(type==4){
                obj2->setShading((obj2->getShading()==0) ? 1 : 0);
                obj3->setShading((obj3->getShading()==0) ? 1 : 0);
                obj4->setShading((obj4->getShading()==0) ? 1 : 0);
            }  
            
            break;       
            
        case 'g':
            
            numCamera++;
            
            if(numCamera%listCamera.size()==0){
                numCamera = 0;
            }
            
            cout << endl << "Se ha cambiado a la cámara " << numCamera << endl;
            
            break;
            
        case 'W':
            listCamera[numCamera]->decreaseEyeZ();
            listCamera[numCamera]->decreaseAtZ();
            break;
            
        case 'A':
            listCamera[numCamera]->decreaseEyeX();
            listCamera[numCamera]->decreaseAtX();
            break;
            
        case 'S':
            listCamera[numCamera]->increaseEyeZ();
            listCamera[numCamera]->increaseAtZ();
            break;
            
        case 'D':
            listCamera[numCamera]->increaseEyeX();
            listCamera[numCamera]->increaseAtX();
            break;
                      
        case 'R':
            listCamera[numCamera]->setEye(0, 0, 100);
            listCamera[numCamera]->setAt(0, 0, 0);
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
            
        // Activa el tipo 3
        case '3':
        case '"':
            
            type = 3;
            polygonMode = obj->getPolygonMode();
            chess = obj->getChess();

            obj = new DogHead("dog.jpg", false);

            obj->setPolygonMode(polygonMode);
            obj->setChess(chess);
            obj->setShading(1);
            
            break;
        
        // Práctica 4
        case '4':
            
            type = 4;
            
            setP4();
            break;
            
    }
    
    // Práctica 1, 2
    if(type == 1 || type == 2){
        
        switch(Tecla1){
                    
            // tetraedro
            case 't':

                polygonMode = obj->getPolygonMode();
                chess = obj->getChess();

                obj = new Tetrahedron();
                
                obj->setCenter(true);

                obj->setPolygonMode(polygonMode);
                obj->setChess(chess);
                obj->setShading(1);

                break;

            // cubo
            case 'c':

                polygonMode = obj->getPolygonMode();
                chess = obj->getChess();

                obj = new Cube();
                
                obj->setCenter(true);

                obj->setPolygonMode(polygonMode);
                obj->setChess(chess);
                obj->setShading(1);

                break;

            // diamond
            case 'd':

                polygonMode = obj->getPolygonMode();
                chess = obj->getChess();

                obj = new Diamond();
                
                obj->setCenter(true);

                obj->setPolygonMode(polygonMode);
                obj->setChess(chess);
                obj->setShading(1);

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
                obj->setShading(1);

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
                obj->setShading(1);

                break;

            // Carga el modelo por revolución con el perfil cargado por PLY
            case 'X':

                polygonMode = obj->getPolygonMode();
                chess = obj->getChess();

                obj = new ObjRevX(true);
                
                obj->setCenter(true);
                obj->setScale(true);

                obj->setPolygonMode(polygonMode);
                obj->setChess(chess);
                obj->setShading(1);

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
                obj->setShading(1);

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
                obj->setShading(1);

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
                obj->setShading(1);

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
                obj->setShading(1);

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
                            obj = new ObjRevX(sides, file);
                            break;

                        case 'y':                        
                            obj = new ObjRevY(sides, file);
                            break;  

                        case 'z':                        
                            obj = new ObjRevZ(sides, file);
                            break;  

                    }                    
                
                    obj->setCenter(true);
                    obj->setScale(true);

                    obj->setPolygonMode(polygonMode);
                    obj->setChess(chess);
                    obj->setShading(1);

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
                            obj = new ObjRevX(sides, file);
                            break;

                        case 'y':                        
                            obj = new ObjRevY(sides, file);
                            break;  

                        case 'z':                        
                            obj = new ObjRevZ(sides ,file);
                            break;  

                    }
                
                    obj->setCenter(true);
                    obj->setScale(true);

                    obj->setPolygonMode(polygonMode);
                    obj->setChess(chess);
                    obj->setShading(1);

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
                    obj->setShading(1);

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
                    obj->setShading(1);

                }

                break;

        }
    
    // Práctica 3
    }else if(type == 3){
    
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
                
            // Aumenta el tamaño de los ojos
            case 'Y':
                dynamic_cast<DogHead*>(obj)->increaseEyesSize();
                break;

            // Disminuye el tamaño de los ojos
            case 'y':
                dynamic_cast<DogHead*>(obj)->decreaseEyesSize();
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
    
    } else if(type == 4){
        
        int f = 10;
    
        switch(tolower(Tecla1)){
            
            case 'a':
                for(unsigned int i=0; i<dynamic_cast<Can*>(obj)->getListObj().size(); i++){                
                    dynamic_cast<Can*>(obj)->getListObj()[i]->getLight()->setBeta(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight()->getBeta()+f);
                }
                obj2->getLight()->setBeta(obj2->getLight()->getBeta()+f);
                obj3->getLight()->setBeta(obj2->getLight()->getBeta()+f);
                obj4->getLight()->setBeta(obj2->getLight()->getBeta()+f);
                break;
                
            case 'z':
                for(unsigned int i=0; i<dynamic_cast<Can*>(obj)->getListObj().size(); i++){                
                    dynamic_cast<Can*>(obj)->getListObj()[i]->getLight()->setBeta(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight()->getBeta()-f);
                }
                obj2->getLight()->setBeta(obj2->getLight()->getBeta()-f);
                obj3->getLight()->setBeta(obj2->getLight()->getBeta()-f);
                obj4->getLight()->setBeta(obj2->getLight()->getBeta()-f);
                break;
            
            case 'x':
                for(unsigned int i=0; i<dynamic_cast<Can*>(obj)->getListObj().size(); i++){                
                    dynamic_cast<Can*>(obj)->getListObj()[i]->getLight()->setAlpha(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight()->getAlpha()+f);
                }
                obj2->getLight()->setAlpha(obj2->getLight()->getAlpha()+f);
                obj3->getLight()->setAlpha(obj2->getLight()->getAlpha()+f);
                obj4->getLight()->setAlpha(obj2->getLight()->getAlpha()+f);
                break;
                
            case 'c':
                for(unsigned int i=0; i<dynamic_cast<Can*>(obj)->getListObj().size(); i++){                
                    dynamic_cast<Can*>(obj)->getListObj()[i]->getLight()->setAlpha(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight()->getAlpha()-f);
                }
                obj2->getLight()->setAlpha(obj2->getLight()->getAlpha()-f);
                obj3->getLight()->setAlpha(obj2->getLight()->getAlpha()-f);
                obj4->getLight()->setAlpha(obj2->getLight()->getAlpha()-f);
                break;
                
            case 'y':
                for(unsigned int i=0; i<dynamic_cast<Can*>(obj)->getListObj().size(); i++){                
                    dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->setPos(
                            get<0>(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->getPos())+f, 
                            get<1>(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->getPos()), 
                            get<2>(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->getPos()));
                }
                obj2->getLight2()->setPos(
                        get<0>(obj2->getLight2()->getPos())+f, 
                        get<1>(obj2->getLight2()->getPos()), 
                        get<2>(obj2->getLight2()->getPos()));
                obj3->getLight2()->setPos(
                        get<0>(obj3->getLight2()->getPos())+f, 
                        get<1>(obj3->getLight2()->getPos()), 
                        get<2>(obj3->getLight2()->getPos()));
                obj4->getLight2()->setPos(
                        get<0>(obj4->getLight2()->getPos())+f, 
                        get<1>(obj4->getLight2()->getPos()), 
                        get<2>(obj4->getLight2()->getPos()));
                break;
                
            case 'u':
                for(unsigned int i=0; i<dynamic_cast<Can*>(obj)->getListObj().size(); i++){                
                    dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->setPos(
                            get<0>(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->getPos()), 
                            get<1>(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->getPos())+f, 
                            get<2>(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->getPos()));
                }
                obj2->getLight2()->setPos(
                        get<0>(obj2->getLight2()->getPos()), 
                        get<1>(obj2->getLight2()->getPos())+f, 
                        get<2>(obj2->getLight2()->getPos()));
                obj3->getLight2()->setPos(
                        get<0>(obj3->getLight2()->getPos()), 
                        get<1>(obj3->getLight2()->getPos())+f, 
                        get<2>(obj3->getLight2()->getPos()));
                obj4->getLight2()->setPos(
                        get<0>(obj4->getLight2()->getPos()), 
                        get<1>(obj4->getLight2()->getPos())+f, 
                        get<2>(obj4->getLight2()->getPos()));
                break;
                
            case 'i':
                for(unsigned int i=0; i<dynamic_cast<Can*>(obj)->getListObj().size(); i++){                
                    dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->setPos(
                            get<0>(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->getPos()), 
                            get<1>(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->getPos()), 
                            get<2>(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->getPos())+f);
                }
                obj2->getLight2()->setPos(
                        get<0>(obj2->getLight2()->getPos()), 
                        get<1>(obj2->getLight2()->getPos()), 
                        get<2>(obj2->getLight2()->getPos())+f);
                obj3->getLight2()->setPos(
                        get<0>(obj3->getLight2()->getPos()), 
                        get<1>(obj3->getLight2()->getPos()), 
                        get<2>(obj3->getLight2()->getPos())+f);
                obj4->getLight2()->setPos(
                        get<0>(obj4->getLight2()->getPos()), 
                        get<1>(obj4->getLight2()->getPos()), 
                        get<2>(obj4->getLight2()->getPos())+f);
                break;
                
            case 'h':
                for(unsigned int i=0; i<dynamic_cast<Can*>(obj)->getListObj().size(); i++){                
                    dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->setPos(
                            get<0>(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->getPos())-f, 
                            get<1>(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->getPos()), 
                            get<2>(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->getPos()));
                }
                obj2->getLight2()->setPos(
                        get<0>(obj2->getLight2()->getPos())-f, 
                        get<1>(obj2->getLight2()->getPos()), 
                        get<2>(obj2->getLight2()->getPos()));
                obj3->getLight2()->setPos(
                        get<0>(obj3->getLight2()->getPos())-f, 
                        get<1>(obj3->getLight2()->getPos()), 
                        get<2>(obj3->getLight2()->getPos()));
                obj4->getLight2()->setPos(
                        get<0>(obj4->getLight2()->getPos())-f, 
                        get<1>(obj4->getLight2()->getPos()), 
                        get<2>(obj4->getLight2()->getPos()));
                break;
                
            case 'j':
                for(unsigned int i=0; i<dynamic_cast<Can*>(obj)->getListObj().size(); i++){                
                    dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->setPos(
                            get<0>(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->getPos()), 
                            get<1>(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->getPos())-f, 
                            get<2>(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->getPos()));
                }
                obj2->getLight2()->setPos(
                        get<0>(obj2->getLight2()->getPos()), 
                        get<1>(obj2->getLight2()->getPos())-f, 
                        get<2>(obj2->getLight2()->getPos()));
                obj3->getLight2()->setPos(
                        get<0>(obj3->getLight2()->getPos()), 
                        get<1>(obj3->getLight2()->getPos())-f, 
                        get<2>(obj3->getLight2()->getPos()));
                obj4->getLight2()->setPos(
                        get<0>(obj4->getLight2()->getPos()), 
                        get<1>(obj4->getLight2()->getPos())-f, 
                        get<2>(obj4->getLight2()->getPos()));
                break;
                
            case 'k':
                for(unsigned int i=0; i<dynamic_cast<Can*>(obj)->getListObj().size(); i++){                
                    dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->setPos(
                            get<0>(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->getPos()), 
                            get<1>(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->getPos()), 
                            get<2>(dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->getPos())-f);
                }
                obj2->getLight2()->setPos(
                        get<0>(obj2->getLight2()->getPos()), 
                        get<1>(obj2->getLight2()->getPos()), 
                        get<2>(obj2->getLight2()->getPos())-f);
                obj3->getLight2()->setPos(
                        get<0>(obj3->getLight2()->getPos()), 
                        get<1>(obj3->getLight2()->getPos()), 
                        get<2>(obj3->getLight2()->getPos())-f);
                obj4->getLight2()->setPos(
                        get<0>(obj4->getLight2()->getPos()), 
                        get<1>(obj4->getLight2()->getPos()), 
                        get<2>(obj4->getLight2()->getPos())-f);
                break;
                
            
            
        }
        
    }
        
    return 0;
    
}

void Escena::teclaEspecial(int Tecla1, int x, int y) {
    
    switch (Tecla1) {
        
        case GLUT_KEY_LEFT:
            listCamera[numCamera]->decreaseAngleY();
            break;
        case GLUT_KEY_RIGHT:
            listCamera[numCamera]->increaseAngleY();
            break;
        case GLUT_KEY_UP:
            listCamera[numCamera]->decreaseAngleX();
            break;
        case GLUT_KEY_DOWN:
            listCamera[numCamera]->increaseAngleX();
            break;
        case GLUT_KEY_PAGE_UP:
            listCamera[numCamera]->increaseDistance();
            break;
        case GLUT_KEY_PAGE_DOWN:
            listCamera[numCamera]->decreaseDistance();
            break;       
            
        case 1:
            
            numCamera = 0;
            change_projection();
            
            break;
            
        case 2:
            
            numCamera = 1;
            change_projection();
            
            break;
            
        case 3:
            
            numCamera = 2;
            change_projection();
            
            break;
        
        /*case GLUT_KEY_LEFT:Observer_angle_y--;
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
            break;*/
    }

    std::cout << Observer_distance << std::endl;
    
    cout << endl << "Cámara activa: " << numCamera << endl;
}


//**************************************************************************
// Funcion para definir la transformaci�n de proyeccion
//***************************************************************************

void Escena::change_projection() {
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    cout << endl << "Projection: " << listCamera[numCamera]->getType() << endl;
            
    if(listCamera[numCamera]->getType() == 0){
        
        glFrustum(-listCamera[numCamera]->getWidth(), 
            listCamera[numCamera]->getWidth(), 
            -listCamera[numCamera]->getHeight(), 
            listCamera[numCamera]->getHeight(), 
            listCamera[numCamera]->getFrontPlane(), 
            listCamera[numCamera]->getBackPlane());
        
    } else{
        
        glOrtho(-listCamera[numCamera]->getWidth(), 
            listCamera[numCamera]->getWidth(), 
            -listCamera[numCamera]->getHeight(), 
            listCamera[numCamera]->getHeight(), 
            listCamera[numCamera]->getFrontPlane(), 
            listCamera[numCamera]->getBackPlane());
        
    }
        
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //glFrustum(-Width, Width, -Height, Height, Front_plane, Back_plane);
    
}

void Escena::redimensionar(int newWidth, int newHeight) {
    
    change_projection();
    
    listCamera[numCamera]->setWidth(newWidth / 10);
    listCamera[numCamera]->setHeight(newHeight / 10);
    
    //Width = newWidth / 10;
    //Height = newHeight / 10;
        
    glViewport(0, 0, newWidth, newHeight);
    
}


//**************************************************************************
// Funcion para definir la transformaci�n de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer() {

    // posicion del observador
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    listCamera[numCamera]->setObserver();
    
    glTranslatef(0, 0, -listCamera[numCamera]->getDistance());
    glRotatef(listCamera[numCamera]->getAngleX(), 1, 0, 0);
    glRotatef(listCamera[numCamera]->getAngleY(), 0, 1, 0);
    
    //glTranslatef(0, 0, -Observer_distance);
    //glRotatef(Observer_angle_x, 1, 0, 0);
    //glRotatef(Observer_angle_y, 0, 1, 0);
    
}


//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void Escena::draw_axis() {
    
    // Se apagan las luces para pintar los ejes de su color
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    
    ejes.draw();
    
    // Se vuelven a encender las luces
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    
}

// Función que se ejecuta cuando no pasa nada y donde se le da movimiento
// al objeto
void Escena::idle(){
    
    switch(type){
        
        case 3:
            
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

            break;
        
        default:
            
            break;
            
    }
    
}

// Dibuja los elementos de la práctica 4
void Escena::setP4(){
    
    obj = new Can("lata.jpg", false);
    obj->setCenter(true);
    obj->setPolygonMode(GL_FILL);
    obj->setChess(true);
    obj->setShading(1);    
    obj->getMaterial()->setAmbient(vector<GLfloat>{0.6, 0.6, 0.6, 1.0});
    obj->getMaterial()->setDiffuse(vector<GLfloat>{1.0, 1.0, 1.0, 1.0});
    obj->getMaterial()->setShininess(20);
    for(unsigned int i=0; i<dynamic_cast<Can*>(obj)->getListObj().size(); i++){                
        dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->setPos(-20, 200, 50);
        dynamic_cast<Can*>(obj)->getListObj()[i]->getLight2()->setType(0);
    }

    obj2 = new ObjRevX(100, "rx", true, true, "madera.jpg", false);
    obj2->setScale(true);
    obj2->setPolygonMode(GL_FILL);
    obj2->setChess(true);
    obj2->setShading(1);
    obj2->getMaterial()->setAmbient(vector<GLfloat>{0.6, 0.6, 0.6, 1.0});
    obj2->getMaterial()->setDiffuse(vector<GLfloat>{1.0, 1.0, 1.0, 1.0});
    obj2->getMaterial()->setSpecular(vector<GLfloat>{1.0, 1.0, 1.0, 1.0});
    obj2->getMaterial()->setShininess(20);
    obj2->getLight2()->setPos(-20, 200, 50);
    obj2->getLight2()->setType(0);

    obj3 = new ObjRevX("rx", 100, true, true);
    obj3->setScale(true);
    obj3->setPolygonMode(GL_FILL);
    obj3->setChess(true);
    obj3->setShading(1);            
    obj3->getMaterial()->setAmbient(vector<GLfloat>{0.8, 0.8, 0.8, 1.0});
    obj3->getMaterial()->setDiffuse(vector<GLfloat>{1.0, 1.0, 1.0, 1.0});
    obj3->getMaterial()->setSpecular(vector<GLfloat>{0.0, 0.0, 0.0, 0.0});
    obj3->getMaterial()->setShininess(128);
    obj3->getLight()->setType(0);
    obj3->getLight2()->setPos(-20, 200, 50);
    obj3->getLight2()->setType(0);

    obj4 = new ObjRevX("rx", 100, true, true);
    obj4->setScale(true);
    obj4->setPolygonMode(GL_FILL);
    obj4->setChess(true);
    obj4->setShading(1);
    obj4->getMaterial()->setAmbient(vector<GLfloat>{0.0, 0.0, 0.0, 1.0});
    obj4->getMaterial()->setDiffuse(vector<GLfloat>{0.0, 0.0, 0.0, 1.0});
    obj4->getMaterial()->setSpecular(vector<GLfloat>{1.0, 1.0, 1.0, 1.0});
    obj4->getMaterial()->setShininess(20);
    obj4->getLight2()->setPos(-20, 200, 50);
    obj4->getLight2()->setType(0);
    
}

////////////////////////////////////////////////////////////////////////////////
// Evento cuando se pulsa el botón
//
void Escena::click(int button, int state, int x, int y){
    
    if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN)
            moving = true;
        else
            moving = false;
    }
    
    if (button == GLUT_LEFT_BUTTON) {
        
        if (state == GLUT_DOWN){
            
            examine = pick(x, y);
            
            cout << endl << "El objeto pintado es: ";
            
            switch(examine){
            
                // lata
                case 1:

                    cout << "lata";

                    break;

                // madera                
                case 2:

                    cout << "peón de madera";

                    break;

                // blanco
                case 3:

                    cout << "peón blanco";

                    break;

                // negro
                case 4:

                    cout << "peón negro";

                    break;

            }
            
            cout << "." << endl;
            
        }
    }
    
    moveX = x;
    moveY = y;
    
}

////////////////////////////////////////////////////////////////////////////////
// Evento cuando se mueve el ratón
//
void Escena::move(int x, int y){
    
    int xAux = moveX - x;
    int yAux = moveY - y;

    moveX = x;
    moveY = y;
  
    // Botón derecho
    if(moving){
        
        listCamera[numCamera]->setEyeX(listCamera[numCamera]->getEye()[0] - xAux*0.6);
        listCamera[numCamera]->setEyeY(listCamera[numCamera]->getEye()[1] - yAux*0.6);
        
    }
    
    // Examina objeto
    if(examine > -1){
        
        switch(examine){
            
            // lata
            case 1:
                
                //listCamera[numCamera]->setEye();
                //listCamera[numCamera]->setEye(-150, -100, 0);
                
                break;
                
            // madera                
            case 2:
                
                //listCamera[numCamera]->setEye(0, 0, 150);
                
                break;
                
            // blanco
            case 3:
                
                //listCamera[numCamera]->setEye(0, 0, -150);
                
                break;
                
            // negro
            case 4:
                
                //listCamera[numCamera]->setEye(150, 0, 0);
                
                break;
            
        }
        
        //listCamera[numCamera]->setObserver();
        
    }
    
    /*case GLUT_KEY_LEFT:
        listCamera[numCamera]->decreaseAngleY();
        break;
    case GLUT_KEY_RIGHT:
        listCamera[numCamera]->increaseAngleY();
        break;
    case GLUT_KEY_UP:
        listCamera[numCamera]->decreaseAngleX();
        break;
    case GLUT_KEY_DOWN:
        listCamera[numCamera]->increaseAngleX();
        break;
    case GLUT_KEY_PAGE_UP:
        listCamera[numCamera]->increaseDistance();
        break;
    case GLUT_KEY_PAGE_DOWN:
        listCamera[numCamera]->decreaseDistance();
        break;   */
    
}

////////////////////////////////////////////////////////////////////////////////
// Método selección
//
int Escena::pick(unsigned int x, unsigned int y){
    
    // Objeto pulsado
    int object = -1;
    
    // Listado con los objetos seleccionados
    GLuint listSelection[1024]; 
    
    GLint viewport[4]; 

    // Declarar buffer de selección
    glSelectBuffer(50, listSelection);
    
    // Obtener los parámetros del viewport
    glGetIntegerv(GL_VIEWPORT,viewport);
    
    // Pasar OpenGL a modo selección
    glRenderMode(GL_SELECT);

    // Fijar la transformación de proyección para la selección
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPickMatrix(x, viewport[3]-y, 5.0, 5.0, viewport);
    
    glFrustum(-listCamera[numCamera]->getWidth(), 
            listCamera[numCamera]->getWidth(), 
            -listCamera[numCamera]->getHeight(), 
            listCamera[numCamera]->getHeight(), 
            listCamera[numCamera]->getFrontPlane(), 
            listCamera[numCamera]->getBackPlane());

    // Dibujar la escena con nombres
    draw_objects();
    
    // Pasar OpenGl a modo render
    GLuint hits = glRenderMode(GL_RENDER);

    // Restablecer la transformación de proyección (sin gluPickMatrix)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glFrustum(-listCamera[numCamera]->getWidth(), 
            listCamera[numCamera]->getWidth(), 
            -listCamera[numCamera]->getHeight(), 
            listCamera[numCamera]->getHeight(), 
            listCamera[numCamera]->getFrontPlane(), 
            listCamera[numCamera]->getBackPlane());
        
    // Si existe algún objeto pulsado
    if(hits>0) { 
        
        // Objeto del buffer
        unsigned int i=0;
        
        // Valor mínimo de profundidad
        unsigned long z = 999999999999999999;
        
        // Se recorren los objetos que se han pulsado
        for(unsigned int j=0; j<hits; j++) {
            
            // Para que sea correcto, no puede ser 0
            if(listSelection[i]!=0) {
                
                // Profundidad del objeto
                unsigned long zAux = listSelection[i+1]; 
                
                // Si la profundidad actuar el menor que la menor anterior,
                // se actualizan los resultados
                if(zAux<z) {
                    
                    object = listSelection[i+3];
                    z = zAux;
                    
                }
                
            }
            
            // Se adelanta el siguiente objeto a inspeccionar
            i += listSelection[i]+3;
            
        }
    }
    
    // Devolver el resultado
    return object;
    
}