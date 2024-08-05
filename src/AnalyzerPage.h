/*************************************************************************
                           AnalyzerPage  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <AnalyzerPage> (fichier AnalyzerPage.h) ----------------
#if ! defined ( ANALYZERPAGE_H )
#define ANALYZERPAGE_H

//--------------------------------------------------- Interfaces utilisées
using namespace std;
#include <string>
#include <unordered_map>

class Analyzer;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <AnalyzerPage>
// Cette classe permet de représenter une page web ou une ressource
// Elle permet de compter le nombre de hits sur cette page et de compter
// le nombre de hits provenant de chaque referer différent
//------------------------------------------------------------------------

class AnalyzerPage
{
    friend class Analyzer; // Analyzer est une classe amie de AnalyzerPage
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    void AddHit (const string & referer );
    // Mode d'emploi :
    // Ajoute un hit à la page
    // Le paramètre referer est l'adresse de la page qui a fait la requête
    // Son compteur total et celui de son referer sont incrémentés

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    AnalyzerPage ( );
    // Mode d'emploi :
    // Constructeur de la classe AnalyzerPage

    virtual ~AnalyzerPage ( );
    // Mode d'emploi :
    // Destructeur de la classe AnalyzerPage

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    unsigned int numberbHits;

    // unordered_map contenant le nombre de hits par referer
    // Clé : adresse du referer (string), Valeur : nombre de hits (unsigned int)
    unordered_map<string, unsigned int> nbHitByReferer; 

};

//-------------------------------- Autres définitions dépendantes de <AnalyzerPage>

#endif // ANALYZERPAGE_H

