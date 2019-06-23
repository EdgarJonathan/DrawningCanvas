#ifndef gestion
#define gestion
#include <string>
#include <bst.h>
#include <fstream>
#include <iostream>



class Gestion
{
private:
    void crearArbolCapas(std::string txt);
    bool esNumero(char l);
    bool esAlfaNumerico(char l);
public:
    Gestion();
    bst* arbolCapas;
    void leerCapas(std::string dir);
    void leerImagenes(std::string dir);


};

#endif // ARCHIVOS_H
