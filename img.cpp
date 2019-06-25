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
    first =last=nullptr;
}


void ListCapas::add(int id, bst* arbol){

    NodoBst* nuevoCapa = arbol->buscar(id);

    if(nuevoCapa){
        capa* nuevoImg = new capa(nuevoCapa);
        if(first){

            if(!search(id)){
                last->setSig(nuevoImg);
                last=nuevoImg;
            }
        }else{
            first = last =nuevoImg;

        }
    }

}


bool ListCapas::search(int id){

    capa*actual= first;
    while (actual) {

        if(actual->getCapa()->id  ==id){
            return true;
        }
        actual =actual->getSig();
    }
    return false;
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

img::img(){

    ant=sig = nullptr;
    listCapa = nullptr;
    this->idImg = 0;
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
    dotEnlacesListaArbol="";
}

bool listImg::search(int idImg){

    img*actual=first;
    do{

        if(actual->getId() ==idImg){
            return true;
        }
        actual = actual->getSig();
    }while (actual!=first);


    return false;
}

void listImg::add(img* &nuevo, int idimg)
{
    if(first){

          if(!search(idimg)){

          last->setSig(nuevo);
          nuevo->setAnt(last);
          first->setAnt(nuevo);
          nuevo->setSig(first);
          last=nuevo;

          }

    }else {

        first= nuevo;
        last = nuevo;
        nuevo->setSig(nuevo);
        nuevo->setAnt(nuevo);

    }

}

void listImg::addImgUsuario(int id,  listImg* listaImganes){
    img* nuevo = searchImg(id,listaImganes);

    if(nuevo){
        if(first){

            if(!search(id)){

                nuevo->setSig(first);
                nuevo->setAnt(last);
                first->setAnt(nuevo);
                last->setSig(nuevo);
                last=nuevo;

            }

        }else {

            nuevo->setSig(nuevo);
            nuevo->setAnt(nuevo);
            last=first=nuevo;
        }
    }
}


img* listImg::searchImg(int id,listImg* listaImagenes){

    return   listaImagenes->getImg(id);

}


void listImg::imprimir(){

    img* actual =first;

    if(first){

        do{
            std::string idImg =std::to_string(actual->getId());
            std::cout<<"-------------Imagen "+idImg+"-------------"<<std::endl;

            capa* actualcapa  = actual->getListCapa()->getFirst();

            while (actualcapa) {

                std::string idCapa = std::to_string(actualcapa->getCapa()->id);
                std::cout<<"\tidCapa "+idCapa<<std::endl;
                actualcapa = actualcapa->getSig();
            }

            actual = actual->getSig();
        }while (actual !=first);

    }



}

void listImg::graficar()
{
    std::string nombre = "ListaImagenes";
    textoDot(nombre);

    //especificar el nomabre en los metodos system
    system("dot -Tpng -O ListaImagenes.dot");
    system("xdg-open ListaImagenes.dot.png");
}

void listImg::textoDot(std::string nombre)
{
    std::ofstream archivo;
    archivo.open(nombre+".dot",std::ios::out);//abriendo el archivo
    if(archivo.fail()){ std::cout<<"No se pudo crear el archivo"; exit(1);}

    archivo<<"digraph g "<<std::endl;
    archivo<<"{"<<std::endl;
    archivo<<"\tnodesep = 0.5;"<<std::endl;
    archivo<<"\tnode[shape=box, color=turquoise4, fillcolor=green,style=filled];"<<std::endl;
    archivo<<"\tedge[color=tomato];"<<std::endl;
    archivo<<getDot()<<std::endl;

    archivo<<"}"<<std::endl;

    archivo.close();//cerrar el archivo

}

std::string listImg::getDotImagen(int id){

    std::string result="";
    img* imagen =getImg(id);
    if(imagen){

        int cont=0;
        std::string scont="";
        std::string node="";
        std::string sconts="";
        std::string Capa="";
        std::string CapaSig="";
        std::string capalabel="";
        std::string capalabelSig="";
        std::string imglabel="imagen"+std::to_string(id);



        capa* actualCapa = imagen->getListCapa()->getFirst();
        while (actualCapa) {
            node = "node"+std::to_string(actualCapa->getCapa()->id);
            scont=std::to_string(cont);
            capalabel = "capa"+std::to_string(actualCapa->getCapa()->id);
            Capa= imglabel+capalabel+scont;

            result+="\t\t\t"+imglabel+"[label=\""+imglabel+"\"];\n";
            // si no es el ultimo nodo
            if(actualCapa->getSig()){
                sconts=std::to_string(cont+1);
                capalabelSig ="capa"+std::to_string(actualCapa->getSig()->getCapa()->id);
                CapaSig =imglabel+capalabelSig+sconts;

                //---------------------------para listas con maas de  un solo nodo------------------------

                //si es un nodo intermedio en una lista con mas de un nodo
                if(actualCapa != imagen->getListCapa()->getFirst()){
                    result+="\t\t\t"+Capa+"[label=\""+capalabel+"\"];\n";
                    result+="\t\t\t"+Capa+" -> "+CapaSig+" [constraint=true];\n";

                    //si es el primer nodo osea si la lista tiene mas de un nodo

                }else{
                    result+="\t\t\t"+imglabel+" -> "+Capa+" [constraint=true];\n";
                    result+="\t\t\t"+Capa+"[label=\""+capalabel+"\"];\n";
                    result+="\t\t\t"+Capa+" -> "+CapaSig+" [constraint=true];\n";

                }

                //si es el ultimo nodo
            }else{

                //---------------------------para listas con un solo nodo------------------------

                //si el ultimo nodo no es igual al primero
                if(actualCapa != imagen->getListCapa()->getFirst()){
                    result+="\t\t\t"+Capa+"[label=\""+capalabel+"\"];\n";

                    //si el ultimo nodo es igual al primer nodo
                    //osea solo existe un nodo
                }else{
                    result+="\t\t\t"+imglabel+" -> "+Capa+" [constraint=true];\n";
                    result+="\t\t\t"+Capa+"[label=\""+capalabel+"\"];\n";
                }

            }

            dotEnlacesListaArbol+= "\t\t"+Capa+" -> "+node+"\n";

            cont++;
            actualCapa = actualCapa->getSig();
        }




    }


    return  result;
}

std::string listImg::getDot(){

    std::string  result= "";
    std::string  imgActual= "";
    std::string  imgSig= "";
    std::string  capaActual= "";
    std::string  nodecapaActual= "";
    std::string  nodecapaSig= "";
    int contCapa = 0;
    std::string scontCapa="";
    std::string scontCapaSig="";

    img* actualImg = first;

    do {

        contCapa=0;
        imgActual = "imagen"+std::to_string(actualImg->getId());

        result +="\n\t//-----------------------------------------------------------------------------\n";
        result +="\t//-----------------"+imgActual+"-------------------------------------------------\n";
        result +="\t//-------------------------------------------------------------------------------\n";

        //si el nodo de la imagen no es el ultimo
        if(actualImg->getSig()!=first){

            imgSig = "imagen"+std::to_string(actualImg->getSig()->getId());
            result+="\t"+imgActual+"[label=\""+imgActual+"\"];\n";
            result+="\t"+imgActual+" -> "+imgSig+" -> "+imgActual+" [constraint=false];\n";

            //si el nodo es el ultimo

        }else{
            std::string firstImg ="imagen"+std::to_string(first->getId());
            result+="\t"+imgActual+"[label=\""+imgActual+"\"];\n";
            result+="\t"+imgActual+" -> "+firstImg+" -> "+imgActual+" [constraint=false];\n";
        }

        capa* actualCapa = actualImg->getListCapa()->getFirst();

        while (actualCapa) {

            scontCapa = std::to_string(contCapa);
            capaActual ="capa"+std::to_string(actualCapa->getCapa()->id);
            nodecapaActual =imgActual+capaActual+scontCapa;

            // si no es la ultima capa de la lista
            if(actualCapa->getSig()){
                scontCapaSig = std::to_string(contCapa+1);
                nodecapaSig =imgActual+"capa"+std::to_string(actualCapa->getSig()->getCapa()->id)+scontCapaSig;
                //si es una capa intermedia de la lista
                if(actualCapa != actualImg->getListCapa()->getFirst()){

                    result+="\t"+nodecapaActual+"[label=\""+capaActual+"\"];\n";
                    result+="\t"+nodecapaActual+" -> "+nodecapaSig+" [constraint=true];\n";

                    //si es la primera capa de la lista
                }else {

                    result+="\t"+imgActual+" -> "+nodecapaActual+" [constraint=true];\n";
                    result+="\t"+nodecapaActual+"[label=\""+capaActual+"\"];\n";
                    result+="\t"+nodecapaActual+" -> "+nodecapaSig+" [constraint=true];\n";

                }

                //si es la ultima capa de la lista
            }else {

                //si la ultima capa no es igual a la primera capa
                if(actualCapa != actualImg->getListCapa()->getFirst()){

                    result+="\t"+nodecapaActual+"[label=\""+capaActual+"\"];\n";

                    //si la ultima capa es igual a la primer capa
                }else {
                    result+="\t"+imgActual+" -> "+nodecapaActual+" [constraint=true];\n";
                    result+="\t"+nodecapaActual+"[label=\""+capaActual+"\"];";

                }



            }

            contCapa++;
            actualCapa = actualCapa->getSig();
        }



        actualImg = actualImg->getSig();
    }while (actualImg!=first);

    return  result;

}

std::string listImg::subGrafoArbol(std::string dotArbol){
    std::string arbol ="";
    arbol+="\t\tsubgraph cluster_0 {\n";
    arbol+="\t\t\tnode[shape=record, height=.1, color=turquoise4, fillcolor=green,style=filled ];\n";
    arbol+="\t\t\tedge[color=blue];\n";
    arbol+=dotArbol;
    arbol+="\t\t\tcolor=blue;\n";
    arbol+="\t\t\tlabel=\"Arbol de Capas\"\n";
    arbol+="\t\t}\n";
    return arbol;
}

std::string listImg::subGrafoLista(int id)
{
    std::string lista="";
    lista+="\t\tsubgraph cluster_1 {\n";
    lista+="\t\t\trankdir=ud;\n";
    lista+="\t\t\tnode[shape=box, color=red, fillcolor=wheat4,style=filled ];\n";
    lista+="\t\t\tedge[color=tomato arrowhead=vee, dir=both,arrowsize=1, arrowtail=dot];\n";
    lista+= ""+getDotImagen(id);
    lista+="\t\t\tcolor=blue;\n";
    lista+="\t\t\tlabel=\"Lista de de imagenes\"\n";
    lista+="\t\t}\n";


    return lista;
}

img* listImg::getImg(int id){

    img*actual=first;
    do {
        if(actual->getId() == id) return actual;
        actual = actual->getSig();
    }while (actual != first);


    return nullptr;
}

void listImg::graficarImagen(int id,std::string dotArbol){

    dotEnlacesListaArbol="";
    std::string nombre = "ImagenArbolCapas";
    graficarImagen(id,dotArbol,nombre);

    //especificar el nomabre en los metodos system
    system("dot -Tsvg -O ImagenArbolCapas.dot");
    //system("dot -Tsvg -O ImagenArbolCapas.dot");
    system("xdg-open ImagenArbolCapas.dot.svg");


}

void listImg::graficarImagen(int id,std::string dotArbol,std::string nombre){



    std::ofstream archivo;
    archivo.open(nombre+".dot",std::ios::out);//abriendo el archivo
    if(archivo.fail()){ std::cout<<"No se pudo crear el archivo"; exit(1);}

    archivo<<"digraph G \n{\n "<<std::endl;
    archivo<<"\tgraph [fontsize=10 fontname=\"Verdana\" compound=true];\n"<<std::endl;
    archivo<<"\tnode [shape=record fontsize=10 fontname=\"Verdana\"];\n"<<std::endl;


    archivo<<subGrafoArbol(dotArbol)<<std::endl;
    archivo<<subGrafoLista(id)<<std::endl;
    archivo<<dotEnlacesListaArbol<<std::endl;

    archivo<<"}\n"<<std::endl;

    archivo.close();//cerrar el archivo


}


//********************************************************************************
//********************************************************************************
//*********************** NodoimgUser *******************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************
NodoImgUser::NodoImgUser(img* imagen, int idImg){

    sig =nullptr;
    this->idImg=idImg;
    this->imagen = imagen;
}


img *NodoImgUser::getImagen() const
{
    return imagen;
}

void NodoImgUser::setImagen(img *value)
{
    imagen = value;
}

int NodoImgUser::getIdImg() const
{
    return idImg;
}

void NodoImgUser::setIdImg(int value)
{
    idImg = value;
}




//********************************************************************************
//********************************************************************************
//*********************** ListImgUser ********************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************




