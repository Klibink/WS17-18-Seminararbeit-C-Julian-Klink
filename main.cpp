#include <iostream>

using namespace std;

#include <fstream>
#include "string.h"

#include "class.h"
#include "token.h"


class ClAusgabe{
  public:
    int laden();
    int druckeNeueDatei(ClToken *token, ClTxt *txtElement);
    ClToken *Atoken;
    ClTxt *Atxt;

};


ClTxt *verarbeiteTxt(ifstream& datei);

int menu();


int main()
{

    cout << "---System geladen---" << endl;
    cout << "Hallo! Drücken Sie Enter um fortzufahren" << endl;
    cin.get();


    for(;;){
    if(menu()==0) break;
    }
    return 0;
}

int menu() {

    char userEingabe;
    char dateiname[100];
    ifstream eingabe;
    ClToken *token;


    cout << "Was moechten Sie tun?" << endl;
    cout << "(1) Parse DTD" <<endl;
    cout << "(2) Parse TXT" <<endl;
    cout << "(3) Parse XML" << endl;
    cout << "(4) Konvertiere Txt und Xml" << endl;
    cout << "(5) help" << endl;
    cout << "(6) Beenden" <<endl;
    cin >> userEingabe;


    switch(userEingabe){


    case '1':{

        char kategorie[80];
        char suchObjekt[80];

        cout << "XML-Dateiname:" <<endl;
        cin>>dateiname;
        eingabe.open(dateiname);


        token=new ClToken;

        if (token->getToken(eingabe)!=0)
        {

        ClToken *aktuelleSuche= new ClToken;

        cout <<"Geben Sie eine Kategorie ein:" <<endl;
        cin >>kategorie;
        cin >>suchObjekt;

      /*  for(aktuelleSuche=token->child()->child();aktuelleSuche!=NULL;aktuelleSuche->sibling())
        {
cout <<aktuelleSuche->name();

            if(!strcmp(kategorie,aktuelleSuche->name()))
            {




                if(!strcmp(suchObjekt,aktuelleSuche->inhalt()))
                {

                        cout <<aktuelleSuche->name() << aktuelleSuche->inhalt() <<endl;


                }
            }

        }*/

            for(aktuelleSuche=token->child()->child();aktuelleSuche->sibling()!=NULL;aktuelleSuche->sibling())
                {
                if(!strcmp(kategorie,aktuelleSuche->name()))
                    {
                        cout << aktuelleSuche->name();


                    }

                }

        }





        break;
}
    case '2':{
        char dateiname[100];
        ifstream eingabe;
        ClTxt *jetzt=NULL, *txttoken;

        cout << "Txt-Dateiname: " <<endl;
        cin >>dateiname;
        eingabe.open(dateiname);

        txttoken=verarbeiteTxt(eingabe);
        for (jetzt=txttoken;jetzt!=NULL;jetzt=jetzt->getNext())
            jetzt->druckeElement(0,txttoken);
        eingabe.close();

        cout << "Txt erfolgreich geladen" <<endl;
        cout << " " << endl;

        return 1;


        break;
}
    case '3':{

        cout << "XML-Dateiname:" <<endl;
        cin>>dateiname;
        eingabe.open(dateiname);


        token=new ClToken;

        if (token->getToken(eingabe)!=0) token->druckeToken(1);
        eingabe.close();

        cout << "XML erfolgreich geladen" <<endl;
        cout << " " << endl;

        return 1;

        break;
}
    case '4':{

        ClAusgabe *ausgabe=new ClAusgabe;
        ausgabe->laden();

        return 1;


        break;
}
    case '5':

        cout <<"Folgende Operationen stehen zur Verfügung:"<<endl;
        cout <<"Das Parsen einer .txt-Datei, das Parsen einer XML-Datei und das Ausgeben beider Formate in eine gemeinsame Instanz" <<endl;
        cout <<"Drücken Sie dafür die in Klammern() angegebenen Ziffern um die Aktionen auszuführen. Nach Ablauf kehren Sie in das Menü zurück." <<endl;
        cout <<" " <<endl;

        return 1;

        break;

    case '6':

        return 0;

        break;

    default:
        cout << "Dieser Befehl existiert nicht. Kehre ins Menü zurück" <<endl;

        return 1;

        break;

    }

    return 0;
}



ClAusgabe::laden(){

    char dateiname[100];
    ifstream eingabe;
    ClToken *token;
    ClTxt *jetzt=NULL, *txttoken;

    cout << "Txt-Dateiname: " <<endl;
    cin >>dateiname;
    eingabe.open(dateiname);

    txttoken=verarbeiteTxt(eingabe);
    for (jetzt=txttoken;jetzt!=NULL;jetzt=jetzt->getNext())
        jetzt->druckeElement(0,txttoken);
    eingabe.close();

    cout << "Txt erfolgreich geladen" <<endl;
    cout << " " << endl;
    cout << "XML-Dateiname:" <<endl;
    cin>>dateiname;
    eingabe.open(dateiname);


    token=new ClToken;

    if (token->getToken(eingabe)!=0) token->druckeToken(1);
    eingabe.close();

    cout << "XML erfolgreich geladen" <<endl;
    cout << " " << endl;


    druckeNeueDatei(token,txttoken);







    return 1;
}


ClAusgabe::druckeNeueDatei(ClToken *token, ClTxt *txtElement){
    //TokenObjekt=token;
   // TxtObjekt=txtElement;
    char dateiname[50];

    cout << "Geben Sie den Namen für die neue XML-Datei ein:" <<endl;
    cin >>dateiname;

    ofstream ausgabeDatei(dateiname);

    ausgabeDatei <<"<" <<token->name() <<">" << endl;
    ausgabeDatei <<" "<<"<" << token->child()->name() <<" "<< token->child()->att.zeigeAttName(0)<< "=" << token->child()->att.zeigeAttWert(0) <<">" << endl; //Beginn erstes Objekt

    ClToken *now=new ClToken;

    for(now=token->child()->child();now->sibling()!=NULL;now=now->sibling()){
    //if(token->tokenChild->tokenChild!=NULL){
        ausgabeDatei << " "<< " <" << now->name() << ">" << now->inhalt() << "</" << now->name() << ">" <<endl;
   // }
         }

    ausgabeDatei << "   <stock> " <<endl;

    ClTxt *aktuelles = new ClTxt;

    for(aktuelles=txtElement;aktuelles->getNext()!=NULL;aktuelles=aktuelles->getNext()){
        if(!strcmp(aktuelles->getTxtID(),token->child()->att.zeigeAttWert(0))){
            ausgabeDatei << "    " << "<Anzahl Ware vorrätig im " << aktuelles->getOrt() << ">" << aktuelles->getMenge() <<"</Anzahl Ware vorrätig>" << endl;
        }
    }


    ausgabeDatei << "   </stock> " <<endl;


    ausgabeDatei <<" "<<"</" << token->child()->name() <<">" << endl; //Ende erstes Objekt

    ClToken *jetziges= new ClToken;
    for(jetziges=token->child()->sibling();jetziges->sibling()!=NULL;jetziges=jetziges->sibling()){

    ausgabeDatei <<" "<<"<" << jetziges->name() <<" "<< jetziges->att.zeigeAttName(0)<< "=" << jetziges->att.zeigeAttWert(0) <<">" << endl;

    for(now=jetziges->child();now->sibling()!=NULL;now=now->sibling()){

        ausgabeDatei << " "<< " <" << now->name() << ">" << now->inhalt() << "</" << now->name() << ">" <<endl;

         }

    ausgabeDatei << "   <stock> " <<endl;

    for(aktuelles=txtElement;aktuelles->getNext()!=NULL;aktuelles=aktuelles->getNext()){
        if(!strcmp(aktuelles->getTxtID(),jetziges->att.zeigeAttWert(0))){
            ausgabeDatei << "    " << "<Anzahl Ware vorrätig im " << aktuelles->getOrt() << ">" << aktuelles->getMenge() <<"</Anzahl Ware vorrätig>" << endl;
        }
    }


    ausgabeDatei << "   </stock> " <<endl;

    ausgabeDatei <<" "<<"</" << jetziges->name() <<">" << endl;
    }
    ausgabeDatei <<"</" <<token->name() <<">" << endl;

    return 1;
}

