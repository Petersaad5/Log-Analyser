/*************************************************************************
                           LogFile  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <LogFile> (fichier LogFile.h) ----------------
#if ! defined ( LOGFILE_H )
#define LOGFILE_H

//--------------------------------------------------- Interfaces utilisées
using namespace std;
#include "Log.h"
#include <fstream>
#include <string>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <LogFile>
// Cette classe permet de représenter un fichier de log
// Elle permet de récupérer les logs un par un
//
//------------------------------------------------------------------------

class LogFile
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    ifstream & getStream();
    // Getter de l'attribut stream

    bool getLog(Log &);
    // Mode d'emploi :
    // Renvoie true si un log a été récupéré, false sinon
    // Contrat :
    // Une référence vers un objet Log doit être passée en paramètre
    // La méthode va mettre le résultat du parsing dans cet objet

    string getFileName() const;
    // Getter de l'attribut filename


//------------------------------------------------- Surcharge d'opérateurs
operator bool ();
// Mode d'emploi :
// Renvoie true si le fichier est ouvert, false sinon

//-------------------------------------------- Constructeurs - destructeur
    LogFile (string);
    // Mode d'emploi :
    // Constructeur de la classe LogFile
    // Contrat :
    // Le paramètre doit être le chemin vers un fichier de log existant

    virtual ~LogFile ( );
    // Mode d'emploi :
    // Destrcuteur de la classe LogFile

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
ifstream stream;
string filename;
};

//-------------------------------- Autres définitions dépendantes de <LogFile>

#endif // LogFile_H

