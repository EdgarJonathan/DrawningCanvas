#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include<string>

//********************************************************************************
//********************************************************************************
//************************CLASE NODO ORTOGONAL************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************

class NodoOrtogonal
{
private:

    int fila;
    int col;
    NodoOrtogonal * up;
    NodoOrtogonal * down;
    NodoOrtogonal * right;
    NodoOrtogonal * left;
    std::string color;

public:
    NodoOrtogonal(int fila, int col, std::string color);


    // metodos de acceso
    int getFila() const;
    void setFila(int value);
    int getCol() const;
    void setCol(int value);

    NodoOrtogonal *getUp() const;
    void setUp(NodoOrtogonal *value);
    NodoOrtogonal *getDown() const;
    void setDown(NodoOrtogonal *value);
    NodoOrtogonal *getRight() const;
    void setRight(NodoOrtogonal *value);
    NodoOrtogonal *getLeft() const;
    void setLeft(NodoOrtogonal *value);
    std::string getColor() const;
    void setColor(const std::string &value);
};
//********************************************************************************
//********************************************************************************
//************************CLASE CUERPO *******************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************

class CuerpoHorizontal
{
private:
    void sort(NodoOrtogonal* nuevo);

public:
    CuerpoHorizontal();
    NodoOrtogonal* first;
    NodoOrtogonal* last;
    void add(NodoOrtogonal* nuevo);
};

class CuerpoVertical
{
private:
     void sort(NodoOrtogonal* nuevo);

public:
    CuerpoVertical();
    NodoOrtogonal* last;
    NodoOrtogonal* first;
   void add(NodoOrtogonal* nuevo);
};

//********************************************************************************
//********************************************************************************
//************************CLASE NODO CABECERA ************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************
class NodoCabeceraFila
{
private:
    int fila;
    NodoCabeceraFila* up;
    NodoCabeceraFila *down;

public:
    NodoCabeceraFila(NodoOrtogonal* nuevo);
    CuerpoHorizontal* listHorizontal;
    int getFila() const;
    void setFila(int value);
    NodoCabeceraFila *getUp() const;
    void setUp(NodoCabeceraFila *value);
    NodoCabeceraFila *getDown() const;
    void setDown(NodoCabeceraFila *value);
};

class NodoCabeceraCol
{
private:
    int col;
    NodoCabeceraCol* right;
    NodoCabeceraCol* left;
public:
    NodoCabeceraCol(NodoOrtogonal* nuevo);
    CuerpoVertical* listVertical;
    int getCol() const;
    void setCol(int value);
    NodoCabeceraCol *getRight() const;
    void setRight(NodoCabeceraCol *value);
    NodoCabeceraCol *getLeft() const;
    void setLeft(NodoCabeceraCol *value);
};

//********************************************************************************
//********************************************************************************
//****************CLASE LISTA CABECERAS ******************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************
class ListaCabeceraFila
{
private:
    NodoCabeceraFila* search(int fila);
    void sort(NodoCabeceraFila* nuevo);

public:
    ListaCabeceraFila();
    NodoCabeceraFila* first;
    NodoCabeceraFila* last;

    void add(NodoOrtogonal* nuevo);
};
class ListaCabecerCol
{
private:

    NodoCabeceraCol* search(int col);
    void sort(NodoCabeceraCol* nuevo);
public:
    ListaCabecerCol();
    NodoCabeceraCol* first;
    NodoCabeceraCol* last;
    void add(NodoOrtogonal* nuevo);
};

//********************************************************************************
//********************************************************************************
//*********************** Matriz *************************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************

class matriz
{
private:


public:
    ListaCabecerCol* columnaC;
    ListaCabeceraFila* filaC;
    matriz();
    void add(int fila, int columna, std::string color );

    void imprimirfIla();
    void imprimirCol();

    std::string txtCabeceraCol();
    std::string txtCabeceraFila();
    std::string txtFilas();
    std::string txtColumnas();

};





#endif // MATRIZ_H
