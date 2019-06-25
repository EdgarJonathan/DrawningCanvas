#ifndef AVL_H
#define AVL_H
#include <img.h>


//********************************************************************************
//********************************************************************************
//************************ nodoAvl ***********************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************

class NodoAvl
{
protected:
    listImg* listaImagen;
    std::string nombre;
    NodoAvl* izq;
    NodoAvl* der;
    int fe;
public:
    NodoAvl(listImg* listaImagen,std::string nombre);
    NodoAvl(listImg* listaImagen,std::string nombre,int fe);
    NodoAvl(NodoAvl* izq,listImg* listaImagen,std::string nombre,NodoAvl* der);
    NodoAvl(NodoAvl* izq,int fe,listImg* listaImagen,std::string nombre, NodoAvl* der);

    //operaciones de acceso
    listImg *getListaImagen() const;
    void setListaImagen(listImg *value);
    std::string getNombre() const;
    void setNombre(const std::string &value);
    NodoAvl *getIzq() const;
    void setIzq(NodoAvl *value);
    NodoAvl *getDer() const;
    void setDer(NodoAvl *value);
    int getFe() const;
    void setFe(int value);

    void imprimir();
};
//********************************************************************************
//********************************************************************************
//************************ clase Avl ********************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************

class Avl
{
private:

    std::string txtgrafica;
    std::string id;
    std::string idIzq;
    std::string idDer;

    //rotacion simple izquierda
    NodoAvl* rsi(NodoAvl*n,NodoAvl*n1);
    //rotacion simple derecha
    NodoAvl* rsd(NodoAvl*n,NodoAvl*n1);
    //rotacion doble derecha izquierda
    NodoAvl* rddi(NodoAvl*n,NodoAvl*n1);
    //rotacion doble izquierda derecha
    NodoAvl* rdid(NodoAvl*n,NodoAvl*n1);


    NodoAvl* insertarAvl(NodoAvl* raiz, listImg* listaImagen,std::string nombre, bool &hc);
    void inorden(NodoAvl* temp);
    void postOrden(NodoAvl* temp);
    void preOrden(NodoAvl* temp);

    void textoDot(std::string nombre);
    void graficarPreorden(NodoAvl* raiz);

public:
    NodoAvl* raiz;
    Avl();
    Avl(NodoAvl* r);
    NodoAvl *getRaiz() const;
    void setRaiz(NodoAvl *value);
    void insertarAvl(listImg* listaImagen,std::string nombre);

    void mostrar(int tipo);

    void graficar();
    void graficarPreorden();





};

#endif // AVL_H
