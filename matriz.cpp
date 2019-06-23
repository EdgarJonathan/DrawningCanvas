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

        if(!search(nuevo)){
            sort(nuevo);
        }


    }else{

        first =last = nuevo;
    }

}
bool CuerpoHorizontal::search(NodoOrtogonal* nuevo){
    NodoOrtogonal* actual = first;


    while (actual) {

        if((actual->getFila()== nuevo->getFila())&&
                (actual->getCol() == nuevo->getCol())){

            actual->setColor(nuevo->getColor());

            return  true;
        }

        actual = actual->getRight();
    }



    return false;

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

//----------------------------------------------------------------------

CuerpoVertical::CuerpoVertical(){
    first=last=nullptr;
}
void CuerpoVertical::add(NodoOrtogonal *nuevo){

    if(first){

        if(!search(nuevo)){
            sort(nuevo);
        }

    }else{

        first= last = nuevo;
    }

}
bool CuerpoVertical::search(NodoOrtogonal* nuevo){

    NodoOrtogonal* actual = first;


    while (actual) {

        if((actual->getFila()== nuevo->getFila())&&
                (actual->getCol() == nuevo->getCol())){

            actual->setColor(nuevo->getColor());

            return  true;
        }

        actual = actual->getDown();
    }



    return false;

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

std::string matriz::coord(int fila,int col , int tipo){

    std::string result ="";
    std::string x ="";
    std::string y ="";
    int auxY =0;

    switch(tipo)
    {
    case COL:
        x = std::to_string(col+2);
        result ="\""+x+",-1!\"";
        break;
    case FILA:
        y = std::to_string(fila-2*(fila+1));
        result ="\"1,"+y+"!\"";
        break;
    case NODO:
        x = std::to_string(col+2);
        auxY = getindexFila(fila);
        y = std::to_string(auxY-2*(auxY+1));
        result ="\""+x+","+y+"!\"";
        break;
    case MATRIZ:
        result="\"1,-1!\"";
        break;
    default :
        break;

    }

    return result;
}

void matriz::graficar(){

    std::string nombre = "matriz";
    generarDot(nombre);

    //especificar el nomabre en los metodos system
    system("neato -Tsvg -O matriz.dot");
    system("xdg-open matriz.dot.svg");

}

void matriz::generarDot(std::string nombre){

    std::ofstream archivo;
    archivo.open(nombre+".dot",std::ios::out);//abriendo el archivo
    if(archivo.fail()){ std::cout<<"No se pudo crear el archivo"; exit(1);}

    archivo<<"digraph g "<<std::endl;
    archivo<<"{\n"<<std::endl;
    archivo<<"\tnodesep = 0.5;\n"<<std::endl;
    archivo<<"\tnode[shape=box, color=turquoise4, fillcolor=green,style=filled];\n"<<std::endl;
    archivo<<"\tedge[color=tomato];\n"<<std::endl;

    archivo<<txtColumnas()<<std::endl;
    archivo<<txtFilas()<<std::endl;

    archivo<<"}"<<std::endl;
    archivo.close();//cerrar el archivo
}

std::string matriz::txtColumnas(){

    std::string result;

    int col =0;
    int fila =0;
    std::string pos ="";
    std::string acfila="";
    std::string antfila="";
    std::string antcol="";
    std::string accol="";
    std::string color ="";

    NodoCabeceraCol* actualCol =columnaC->first;

    while (actualCol) {

        accol =std::to_string(actualCol->getCol())+"c";
        pos = coord(fila,col,COL);

        if(actualCol!=columnaC->first){

            antcol =std::to_string(actualCol->getLeft()->getCol())+"c";

            result+="\t//----------------------------------Columna "+accol+"-----------------------\n";
            result+="\tcol"+accol

                    +"[label=\"("+accol+")\";"
                    +" pos="+pos+"];\n";

            result+="\tcol"+antcol
                    +" -> col"+accol
                    + "-> col"+antcol+";\n\n";

        }//si es la primera columna de la matriz
        else{

            //------------------------------------------------------------------------------------------------
            //------------------------------- Cabecera y la primera columna------------------------------------
            //------------------------------------------------------------------------------------------------
            result+="\t//---------------------------------Nodo Matriz-----------------------\n";

            result+="\tm[label=\"Capa\"; pos=\"1,-1!\"];\n";
            result+="\t//----------------------------------Columna "+accol+"-----------------------\n";
            result+="\tcol"+accol
                    +"[label=\"("+accol+")\";"
                    +" pos="+pos+"];\n";

            result+="\tm -> col"+accol+";\n\n";
        }



        //------------------------------------------------------------------------------------------------
        //------------------------------- columnas-----------------------------------
        //------------------------------------------------------------------------------------------------
        NodoOrtogonal* actualFila = actualCol->listVertical->first;

        while (actualFila) {

            fila = actualFila->getFila();
            acfila=std::to_string(fila)+"f";
            pos = coord(fila,col,NODO);
            color = actualFila->getColor();

            //  result+="\t//----------------------------------Nodo"+acfila+accol+"-----------------------\n";

            if(actualFila != actualCol->listVertical->first){

                antfila =std::to_string(actualFila->getUp()->getFila())+"f";

                result+="\tnd"+acfila+accol
                        +"[label=\""+color+"\";"
                        +" pos="+pos+"; fillcolor=\""+color+"\"; tyle=filled;fontcolor=white];\n";

                result+="\tnd"+antfila+accol
                        +" -> nd"+acfila+accol+""
                        +" -> nd"+antfila+accol+";\n";

            }//si es el primer nodo de la columna de la matriz
            else{


                result+="\tnd"+acfila+accol
                        +"[label=\""+color+"\";"
                        +" pos="+pos+"; fillcolor=\""+color+"\";style=filled;fontcolor=white];\n";

                result+="\tcol"+accol+" -> nd"+acfila+accol+";\n\n";

            }



            actualFila = actualFila->getDown();
        }




        col++;
        actualCol = actualCol->getRight();
    }


    return result;
}

std::string matriz::txtFilas(){
    std::string result;

    NodoCabeceraFila* actualFila = filaC->first;
    int col =0;
    int fila =0;
    std::string pos ="";
    std::string acfila="";
    std::string antfila="";
    std::string antcol="";
    std::string accol="";
    std::string color ="";


    while (actualFila) {

        acfila=std::to_string(actualFila->getFila())+"f";
        pos = coord(fila,col,FILA);

        if(actualFila!=filaC->first){
            antfila = std::to_string(actualFila->getUp()->getFila())+"f";

            result+="\tf"+acfila+"[label=\"("+acfila+")\"; pos="+pos+"];\n";
            result+="\t"
                    "f"+antfila+" -> f"+acfila+" -> f"+antfila+"\n";

        }else{

            result+="\t//-----------------------filas----------------------------\n";

            result+="\tf"+acfila+"[label=\"("+acfila+")\"; pos="+pos+"];\n";
            result+="\tm -> f"+acfila+"\n";

        }




        NodoOrtogonal* actualCol = actualFila->listHorizontal->first;

        while (actualCol) {

            accol = std::to_string(actualCol->getCol())+"c";


            if(actualCol != actualFila->listHorizontal->first){

                antcol = std::to_string(actualCol->getLeft()->getCol())+"c";

                result+="\tnd"+acfila+antcol
                        +" ->  nd"+acfila+accol
                        +" ->  nd"+acfila+antcol+"\n";

            }else{

                result+="\tf"+acfila
                        +" -> "
                        +" nd"+acfila+accol+";\n";

            }

            actualCol= actualCol->getRight();
        }



        fila++;
        actualFila = actualFila->getDown();
    }


    return result;
}





int matriz::getindexFila(int fila){

    int result =0;


    NodoCabeceraFila* actual = filaC->first;

    while (actual) {

        if(actual->getFila() == fila){
            break;
        }

        result++;
        actual = actual->getDown();
    }


    return  result;
}





