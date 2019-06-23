#include "bst.h"

//********************************************************************************
//********************************************************************************
//************************ Clase nodo bst ****************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************
NodoBst::NodoBst(int id, matriz* capa){

    this->id =id;
    this->capa = capa;
    this->der =nullptr;
    this->izq = nullptr;


}


//********************************************************************************
//********************************************************************************
//************************ Clase BST *********************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************

bst::bst(){

    this->raiz =nullptr;
    txtgrafica = "";
    id ="";
    idDer= "";
    idIzq ="";
}

void bst::add(int id, matriz* capa){

    if(raiz){
        add(id,capa, raiz);
    }else {
        raiz = new NodoBst(id,capa);
    }

}

void bst::add(int id, matriz *capa, NodoBst*&temp){

    if(temp){

        if(id>temp->id){
            add(id, capa, temp->der);
        }else if(id<temp->id){
            add(id, capa, temp->izq);
        }else{
            std::cout<<"ya existe en nodo "<<std::endl;
        }
    }else {
        temp = new NodoBst(id, capa);
    }


}

void bst::inorden(NodoBst* temp){

    if(temp){

        inorden(temp->izq);
        std::cout<<"id: "+std::to_string(temp->id)+"\n"<<std::endl;
        inorden(temp->der);

    }
}
void bst::postOrden(NodoBst* temp){
    if(temp){

        postOrden(temp->izq);
        postOrden(temp->der);
        std::cout<<"id: "+std::to_string(temp->id)+"\n"<<std::endl;

    }
}
void bst::preOrden(NodoBst* temp){

    if(temp){

        std::cout<<"id: "+std::to_string(temp->id)+"\n"<<std::endl;
        preOrden(temp->izq);
        preOrden(temp->der);


    }
}

void bst::mostrar(int tipo){

    switch (tipo) {
    case INORDEN:
        inorden(raiz);
        break;
    case POSTORDEN:
        postOrden(raiz);
        break;
    case PREORDEN:
        preOrden(raiz);
        break;


    }
}

NodoBst* bst::buscar(int id){
    return buscar(id ,raiz);
}



NodoBst* bst::buscar(int id, NodoBst *raiz){

    if(raiz){
        if(id>raiz->id){
            return   buscar(id, raiz->der);
        }else if(id<raiz->id){
            return buscar(id,raiz->izq );
        }else{
            return raiz;
        }
    }else {
        return nullptr;
    }

}





void bst::graficarPreorden()
{
    txtgrafica="";
    if(this->raiz)
    {
        graficarPreorden(this->raiz);
    }else {
        txtgrafica = "node20[label = \"<f0> | <f1> Arbol Vacio | <f2>\"]";
    }
}

void bst::graficarPreorden(NodoBst* raiz)
{
    if(raiz)
    {
        id= std::to_string(raiz->id);
        txtgrafica +="\t\t\tnode"+id+"[label =\"<f0> | <f1> capa: "+id+" | <f2>\"]\n";

        graficarPreorden(raiz->izq);
        if(raiz->izq)
        {
            id= std::to_string(raiz->id);
            idIzq=std::to_string(raiz->izq->id);
            txtgrafica += "\t\t\t\"node"+id+"\":f0-> \"node"+idIzq+"\":f1\n\n";
        }

        graficarPreorden(raiz->der);
        if(raiz->der)
        {
            id= std::to_string(raiz->id);
            idDer = std::to_string(raiz->der->id);
            txtgrafica += "\t\t\t\"node"+id+"\":f2-> \"node"+idDer+"\":f1\n\n";
        }
    }

}



void bst::graficar()
{
    std::string nombre = "arbolBst";
    textoDot(nombre);

    //especificar el nomabre en los metodos system
    system("dot -Tpng -O arbolBst.dot");
    system("xdg-open arbolBst.dot.png");
}

void bst::textoDot(std::string nombre)
{
    std::ofstream archivo;
    archivo.open(nombre+".dot",std::ios::out);//abriendo el archivo
    if(archivo.fail()){ std::cout<<"No se pudo crear el archivo"; exit(1);}

    archivo<<"digraph g "<<std::endl;
    archivo<<"{\n"<<std::endl;
    archivo<<"node[shape=record, height=.1, color=turquoise4, fillcolor=green,style=filled ];"<<std::endl;
    archivo<<"edge[color=tomato];"<<std::endl;

    graficarPreorden();
    archivo<<txtgrafica<<std::endl;

    archivo<<"}"<<std::endl;

    archivo.close();//cerrar el archivo

}







