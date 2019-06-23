#include "gestion.h"



Gestion::Gestion()
{
    arbolCapas= new bst();
}


void Gestion::leerCapas(std::string dir){

    std::string texto;

    std::ifstream archivo;
    archivo.open(dir);

    if (archivo.is_open())
    {
        char c;
        while(!archivo.eof()){
            c = archivo.get();

            if(!(c==' ' || c=='\n'||c=='\t'|| c=='\r'|| c=='\f'||c=='\377')){
                texto += c;
            }
        }
        archivo.close();

    }else  {
        std::cout<<"Archivo no encontrado"<<std::endl;
        archivo.close();

    }


    crearArbolCapas(texto);

}

void Gestion::leerImagenes(std::string dir){

}

void Gestion::crearArbolCapas(std::string txt){

    int fila =0;
    int col = 0;
    int idCapa =0;
    matriz* capa = new matriz();
    std::string color="";
    std::string lexema="";
    int estado= 0;

    for(int i=0 ; i<txt.size();i++){

        char letra =txt[i];

        switch (estado) {
        case 0:

            if(esNumero(letra)){
                capa = new matriz();
                lexema+=letra;
                estado = 1;
            }else {
                std::cout<<"se esperaba un numero entero"<<std::endl;
                estado  = 11;
            }
            break;
        case 1:
            if(esNumero(letra)){
                lexema+=letra;
                estado = 1;
            }else if(letra=='{'){
                idCapa = std::atoi(lexema.c_str());
                lexema="";
                estado = 2;
            }else{
                std::cout<<"se esperaba un numero entero"<<std::endl;
                estado  = 8;
            }
            break;
        case 2:
            if(esNumero(letra)){
                lexema+=letra;
                estado=3;
            }else {
                std::cout<<"se esperaba un numero entero"<<std::endl;
                estado  = 11;
            }

            break;
        case 3:
            if(esNumero(letra)){
                lexema+=letra;
                estado=3;
            }else if(letra==','){
                fila = std::atoi(lexema.c_str());
                lexema="";
                estado = 4;
            }else{
                std::cout<<"se esperaba un numero entero"<<std::endl;
                estado  = 11;
            }
            break;
        case 4:
            if(esNumero(letra)){
                lexema+=letra;
                estado=5;
            }else {
                std::cout<<"se esperaba un numero entero"<<std::endl;
                estado  = 11;
            }
            break;
        case 5:
            if(esNumero(letra)){
                lexema+=letra;
                estado=5;
            }else if(letra==','){
                col = std::atoi(lexema.c_str());
                lexema="";
                estado =6;
            }else{
                std::cout<<"se esperaba un numero entero"<<std::endl;
                estado  = 11;
            }
            break;
        case 6:
            if(letra=='#'){
                lexema+=letra;
                estado =7;
            }else{
                std::cout<<"se esperaba un '#' "<<std::endl;
                estado  = 11;
            }

            break;
        case 7:
            if(esAlfaNumerico(letra)){
                lexema+=letra;
                estado =8;
            }else {
                std::cout<<"se esperaba un caracter alfanumerico "<<std::endl;
                estado  = 11;
            }
            break;
        case 8:
            if(esAlfaNumerico(letra)){
                lexema+=letra;
                estado =8;
            }else if (letra==';') {
                color = lexema;
                lexema="";
                estado =9;
            }else {
                std::cout<<"se esperaba un caracter alfanumerico o una ';' "<<std::endl;
                estado  = 11;
            }

            break;
        case 9:
            if(esNumero(letra)){
                lexema+=letra;
                capa->add(fila,col,color);
                estado =3;
            }else if (letra=='}') {
                arbolCapas->add(idCapa, capa);
                estado=0;
            }else{
                std::cout<<"se esperaba un '}' "<<std::endl;
                estado  = 11;
            }
            break;

        case 11:

            std::cout<<"hubo un error lexico al leer el archivo"<<std::endl;
            break;

        }

    }

}




bool Gestion::esNumero(char l){

    if(l>='0' && l<='9'){
        return true;
    }else{
        return false;
    }

}


bool Gestion::esAlfaNumerico(char l){


    if((l>='a'&& l<='z')||(l>='A'&& l<='Z')||(esNumero(l))){

        return true;
    }else{
        return false;
    }

}

























