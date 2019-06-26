#ifndef IMG_H
#define IMG_H
#include <bst.h>



//********************************************************************************
//********************************************************************************
//************************ NodoListImg *******************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************
class capa
{
private:

    capa* sig;
    NodoBst* Capa;
public:
    capa(NodoBst* nuevo);
    capa *getSig() const;
    void setSig(capa *value);
    NodoBst *getCapa() const;
    void setCapa(NodoBst *value);
};

//********************************************************************************
//********************************************************************************
//************************ ListImg ***********************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************

class ListCapas
{
private:
    capa* first;
    capa* last;

    bool search(int id);

public:
    ListCapas();
    void add(int id, bst* arbol);

    capa *getFirst() const;
    void setFirst(capa *value);
};
//********************************************************************************
//********************************************************************************
//************************ Nodo Img **********************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************

class img
{
private:
    img* sig;
    img* ant;
    ListCapas* listCapa;
    int idImg;

public:
    img(ListCapas* list,int idImg);
    img();
    img *getSig() const;
    void setSig(img *value);
    img *getAnt() const;
    void setAnt(img *value);
    int getId() const;
    void setId(int value);
    bool search(int idCapa);

    ListCapas *getListCapa() const;
    void setListCapa(ListCapas *value);
};

//********************************************************************************
//********************************************************************************
//************************ list Img **********************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************
class listImg
{

private:
    std::string  dotEnlacesListaArbol;
    img* first;
    img* last;
    void textoDot(std::string nombre);

    std::string getDotImagen(int id);
    std::string getDot();
    std::string subGrafoArbol(std::string dotArbol);
    std::string subGrafoLista(int id);
    void graficarImagen(int id,std::string dotArbol,std::string nombre);

    img* searchImg(int id,listImg* listaImagenes);


public:
    listImg();
    bool search(int idImg);

    void add(img* &listCapa, int idimg);
    void graficar();
    void graficarImagen(int id,std::string dotArbol);
    void imprimir();
    img* getImg(int id);
    void addImgUsuario(int id, listImg *listaImganes);
};


//********************************************************************************
//********************************************************************************
//*********************** NodoimgUser *******************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************

class NodoImgUser
{
private:
    NodoImgUser *sig;
    int idImg;
    img* imagen;

public:
    NodoImgUser(img* imagen, int idImg);
    int getIdImg() const;
    void setIdImg(int value);
    img *getImagen() const;
    void setImagen(img *value);
    NodoImgUser *getSig() const;
    void setSig(NodoImgUser *value);
};


//********************************************************************************
//********************************************************************************
//*********************** ListImgUser ********************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************


class ListImgUser
{

private:

public:
    NodoImgUser*first;
    NodoImgUser*last;
    ListImgUser();
    void add(int id, listImg *listaImganes);
    std::string getDot(std::string ndArbol);


};

#endif // IMG_H
