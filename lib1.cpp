#include <iostream>

using namespace std;

#include <fstream>
#include "string.h"
#include "class.h"



/*int Cltxt::verarbeite(ifstream &datei){
    char zeichen;

    Cltxt *ptr;

    char puffer[50];
    int zaehler;

    enum zustand{standard, erwarteID, erwarteOrt, erwarteMenge};
         zustand zustand=erwarteID;

         if (id!=NULL)
            {
            delete id;
            id=NULL;
            }
         if (ort!=NULL)
            {
            delete ort;
            ort=NULL;
            }
         if (menge=NULL)
            {
            delete menge;
            menge=NULL;
            }
         for(datei.get(zeichen);!datei.eof();datei.get(zeichen)){

             switch(zeichen){

                 case ' ' :
                 if(zustand==erwarteID){
                     puffer[zaehler]='\0';
                     ptr=new Cltxt;
                     strcpy(ptr->id, puffer);
                     cout << ptr->id;
                     zustand=erwarteOrt;
                     zaehler=0;
                     }

                 if(zustand==erwarteOrt){
                     puffer[zaehler]='\0';
                     ptr=new Cltxt;
                     strcpy(ptr->ort, puffer);
                     cout << ptr->ort;
                     zustand=erwarteMenge;
                     zaehler=0;

                 }


                 if(zustand==erwarteMenge){
                     puffer[zaehler]='\0';
                     ptr=new Cltxt;
                     strcpy(ptr->menge, puffer);
                     cout << ptr->menge;
                     zustand=erwarteID;
                     zaehler=0;
                 }


                 break;



             case '\n':

                 zustand=erwarteID;

                 break;

             default:
                 puffer[zaehler]=zeichen;
                 zaehler++;

                 break;

             }



         }

}
*/
