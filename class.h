

class ClTxt {

public:
    ClTxt();
    ClTxt(char *string);
    void setOrt(char *string);
    void setMenge(char *string);
    void setNext(ClTxt *neu){naechstes=neu;}
    ClTxt *getNext(void){return naechstes;}
    void druckeElement(int ebene, ClTxt *element);

    char *getTxtID(void){return id;}             //neu hinzugefügt
    char *getOrt(void) {return ort;}
    char *getMenge(void) {return menge;}

private:
    char id[10];
    char ort[30];
    char menge[15];
    ClTxt *naechstes;

};

enum zustandTxt {erwarteId, erwarteOrt, erwarteMenge};


