using namespace std;
#include <iostream>
#include "Analyzer.h"
#include "LogFile.h"
#include <fstream>

int main() {
    
    LogFile file("./fichiers-fournis/anonyme.log");
    ofstream b("out.txt"); // 
    file.getStream().seekg(0, ios::end);
    int size = file.getStream().tellg();
    file.getStream().seekg(0, ios::beg);
    int lar = 50; 
    while (file) { 
        Log a;
        file.getLog(a);
        b << a << endl;
        int perc = (int) (file.getStream().tellg()*100/size);
        int nb = perc/100.0 *lar;
        cout << "\r" << "[" << string(nb, '#') << string(lar-nb, ' ') << "] " << perc << " %";
    }
    cout << "\r" << string(lar+8, ' ') << '\r';

    
    b.close();

    ifstream orignal("./fichiers-fournis/anonyme.log");
    ifstream copie("out.txt");

    while (orignal && copie) {
        if (orignal.get() != copie.get()) {
            throw(invalid_argument("Caractère différents"));
        }
    }
    cout << "Tous les caractères sont égaux" << endl;
    if (!orignal && !copie) {
        cout << "Fin simultanée" << endl;
    } else {
        cout << "Fin non simultanée" << endl;
    }

}