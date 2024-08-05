/*************************************************************************
                           DateTime  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <DateTime> (fichier DateTime.h) ----------------
#if ! defined ( DATETIME_H )
#define DATETIME_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <iostream>
#include <unordered_map>
//------------------------------------------------------------- Constantes
enum Month {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <DateTime>
//  Cette classe permet de représenter une date et une heure de façon structurée
//  Elle permet également de comparer deux dates entre elles
// 
//------------------------------------------------------------------------

class DateTime
{
//----------------------------------------------------------------- PUBLIC
public:
static const unordered_map <string, unsigned int> monthMap; // Map associant le nom du mois à son numéro
static const unordered_map <unsigned int, string> invertedMonthMap; // Map associant le numéro du mois à son nom
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    unsigned int getYear() const;
    // Getter de l'attribut year

    unsigned int getMonth() const;
    // Getter de l'attribut month

    unsigned int getDay() const;
    // Getter de l'attribut day

    unsigned int getHour() const;
    // Getter de l'attribut hour

    unsigned int getMinute() const;
    // Getter de l'attribut minute

    unsigned int getSecond() const;
    // Getter de l'attribut second

    static bool isLeap(unsigned int year); 
    // Renvoie true si l'année est bissextile, false sinon

//------------------------------------------------- Surcharge d'opérateurs

friend ostream & operator << (ostream &, const DateTime &);
friend bool operator == (const DateTime & date, const DateTime & other);
friend bool operator < (const DateTime & date, const DateTime & other);
friend bool operator > (const DateTime & date, const DateTime & other);
friend bool operator != (const DateTime & date, const DateTime & other);
friend bool operator <= (const DateTime & date, const DateTime & other);
friend bool operator >= (const DateTime & date, const DateTime & other);

//-------------------------------------------- Constructeurs - destructeur
    DateTime (unsigned int da = 1, unsigned int mo = JAN, unsigned int ye = 1970, unsigned int ho = 0, unsigned int mi = 0, unsigned int se = 0, string tz = "");
    // Mode d'emploi :
    // Constructeur par défaut
    //
    // Contrat :
    // Les vérifications seront effecutés et une erreur sera levée si les paramètres ne sont pas valides

    DateTime (unsigned int da, string mo, unsigned int ye, unsigned int ho = 0, unsigned int mi = 0, unsigned int se = 0, string tz = "");
    // Mode d'emploi : Constructeur par défaut à partir d'une string
    //
    // Contrat :
    // Les vérifications seront effecutés et une erreur sera levée si les paramètres ne sont pas valides

    virtual ~DateTime ( );
    // Mode d'emploi :
    // Destrcuteur par défaut

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
unsigned int day;
unsigned int month;
unsigned int year;
unsigned int hour;
unsigned int minute; 
unsigned int second;
string timezone;
};

//-------------------------------- Autres définitions dépendantes de <DateTime>

#endif // DateTime_H

