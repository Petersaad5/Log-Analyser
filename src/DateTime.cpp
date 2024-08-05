/*************************************************************************
                           DateTime  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <DateTime> (fichier DateTime.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <iomanip>

//------------------------------------------------------ Include personnel
#include "DateTime.h"

//------------------------------------------------------------- Constantes
const unordered_map <string, unsigned int> DateTime::monthMap = {
        {"Jan", JAN},
        {"Feb", FEB},
        {"Mar", MAR},
        {"Apr", APR},
        {"May", MAY},
        {"Jun", JUN},
        {"Jul", JUL},
        {"Aug", AUG},
        {"Sep", SEP},
        {"Oct", OCT},
        {"Nov", NOV},
        {"Dec", DEC}
    };

const unordered_map <unsigned int, string> DateTime::invertedMonthMap = {
        {JAN, "Jan"},
        {FEB, "Feb"},
        {MAR, "Mar"},
        {APR, "Apr"},
        {MAY, "May"},
        {JUN, "Jun"},
        {JUL, "Jul"},
        {AUG, "Aug"},
        {SEP, "Sep"},
        {OCT, "Oct"},
        {NOV, "Nov"},
        {DEC, "Dec"}
    };
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

unsigned int DateTime::getYear() const {
    return year;
} // Fin de getYear

unsigned int DateTime::getMonth() const {
    return month;
} // Fin de getMonth

unsigned int DateTime::getDay() const {
    return day;
} // Fin de getDay

unsigned int DateTime::getHour() const {
    return hour;
} // Fin de getHour

unsigned int DateTime::getMinute() const {
    return minute;
} // Fin de getMinute

unsigned int DateTime::getSecond() const {
    return second;
} // Fin de getSecond

bool DateTime::isLeap(unsigned int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)); // hhttps://fr.wikipedia.org/wiki/Année_bissextile
} // Fin de isLeap

//------------------------------------------------- Surcharge d'opérateurs

ostream & operator << (ostream & out, const DateTime & date) {
    // Affichage de la date au format : 01/Jan/2017:00:00:00 +0100
    out << setw(2) << setfill('0') << date.day << "/" << DateTime::invertedMonthMap.find(date.month)->second << "/" << date.year << ":" << setw(2) << setfill('0') << date.hour << ":" << setw(2) << setfill('0') << date.minute << ":" << setw(2) << setfill('0') << date.second <<  " " << date.timezone;
    return out;
}

// Opérateurs de comparaison

bool operator < (const DateTime & date, const DateTime & other) {
    return (date.year < other.year) ||
           (date.year == other.year && date.month < other.month) ||
           (date.year == other.year && date.month == other.month && date.day < other.day) ||
           (date.year == other.year && date.month == other.month && date.day == other.day && date.hour < other.hour) ||
           (date.year == other.year && date.month == other.month && date.day == other.day && date.hour == other.hour && date.minute < other.minute) ||
           (date.year == other.year && date.month == other.month && date.day == other.day && date.hour == other.hour && date.minute == other.minute && date.second < other.second);
}
bool operator == (const DateTime & date, const DateTime & other) {
    return date.day == other.day && date.month == other.month && date.year == other.year && date.hour == other.hour && date.minute == other.minute && date.second == other.second;
}
bool operator > (const DateTime & date, const DateTime & other) {
    return !(date < other) && !(date == other);
}
bool operator != (const DateTime & date, const DateTime & other) {
    return !(date == other);
}
bool operator >= (const DateTime & date, const DateTime & other) {
    return date == other || date > other;
}
bool operator <= (const DateTime & date, const DateTime & other) {
    return date == other || date < other;
}

//-------------------------------------------- Constructeurs - destructeur

DateTime::DateTime (unsigned int da, unsigned int mo, unsigned int ye, unsigned int ho, unsigned int mi, unsigned int se, string tz) :
day(da), month(mo), year(ye), hour(ho), minute(mi), second(se), timezone(tz)
// Algorithme :
// Vérification de la validité des paramètres
{
#ifdef MAP
    cout << "Appel au constructeur de <DateTime>" << endl;
#endif
if (ho >= 24) { // L'heure doit être comprise entre 0 et 23
    throw invalid_argument("Hour must be include between 0 and 23");
}
if (mi >= 60) { // La minute doit être comprise entre 0 et 59
    throw invalid_argument("Minute must be include between 0 and 59");
}
if (se >= 60) { // La seconde doit être comprise entre 0 et 59
    throw invalid_argument("Second must be include between 0 and 59");
}
if (da == 0 || da > 31) { // Le jour doit être compris entre 1 et 31
    throw invalid_argument("Day cannot be 0 or superior to 31");
}
if (mo == 0 || mo > 12) { // Le mois doit être compris entre 1 et 12
    throw invalid_argument("Month must be include between 1 and 12");
}

bool leap = isLeap(ye); // Vérification si l'année est bissextile
if (mo == FEB) { // Si le mois est février, on vérifie si l'année est bissextile
    if (leap && da > 29) { // Si l'année est bissextile, le jour doit être compris entre 1 et 29
        throw invalid_argument("Day must be include between 1 and 29 for this month");
    } else if (!leap && da > 28) { // Sinon, le jour doit être compris entre 1 et 28
        throw invalid_argument("Day must be include between 1 and 28 for this month");
    }
} else if ((mo == APR || mo == JUN || mo == SEP || mo == NOV) && da > 30) { // Si le mois est avril, juin, septembre ou novembre, le jour doit être compris entre 1 et 30
    throw invalid_argument("Day must be include between 1 and 30 for this month");
}
} //----- Fin de DateTime

DateTime::DateTime (unsigned int da, string mo, unsigned int ye, unsigned int ho, unsigned int mi, unsigned int se, string tz) : 
DateTime(da, 1, ye, ho, mi, se, tz)
// Algorithme :
// Convertion du mois en entier et appel au constructeur principal
{
#ifdef MAP
    cout << "Appel au constructeur de <DateTime>" << endl;
#endif

unordered_map <string, unsigned int>::const_iterator itMonth = DateTime::monthMap.find(mo);
if (itMonth == DateTime::monthMap.end()) { // Si le mois n'est pas dans la map, on renvoie une erreur
    throw invalid_argument("month is not valid");
}
month = DateTime::monthMap.find(mo)->second; // Sinon, on récupère le mois dans la map

} //----- Fin de DateTime

DateTime::~DateTime ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <DateTime>" << endl;
#endif
} //----- Fin de ~DateTime


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

