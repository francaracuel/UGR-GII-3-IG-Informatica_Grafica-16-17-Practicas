////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 4
//
// obj_rev_x.cc
//
////////////////////////////////////////////////////////////////////////////////

#include "obj_rev_x.h"

////////////////////////////////////////////////////////////////////////////////
// Constructor
//
// Crea la geometría del objeto por revolución
//
ObjRevX::ObjRevX(bool ask) : ObjRev(ask){
        
    init();
    
}

// Crea la geometría del objeto por revolución con un número de caras dadas
ObjRevX::ObjRevX(bool ask, unsigned int sides) : ObjRev(ask, sides){
    
    init();
    
}

// Crea la geometría del objeto por revolución con un número de caras dadas
// y un fichero
ObjRevX::ObjRevX(unsigned int sides, string f) : ObjRev(sides, f){
        
    init();
    
}

// Crea la geometría del objeto por revolución con un número de caras dadas
// y un fichero, indicando si se muestran las tapas o no
ObjRevX::ObjRevX(string f, unsigned int sides, bool top, bool bottom) : 
                ObjRev(f, sides, top, bottom){
    
    init();
    
}

// Crea la geometría del objeto por revolución con un número de caras dadas,
// un fichero y aplicando una textura
ObjRevX::ObjRevX(unsigned int sides, string f, string name, 
        bool generateAutomatic) : ObjRev(sides, f){
    
    material = new Material(name, generateAutomatic);
            
    init();
    
}

// Crea la geometría del objeto por revolución con un número de caras dadas
// y un fichero, indicando si se muestran las tapas o no
ObjRevX::ObjRevX(unsigned int sides, string f, bool top, bool bottom, 
                    string name, bool generateAutomatic) : 
                    ObjRev(f, sides, top, bottom){
    
    material = new Material(name, generateAutomatic);
            
    init();
    
}

////////////////////////////////////////////////////////////////////////////////
// Inicializa todos los datos necesarios
//
void ObjRevX::init(){
    
    type = 'x';
    
    if(file.empty()){
        createOutline();
    } else{
        createOutlinePly();     
    }
                         
    // Se crean los puntos para crear la geometría dependiendo de si hay que 
    // dibujar las tapas o no.
    setPoints();
            
    createGeometry();
    
}

////////////////////////////////////////////////////////////////////////////////
// Crea el perfil del objeto por revolución que se quiere dibujar
//
void ObjRevX::createOutline(){
    
    // Perfil del modelo   
    listVertexOutline.push_back(0);
    listVertexOutline.push_back(axisSize);
    listVertexOutline.push_back(0);
    
    listVertexOutline.push_back(axisSize/4);
    listVertexOutline.push_back(axisSize/2);
    listVertexOutline.push_back(0);
    
    listVertexOutline.push_back(axisSize);
    listVertexOutline.push_back(axisSize/2);
    listVertexOutline.push_back(0);
    
    listVertexOutline.push_back(axisSize/3);
    listVertexOutline.push_back(0);
    listVertexOutline.push_back(0);
    
    listVertexOutline.push_back(axisSize/2.5);
    listVertexOutline.push_back(-axisSize);
    listVertexOutline.push_back(0);
    
}

////////////////////////////////////////////////////////////////////////////////
// Crea la geometría del objeto por revolución que se quiere dibujar
//
void ObjRevX::createGeometry(){
        
    // Se crea el vector de vértices 
    vector<float> listVertex;
    
    // Se sacan las primeras coordenadas para trabajar con ellas y 
    // transformarlas
    float x;
    float y;
    float z;
    
    float auxX;
    
    // Recorre todo el vector de puntos del perfil    
    for(unsigned int i=0; i<listVertexOutline.size(); i=i+3){
            
        x = listVertexOutline[i];
        y = listVertexOutline[i+1];
        z = listVertexOutline[i+2];
        
        //cout << "Nuevo anillo de puntos\n";
        
        // Por cada punto del perfil crea los restantes de su mismo eje Y por
        // revolución
        for(unsigned int j=0; j<side; j++){

            //std::cout << "X: " << x << " Y: " << y << "Z: " << z << std::endl;
            
            // 1
            listVertex.push_back(x);
            listVertex.push_back(y);
            listVertex.push_back(z);

            auxX = x;

            x = cos(alpha)*x+sin(alpha)*z;                
            z = -sin(alpha)*auxX+cos(alpha)*z;

        }
              
    }
    
    // Se crea el vector de índices
    vector<unsigned int> listIndex;
    
    //std::cout << "Número de vértices en el perfil: " << listVertexOutline.size() << std::endl;
        
    //std::cout << "Vértice perfil * lados: " << side*(listVertexOutline.size()/3)+side << std::endl;
    
    // Se comprueba si está en el orden correcto
    if(listVertexOutline[1] > listVertexOutline[4]){
        
        for(unsigned int i=side; i<side*(listVertexOutline.size()/3); i++){
        
            if(i%side==0){


                listIndex.push_back(i-side);
                listIndex.push_back(i-1);
                listIndex.push_back(i);


                listIndex.push_back(i-1);
                listIndex.push_back(i+side-1);
                listIndex.push_back(i);

            } else{

                listIndex.push_back(i-side);
                listIndex.push_back(i-side-1);
                listIndex.push_back(i);

                listIndex.push_back(i-side-1);
                listIndex.push_back(i-1);
                listIndex.push_back(i);

            }

        }

        // Se crea la tapa inferior
        if(bottomCover){

            // Se inserta el vertice que cierra la tapa
            listVertex.push_back(get<0>(bottom));
            listVertex.push_back(get<1>(bottom));
            listVertex.push_back(get<2>(bottom));

            // Se insertan los índices
            for(unsigned int i=listVertex.size()/3-side-1; i<listVertex.size()/3-2; i++){

                listIndex.push_back(listVertex.size()/3-1);
                listIndex.push_back(i+1);
                listIndex.push_back(i);

            }

            listIndex.push_back(listVertex.size()/3-1);
            listIndex.push_back(listVertex.size()/3-side-1);
            listIndex.push_back(listVertex.size()/3-2);

            // Cuando se tiene un número impar de lados y no se pinta la tapa 
            // superior, falta un triángulo por pintar. Con esto se soluciona, pero 
            // no sé por qué se produce.
            // Se mantiene hasta que encuentre el motivo
            if(!topCover && side%2!=0){
                listIndex.push_back(listVertex.size()/3-1);
                listIndex.push_back(listVertex.size()/3-side-4);
                listIndex.push_back(listVertex.size()/3-5);
            }

        }

        // Se crea la tapa superior
        if(topCover){

            // Se inserta el vertice que cierra la tapa
            listVertex.push_back(get<0>(top));
            listVertex.push_back(get<1>(top));
            listVertex.push_back(get<2>(top));

            // Se insertan los índices
            listIndex.push_back(0);
            listIndex.push_back(listVertex.size()/3-1);
            listIndex.push_back(side-1);

            // Se recorren los restantes
            for(unsigned int i=1; i<side; i++){

                listIndex.push_back(i);
                listIndex.push_back(listVertex.size()/3-1);
                listIndex.push_back(i-1);

            }

            // Cuando se tiene un número impar de lados y no se pinta la tapa 
            // inferior, falta un triángulo por pintar. Con esto se soluciona, pero 
            // no sé por qué se produce.
            // Se mantiene hasta que encuentre el motivo
            if(!bottomCover && side%2!=0){
                listIndex.push_back(0);
                listIndex.push_back(listVertex.size()/3-4);
                listIndex.push_back(side-4);
            }

        }
        
    // Los puntos están dados al revés
    } else{
        //cout << "Al reves";
        for(unsigned int i=side; i<side*(listVertexOutline.size()/3); i++){

            if(i%side==0){


                listIndex.push_back(i-side);
                listIndex.push_back(i);
                listIndex.push_back(i-1);


                listIndex.push_back(i-1);
                listIndex.push_back(i);
                listIndex.push_back(i+side-1);

            } else{

                listIndex.push_back(i-side);
                listIndex.push_back(i);
                listIndex.push_back(i-side-1);

                listIndex.push_back(i-side-1);
                listIndex.push_back(i);
                listIndex.push_back(i-1);

            }

        }

        // Se crea la tapa inferior
        if(bottomCover){

            // Se inserta el vertice que cierra la tapa
            listVertex.push_back(get<0>(bottom));
            listVertex.push_back(get<1>(bottom));
            listVertex.push_back(get<2>(bottom));

            // Se insertan los índices
            for(unsigned int i=listVertex.size()/3-side-1; i<listVertex.size()/3-2; i++){

                listIndex.push_back(listVertex.size()/3-1);
                listIndex.push_back(i);
                listIndex.push_back(i+1);

            }

            listIndex.push_back(listVertex.size()/3-1);
            listIndex.push_back(listVertex.size()/3-2);
            listIndex.push_back(listVertex.size()/3-side-1);

            // Cuando se tiene un número impar de lados y no se pinta la tapa 
            // superior, falta un triángulo por pintar. Con esto se soluciona, pero 
            // no sé por qué se produce.
            // Se mantiene hasta que encuentre el motivo
            if(!topCover && side%2!=0){
                listIndex.push_back(listVertex.size()/3-1);
                listIndex.push_back(listVertex.size()/3-5);
                listIndex.push_back(listVertex.size()/3-side-4);
            }

        }

        // Se crea la tapa superior
        if(topCover){

            // Se inserta el vertice que cierra la tapa
            listVertex.push_back(get<0>(top));
            listVertex.push_back(get<1>(top));
            listVertex.push_back(get<2>(top));

            // Se insertan los índices
            listIndex.push_back(0);
            listIndex.push_back(side-1);
            listIndex.push_back(listVertex.size()/3-1);

            // Se recorren los restantes
            for(unsigned int i=1; i<side; i++){

                listIndex.push_back(i);
                listIndex.push_back(i-1);
                listIndex.push_back(listVertex.size()/3-1);

            }

            // Cuando se tiene un número impar de lados y no se pinta la tapa 
            // inferior, falta un triángulo por pintar. Con esto se soluciona, pero 
            // no sé por qué se produce.
            // Se mantiene hasta que encuentre el motivo
            if(!bottomCover && side%2!=0){
                listIndex.push_back(0);
                listIndex.push_back(side-4);
                listIndex.push_back(listVertex.size()/3-4);
            }

        }
        
    }
            
    mesh = new Mesh(listVertex.size()/3, listIndex.size(), listVertex, listIndex, 30, 182, 129, 182, 30, 83, axisSize, false, side, listVertexOutline.size()/3, listVertexOutline);
        
}

// A partir del vector que se recibe con el perfil, obtiene la tapa, la base
// y borra esos elementos del propio vector, para contener solo los puntos
// que se revolucionan.
// Si no tiene que dibujarse la tapa, top y bottom serán null
void ObjRevX::setPoints(){
    
    // coordenada1.Y > coordenada2.Y > coordenada3.Y > ... > coordenadaN.Y
    // Si esto no se cumple se le da la vuelta a las coordenadas
    /*if(listVertexOutline[1] < listVertexOutline[4]){
        
        int listVertexOutlineSize = listVertexOutline.size();
        
        // Se recorre desde el final hasta el principio y se insertan al final
        // las tuplas de 3 para invertir el orden. Al final se elimina la
        // primera parte que tiene el orden invertido
        for(unsigned int i=listVertexOutline.size()-4; i>=3; i=i-3){
            
            listVertexOutline.push_back(listVertexOutline[i-2]);
            listVertexOutline.push_back(listVertexOutline[i-1]);
            listVertexOutline.push_back(listVertexOutline[i]);

        }
        
        listVertexOutline.erase(listVertexOutline.begin(), listVertexOutline.begin()+listVertexOutlineSize-3);
        
    }*/
    
    // Se debe dibujar la tapa superior
    if(topCover){
        
        // Si se dibuja la tapa superior, tanto si se recibe la coordenada
        // de la tapa como si no, el punto central valdrá x=0. y valdrá la
        // altura que se reciba. z valdrá la profundidad que se reciba.
        // Por tanto, la tapa será siempre las primeras coordenadas recibidas,
        // con x=0.
        // Si se recibe el punto de la tapa, si se debe eliminar del vector, si
        // no, no se hace nada.
        
        // Coordenadas de la tapa superior
        get<0>(top) = 0;
        get<1>(top) = listVertexOutline[1];
        get<2>(top) = 0;
                 
    }
    
    // Se comprueba si el primer punto está en el eje Y
    if(listVertexOutline[0] == 0){

        // Se eliminan las 3 primeras coordenadas
        listVertexOutline.erase(listVertexOutline.begin(), listVertexOutline.begin()+3);

    }
    
    // Se debe dibujar la tapa inferior
    if(bottomCover){
        
        // Si se dibuja la tapa inferior, tanto si se recibe la coordenada
        // de la tapa como si no, el punto central valdrá x=0. y valdrá la
        // altura que se reciba. z valdrá la profundidad que se reciba.
        // Por tanto, la tapa será siempre las últimas coordenadas recibidas,
        // con x=0.
        // Si se recibe el punto de la tapa, si se debe eliminar del vector, si
        // no, no se hace nada.
        
        // Coordenadas de la tapa inferior
        get<0>(bottom) = 0;
        get<1>(bottom) = listVertexOutline[listVertexOutline.size()-2];
        get<2>(bottom) = 0;
                        
    }
    
    // Se comprueba si el primer punto está en el eje Y
    if(listVertexOutline[listVertexOutline.size()-3] == 0){

        // Se eliminan las 3 últimas coordenadas
        for(unsigned int i=0; i<3; i++){
            listVertexOutline.pop_back();
        }

    }
    
    //std::cout << "Tapa Superior -> X: " << get<0>(top) << " Y: " << get<1>(top) << " Z: " << get<2>(top) << std::endl;
    
    //std::cout << "Tapa Inferior -> X: " << get<0>(bottom) << " Y: " << get<1>(bottom) << " Z: " << get<2>(bottom) << std::endl;
    
}
