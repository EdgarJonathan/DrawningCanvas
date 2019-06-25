#include "gestion.h"


Gestion::Gestion()
{
    arbolCapas   = new bst();
    listaImganes = new listImg();
    arbolUsuarios= new Avl();

    capasCargadas = false;
    imagenesCargadas = false;
    imagenesCargadas = false;

}

//-----------------Validar Entrada

int Gestion::validarEntrada(std::string txt){

    std::string lexema="";
    int result= 0;

    //--componentes
    for(unsigned int i=0 ; i<txt.size();i++){
        char letra =txt[i];
        //mientras no se el ultimo caracter
        if(i!=(txt.size()-1)){
            if(esNumero(letra)){
                lexema+=letra;
            }else {
                return -1;
            }
        }else {
            lexema+=letra;
            result = std::atoi(lexema.c_str());
        }
    }

    return result;

}

//-----------------Utilidades
void Gestion::limpiar(){
    system("clear");
}

//-----------------crear estructuras
void Gestion::crearCapas(std::string txt){

    int fila =0;
    int col = 0;
    int idCapa =0;
    matriz* capa = new matriz();
    std::string color="";
    std::string lexema="";
    int estado= 0;

    for(unsigned int i=0 ; i<txt.size();i++){

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
                estado  = 11;
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
            std::cout<<"error lexico en el archivo de capas"<<std::endl;
            std::cout<<"modifique el archivo y vuelva a intentar"<<std::endl;
            return;

        }

    }

    capasCargadas =true;

}

void Gestion::crearImagenes(std::string txt){

    std::string lexema="";
    int estado= 0;

    //--componentes
    int idImg =0;
    int idCapa =0;


    for(unsigned int i=0 ; i<txt.size();i++){

        char letra =txt[i];

        switch (estado) {
        case 0:
            if(esNumero(letra)){
                lexema+=letra;
                estado = 1;
            }else {
                std::cout<<"se esperaba un numero entero"<<std::endl;
                estado  = 5;
            }

            break;
        case 1:
            if(esNumero(letra)){
                lexema+=letra;
                estado = 1;
            }else if(letra=='{'){
                idImg = std::atoi(lexema.c_str());
                lexema="";
                estado = 2;
            }else{
                std::cout<<"se esperaba un numero entero"<<std::endl;
                estado  = 4;
            }

             break;
        case 2:
            if(esNumero(letra)){
                lexema+=letra;
                estado=3;
            }else {
                std::cout<<"se esperaba un numero entero"<<std::endl;
                estado  = 4;
            }
            break;
        case 3:
            if(esNumero(letra)){
                lexema+=letra;
                estado=3;
            }else if(letra==','){
                idCapa = std::atoi(lexema.c_str());
                Listacapa->add(idCapa,arbolCapas);

                lexema="";
                estado = 2;
            }else if(letra =='}'){

                idCapa = std::atoi(lexema.c_str());
                Listacapa->add(idCapa,arbolCapas);
                auxImg = new img(Listacapa,idImg);

                listaImganes->add(auxImg,idImg);

                Listacapa = new ListCapas();
                lexema ="";

                estado =0;
            }else{
                std::cout<<"se esperaba un numero entero"<<std::endl;
                estado  = 4;
            }

            break;
        case 4:
            std::cout<<"error lexico en el archivo de Imagenes"<<std::endl;
            std::cout<<"modifique el archivo y vuelva a intentar"<<std::endl;
            return;
        }

    }

    imagenesCargadas = true;
}

void Gestion::crearUsuarios(std::string txt){

    std::string lexema="";
    int estado= 0;

    //--componentes
    std::string user="";
    int idimg=0;
    listImg* auxList = new listImg();

    for(unsigned int i=0 ; i<txt.size();i++){

        char letra =txt[i];
        if(i==(44)){

            std::cout<<"letra "<<letra<<std::endl;
        }

        switch (estado) {
        case 0:
            if(esAlfaNumerico(letra)){
                lexema+=letra;
                estado = 1;
            }else {
                std::cout<<"se esperaba un dato alfanumerico "<<std::endl;
                estado  = 4;
            }

            break;
        case 1:
            if(esAlfaNumerico(letra)){
                lexema+=letra;
                estado = 1;
            }else if(letra==':'){

                user = lexema;
                lexema="";
                estado = 2;
            }else{
                std::cout<<"se esperaba un dato alfanumerico o ':' "<<std::endl;
                estado  = 4;
            }
            break;
        case 2:
            if(esNumero(letra)){
                lexema+=letra;
                estado=2;
            }else if(letra==','){

                idimg = std::atoi(lexema.c_str());
                auxList->addImgUsuario(idimg,listaImganes);
                lexema="";
                estado =3;
            }else if(letra==';'){
                arbolUsuarios->insertarAvl(auxList,user);
                lexema="";
                auxList = new listImg();
                estado =0;

            }else{
                std::cout<<"la entrada no fue la esperada"<<std::endl;
                estado  = 4;
            }
            break;
        case 3:
            if(esNumero(letra)){
                lexema+=letra;
                estado=2;
            }else{
                std::cout<<"la entrada no fue la esperada"<<std::endl;
                estado  = 4;
            }

            break;
        case 4:
            std::cout<<"error lexico en el archivo de Usuarios"<<std::endl;
            std::cout<<"modifique el archivo y vuelva a intentar"<<std::endl;
            return;
        }

    }

    usuariosCargados = true;

}

bool Gestion::caracterBasura(char caracter){

    if(!(caracter==' ' || caracter=='\n'||caracter=='\t'|| caracter=='\r'|| caracter=='\f'||caracter=='\377')){
        return true;

    }else {
        return false;
    }
}

//-----------------Verificar Cadenas
bool Gestion::esAlfaNumerico(char l){


    if((l>='a'&& l<='z')||(l>='A'&& l<='Z')||(esNumero(l))){

        return true;
    }else{
        return false;
    }

}
bool Gestion::esNumero(char l){

    if(l>='0' && l<='9'){
        return true;
    }else{
        return false;
    }

}

//-----------------Leer
void Gestion::leer(std::string dir, int tipo){

    std::string txt;
    std::ifstream f;
    f.open(dir,std::ios::in);

    if (f.is_open())
    {
        char caracter;
        while(!f.eof()){
            caracter = char(f.get());
            if(caracterBasura(caracter))
                txt += caracter;
        }
        f.close();
    }else  {
        std::cout<<"Error al leer archivo ingrese una direccion valida"<<std::endl;
        f.close();
        return;
    }

    switch (tipo) {
    case CAPAS:
        crearCapas(txt);
        if(capasCargadas)
            std::cout<<"se ingreso correctamente el archivo Capas al sistema"<<std::endl;

        break;
    case IMAGENES:
        crearImagenes(txt);

        if(imagenesCargadas)
            std::cout<<"se ingreso correctamente el archivo Imagenes al sistema"<<std::endl;
        break;
    case USUARIOS:
        crearUsuarios(txt);

        if(usuariosCargados)
            std::cout<<"se ingreso correctamente el archivo Usuarios al sistema"<<std::endl;
        break;
    }

}


//************************************************************
//*****************************menu***************************
//************************************************************
void Gestion::init(){

    int choice =0;
    do
    {
         listaImganes->imprimir();

        std::cout << std::endl
                  << "**********************************\n"
                  << " 1 - Carga Masiva.\n"
                  << " 2 - Generacion de Imagenes.\n"
                  << " 3 - ABC.\n"
                  << " 4 - Estado de la memoria.\n"
                  << " 5 - Otros Reportes.\n"
                  << " 6 - Exit.\n"
                  << " elige una opcion y presiona enter: \n"
                  << "**********************************\n";
        std::cin >> entrada;

        choice = validarEntrada(entrada);
        limpiar();

        switch (choice)
        {
        case 1:
            cargaMasiva();
            break;
        case 2:
            generacionImagenes();
            break;
        case 3:
            ABC();
            break;
        case 4:
            listaImganes->imprimir();
            estadoMemoria();
            break;
        case 5:
            otrosReportes();
            break;
        case 6:
            std::cout << "Fin del Programa.\n";
            break;
        default:
            std::cout << "opcion No valida. \n"
                      << "Vuelva a elegir una opcion.\n";
            break;
        }

    }while (choice !=6);

}
void Gestion::cargaMasiva(){


    if(!capasCargadas || !imagenesCargadas || !usuariosCargados){

        while (!capasCargadas)
        {

            std::cout<<"\nPresione cualquier tecla y Enter para continuar..."<<std::endl;
            std::cin >> entrada;

            limpiar();
            std::cout << std::endl
                      << "**********************************\n"
                      << " - Ingrese la ruta de del archivo \n"
                      << " -          de Capas              \n"
                      << "**********************************\n";
            std::cin >> entrada;

            //leer(entrada,CAPAS);
            leer("/home/jonathan/Escritorio/proyecto1/entrada/alex/MarioBros2.txt",CAPAS);
        }


        while (!imagenesCargadas)
        {

            std::cout<<"\nPresione cualquier tecla y Enter para continuar..."<<std::endl;
            std::cin >> entrada;

            limpiar();
            std::cout << std::endl
                      << "**********************************\n"
                      << " - Ingrese la ruta de del archivo \n"
                      << " -          de Imagenes           \n"
                      << "**********************************\n";
            std::cin >> entrada;

            //leer(entrada,IMAGENES);
            leer("/home/jonathan/Escritorio/proyecto1/entrada/alex/ListaIMG.txt",IMAGENES);

            listaImganes->imprimir();
        }

        listaImganes->imprimir();


        while (!usuariosCargados)
        {

            std::cout<<"\nPresione cualquier tecla y Enter para continuar..."<<std::endl;
            std::cin >> entrada;

            limpiar();
            std::cout << std::endl
                      << "**********************************\n"
                      << " - Ingrese la ruta de del archivo \n"
                      << " -          de Usuarios           \n"
                      << "**********************************\n";
            std::cin >> entrada;

            //leer(entrada,USUARIOS);
            leer("/home/jonathan/Escritorio/proyecto1/entrada/alex/ListaUSR.txt",USUARIOS);
             listaImganes->imprimir();

        }


    }else{
        std::cout<<"Ya se ah hecho la carga masiva respectiva"<<std::endl;
        std::cout<<"para cargar otros archivos reinice el programa"<<std::endl;

    }



}
void Gestion::generacionImagenes(){

    int choice =0;
    do
    {

        std::cout << std::endl
                  << "**********************************\n"
                  << " 1 - Por recorrido Limitado.\n"
                  << " 2 - Por Lista de imagenes.\n"
                  << " 3 - Por Capa.\n"
                  << " 4 - Por Usuario.\n"
                  << " 5 - regresar.\n"
                  << " elige una opcion y presiona enter: \n"
                  << "**********************************\n";
        std::cin >> entrada;

        choice = validarEntrada(entrada);
        limpiar();

        switch (choice)
        {
        case 1:
            recorridoLimitado();
            break;
        case 2:
            listadeImagenes();
            break;
        case 3:
            imagenPorCapa();
            break;
        case 4:
            imagenPorUsuario();
            break;
        case 5:
            //   std::cout << "Fin del Programa.\n";
            break;
        default:
            std::cout << "opcion No valida. \n"
                      << "Vuelva a elegir una opcion.\n";
            break;
        }

    }while (choice !=5);


}
void Gestion::ABC(){
    int choice =0;
    do
    {

        std::cout << std::endl
                  << "**********************************\n"
                  << " 1 - Usuarios.\n"
                  << " 2 - Imagenes.\n"
                  << " 3 - regresar.\n"
                  << " elige una opcion y presiona enter: \n"
                  << "**********************************\n";
        std::cin >> entrada;

        choice = validarEntrada(entrada);
        limpiar();

        switch (choice)
        {
        case 1:
            Usuarios();
            break;
        case 2:
            Imagenes();
            break;
        case 3:
            //std::cout << "Fin del Programa.\n";
            break;
        default:
            std::cout << "opcion No valida. \n"
                      << "Vuelva a elegir una opcion.\n";
            break;
        }

    }while (choice !=3);
}
void Gestion::estadoMemoria(){
    int choice =0;
    do
    {

        std::cout << std::endl
                  << "**********************************\n"
                  << " 1 - Ver Lista de Imagenes.\n"
                  << " 2 - Ver Arbol de Capas.\n"
                  << " 3 - Ver Arbol de Capas Espejo.\n"
                  << " 4 - Ver Capa.\n"
                  << " 5 - Ver Imagen y arbol de Capas.\n"
                  << " 6 - Ver Arbol de Usuarios.\n"
                  << " 7 - regresar.\n"
                  << " elige una opcion y presiona enter: \n"
                  << "**********************************\n";
        std::cin >> entrada;

        choice = validarEntrada(entrada);
        limpiar();

        switch (choice)
        {
        case 1:
            listaImganes->imprimir();
            verLIstaImagenes();
            break;
        case 2:
            verArbolCapas();
            break;
        case 3:
            verArbolCapasEspejo();
            break;
        case 4:
            verCapa();
            break;
        case 5:
            verImagenyArbolCapas();
            break;
        case 6:
            verArboldeUsuarios();
            break;
        case 7:
            //std::cout << "Fin del Programa.\n";
            break;
        default:
            std::cout << "opcion No valida. \n"
                      << "Vuelva a elegir una opcion.\n";
            break;
        }

    }while (choice !=7);
}
void Gestion::otrosReportes(){
    int choice =0;
    do
    {

        std::cout << std::endl
                  << "**********************************\n"
                  << " 1 - Top  5 Imagenes Con Mas Numero de Hojas.\n"
                  << " 2 - Todas Las Capas que Son Hojas.\n"
                  << " 3 - Profunidad de Arbol de Capas.\n"
                  << " 4 - Mostrar Capas en Postorden.\n"
                  << " 5 - ListarCapas.\n"
                  << " 6 - Top 5 de usuarios con mas imagenes.\n"
                  << " 7 - Arbol espejo de usuarios.\n"
                  << " 8 - Listar Usuarios.\n"
                  << " 9 - regresar.\n"
                  << " elige una opcion y presiona enter: \n"
                  << "**********************************\n";
        std::cin >> entrada;

        choice = validarEntrada(entrada);
        limpiar();

        switch (choice)
        {
        case 1:
            top5imagenes();
            break;
        case 2:
            todasLasCapasHojas();
            break;
        case 3:
            profundidadArbolCapas();
            break;
        case 4:
            mostrarCapasPostorden();
            break;
        case 5:
            listarCapas();
            break;
        case 6:
            top5usuarios();
            break;
        case 7:
            arbolEspejoUsuarios();
            break;
        case 8:
            ListarUsuariosEnRecorrido();
            break;
        case 9:
            //std::cout << "Fin del Programa.\n";
            break;
        default:
            std::cout << "opcion No valida. \n"
                      << "Vuelva a elegir una opcion.\n";
            break;
        }

    }while (choice !=7);
}
//************************************************************
//*************************fin menu***************************
//************************************************************


//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//------------------------------------3.1----------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------

void Gestion::recorridoLimitado(){

}
void Gestion::listadeImagenes(){

    int choice =0;
    do
    {
        std::cout << std::endl
                  << "****************************************\n"
                  << " - Ingresar Id de la imagen a graficar. \n"
                  << "****************************************\n";
        std::cin >> entrada;

        choice = validarEntrada(entrada);
        limpiar();

        img* aux=listaImganes->getImg(choice);

        if(aux){
            matriz* auxMatriz = generarImagen(aux);

            if(auxMatriz){
                auxMatriz->graficarCapaAplicacion();
            }

        }

    }while (choice == -1);

}

void Gestion::imagenPorCapa(){

    int choice =0;
    do
    {
        std::cout << std::endl
                  << "**********************************\n"
                  << " - Ingresar Id de capa a gaficar.\n"
                  << "**********************************\n";
        std::cin >> entrada;

        choice = validarEntrada(entrada);
        limpiar();

        NodoBst* aux = arbolCapas->buscar(choice);
        if(aux){
            aux->capa->graficarCapaAplicacion();
        }
    }while (choice == -1);
}



void Gestion::imagenPorUsuario(){}

//--3.2
void Gestion::Usuarios(){}
void Gestion::Imagenes(){}

//--3.3
void Gestion::verLIstaImagenes(){
//    listaImganes->imprimir();
  // listaImganes->graficar();
   listaImganes->imprimir();
}
void Gestion::verArbolCapas(){
    arbolCapas->graficar();
}
void Gestion::verArbolCapasEspejo(){}
void Gestion::verCapa(){}
void Gestion::verImagenyArbolCapas(){}
void Gestion::verArboldeUsuarios(){
    arbolUsuarios->graficar();
}

//--3.4
void Gestion::top5imagenes(){}
void Gestion::todasLasCapasHojas(){}
void Gestion::profundidadArbolCapas(){}
void Gestion::mostrarCapasPostorden(){}
void Gestion::listarCapas(){}
void Gestion::top5usuarios(){}
void Gestion::arbolEspejoUsuarios(){}
void Gestion::ListarUsuariosEnRecorrido(){}

//----------------imagenes
matriz* Gestion::generarImagen(img* imagen){

    matriz* result = new matriz();
    int fila =0;
    int col = 0;
    std::string color ="";

    capa* capaActual =imagen->getListCapa()->getFirst();

    while (capaActual) {

        NodoCabeceraFila* actualFila =capaActual->getCapa()->capa->filaC->first;

        while (actualFila) {

            NodoOrtogonal* actualCol = actualFila->listHorizontal->first;

            while (actualCol) {

                fila =actualCol->getFila();
                col = actualCol->getCol();
                color = actualCol->getColor();
                result->add(fila,col,color);

                actualCol = actualCol->getRight();
            }

            actualFila = actualFila->getDown();
        }


        capaActual = capaActual->getSig();
    }





    return  result;
}














