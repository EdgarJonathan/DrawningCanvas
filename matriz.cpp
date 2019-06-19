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
void NodoCabeceraFila::setDown(NodoCabeceraFila *value)
{
    down = value;
}
NodoCabeceraFila::NodoCabeceraFila(NodoOrtogonal* nuevo){

    fila=nuevo->getFila();
    up=down=nullptr;
    listHorizontal = new CuerpoHorizontal();
}
int NodoCabeceraCol::getCol() const
{
    return col;
}
void NodoCabeceraCol::setCol(int value)
{
    col = value;
}
NodoCabeceraCol *NodoCabeceraCol::getRight() const
{
    return right;
}
void NodoCabeceraCol::setRight(NodoCabeceraCol *value)
{
    right = value;
}
NodoCabeceraCol *NodoCabeceraCol::getLeft() const
{
    return left;
}
void NodoCabeceraCol::setLeft(NodoCabeceraCol *value)
{
    left = value;
}
NodoCabeceraCol::NodoCabeceraCol(NodoOrtogonal* nuevo){
    col = nuevo->getCol();
    right =left= nullptr;
    listVertical= new CuerpoVertical();
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

    if(first){

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

}
void ListaCabeceraFila::sort(NodoCabeceraFila*nuevo){

    //si el numero de fila es menor o igual al primero
    if(nuevo->getFila() <= first->getFila()){
        nuevo->setDown(first);
        first->setUp(nuevo);
        first = nuevo;
    }//si el numero es mayor al ulimo
    else if(nuevo->getFila() >= last->getFila()){
        last->setDown(nuevo);
        nuevo->setUp(last);
        last = nuevo;
    }else {

        NodoCabeceraFila* actual=first;

        while (actual !=last) {

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
NodoCabeceraFila* ListaCabeceraFila::search(int fila){

    NodoCabeceraFila* actual = first;

    while (actual) {
        if(actual->getFila() == fila)
            break;

        actual= actual->getDown();
    }


    return actual;

}
//********************************************************************************
//********************************************************************************
//****************CLASE LISTA CABECERA COLUMNA ***********************************
//********************************************************************************
//********************************************************************************
//********************************************************************************

ListaCabecerCol::ListaCabecerCol(){
    first=last=nullptr;
}
void ListaCabecerCol::add(NodoOrtogonal *nuevo){

    if(first){

        NodoCabeceraCol* aux = search(nuevo->getCol());
        //si se encontro el nodo con la cabecera ya existente solo se utiliza
        if(aux){
            aux->listVertical->add(nuevo);
        }//no se encontro con el nodo y la cabecera no existe
        else {
            NodoCabeceraCol* nuevoCol = new NodoCabeceraCol(nuevo);
            nuevoCol->listVertical->add(nuevo);
            sort(nuevoCol);
        }

    }else{
        NodoCabeceraCol* nuevoCol = new  NodoCabeceraCol(nuevo);
        nuevoCol->listVertical->add(nuevo);
        first=last=nuevoCol;
    }

}
void ListaCabecerCol::sort(NodoCabeceraCol *nuevo){


    if(nuevo->getCol() <= first->getCol()){
        nuevo->setRight(first);
        first->setLeft(nuevo);
        first = nuevo;
    }else if(nuevo->getCol() >= last->getCol()){
        last->setRight(nuevo);
        nuevo->setLeft(last);
        last=nuevo;
    }else{

        NodoCabeceraCol* actual= first;

        while (actual!= last) {

            if( (nuevo->getCol() >= actual->getCol())&&
                    (nuevo->getCol() <= actual->getRight()->getCol())){

                nuevo->setRight(actual->getRight());
                nuevo->setLeft(actual);
                actual->getRight()->setLeft(nuevo);
                actual->setRight(nuevo);
                break;
            }
            actual = actual->getRight();
        }
    }

}
NodoCabeceraCol* ListaCabecerCol::search(int col){
    NodoCabeceraCol* actual= first;

    while (actual) {
        if(actual->getCol() == col)
            break;
        actual = actual->getRight();
    }

    return actual;
}

//********************************************************************************
//********************************************************************************
//*********************** Matriz *************************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************
matriz::matriz(){
    filaC=new ListaCabeceraFila();
    columnaC = new ListaCabecerCol();
}

void matriz::add(int fila, int col, std::string color){

    NodoOrtogonal* nuevo = new NodoOrtogonal(fila,col,color);
    this->filaC->add(nuevo);
    this->columnaC->add(nuevo);

}


void matriz::imprimirfIla(){

    NodoCabeceraFila* actualFila = filaC->first;
    while(actualFila){
        std::cout<<"********fila: "+std::to_string(actualFila->getFila())+" ***************"<<std::endl;
        NodoOrtogonal* actualCol = actualFila->listHorizontal->first;
        while (actualCol) {
            std::cout<<"     col: "+std::to_string(actualCol->getCol())
                       +" color:("+actualCol->getColor()+ ")"<<std::endl;

            actualCol= actualCol->getRight();
        }

        actualFila = actualFila->getDown();

    }

}


void matriz::imprimirCol(){

    NodoCabeceraCol* actualCol = columnaC->first;


    while(actualCol){
        std::cout<<"********Columna: "+std::to_string(actualCol->getCol())+" ***************"<<std::endl;
        NodoOrtogonal* actualFila = actualCol->listVertical->first;

        while(actualFila){
            std::cout<<"     fila: "+std::to_string(actualFila->getFila())
                       +" color:("+actualFila->getColor()+ ")"<<std::endl;

            actualFila = actualFila->getDown();
        }

        actualCol = actualCol->getRight();
    }



}

std::string matriz::txtCabeceraCol(){

    std::string  result ="";
    std::string rank ="\t{ rank = same ;";
    std::string col ="";
    std::string colsig ="";
    NodoCabeceraCol* actual = columnaC->first;


    result+="\t//----------------------cabecera columnas-----------------------\n";

    while (actual) {

            col = std::to_string(actual->getCol());

        // si el  es el ultimo nodo de la matriz
        if(actual==columnaC->last){

            //si ese ultimo nodo es igual al primero
            //osea solo existe un nodo en la matriz
            if(actual == columnaC->first){
                result+="\tcapa -> nd"+col+";\n";
                result+="\tnd"+col;
                result+="[label =\"("+col+")\"];\n";
                rank+="capa; nd"+col+";}\n";
            }else{
                result+="\tnd"+col;
                result+="[label =\"("+col+")\"];\n";
                rank+=" nd"+col+";}\n";
            }


        }else{

            colsig = std::to_string(actual->getRight()->getCol());

            //el nodo actual es igual al primero
            //osea la lista tiene mas de un solo nodo
            if(actual==columnaC->first){

                result+="\tcapa -> nd"+col+";\n";

                result+="\tnd"+col;
                result+="[label =\"("+col+")\"];\n";

                result+="\tnd"+col;
                result+=" -> ";
                result+= "nd"+colsig;
                result+=" -> ";
                result+="nd"+col+"[constraint=false]s;\n";

                rank+="capa ; nd"+col+";";

            }else{

                result+="\tnd"+col;
                result+="[label =\"("+col+")\"];\n";

                result+="\tnd"+col;
                result+=" -> ";
                result+= "nd"+colsig;
                result+=" -> ";
                result+="nd"+col+"[constraint=false];\n";

                rank+=" nd"+col+";";

            }

        }


        actual = actual->getRight();
    }

    result+=rank;

    return result;
}
std::string matriz::txtCabeceraFila(){
    std::string  result ="";




    return result;
}
std::string matriz::txtFilas(){
    std::string  result ="";




    return result;
}
std::string matriz::txtColumnas(){
    std::string  result ="";




    return result;
}






















