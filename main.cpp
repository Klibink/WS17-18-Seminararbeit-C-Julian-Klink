#include <iostream>

using namespace std;

#include <fstream>
#include "string.h"

#include "class.h"
#include "token.h"


class ClAusgabe{    // Die Klasse, die für das Erstellen der neuen xml-Datei zuständig ist
  public:
    int laden();    // Methode, die Inhalte aus XML und Txt Datei liest
    int druckeNeueDatei(ClToken *token, ClTxt *txtElement); //Methode, die 2 Objekte als Parameter übergibt und damit die neue Datei erstellt


};


ClTxt *verarbeiteTxt(ifstream& datei); // Pre-Deklaration einer Funktion, die eine Eingabedatei vom Typ "ifstream" als Parameter übergibt und ein Objekt vom Typ ClTxt als Rückgabewert erhält

int menu(); // Pre-Deklaration der Menü-Funktion


int main()                                                              //main Funktion
{

    cout << "---System geladen---" << endl;
    cout << "Hallo! Drücken Sie Enter um fortzufahren" << endl;         //Benutzer wird begrüßt
    cin.get();                                                          //Benutzer-Aktion wird erwartet


    for(;;){                                                            //Endlosschleife,
    if(menu()==0) break;                                                //die unterbrochen wird, wenn die Funktion "menu()" als Rückgabewert '0' erhält
    }
    return 0;
}

int menu() {

    char userEingabe;                                                   // char Variable erstellt
    char dateiname[100];                                                // char Array erstellt
    ifstream eingabe;                                                   // ifstream Objekt erstellt
    ClToken *token;                                                     // pointer vom Typ ClToken erstellt


    cout << "Was moechten Sie tun?" << endl;
    cout << "(1) Suche Kategorie" <<endl;
    cout << "(2) Parse TXT" <<endl;
    cout << "(3) Parse XML" << endl;
    cout << "(4) Konvertiere Txt und Xml" << endl;
    cout << "(5) help" << endl;
    cout << "(6) Beenden" <<endl;
    cin >> userEingabe;                                                 // Benutzer trifft Entscheidung


    switch(userEingabe){                                                // switch/case Verfahren, abhängig von der Entscheidung des Benutzers


    case '1':{                                                          // case '1' umfasst die Suchfunktion(Aufgabe 1.2)

        char kategorie[80];                                             // char Array erstellt
        char suchObjekt[80];                                            // char Array erstellt

        cout << "XML-Dateiname:" <<endl;
        cin>>dateiname;                                                 // Benutzer wird nach der zu Benutzenden xml-Datei gefragt
        eingabe.open(dateiname);


        token=new ClToken;                                              // Der pointer vom Typ ClToken wird als "new ClToken" deklariert

        if (token->getToken(eingabe)!=0)                                // ClToken Methode, deren Rückgabewert vom Typ Integer ist. Falls der Rückgabewert ungleich '0' ist, wird die if-Anweisung ausgeführt
        {

        ClToken *aktuelleSuche= new ClToken;                            // Erstelle einen pointer vom Typ ClToken und deklariere ihn als "new ClToken"
        ClToken *aktuellesProdukt = new ClToken;                        // Erstelle einen pointer vom Typ ClToken und deklariere ihn als "new ClToken"

        for(;;)                                                         // Endlosschleife
        {

        cout <<"Geben Sie eine Kategorie ein: (0 zum beenden)" <<endl;  // Benutzer wird gebeten eine Kategorie einzugeben
        cin >>kategorie;
        cout <<"Geben Sie das gesuchte Objekt ein: (0 zum beenden)" <<endl; // Benutzer wird gebeten ein Suchobjekt einzugeben
        cin >>suchObjekt;



        for(aktuellesProdukt=token->child();aktuellesProdukt!=NULL;aktuellesProdukt=aktuellesProdukt->sibling()) // Äußere for-Schleife, die durchläuft bis token->tokenchild keinen Sibling mehr hat(->sibling()!=NULL)
        {
            for(aktuelleSuche=aktuellesProdukt->child();aktuelleSuche!=NULL;aktuelleSuche=aktuelleSuche->sibling()) // Innere for-Schleife, die durchläuft bis token->tokenchild->tokenchild keinen Sibling mehr hat
            {
                if(!strcmp(kategorie,aktuelleSuche->name())) // Prüft, ob erste Benutzereingabe mit Namen des aktuellen Objekts übereinstimmt. Falls nicht ist der erste Durchlauf der inneren for-Schleife beendet
                {
                    if(!strcmp(suchObjekt,aktuelleSuche->inhalt())) // Prüft, ob zweite Benutzereingabe mit Inhalt des aktuellen Objekts übereinstimmt.
                    {

                            cout << aktuellesProdukt->name() <<" " << aktuellesProdukt->att.zeigeAttName(0)<< "=" << aktuellesProdukt->att.zeigeAttWert(0) <<" "<<aktuelleSuche->name() << " hat den Inhalt " << aktuelleSuche->inhalt() <<endl; //falls str1 und str2 von strcmp übereinstimmen wird der Name mit Id und der Inhalt des Tokens ausgegeben.

                    }
                    else cout <<"In " <<aktuellesProdukt->name() <<" " << aktuellesProdukt->att.zeigeAttName(0)<< "=" << aktuellesProdukt->att.zeigeAttWert(0) << " wurde nichts gefunden." <<endl;   //falls die Strings nicht übereinstimmen erscheint ein Hinweis, dass in Produkt xy nichts gefunden wurde
                }

            }

        }

        if(kategorie[0]=='0')break; // Endbedingung der Endlosschleife

        }




        }


        return 1;               // da '1' returned wird, wird Funktion menu() erneut aufgerufen


        break;
}
    case '2':{                      // case '2' parst die Txt-Datei und gibt das Ergebnis auf dem Bildschirm aus
        char dateiname[100];
        ifstream eingabe;
        ClTxt *jetzt=NULL, *txttoken;   // pointer vom Typ ClTxt erstellt

        cout << "Txt-Dateiname: " <<endl;
        cin >>dateiname;
        eingabe.open(dateiname);

        txttoken=verarbeiteTxt(eingabe);    // dem pointer vom Typ ClTxt wird der Rückgabewert der Methode "verarbeiteTxt" zugewiesen.
        for (jetzt=txttoken;jetzt!=NULL;jetzt=jetzt->getNext()) //for-Schleife: ClTxt pointer "jetzt" zeigt auf das gleiche Objekt wie "txttoken". Nach jedem Durchlauf wird die Methode "getNext" aufgerufen und die Schleife wird beendet, sobald "jetzt"!=NULL ist
            jetzt->druckeElement(); // ClTxt Methode wird aufgerufen. Diese Methode ist zuständig dafür, dass das Ergebnis auf dem Bildschirm erscheint
        eingabe.close();

        cout << "Txt erfolgreich geladen" <<endl;
        cout << " " << endl;

        return 1;               // da '1' returned wird, wird Funktion menu() erneut aufgerufen


        break;
}
    case '3':{                  // case '3' parst die XML-Datei und gibt das Ergebnis auf dem Bildschirm aus

        cout << "XML-Dateiname:" <<endl;
        cin>>dateiname;
        eingabe.open(dateiname);


        token=new ClToken;

        if (token->getToken(eingabe)!=0) token->druckeToken(1);
        eingabe.close();

        cout << "XML erfolgreich geladen" <<endl;
        cout << " " << endl;

        return 1;               // da '1' returned wird, wird Funktion menu() erneut aufgerufen

        break;
}
    case '4':{                  // case '4' umfasst Aufgabe 1.1

        ClAusgabe *ausgabe=new ClAusgabe; //Erstelle einen pointer vom Typ ClAusgabe und deklariere ihn als "new ClAusgabe"
        ausgabe->laden();                 // Methode der Klasse ClAusgabe wird aufgerufen

        return 1;               // da '1' returned wird, wird Funktion menu() erneut aufgerufen


        break;
}
    case '5':                   // case '5' beschreibt dem Benutzer was das Programm kann, wenn er Hilfe benötigt

        cout <<"Folgende Operationen stehen zur Verfügung:"<<endl;
        cout <<"Das Parsen einer .txt-Datei, das Parsen einer XML-Datei und das Ausgeben beider Formate in eine gemeinsame Instanz" <<endl;
        cout <<"Zusätzlich wird eine Suchfunktion geboten, mit der innerhalb einer XML-Datei Objekte gesucht werden können" <<endl;
        cout <<"Drücken Sie dafür die in Klammern() angegebenen Ziffern um die Aktionen auszuführen. Nach Ablauf kehren Sie in das Menü zurück." <<endl;
        cout <<" " <<endl;

        return 1;               // da '1' returned wird, wird Funktion menu() erneut aufgerufen

        break;

    case '6':                   // beendet das Programm

        return 0;               // da '0' returned wird ist die Endlosschleife aus der main Funktion beendet

        break;

    default:                    // wenn der Benutzer einen unbekannten Charakter eingibt wird default ausgeführt

        cout << "Dieser Befehl existiert nicht. Kehre ins Menü zurück" <<endl;

        return 1;           // da '1' returned wird, wird Funktion menu() erneut aufgerufen

        break;

    }

    return 0;
}



ClAusgabe::laden(){

    char dateiname[100];
    ifstream eingabe;
    ClToken *token;
    ClTxt *jetzt=NULL, *txttoken;           // pointer vom Typ ClTxt erstellt

    cout << "Txt-Dateiname: " <<endl;       // Benutzer wird nach Txt-Datei gefragt
    cin >>dateiname;
    eingabe.open(dateiname);                // Eingabe-Objekt wird "geöffnet"

    txttoken=verarbeiteTxt(eingabe);        // dem pointer vom Typ ClTxt wird der Rückgabewert der Methode "verarbeiteTxt" zugewiesen. Die Methode "verarbeiteTxt" füllt ein Objekt vom Typ ClTxt mit Inhalt
    for (jetzt=txttoken;jetzt!=NULL;jetzt=jetzt->getNext()) //for-Schleife: ClTxt pointer "jetzt" zeigt auf das gleiche Objekt wie "txttoken". Nach jedem Durchlauf wird die Methode "getNext" aufgerufen und die Schleife wird beendet, sobald "jetzt"==NULL ist
        jetzt->druckeElement();             // ClTxt Methode wird aufgerufen. Diese Methode ist zuständig dafür, dass das Ergebnis auf dem Bildschirm erscheint
    eingabe.close();                        // Eingabe-Objekt wird "geschlossen"

    cout << "Txt erfolgreich geladen" <<endl;
    cout << " " << endl;
    cout << "XML-Dateiname:" <<endl;        // Benutzer wird nach XML-Datei gefragt
    cin>>dateiname;
    eingabe.open(dateiname);


    token=new ClToken;

    if (token->getToken(eingabe)!=0) token->druckeToken(1);
    eingabe.close();

    cout << "XML erfolgreich geladen" <<endl;
    cout << " " << endl;


    druckeNeueDatei(token,txttoken);  // Methode der Klasse ClAusgabe wird aufgerufen und als Parameter wird ein Objekt vom Typ ClToken und ein Objekt vom Typ ClTxt übergeben







    return 1;
}


ClAusgabe::druckeNeueDatei(ClToken *token, ClTxt *txtElement){

    char dateiname[50];

    cout << "Geben Sie den Namen für die neue XML-Datei ein:" <<endl;
    cin >>dateiname;                                                            // Benutzer gibt Namen der neuen XML-Instanz ein

    ofstream ausgabeDatei(dateiname);                                           // ofstream Objekt wird deklariert

    ausgabeDatei << "<?xml version=""1.0"" encoding=""UTF-8""?>" <<endl;
    ausgabeDatei << "<!DOCTYPE "<<token->name() <<" SYSTEM ""daten.dtd"">"<<endl;


    //Beginn Ausgabe Wurzelobjekt
    ausgabeDatei <<"<" <<token->name() <<">" << endl;       //Name des Wurzelobjekts wird ausgegeben, da es auf jeden Fall vorhanden ist
    ausgabeDatei <<" "<<"<" << token->child()->name() <<" "<< token->child()->att.zeigeAttName(0)<< "=" << token->child()->att.zeigeAttWert(0) <<">" << endl; //Name des ersten Kindobjekts wird ausgegeben, da auch dies auf jeden Fall vorhanden ist

    ClToken *now=new ClToken;

    for(now=token->child()->child();now!=NULL;now=now->sibling()){ //for-Schleife, die das Kind vom Kind des Wurzelobjekts und deren Geschwister ausgibt

        ausgabeDatei << " "<< " <" << now->name() << ">" << now->inhalt() << "</" << now->name() << ">" <<endl;

         }

    ausgabeDatei << "  <stock> " <<endl;        //Beginn Zusammenführung XML und Txt

    ClTxt *aktuelles = new ClTxt;

    for(aktuelles=txtElement;aktuelles->getNext()!=NULL;aktuelles=aktuelles->getNext()){ // for-Schleife, die alle Txt-Objekte durchläuft, indem nach jedem Durchgang das "Nächste" returned wird

        if(!strcmp(aktuelles->getTxtID(),token->child()->att.zeigeAttWert(0))){          // strcmp vergleicht ID des Txt-Objekts mit dem Attributwert von token->tokenchild

            ausgabeDatei << "    " << "<Anzahl Ware vorrätig im " << aktuelles->getOrt() << ">" << aktuelles->getMenge() <<"</Anzahl Ware vorrätig>" << endl; // wenn die Strings übereinstimmen werden Variablen der ClTxt Objekte ausgegeben
        }
    }


    ausgabeDatei << "  </stock> " <<endl;       //Ende Zusammenführung XML und Txt


    ausgabeDatei <<" "<<"</" << token->child()->name() <<">" << endl;       // Wurzel-Tag wird geschlossen

    //Ende Wurzelobjekt

    ClToken *jetziges= new ClToken;
    for(jetziges=token->child()->sibling();jetziges!=NULL;jetziges=jetziges->sibling()){ //for-Schleife, die prüft, ob das Kindobjekt vom Wurzelobjekt ein Geschwisterobjekt. Sofern es eins hat wird dieses auch in gleicher Weise in die neue Xml-Instanz überführt. Schleife wird beendet, wenn das Geschwisterobjekt==NULL ist.(Ablauf der selbe wie bei der Ausgabe des Wurzelobjekts)

    ausgabeDatei <<" "<<"<" << jetziges->name() <<" "<< jetziges->att.zeigeAttName(0)<< "=" << jetziges->att.zeigeAttWert(0) <<">" << endl;

    for(now=jetziges->child();now->sibling()!=NULL;now=now->sibling()){

        ausgabeDatei << " "<< " <" << now->name() << ">" << now->inhalt() << "</" << now->name() << ">" <<endl;

         }

    ausgabeDatei << "  <stock> " <<endl;

    for(aktuelles=txtElement;aktuelles->getNext()!=NULL;aktuelles=aktuelles->getNext()){
        if(!strcmp(aktuelles->getTxtID(),jetziges->att.zeigeAttWert(0))){
            ausgabeDatei << "    " << "<Anzahl Ware vorrätig im " << aktuelles->getOrt() << ">" << aktuelles->getMenge() <<"</Anzahl Ware vorrätig>" << endl;
        }
    }


    ausgabeDatei << "  </stock> " <<endl;

    ausgabeDatei <<" "<<"</" << jetziges->name() <<">" << endl;
    }
    ausgabeDatei <<"</" <<token->name() <<">" << endl;

    return 1;
}

