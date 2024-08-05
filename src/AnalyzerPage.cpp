/*************************************************************************
                           AnalyzerPage  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <AnalyzerPage> (fichier AnalyzerPage.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "AnalyzerPage.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void AnalyzerPage::AddHit (const string & referer )
// Algorithme :
// On incrémente le nombre de hits total et le nombre de hits provenant du referer passé en paramètre
{
    numberbHits++;
    nbHitByReferer[referer]++;
} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

AnalyzerPage::AnalyzerPage ( ): numberbHits(0) {
#ifdef MAP
    cout << "Appel au constructeur de <AnalyzerPage>" << endl;
#endif
} //----- Fin de AnalyzerPage


AnalyzerPage::~AnalyzerPage ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <AnalyzerPage>" << endl;
#endif
} //----- Fin de ~AnalyzerPage


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

