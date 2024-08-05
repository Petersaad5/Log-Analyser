/*************************************************************************
                           LogFile  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <LogFile> (fichier LogFile.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
using namespace std;
#include "LogFile.h"


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
ifstream & LogFile::getStream() {
    return stream;
} // Fin de getStream

bool LogFile::getLog(Log & log) {
    string line;
    bool ok = false;
    getline(stream ,line); // On récupère une ligne du fichier
    if (line.back() == '\r') { // On supprime le \r si il y en a un
        line.pop_back();
    }
    try { // On essaye de parser la ligne avec le constructeur de Log
        log = Log(line); // Si la ligne est valide, on met le résultat dans l'objet passé en paramètre
        ok = true;
    }
    catch (exception& e) { // Si la ligne n'est pas valide, on affiche un message d'erreur et on l'ignore
        cerr << "Warning : a line of " << filename << " is not valid" << endl;
        ok = false;
    }
    return ok; // On renvoie true si la ligne a été parsée, false sinon
} // Fin de getLog

string LogFile::getFileName() const {
    return filename;
} // Fin de getFileName

//------------------------------------------------- Surcharge d'opérateurs
LogFile::operator bool() {
    return stream && stream.peek() != EOF;
} // Fin de operator bool
//-------------------------------------------- Constructeurs - destructeur


LogFile::LogFile (string file) : stream(ifstream(file)), filename(file)
// Algorithme :
// On créé un flux à partir du fichier passé en paramètre
{
#ifdef MAP
    cout << "Appel au constructeur de <LogFile>" << endl;
#endif
} //----- Fin de LogFile


LogFile::~LogFile ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <LogFile>" << endl;
#endif
} //----- Fin de ~LogFile


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

