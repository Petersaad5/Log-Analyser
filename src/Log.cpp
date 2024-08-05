/*************************************************************************
                           Log  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Log> (fichier Log.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Log.h"

//------------------------------------------------------------- Constantes
const regex Log::regexPattern("^(\\S+)\\s+(\\S+)\\s+(\\S+)\\s+\\[([\\d]+)\\/([^\\]\\/]+)\\/([\\d]+):([\\d]+):([[\\d]+):([\\d]+)\\s+([^\\]]+)\\]\\s+\"(\\S+)\\s+(.+)\\s+(\\S+)\"\\s+(\\S+)\\s+(\\S+)\\s+\"([^\"]+)\"\\s+\"([^\"]+)\"$");
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

string Log::getIp() const {
    return ip;
} // Fin de getIp

string Log::getUserLogName() const {
    return userLogName;
} // Fin de getUserLogName

string Log::getAuthenticatedUser() const {
    return authenticatedUser;
} // Fin de getAuthenticatedUser

DateTime Log::getDateTime() const {
    return dateTime;
} // Fin de getDateTime

string Log::getMethod() const {
    return method;
} // Fin de getMethod

string Log::getDestination() const {
    return destination;
} // Fin de getDestination

string Log::getProtocol() const {
    return protocol;
} // Fin de getProtocol

string Log::getCode() const {
    return code;
} // Fin de getCode

string Log::getData() const {
    return data;
} // Fin de getData

string Log::getReferer() const {
    return referer;
} // Fin de getReferer

string Log::getWebBrowser() const {
    return webBrowser;
} // Fin de getWebBrowser

//------------------------------------------------- Surcharge d'opérateurs

ostream & operator << (ostream & out, const Log & log) {
    // Affichage au format "ip userLogName authenticatedUser [dateTime] "method destination protocol" code data "referer" "webBrowser""
    // Permet de reconstruire un log à partir de son affichage
    out << log.ip << " " << log.userLogName << " " << log.authenticatedUser << " [" << log.dateTime << "] \"" << log.method << " " << log.destination << " " << log.protocol << "\" " << log.code << " " << log.data << " \"" << log.referer << "\" \"" << log.webBrowser << "\"";
    return out;
}
//-------------------------------------------- Constructeurs - destructeur

Log::Log() : ip(string()), userLogName(string()), authenticatedUser(string()), dateTime(DateTime()), method(string()), destination(string()), protocol(string()), code(string()), data(string()), referer(string()), webBrowser(string())
{
#ifdef MAP
cout << "Appel au constructeur de <Log>" << endl;
#endif
} //----- Fin de Log

Log::Log(string stream)
// Algorithme :
// Utilise l'expression régulière regexPattern pour parser la chaine de caractère
{
#ifdef MAP
    cout << "Appel au constructeur de <Log>" << endl;
#endif
    smatch match;
    if (regex_match(stream, match, regexPattern)) // Si la chaine de caractère correspond à l'expression régulière
    {
        // On affecte les attributs à partir des groupes de l'expression régulière
        ip = match[1];
        userLogName = match[2];
        authenticatedUser = match[3];
        dateTime = DateTime(stoi(match[4]), match[5], stoi(match[6]), stoi(match[7]), stoi(match[8]), stoi(match[9]), match[10]);
        method = match[11];
        destination = match[12];
        protocol = match[13];
        code = match[14];
        data = match[15];
        referer = match[16];
        webBrowser = match[17];
    }
    else // Si la chaine de caractère ne correspond pas à l'expression régulière, on lève une erreur
    {
        throw invalid_argument("string doesn't match with Log regex");
    }
} //----- Fin de Log

Log::~Log()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Log>" << endl;
#endif
} //----- Fin de ~Log

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
