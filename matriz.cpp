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
/*

matriz::matriz()
{
    this->fila = new ListaCabeceraFila();
    this->col = new ListaCabeceraColumna();

}

std::string  matriz::insertar(stOrtogonal datos,listCursos* cursos, listEdificios* edificios ){

    std::string respuesta="";
    salonEdificio EdificioEncontrado = edificios->obtnerSalon(datos.edificio,datos.no_salon);
    nodoCurso* cursoEncontrado = cursos->buscarId(datos.idCurso);

    if((EdificioEncontrado.salon!=nullptr)&&(cursoEncontrado!= nullptr)&&(EdificioEncontrado.edificio!=nullptr))
    {
        xy indice;
        indice.horaInicio=datos.horaInicio;
        indice.salon = EdificioEncontrado.salon;
        indice.edificio= EdificioEncontrado.edificio;
        contenido cont ;
        cont.horaFinal = datos.horaFinal;
        cont.curso = cursoEncontrado;
        NodoOrtogonal* nuevo = new NodoOrtogonal(indice,cont);

        this->dia = datos.dia;
        respuesta +="{"+fila->insertar(nuevo)+"}";
        respuesta +="{"+col->insertar(nuevo)+"}";

    }else{


        respuesta ="no se encontro el salon o el edificio enviado o el curso";
    }


    return  respuesta;

}

void matriz::graficar(){
    std::string nombre = "matriz";
    generarDot(nombre);

    //especificar el nomabre en los metodos system
    system("dot -Tsvg -O matriz.dot");
    system("xdg-open matriz.dot.svg");

}

void matriz::generarDot(std::string nombre){

    std::ofstream archivo;
    archivo.open(nombre+".dot",std::ios::out);//abriendo el archivo
    if(archivo.fail()){ std::cout<<"No se pudo crear el archivo"; exit(1);}

    archivo<<"digraph g "<<std::endl;
    archivo<<"{\n"<<std::endl;
    archivo<<"\tnodesep = 0.5;\n"<<std::endl;
    archivo<<"\tnode[shape=box, color=turquoise4, fillcolor=green,style=filled ];\n"<<std::endl;
    archivo<<"\tedge[color=tomato];\n"<<std::endl;
    archivo<<"\trankdir=UD;\n"<<std::endl;

    archivo<<txtCabeceraCol()<<std::endl;
    archivo<<txtCabeceraFila()<<std::endl;
    archivo<<txtFilas()<<std::endl;
    archivo<<txtColumnas()<<std::endl;

    archivo<<"}"<<std::endl;
    archivo.close();//cerrar el archivo


}

std::string matriz::txtCabeceraCol()
{
    std::string result = "";
    std::string rank ="\t{ rank = same ;";


    NodoCabeceraColumna* actual = col->primero;
    std::string Aclean="";
    std::string Acleansig="";
    std::string Ahora="";

    result+="\t//----------------------cabecera columnas-----------------------\n";
    while(actual != nullptr){

        Aclean = dia+csv::clean(actual->horaInicio);
        Ahora = actual->horaInicio;

        if(actual->sig==nullptr){

            if(actual==col->primero){


                result+="\t"+dia+" -> nd"+Aclean+"[constraint=false];\n";
                result+="\tnd"+Aclean;
                result+="[label =\""+Ahora+"\"];\n";
                rank+= dia+"; nd"+Aclean+";}\n";

            }else{


                result+="\tnd"+Aclean;
                result+="[label =\""+Ahora+"\"];\n";

                rank+=" nd"+Aclean+";}\n";

            }

        }else{

            Acleansig = dia+csv::clean(actual->sig->horaInicio);
            if(actual==col->primero){

                result+="\t"+dia+" -> nd"+Aclean+"[constraint=false];\n";

                result+="\tnd"+Aclean;
                result+="[label =\""+Ahora+"\"];\n";

                result+="\tnd"+Aclean;
                result+=" -> ";
                result+= "nd"+Acleansig;
                result+=" -> ";
                result+="nd"+Aclean+"[constraint=false];\n";

                rank+= dia+"; nd"+Aclean+";";

            }else{

                result+="\tnd"+Aclean;
                result+="[label =\""+Ahora+"\"];\n";

                result+="\tnd"+Aclean;
                result+=" -> ";
                result+= "nd"+Acleansig;
                result+=" -> ";
                result+="nd"+Aclean+"[constraint=false];\n";

                rank+=" nd"+Aclean+";";

            }

        }

        actual =actual->sig;
    }


     result+=rank;
     return result;
}

std::string matriz::txtCabeceraFila(){

    std::string result="\n\n";
    std::string edificio="";
    std::string edificiosig="";
    std::string no_salon ="";
    std::string no_salonsig="";
    std::string edificioClean ="";
    std::string edificioCleanSig ="";

    NodoCabeceraFila* actual = fila->primero;

    result+="\t//----------------------cabecera filas-----------------------\n";
    while(actual != nullptr){

        edificioClean =actual->edificio->getValor();
        edificio = dia+csv::ReplaceAll(edificioClean,"-","") ;
        no_salon = std::to_string(actual->salon->getValor().no_salon);

        if(actual->abajo==nullptr){

            if(actual==fila->primero){

                result+="\t"+dia+" -> nd"+edificio+no_salon+"[constraint=true];\n";
                result+="\tnd"+edificio+no_salon;
                result+="[label =\""+edificioClean+"\\n"+no_salon+"\"];\n";


            }else{

                result+="\tnd"+edificio+no_salon;
                result+="[label =\""+edificioClean+"\\n"+no_salon+"\"];\n";

            }

        }else{
            edificioCleanSig = actual->abajo->edificio->getValor();
            edificiosig =dia+csv::ReplaceAll(edificioCleanSig,"-","") ;
            no_salonsig = std::to_string(actual->abajo->salon->getValor().no_salon);

            if(actual==fila->primero){

                result+="\t"+dia+" -> nd"+edificio+no_salon+"[constraint=true];\n";

                result+="\tnd"+edificio+no_salon;
                result+="[label =\""+edificioClean+"\\n"+no_salon+"\"];\n";

                result+="\t nd"+edificio+no_salon;
                result+=" -> ";
                result+= "nd"+edificiosig+no_salonsig;
                result+=" -> ";
                result+="nd"+edificio+no_salon+"[constraint=true];\n";

            }else{

                result+="\tnd"+edificio+no_salon;
                result+="[label =\""+edificioClean+"\\n"+no_salon+"\"];\n";

                result+="\t nd"+edificio+no_salon;
                result+=" -> ";
                result+= "nd"+edificiosig+no_salonsig;
                result+=" -> ";
                result+="nd"+edificio+no_salon+"[constraint=true];\n";

            }

        }

        actual =actual->abajo;
    }



    return result;
}

std::string matriz::txtFilas(){
    std::string result = "";
    std::string cabecera ="";
    std::string nodo="";
    std::string nodosig ="";
    std::string horafinal="";
    std::string cat ="";
    std::string curso="";
    std::string rank ="\t{ rank = same ;";



    NodoCabeceraFila* actual = fila->primero;
    NodoOrtogonal* aux ;

    while(actual != nullptr){
        rank ="\t{ rank = same ;";
        cabecera ="nd";
        cabecera +=dia+csv::ReplaceAll(actual->edificio->getValor(),"-","") ;
        cabecera += std::to_string(actual->salon->getValor().no_salon);

         result +="\t//---------------- FIla:"+cabecera+"--------------------------\n";

        aux = actual->listHorizontal->primerolistaHorizontal;
        while(aux!=nullptr)
        {

             nodo = "";
             nodo += cabecera;
             nodo += csv::clean(aux->getIndex().horaInicio);
             horafinal = aux->getContenido().horaFinal;
             cat = aux->getContenido().curso->getCatedratico()->getValor().nombre;
             curso =aux->getContenido().curso->getValor().nombre;


            if(aux->getder()==nullptr)
            {
                if(aux == actual->listHorizontal->primerolistaHorizontal){

                    result+="\t"+cabecera+" -> "+nodo+"[constraint=false];\n";
                    result+="\t"+nodo;
                    result+="[label =\""+cat+"\\n"+curso+"\\n"+horafinal+"\"];\n";
                    rank+= cabecera+"; "+nodo+";}\n";

                }else{

                    result+="\t"+nodo;
                    result+="[label =\""+cat+"\\n"+curso+"\\n"+horafinal+"\"];\n";
                    rank+= nodo+";}\n";

                }


            }else{

                nodosig ="";
                nodosig += cabecera;
                nodosig += csv::clean(aux->getder()->getIndex().horaInicio);

                if(aux == actual->listHorizontal->primerolistaHorizontal){


                    result+="\t"+cabecera+" -> "+nodo+";\n";
                    result+="\t"+nodo;
                    result+="[label =\""+cat+"\\n"+curso+"\\n"+horafinal+"\"];\n";
                    result+="\t"+nodo;
                    result+=" -> ";
                    result+= nodosig;
                    result+=" -> ";
                    result+=nodo+"[constraint=false];\n";

                    rank+= cabecera+"; "+nodo+";";


                }else{

                    result+="\t"+nodo;
                    result+="[label =\""+cat+"\\n"+curso+"\\n"+horafinal+"\"];\n";

                    result+="\t"+nodo;
                    result+=" -> ";
                    result+= nodosig;
                    result+=" -> ";
                    result+=nodo+";\n";

                    rank+= nodo+";";


                }

            }


            aux= aux->getder();
        }

        result+= rank+"";
        actual =actual->abajo;
    }



    return result;
}

std::string matriz::txtColumnas(){
    std::string result = "";

    std::string cabecera ="";
    std::string nodo="";
    std::string nodosig ="";




    NodoCabeceraColumna* actual = col->primero;
    NodoOrtogonal* aux ;

    while(actual != nullptr){

        cabecera ="";
        cabecera +=csv::clean(actual->horaInicio);

        aux = actual->listVertical->primerolistaVertical;
         result +="\n\t//---------------- Col:"+dia+cabecera+"--------------------------\n";
        while(aux!=nullptr)
        {
             nodo = "";
             nodo += dia+csv::ReplaceAll(aux->getIndex().edificio->getValor(),"-","");
             nodo +=std::to_string(aux->getIndex().salon->getValor().no_salon);
             nodo += cabecera;



            if(aux->getDown()==nullptr)
            {
                if(aux == actual->listVertical->primerolistaVertical){

                    result+="\tnd"+dia+cabecera+" -> nd"+nodo+"[constraint=true];\n";

                }


            }else{

                nodosig ="";
                nodosig +=dia+csv::ReplaceAll(aux->getDown()->getIndex().edificio->getValor(),"-","");
                nodosig +=std::to_string(aux->getDown()->getIndex().salon->getValor().no_salon);
                nodosig += cabecera;

                if(aux == actual->listVertical->primerolistaVertical){


                    result+="\t nd"+dia+cabecera+" -> nd"+nodo+"[constraint=true];\n";
                    result+="\tnd"+nodo;
                    result+=" -> ";
                    result+="nd"+nodosig;
                    result+=" -> ";
                    result+="nd"+nodo+"[constraint=true];\n";

                }else{

                    result+="\tnd"+nodo;
                    result+=" -> ";
                    result+="nd"+nodosig;
                    result+=" -> ";
                    result+="nd"+nodo+"[constraint=true];\n";



                }

            }


            aux= aux->getDown();
        }


        actual =actual->sig;
    }

    return result;
}

std::string matriz::getDot()
{
    std::string result ="";

    result += "//------------------------------------"+this->dia+"------------------------\n";
    result += "subgraph cluster_"+this->dia+"\n";
    result += "{\n";
    result += "\tnodesep = 0.5;\n";
    result += "\tnode[shape=box, color=turquoise4, fillcolor=green,style=filled ];\n";
    result += "\tedge[color=tomato];\n";
    result += "\trankdir=UD;\n";
    result += txtCabeceraCol();
    result += txtCabeceraFila();
    result += txtFilas();
    result += txtColumnas();
    result += "\tcolor=blue;\t";
    result += "\tlabel=\"Matriz del dia "+this->dia+"\"\n";
    result += "\t}\n";

    return result;
}




*/
