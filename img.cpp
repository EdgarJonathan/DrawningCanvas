#include "img.h"

//********************************************************************************
//********************************************************************************
//************************ nodo capa *********************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************
NodoBst *capa::getCapa() const
{
    return Capa;
}

void capa::setCapa(NodoBst *value)
{
    Capa = value;
}

capa::capa(NodoBst*nuevo){
    this->Capa = nuevo;
    sig=nullptr;
}

capa* capa::getSig() const
{
    return sig;
}

void capa::setSig(capa *value)
{

    sig = value;
}


//********************************************************************************
//********************************************************************************
//************************ lista capa *** ****************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************
capa *ListCapas::getFirst() const
{
    return first;
}

void ListCapas::setFirst(capa *value)
{
    first = value;
}

ListCapas::ListCapas()
{
    first =nullptr;
}


void ListCapas::add(int id, bst* arbol){

    NodoBst* nuevoCapa = arbol->buscar(id);

    if(nuevoCapa){
        capa* nuevoImg = new capa(nuevoCapa);

        if(first){
            nuevoImg->setSig(first);
            first=nuevoImg;
        }else{
            first = nuevoImg;
        }
    }else {
        std::cout<<"No se pudo encontrar la capa"<<id<<"para agregarla a una imagen"<<std::endl;
    }



}

//********************************************************************************
//********************************************************************************
//************************ Nodo Img **********************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************

img *img::getAnt() const
{
    return ant;
}

void img::setAnt(img *value)
{
    ant = value;
}

int img::getId() const
{
    return idImg;
}

void img::setId(int value)
{
    idImg = value;
}

ListCapas *img::getListCapa() const
{
    return listCapa;
}

void img::setListCapa(ListCapas *value)
{
    listCapa = value;
}

img::img(ListCapas* list,int id){
    ant=sig = nullptr;
    listCapa = list;
    this->idImg = id;
}

img *img::getSig() const
{
    return sig;
}

void img::setSig(img *value)
{
    sig = value;
}


//********************************************************************************
//********************************************************************************
//************************ Img ***************************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************

listImg::listImg(){
    this->first= nullptr;
    this->last=nullptr;
}


void listImg::add(ListCapas *listCapa, int idimg)
{
    img* nuevo = new img(listCapa,idimg);

    if(first){
        nuevo->setSig(first);
        nuevo->setAnt(last);
        first->setAnt(nuevo);
        first->setSig(nuevo);
        first=nuevo;

    }else {

        nuevo->setSig(nuevo);
        nuevo->setAnt(nuevo);
        last=first=nuevo;
    }

}



void listImg::graficar()
{
    std::string nombre = "arbolBst";
    textoDot(nombre);

    //especificar el nomabre en los metodos system
    system("dot -Tpng -O arbolBst.dot");
    system("xdg-open arbolBst.dot.png");
}


void listImg::textoDot(std::string nombre)
{
    std::ofstream archivo;
    archivo.open(nombre+".dot",std::ios::out);//abriendo el archivo
    if(archivo.fail()){ std::cout<<"No se pudo crear el archivo"; exit(1);}

    archivo<<"digraph g "<<std::endl;
    archivo<<"{\n"<<std::endl;
    archivo<<"node[shape=record, height=.1, color=turquoise4, fillcolor=green,style=filled ];"<<std::endl;
    archivo<<"edge[color=tomato];"<<std::endl;

    archivo<<getDot()<<std::endl;

    archivo<<"}"<<std::endl;

    archivo.close();//cerrar el archivo

}

std::string listImg::getDot(){

    std::string  result= "";
    std::string  imgActual= "";
    std::string  imgSig= "";
    std::string  capaActual= "";
    std::string  capaSig= "";

    img* actualImg = first;

    while (actualImg) {

        imgActual = "imagen_"+std::to_string(actualImg->getId());

        //si el nodo de la imagen no es el ultimo
        if(actualImg->getSig()){

            imgSig = "imagen_"+std::to_string(actualImg->getSig()->getId());
            result+"\t"+imgActual+"[label=\""+imgActual+"\"];\n";
            result=+"\t"+imgActual+" -> "+imgSig+" -> "+imgActual+" [constraint=false];\n";

            //si el nodo es el ultimo

        }else{
            std::string firstImg ="imagen_"+std::to_string(first->getId());

            result+"\t"+imgActual+"[label=\""+imgActual+"\"];\n";
            result=+"\t"+imgActual+" -> "+firstImg+" -> "+imgActual+" [constraint=false];\n";
        }

        capa* actualCapa = actualImg->getListCapa()->getFirst();

        while (actualCapa) {

            capaActual ="capa"+std::to_string(actualCapa->getCapa()->id);


            // si no es la ultima capa de la lista
            if(actualCapa->getSig()){

                capaSig ="capa"+std::to_string(actualCapa->getSig()->getCapa()->id);
                //si es una capa intermedia de la lista
                if(actualCapa != actualImg->getListCapa()->getFirst()){

                    result+="\t"+capaActual+"[label=\""+capaActual+"\"];";
                    result+="\t"+capaActual+" -> "+capaSig+" [constraint=true];\n";

                    //si es la primera capa de la lista
                }else {

                    result+="\t"+imgActual+" -> "+capaActual+" [constraint=true];\n";
                    result+="\t"+capaActual+"[label=\""+capaActual+"\"];";
                    result+="\t"+capaActual+" -> "+capaSig+" [constraint=true];\n";

                }

                //si es la ultima capa de la lista
            }else {

                //si la ultima capa no es igual a la primera capa
                if(actualCapa != actualImg->getListCapa()->getFirst()){

                    result+="\t"+capaActual+"[label=\""+capaActual+"\"];";

                    //si la ultima capa es igual a la primer capa
                }else {
                    result+="\t"+imgActual+" -> "+capaActual+" [constraint=true];\n";
                    result+="\t"+capaActual+"[label=\""+capaActual+"\"];";

                }



            }


            actualCapa = actualCapa->getSig();
        }



        actualImg = actualImg->getSig();
    }

    return  result;

}










