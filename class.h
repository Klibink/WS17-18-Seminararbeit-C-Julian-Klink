

class ClTxt {

public:
    ClTxt();                                        // Konstruktor ohne Parameter
    ClTxt(char *string);                            // Konstruktor mit Parameter
    void setOrt(char *string);                      // Methode, die char ort mit Inhalt füllt
    void setMenge(char *string);                    // Methode, die char menge mit Inhalt füllt
    void setNext(ClTxt *neu){naechstes=neu;}        // Methode, die dem Pointer "naechstes" ein Objekt zum drauf zeigen zuweist
    ClTxt *getNext(void){return naechstes;}         // Methode, die einen Pointer auf ein ClTxt Objekt als Rückgabewert hat
    void druckeElement();                           // Methode, zum "Drucken" des Inhalts

    char *getTxtID(void){return id;}                // Methode, die char id returned
    char *getOrt(void) {return ort;}                // Methode, die char ort returned
    char *getMenge(void) {return menge;}            // Methode, die char menge returned

private:
    char id[10];
    char ort[30];
    char menge[15];
    ClTxt *naechstes;

};

enum zustandTxt {erwarteId, erwarteOrt, erwarteMenge};


