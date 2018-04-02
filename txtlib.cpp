#include <iostream>

using namespace std;

#include <fstream>
#include "string.h"

#include "class.h"
#include "token.h"

ClTxt::ClTxt(){

    naechstes=NULL;
}


ClTxt::ClTxt(char *string){

    strcpy(id,string);

    naechstes=NULL;
}

ClTxt *verarbeiteTxt(ifstream& datei){


    char zeichen;
    char letztes;
    char puffer[100];
    int zaehler;
    enum zustandTxt zustand;
    ClTxt *jetzt=NULL, *hauptelement=NULL, *neu;


    for (datei.get(zeichen),zustand = erwarteId, zaehler=0;!datei.eof();datei.get(zeichen)){

        switch(zeichen){

        case ' ':
            //if (letztes==' ') continue;
            puffer[zaehler]='\0';
            zaehler=0;
            if(zustand==erwarteId){
                neu = new ClTxt(puffer);
                if (jetzt!=NULL) jetzt->setNext(neu);
                else hauptelement=neu;
                jetzt=neu;
                zustand=erwarteOrt;
            }

            else{

                jetzt->setOrt(puffer);
                zustand=erwarteMenge;
            }



            break;


        case '\n':
            if(zustand==erwarteMenge){
            puffer[zaehler]='\0';
            zaehler=0;
            jetzt->setMenge(puffer);
            zustand=erwarteId;
            }

            break;


        default:

            puffer[zaehler]=zeichen;
            zaehler++;


            break;
        }

    }

   return hauptelement;
}

void ClTxt::setOrt(char *string){
    strcpy(ort,string);
}

void ClTxt::setMenge(char *string){
    strcpy(menge,string);
}


void ClTxt::druckeElement(int                           ebene,
ClTxt                          *element)
{

cout << "Von dem Produkt mit der ID " << id << " sind im " << ort << " " << menge<< " Stück vorhanden "<< endl;
}



