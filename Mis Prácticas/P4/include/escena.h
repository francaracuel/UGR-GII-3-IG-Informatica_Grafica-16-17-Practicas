////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 4
//
// escena.h
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _ESCENA_H
#define _ESCENA_H

#include <vector>
#include "ejes.h"
#include "obj3D.h"
#include "tetrahedron.h"
#include "cube.h"
#include "diamond.h"
#include "obj_ply.h"
#include "sphere.h"
#include "obj_rev_x.h"
#include "obj_rev_y.h"
#include "obj_rev_z.h"
#include "dog_head.h"
#include "can.h"

class Escena {
private:
    // tamaño de los ejes
#define AXIS_SIZE 5000
    Ejes ejes;

    // variables que definen la posicion de la camara en coordenadas polares
    GLfloat Observer_distance;
    GLfloat Observer_angle_x;
    GLfloat Observer_angle_y;

    // variables que controlan la ventana y la transformacion de perspectiva
    GLfloat Width, Height, Front_plane, Back_plane;
    
    // Objeto que se visualiza
    Obj3D *obj, *obj2, *obj3, *obj4;    
    
    // Variables de control para la animación
    vector<int> listIncDec;
    
    // Tipo de objeto que se está visualizando
    // 1 -> Normal
    // 2 -> Jerárquico animado
    int type;

private:
    void clear_window();
    void draw_axis();
    void draw_objects();

    //Transformaci�n de c�mara
    void change_projection();
    void change_observer();
    
    // Se utiliza para poder cambiar el archivo ply que se carga en caliente
    string file;
    
    // Dibuja los elementos de la practica 4
    void setP4();


public:
    Escena();
    void inicializar(int UI_window_width, int UI_window_height);
    void redimensionar(int newWidth, int newHeight);

    // Dibujar
    void dibujar();

    // Interacci�n con la escena
    int teclaPulsada(unsigned char Tecla1, int x, int y);
    void teclaEspecial(int Tecla1, int x, int y);
    
    // Función que se ejecuta cuando no pasa nada y donde se le da movimiento
    // al objeto
    void idle();
    
};
#endif
