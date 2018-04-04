#include <iostream>

using namespace std;

#include <fstream>
#include "string.h"

#include "class.h"
#include "token.h"

ClTxt::ClTxt(){   // Klassenkonstruktor der jedes Mal aufgerufen wird, wenn ein Objekt vom Typ ClTxt erstellt wird und kein Parameter übergeben wird

    naechstes=NULL;
}


ClTxt::ClTxt(char *string){ // Klassenkonstruktor der jedes Mal aufgerufen wird, wenn ein Objekt vom Typ ClTxt erstellt wird und ein Parameter vom typ char * übergeben wird

    strcpy(id,string);

    naechstes=NULL;
}

ClTxt *verarbeiteTxt(ifstream& datei){  //Funktion, die eine Eingabedatei vom Typ "ifstream" als Parameter übergibt und ein Objekt vom Typ ClTxt als Rückgabewert erhält


    char zeichen;
    char puffer[100];
    int zaehler;
    enum zustandTxt zustand;
    ClTxt *jetzt=NULL, *hauptelement=NULL, *neu;

   // Die Funktion "ClTxt::ClTxt *verarbeite Txt(ifstream &datei)" füllt die Variablen der ClTxt Objekte mit Inhalt und ist den "verarbeite" Funktionen aus der Vorlesung sehr ähnlich.
   // Default wird der "puffer" mit Inhalt gefüllt und abhängig davon in welchem Zustand es sich befindet, wenn die Schleife auf ein Leerzeichen trifft, wird eine andere Variable des Objekts mit dem Inhalt aus "puffer" gefüllt.


    for (datei.get(zeichen),zustand = erwarteId, zaehler=0;!datei.eof();datei.get(zeichen)){    // for-Schleife, die Variablen eines Txt-Objekts mit Inhalt füllt, beendet wird diese wenn das Ende der Eingabedatei erreicht wurde und nach jedem Durchlauf wird das nächste Zeichen "geholt"

        switch(zeichen){

        case ' ':

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
    strcpy(ort,string);                     // kopiert den Inhalt aus string in die variable ort eines ClTxt Objekts
}

void ClTxt::setMenge(char *string){
    strcpy(menge,string);                    // kopiert den Inhalt aus string in die variable menge eines ClTxt Objekts
}


void ClTxt::druckeElement()
{

cout << "Von dem Produkt mit der ID " << id << " sind im " << ort << " " << menge<< " Stück vorhanden "<< endl;
}



