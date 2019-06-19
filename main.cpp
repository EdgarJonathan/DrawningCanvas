#include <iostream>
#include <matriz.h>
using namespace std;

int main()
{

    matriz* mimatriz = new matriz();

    mimatriz->add(0,4,"0,4");
    mimatriz->add(0,2,"0,2");
    mimatriz->add(1,3,"1,3");
    mimatriz->add(1,4,"1,4");
    mimatriz->add(2,5,"2,5");
    mimatriz->add(3,4,"3,4");
    mimatriz->add(3,6,"3,6");


    mimatriz->imprimirfIla();
    std::cout<<"\n\n--------------------------------------------------------------------------------\n\n"<<std::endl;
    mimatriz->imprimirCol();
    std::cout<<"\n"<<std::endl;

    std::cout<<mimatriz->txtCabeceraCol()<<std::endl;



    return 0;
}
