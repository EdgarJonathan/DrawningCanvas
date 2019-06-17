#include "matriz.h"
//********************************************************************************
//********************************************************************************
//************************CLASE NODO ORTOGONAL************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************
int NodoOrtogonal::getCol() const
{
    return col;
}
void NodoOrtogonal::setCol(int value)
{
    col = value;
}
NodoOrtogonal *NodoOrtogonal::getUp() const
{
    return up;
}
void NodoOrtogonal::setUp(NodoOrtogonal *value)
{
    up = value;
}
NodoOrtogonal *NodoOrtogonal::getDown() const
{
    return down;
}
void NodoOrtogonal::setDown(NodoOrtogonal *value)
{
    down = value;
}
NodoOrtogonal *NodoOrtogonal::getRight() const
{
    return right;
}
void NodoOrtogonal::setRight(NodoOrtogonal *value)
{
    right = value;
}
NodoOrtogonal *NodoOrtogonal::getLeft() const
{
    return left;
}
void NodoOrtogonal::setLeft(NodoOrtogonal *value)
{
    left = value;
}
int NodoOrtogonal::getFila() const
{
    return fila;
}
void NodoOrtogonal::setFila(int value)
{
    fila = value;
}
std::string NodoOrtogonal::getColor() const
{
    return color;
}

void NodoOrtogonal::setColor(const std::string &value)
{
    color = value;
}

NodoOrtogonal::NodoOrtogonal(int fila, int col, std::string color){

    up=down=left=right =nullptr;
    this->fila = fila;
    this->col = col;
    this->color = color;

}

//********************************************************************************
//********************************************************************************
//************************CLASE CUERPO *******************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************
CuerpoHorizontal::CuerpoHorizontal(){

    first =last =nullptr;
}
void CuerpoHorizontal::add(NodoOrtogonal* nuevo){

    // se ordena la lista si ya existe un nodo
    // si no existe un nodo se agrega por primera vez
    if(first){
        sort(nuevo);

    }else{

        first =last = nuevo;
    }

}
void CuerpoHorizontal::sort(NodoOrtogonal *nuevo){

    //si el nuevo es menor al primero
    if(nuevo->getCol() <= first->getCol()){
        nuevo->setRight(first);
        first->setLeft(nuevo);
        first = nuevo;
    }//si es mayor igual al ultimo
    else if(nuevo->getCol() >= last->getCol()){
        last->setRight(nuevo);
        nuevo->setLeft(last);
        last =nuevo;
    }else{

        NodoOrtogonal* actual = first;
        while(actual!=last){

            if( (nuevo->getCol() >= actual->getCol())&&
                    (nuevo->getCol() <= actual->getRight()->getCol())  ){

                nuevo->setRight(actual->getRight());
                nuevo->setLeft(actual);
                actual->getRight()->setLeft(nuevo);
                actual->setRight(nuevo);
                break;
            }

        }

    }

}

CuerpoVertical::CuerpoVertical(){
     first=last=nullptr;
}
void CuerpoVertical::add(NodoOrtogonal *nuevo){

    if(first){
        sort(nuevo);
    }else{

        first= last = nuevo;
    }

}
void CuerpoVertical::sort(NodoOrtogonal *nuevo){

    //si el nuevo es menor igual al primero
    if(nuevo->getFila() <= first->getFila()){
        first->setUp(nuevo);
        nuevo->setDown(first);
        first = nuevo;

    }//si es mayor igual al ultimo
    else if(nuevo->getFila() >= last->getFila() ){
        last->setDown(nuevo);
        nuevo->setUp(last);
        last = nuevo;
    }else {

        NodoOrtogonal* actual = first;

        while (actual!= last) {

            if( (nuevo->getFila() >= actual->getFila())&&
                    (nuevo->getFila() <= actual->getDown()->getFila())){

                nuevo->setDown(actual->getDown());
                nuevo->setUp(actual);
                actual->getDown()->setUp(nuevo);
                actual->setDown(nuevo);

                break;
            }


            actual = actual->getDown();
        }


    }

}

//********************************************************************************
//********************************************************************************
//****************CLASE NODO CABECERAS *******************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************
int NodoCabeceraFila::getFila() const
{
    return fila;
}

void NodoCabeceraFila::setFila(int value)
{
    fila = value;
}

NodoCabeceraFila *NodoCabeceraFila::getUp() const
{
    return up;
}

void NodoCabeceraFila::setUp(NodoCabeceraFila *value)
{
    up = value;
}

NodoCabeceraFila *NodoCabeceraFila::getDown() const
{
    return down;
}

NodoCabeceraFila::NodoCabeceraFila(NodoOrtogonal* nuevo){

    fila=nuevo->getFila();
    up=down=nullptr;
    listHorizontal = new CuerpoVertical();
}

int NodoCabeceraCol::getCol() const
{
    return col;
}

void NodoCabeceraCol::setCol(int value)
{
    col = value;
}

NodoCabeceraCol::NodoCabeceraCol(NodoOrtogonal* nuevo){
    col = nuevo->getCol();
    right =left= nullptr;
    listVertical= new CuerpoHorizontal();
}

//********************************************************************************
//********************************************************************************
//****************CLASE LISTA CABECERA  FILA *************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************

ListaCabeceraFila::ListaCabeceraFila(){
    first=last=nullptr;
}


void ListaCabeceraFila::add(NodoOrtogonal *nuevo){

   /* if(first){

        NodoCabeceraFila* aux = search(nuevo->getFila());
        //si se encontro el nodo con la cabecera ya existente solo se utiliza
        if(aux){
            aux->listHorizontal->add(nuevo);
        }//no se encontro con el nodo y la cabecera no existe
        else {
            NodoCabeceraFila* nuevoFila = new NodoCabeceraFila(nuevo);
            nuevoFila->listHorizontal->add(nuevo);
            sort(nuevoFila);

        }

    }//si es el primero nodo a ingresar
    else {

        NodoCabeceraFila* nuevoFila = new  NodoCabeceraFila(nuevo);
        nuevoFila->listHorizontal->add(nuevo);
        first=last=nuevoFila;

    }
*/

}
void ListaCabeceraFila::sort(NodoCabeceraFila*nuevo){




/*

    NodoCabeceraFila* actual = primero;
    int nuevo_salon = nuevo->salon->getValor().no_salon;

    //si el nuevo es menor al primero
    if(nuevo_salon <= primero->salon->getValor().no_salon)
    {
        primero->arriba=nuevo;
        nuevo->abajo = primero;
        nuevo->arriba= nullptr;
        primero=nuevo;


    }//si  es mayor o igual al ultimo
    else if(nuevo_salon >= ultimo->salon->getValor().no_salon)
    {
        ultimo->abajo = nuevo;
        nuevo->arriba = ultimo;
        nuevo->abajo  = nullptr;
        ultimo = nuevo;

    }//recoriendo la lista si nuevo es mayor o igual actual
    //y si nuevo es menor o igual siguiente de actual
    else
    {
        while(actual!=ultimo)
        {
            if((nuevo_salon >= actual->salon->getValor().no_salon)
               &&(nuevo_salon <= actual->abajo->salon->getValor().no_salon))
            {
                nuevo->abajo =actual->abajo;
                nuevo->arriba =  actual;
                nuevo->abajo->arriba =nuevo;
                actual->abajo = nuevo;
                break;
            }

            actual = actual->abajo;
        }

    }
*/
}




//********************************************************************************
//********************************************************************************
//****************CLASE LISTA CABECERA COLUMNA ***********************************
//********************************************************************************
//********************************************************************************
//********************************************************************************















