/*************************************************************************
                           Log  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Log> (fichier Log.h) ----------------
#if ! defined ( LOG_H )
#define LOG_H

//--------------------------------------------------- Interfaces utilisées
using namespace std;
#include <string>
#include <regex>
#include <unordered_map>
#include "DateTime.h"
//------------------------------------------------------------- Constantes

class LogFile;
//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Log>
// Cette classe permet de représenter un log de façon structurée
// Chaque attribut correspond à une partie du log
// Elle permet pricipalement de parser un log depuis une chaine de caractère
// Des expressions régulières sont utilisées pour cela
//------------------------------------------------------------------------

class Log
{
//----------------------------------------------------------------- PUBLIC
friend LogFile; // Pour que LogFile puisse accéder aux attributs privés

public:
static const regex regexPattern; // Expression régulière pour parser un log

//----------------------------------------------------- Méthodes publiques

string getIp() const;
// Getter de l'attribut ip

string getUserLogName() const;
// Getter de l'attribut userLogName

string getAuthenticatedUser() const;
// Getter de l'attribut authenticatedUser

DateTime getDateTime() const;
// Getter de l'attribut dateTime

string getMethod() const;
// Getter de l'attribut method

string getDestination() const;
// Getter de l'attribut destination

string getProtocol() const;
// Getter de l'attribut protocol

string getCode() const;
// Getter de l'attribut code

string getData() const;
// Getter de l'attribut data

string getReferer() const;
// Getter de l'attribut referer

string getWebBrowser() const;
// Getter de l'attribut webBrowser

//------------------------------------------------- Surcharge d'opérateurs

friend ostream & operator << (ostream &, const Log &);

//-------------------------------------------- Constructeurs - destructeur
    Log ();
    // Mode d'emploi :
    // Constructeur par défaut, tous les attributs sont initialisés à ""

    
    Log (string);
    // Mode d'emploi :
    // Constructeur à partir d'une chaine de caractère correspondant à un log
    // Les attributs sont initialisés à partir de la chaine de caractère
    // Utilise l'expression régulière regexPattern pour parser la chaine de caractère
    // Contrat :
    // La chaine de caractère doit correspondre à un log valide
    // La cohérence des données sera vérifiée et une erreur sera levée si les données ne sont pas valides

    virtual ~Log ( );
    // Mode d'emploi :
    // Destrcuteur par défaut
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
string ip;
string userLogName;
string authenticatedUser;
DateTime dateTime;
string method;
string destination;
string protocol;
string code;
string data;
string referer;
string webBrowser;
};

//-------------------------------- Autres définitions dépendantes de <Log>

#endif // Log_H

