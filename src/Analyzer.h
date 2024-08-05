/*************************************************************************
                           Analyzer  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Analyzer> (fichier Analyzer.h) ----------------
#if ! defined ( ANALYZER_H )
#define ANALYZER_H

//--------------------------------------------------- Interfaces utilisées
#include "AnalyzerPage.h"

#include <iostream>
#include <vector>
#include <unordered_set>
// 
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Analyzer>
// Cette classe permet de représenter un analyseur de log
// Elle permet de compter le nombre de hits sur chaque page
// L'anayleur est dans notre cas spécialisé dans le comptahe des pages les plus consultées
// On peut afficher les ressources les plus consultées
// On peut afficher un graphique des consultations
//------------------------------------------------------------------------

class Analyzer
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    void MostConsulted ( unsigned int numberResults = 10, ostream & out = cout ) const;
    // Mode d'emploi :
    // Affiche les ressources les plus consultées
    // Le paramètre numberResults permet de définir le nombre de ressources à afficher
    // Le paramètre out permet de définir le flux de sortie

    void ConsultationGraph ( ostream & out = cout ) const;
    // Mode d'emploi :
    // Affiche un graphique des consultations au format GraphViz
    // Le paramètre out permet de définir le flux de sortie

//-------------------------------------------- Constructeurs - destructeur
    Analyzer ( const vector<string> & pathsToLogFiles, const unordered_set<string> & localDomains, const unordered_set<string> & extentionsToExclude = {}, int hour = -1, bool progressBar = false);
    // Mode d'emploi : Constructeur de la classe Analyzer
    // 
    // Contrat :
    // pathsToLogFiles doit être un vecteur de chemins vers des fichiers de log existants
    // localDomains doit être un ensemble de domaines locaux qui ne doivent pas être comptés dans l'URL
    // extentionsToExclude doit être un ensemble d'extensions de fichiers qui ne doivent pas être comptées dans l'analyse
    // hour doit être un entier entre 0 et 23, il permet de ne compter que les hits entre hour et hour+1
    // progressBar permet d'afficher une barre de progression lors de l'analyse

    virtual ~Analyzer ( );
    // Mode d'emploi : Destructeur de la classe Analyzer
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

    bool cropBeforeChar ( string & str, char c ) const;
    // Mode d'emploi :
    // Coupe la chaîne de caractères str avant le premier caractère c
    // Contrat : 
    // str doit être une chaîne de caractères non vide
    // c doit être un caractère

    string removeParametersFromUrl ( string url ) const;
    // Mode d'emploi :
    // Supprime les paramètres d'une URL
    // Tout ce qui se trouve après le premier ? (ou ; pour certains fichiers) est supprimé

//----------------------------------------------------- Attributs protégés

    // Map contenant les pages analysées
    // Clé : URL de la page, Valeur : objet AnalyzerPage correspondant (voir AnalyzerPage.h)
    unordered_map<string, AnalyzerPage> analyzerPages;

};

//-------------------------------- Autres définitions dépendantes de <Analyzer>

#endif // ANALYZER_H

