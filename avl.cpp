#include "avl.h"
//********************************************************************************
//********************************************************************************
//************************ nodoAvl ***********************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************
listImg *NodoAvl::getListaImagen() const
{
    return listaImagen;
}

void NodoAvl::setListaImagen(listImg *value)
{
    listaImagen = value;
}

std::string NodoAvl::getNombre() const
{
    return nombre;
}

void NodoAvl::setNombre(const std::string &value)
{
    nombre = value;
}

NodoAvl *NodoAvl::getIzq() const
{
    return izq;
}

void NodoAvl::setIzq(NodoAvl *value)
{
    izq = value;
}

NodoAvl *NodoAvl::getDer() const
{
    return der;
}

void NodoAvl::setDer(NodoAvl *value)
{
    der = value;
}

int NodoAvl::getFe() const
{
    return fe;
}

void NodoAvl::setFe(int value)
{
    fe = value;
}

NodoAvl::NodoAvl(listImg* listaImagen,std::string nombre){

    this->listaImagen = listaImagen;
    this->nombre = nombre;
    izq=der=nullptr;
    fe=0;

}
NodoAvl::NodoAvl(listImg* listaImagen,std::string nombre,int fe){

    this->listaImagen = listaImagen;
    this->nombre = nombre;
    izq=der=nullptr;
    this->fe=fe;


}
NodoAvl::NodoAvl(NodoAvl* izq,listImg* listaImagen,std::string nombre,NodoAvl* der){

    this->listaImagen = listaImagen;
    this->nombre = nombre;
    this->izq=izq;
    this->der=der;
    this->fe=0;

}
NodoAvl::NodoAvl(NodoAvl* izq,int fe,listImg* listaImagen,std::string nombre, NodoAvl* der){
    this->listaImagen = listaImagen;
    this->nombre = nombre;
    this->izq=izq;
    this->der=der;
    this->fe=fe;
}

void NodoAvl::imprimir(){

    std::cout<<"Usuario: "+this->nombre<<std::endl;
}
//********************************************************************************
//********************************************************************************
//************************ clase Avl ********************************************
//********************************************************************************
//********************************************************************************
//********************************************************************************
NodoAvl *Avl::getRaiz() const
{
    return raiz;
}

void Avl::setRaiz(NodoAvl *value)
{
    raiz = value;
}
Avl::Avl(){
    raiz=nullptr;
}
Avl::Avl(NodoAvl* r){
    raiz =r;
}

NodoAvl* Avl::rsi(NodoAvl*n,NodoAvl*n1){

    n->setIzq(n1->getDer());
    n1->setDer(n);

    //actualizacon de los factores de equilibrio
    if(n1->getFe() ==-1)//la condicion es true en la insercion
    {
        n->setFe(0);
        n1->setFe(0);
    }else {
        n->setFe(-1);
        n1->setFe(1);
    }
    return n1;
}

NodoAvl* Avl::rsd(NodoAvl*n,NodoAvl*n1){

    n->setDer(n1->getIzq());
    n1->setIzq(n);

    //actualizacon de los factores de equilibrio
    if(n1->getFe() ==1)//la condicion es true en la insercion
    {
        n->setFe(0);
        n1->setFe(0);
    }else {
        n->setFe(1);
        n1->setFe(-1);
    }

    return n1;
}

NodoAvl* Avl::rddi(NodoAvl*n,NodoAvl*n1){

    NodoAvl*n2;
    n2 =n1->getIzq();

    n->setDer(n2->getIzq());
    n2->setIzq(n);
    n1->setIzq(n2->getDer());
    n2->setDer(n1);


    if (n2->getFe() == 1)
        n->setFe(-1);
    else
        n->setFe(0);
    if (n2->getFe() == -1)
        n1->setFe(1);
    else
        n1->setFe(0);
    n2->setFe(0);
    return n2;

}


NodoAvl* Avl::rdid(NodoAvl*n,NodoAvl*n1){

    NodoAvl* n2;
    n2 =n1->getDer();

    n->setIzq(n2->getDer());
    n2->setDer(n);
    n1->setDer(n2->getIzq());
    n2->setIzq(n1);

    if (n2->getFe() == 1)
        n1->setFe(-1);
    else
        n1->setFe(0);
    if (n2->getFe() == -1)
        n->setFe(1);
    else
        n->setFe(0);
    n2->setFe(0);
    return n2;

}


void Avl::insertarAvl(listImg* listaImagen,std::string nombre){

    bool hc = false;

    raiz = insertarAvl(raiz,listaImagen,nombre,hc);

}


NodoAvl* Avl::insertarAvl(NodoAvl* raiz, listImg* listaImagen,std::string nombre, bool &hc){

    NodoAvl *n1;
    if (raiz == nullptr)
    {
        raiz = new NodoAvl(listaImagen,nombre);
        hc = true;
    }
    else if (nombre < raiz->getNombre())
    {
        NodoAvl *iz;
        iz = insertarAvl(raiz->getIzq(),listaImagen,nombre, hc);
        raiz->setIzq(iz);
        // regreso por los nodos del camino de búsqueda
        if (hc)
            // siempre se comprueba si creció en altura
        {
            // decrementa el fe por aumentar la altura de rama izquierda
            switch (raiz->getFe())
            {
            case 1:
                // tenía +1 y creció su izquierda
                raiz->setFe(0);
                hc = false; // árbol deja de crecer
                break;
            case 0:
                // tenía 0 y creció su izquierda
                raiz->setFe(-1); // árbol sigue creciendo
                break;
            case -1:
                // aplicar rotación a la izquierda
                n1 = raiz->getIzq();
                if (n1->getFe() == -1)
                    raiz = rsi(raiz, n1);
                else
                    raiz = rdid(raiz, n1);
                hc = false; // árbol deja de crecer en ambas rotaciones
            }
        }
    }
    else if (nombre > raiz->getNombre())
    {
        NodoAvl *dr;
        dr = insertarAvl(raiz->getDer(), listaImagen,nombre, hc);
        raiz->setDer(dr);
        // regreso por los nodos del camino de búsqueda
        if (hc)
            // siempre se comprueba si creció en altura
        {
            // incrementa el fe por aumentar la altura de rama izquierda
            switch (raiz->getFe())
            {
            case 1:
                // aplicar rotación a la derecha
                n1 = raiz->getDer();
                if (n1->getFe() == +1)
                    raiz = rsd(raiz, n1);
                else
                    raiz = rddi(raiz,n1);
                hc = false; // árbol deja de crecer en ambas rotaciones
                break;
            case
            0: // tenía 0 y creció su derecha
                raiz->setFe(+1);
                // árbol sigue creciendo
                break;
            case -1:
                // tenía -1 y creció su derecha
                raiz->setFe(0);
                hc = false;
                // árbol deja de crecer
            }
        }
    }
    else{
        // throw "No puede haber claves repetidas " ;
        std::cout<<""<<std::endl;
    }

    return raiz;

}



void Avl::mostrar(int tipo){

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

void Avl::inorden(NodoAvl* temp){

    if(temp){

        inorden(temp->getIzq());
        std::cout<<"id: "+temp->getNombre()+"\n"<<std::endl;
        inorden(temp->getDer());

    }
}
void Avl::postOrden(NodoAvl* temp){
    if(temp){

        postOrden(temp->getIzq());
        postOrden(temp->getDer());
        std::cout<<"id: "+temp->getNombre()+"\n"<<std::endl;

    }
}
void Avl::preOrden(NodoAvl* temp){

    if(temp){

        std::cout<<"id: "+temp->getNombre()+"\n"<<std::endl;
        preOrden(temp->getIzq());
        preOrden(temp->getDer());


    }
}



void Avl::graficar()
{
    std::string nombre = "arbolAvl";
    textoDot(nombre);

    //especificar el nomabre en los metodos system
    system("dot -Tpng -O arbolAvl.dot");
    system("xdg-open arbolAvl.dot.png");
}

void Avl::textoDot(std::string nombre)
{
    std::ofstream archivo;
    archivo.open(nombre+".dot",std::ios::out);//abriendo el archivo
    if(archivo.fail()){ std::cout<<"No se pudo crear el archivo"; exit(1);}

    archivo<<"digraph g "<<std::endl;
    archivo<<"{\n"<<std::endl;
    archivo<<"node[shape=record, height=.1, color=turquoise4, fillcolor=green,style=filled ];"<<std::endl;
    archivo<<"edge[color=blue];"<<std::endl;

    graficarPreorden();
    archivo<<txtgrafica<<std::endl;

    archivo<<"}"<<std::endl;

    archivo.close();//cerrar el archivo

}

void Avl::graficarPreorden()
{
    txtgrafica="";
    if(this->raiz)
    {
        graficarPreorden(this->raiz);
    }else {
        txtgrafica = "node20[label = \"<f0> | <f1> Arbol Vacio | <f2>\"]";
    }
}

void Avl::graficarPreorden(NodoAvl* raiz)
{
    if(raiz)
    {
        id =raiz->getNombre();
        txtgrafica +="\t\t\tnode"+id+"[label =\"<f0> | <f1> Usuario: "+id+" | <f2>\"]\n";

        graficarPreorden(raiz->getIzq());
        if(raiz->getIzq())
        {
            id= raiz->getNombre();
            idIzq=raiz->getIzq()->getNombre();
            txtgrafica += "\t\t\t\"node"+id+"\":f0-> \"node"+idIzq+"\":f1\n\n";
        }

        graficarPreorden(raiz->getDer());
        if(raiz->getDer())
        {
            id= raiz->getNombre();
            idDer = raiz->getDer()->getNombre();
            txtgrafica += "\t\t\t\"node"+id+"\":f2-> \"node"+idDer+"\":f1\n\n";
        }
    }

}





