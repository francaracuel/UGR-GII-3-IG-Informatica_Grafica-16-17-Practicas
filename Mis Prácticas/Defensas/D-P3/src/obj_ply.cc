////////////////////////////////////////////////////////////////////////////////
//
// Francisco Javier Caracuel Beltrán
//
// Práctica 3
//
// obj_ply.cc
//
////////////////////////////////////////////////////////////////////////////////

#include "obj_ply.h"

////////////////////////////////////////////////////////////////////////////////
// Constructor
//
// Crea la geometría el objeto PLY
//
ObjPLY::ObjPLY(bool ask){
    
    if(ask){
        
        setFile();
        createGeometry();
                
    }
            
}

// Crea la geometría el objeto PLY sin preguntar por el archivo ply
//
ObjPLY::ObjPLY(bool ask, string f) : file(f){
    
    createGeometry();
    
}

// Crea la geometría el objeto PLY sin preguntar por el archivo ply
//
ObjPLY::ObjPLY(bool ask, string f, vector<float> colors) : file(f){
    
    createGeometry();
    
    mesh->setColors(colors);
    
}

////////////////////////////////////////////////////////////////////////////////
// Crea la geometría del objeto PLY que se quiere dibujar
//
void ObjPLY::createGeometry(){
    
    _file_ply *ply = new _file_ply();
    
    // Si da un error al abrir el fichero
    if(ply->open(getFileChar())==-1){
                
        file = "data/"+file;
        
        if(ply->open(getFileChar())!=-1){
            success();
        }
        
    } else{
        success();
    }
        
    // Se crea el vector de vértices
    vector<float> listVertex;
    
    // Se crea el vector de índices de tipo int que se le pasará al lector ply
    vector<int> listIndexAux;
    
    ply->read(listVertex, listIndexAux);
    
    // Se tiliza unsigned int y el lector ply int. Se hace la conversión
    // de int a unsigned int
    vector<unsigned int> listIndex(listIndexAux.begin(), listIndexAux.end());
        
    mesh = new Mesh(listVertex.size()/3, listIndex.size(), listVertex, listIndex, 30, 182, 129, 182, 30, 83, axisSize);
        
}

// Devuelve el nombre del fichero como *char
char* ObjPLY::getFileChar(){
    
    char * f = new char[file.size() + 1];
    std::copy(file.begin(), file.end(), f);
    f[file.size()] = '\0';
    
    return f;
    
}

// Devuelve el nombre del fichero
string ObjPLY::getFile(){    
    return file;
}

// Asigna un fichero al objeto
void ObjPLY::setFile(string name){
    file = name;
}

// Asigna un fichero al objeto y pide por consola el nombre
void ObjPLY::setFile(){
    
    cout << "\nIntroduce el nombre del fichero ply (el fichero ply debe estar en la raíz o en el directorio \"data\": ";
    getline(cin, file);
    
}

// Mensaje indicando que ha habido éxito al leer el fichero
void ObjPLY::success(){
    cout << "\nEl fichero se ha leído con éxito\n\n";
}