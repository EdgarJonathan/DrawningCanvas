#ifndef gestion
#define gestion
#include <string>
#include <bst.h>
#include <img.h>
#include <avl.h>
#include <fstream>
#include <iostream>

enum{

    CAPAS=0,
    IMAGENES=1,
    USUARIOS=2

};

class Gestion
{
private:

    //--para validar entrada
    std::string entrada ="";
    int validarEntrada(std::string txt);
    char a;

    //---utilidades
    void limpiar();

    //-crear archivos
    void crearCapas(std::string txt);
    void crearImagenes(std::string txt);
    void crearUsuarios(std::string txt);
    bool caracterBasura(char caracter);

    //--verificar cadenas
    bool esNumero(char l);
    bool esAlfaNumerico(char l);

    //--leer
    void leer(std::string dir,int tipo);

    //----funcionalidades
    void cargaMasiva();
    void generacionImagenes();
    void ABC();
    void estadoMemoria();
    void otrosReportes();



    //--atributos
    bst* arbolCapas;
    listImg* listaImganes;
    Avl* arbolUsuarios;

    //--para graficar por recorrido limitadod
    int contcapas;
    matriz* auxCapa;

    //---booleanas
    bool capasCargadas;
    bool imagenesCargadas;
    bool usuariosCargados;


    //---funcionalidades
    //---3.1
    void recorridoLimitado();
    void listadeImagenes();
    void imagenPorCapa();
    void imagenPorUsuario();

    //--3.2
    void Usuarios();
    void Imagenes();

    //--3.3
    void verLIstaImagenes();
    void verArbolCapas();
    void verArbolCapasEspejo();
    void verCapa();
    void verImagenyArbolCapas();
    void verArboldeUsuarios();

    //--3.4
    void top5imagenes();
    void todasLasCapasHojas();
    void profundidadArbolCapas();
    void mostrarCapasPostorden();
    void listarCapas();
    void top5usuarios();
    void arbolEspejoUsuarios();
    void ListarUsuariosEnRecorrido();


    //---graficas
    matriz* generarImagen(img* imagen);
    matriz* generarImagen(matriz* capa1,matriz* capa0);

    void adminRecorridoLimitado(int tipo);

    void generarImgpostorden(img* imagen, NodoBst* raiz);
    void generarImginorden(img* imagen, NodoBst* raiz);
    void generarImgpreorden(img* imagen, NodoBst* raiz);




public:
    Gestion();
    void init();

};

#endif // ARCHIVOS_H
