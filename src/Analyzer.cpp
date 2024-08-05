/*************************************************************************
                           Analyzer  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Analyzer> (fichier Analyzer.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iomanip>
#include <filesystem>
#include <cmath>
#include <regex>
#include <set>
#include <list>

//------------------------------------------------------ Include personnel
#include "Analyzer.h"
#include "LogFile.h"
#include "Log.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Analyzer::MostConsulted ( unsigned int numberResults, ostream & out) const
// Algorithme :
// On parcourt toutes les pages et on les insère dans une liste triée par nombre de hits décroissant
// On affiche ensuite les éléments de la liste
// Au fur et à mesure, on supprime les éléments de la liste qui sont en trop
// 
// note : nthElement est un itérateur vers le numberResults-ème élément, c'est-à-dire à partir du quel
// on doit supprimer la fin de la liste lorsque l'on insère un élément avant et qu'il n'y a pas d'égalité
// en nombre de hits pour la numberResults-ème place.
{
    if (numberResults == 0) return; // Si on ne veut pas afficher de résultats, on ne fait rien

    typedef list<pair<unsigned int, string>> resultList; 
    resultList results; // Liste triée par nombre de hits décroissant
    resultList::iterator it, nthElement;

    // Pour chaque page récupérée après le parcours des logs
    for (const pair<const string, AnalyzerPage> & page: analyzerPages) {
        it = results.begin();
        
        // On cherche le premier élément de la liste qui a un nombre de hits inférieur ou égal à celui de la page
        while (it != results.end() && (it->first > page.second.numberbHits || (it->first == page.second.numberbHits && it->second < page.first))) {
            it++;
        }

        // On insère la page à cet endroit
        if (results.size() < numberResults || page.second.numberbHits >= nthElement->first) {
            results.insert(it, make_pair(page.second.numberbHits, page.first));

            if (results.size() == numberResults) {
                // Initialisation de nthElement lorsque l'on atteint une taille de numberResults
                nthElement = prev(results.end());
            }
            else if (results.size() > numberResults) {
                // On supprime les derniers éléments à chaque fois quelle dépasse une taille de numberResults
                // et qu'il n'y a pas d'égalité en nombre de hit pour la dernière place
                if (page.second.numberbHits > nthElement->first || (page.second.numberbHits == nthElement->first && page.first <= nthElement->second)) {
                    resultList::iterator nextNthElement = prev(nthElement);
                    if (nextNthElement->first != nthElement->first) {
                        results.erase(nthElement, results.end());
                    }
                    nthElement = nextNthElement;
                }
            }
        }
    }

    // On affiche les résultats
    unsigned int numberResultsNumberDigits = log10 (numberResults) + 1; 

    it = results.begin();
    unsigned int count = 1;
    unsigned int lastNumberHits = 0;
    out << "Most consulted urls :" << endl;
    while (it != results.end()) {
        if (it->first != lastNumberHits)
            out << setw(numberResultsNumberDigits) << count << " : " << it->second << " (" << it->first << " hits)" << endl;
        else
            out << setw(numberResultsNumberDigits + 3) << " " << it->second << " (" << it->first << " hits)" << endl;
        
        lastNumberHits = it->first;
        count++;
        it++;
    }
} //----- Fin de MostConsulted

void Analyzer::ConsultationGraph ( ostream & out ) const
// Algorithme :
// Exporte le graphique au format GraphViz en parcourant toutes les pages analysées
{
    out << "digraph {" << endl; // Début du graphique

    // On parcourt toutes les pages
    // On parcourt tous les referers de chaque page
    // On affiche une flèche entre le referer et la page
    for (const pair<const string, AnalyzerPage> & destinationPage: analyzerPages) {
        for (const pair<const string, unsigned int> & refererPage: destinationPage.second.nbHitByReferer) {
            out << "    \"" << refererPage.first << "\" -> \"" << destinationPage.first << "\" [label=\"" << refererPage.second << "\"];" << endl;
        }
    }

    out << "}" << endl; // Fin du graphique
} //----- Fin de ConsultationGraph

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Analyzer::Analyzer ( const vector<string> & pathsToLogFiles, const unordered_set<string> & localDomains, const unordered_set<string> & extentionsToExclude, int hour, bool progressBar)
{
#ifdef MAP
    cout << "Appel au constructeur de <Analyzer>" << endl;
#endif

    unordered_map<string, string> refererFullUrlToShorterUrl; 

    // Pour chaque fichier de log
    for (const string & pathToLogFile: pathsToLogFiles) {
        LogFile logfile(pathToLogFile); // On ouvre le fichier de log

        // On récupère la taille du fichier
        logfile.getStream().seekg(0, ios::end);
        int size = logfile.getStream().tellg();
        logfile.getStream().seekg(0, ios::beg);

        Log log; // On crée un log vide
        while (logfile) { // Tant qu'on n'est pas à la fin du fichier
            if (logfile.getLog(log)) { // On récupère un log et on vérifie qu'il est valide
                string destination = removeParametersFromUrl(log.getDestination());
                string destinationExtension = filesystem::path(destination).extension();
                for (char & c: destinationExtension) c = tolower(c);
                
                // Si l'extension n'est pas dans la liste des extensions à exclure et que l'heure est dans la bonne tranche horaire
                if ((hour == -1 || hour == (int) log.getDateTime().getHour()) && ! extentionsToExclude.count(destinationExtension)) {
                    
                    string referer = removeParametersFromUrl(log.getReferer());
                    
                    if (!refererFullUrlToShorterUrl.count(referer)) {
                        string shorterReferer = referer;
                        smatch match;
                        //On enlève le http:// ou https:// du début de l'URL 
                        if (regex_search(referer, match, regex("^https?://"))) {
                            shorterReferer = shorterReferer.substr(match[0].length());
                        }
                        size_t pos_slash = min(shorterReferer.find('/'), shorterReferer.length());
                        size_t pos_port = shorterReferer.find(':');

                        // On enlève le domaine local du début de l'URL
                        if (localDomains.count(shorterReferer.substr(0, min(pos_slash, pos_port)))) {
                            shorterReferer = shorterReferer.substr(pos_slash);
                        }

                        refererFullUrlToShorterUrl[referer] = shorterReferer;
                    }   

                    // On remplace le referer par sa version raccourcie
                    referer = refererFullUrlToShorterUrl[referer];

                    // On ajoute le referer à la page de destination
                    if (! analyzerPages.count(destination)) {
                        analyzerPages[destination] = AnalyzerPage();
                    }
                    analyzerPages[destination].AddHit(referer); // On ajoute un hit à la page de destination
                }
            }
            if (progressBar) { // Affichage de la barre de progression
                int perc = (int) (logfile.getStream().tellg()*100/size);
                cout << "\r" << "[" << string(perc/2, '#') << string(50-perc/2, ' ') << "] " << perc << " %";
            }
            
        }
        if (progressBar) { // Effacement de la barre de progression
            cout << "\r" << string(50+8, ' ') << '\r';
        }
    }
} //----- Fin de Analyzer


Analyzer::~Analyzer ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Analyzer>" << endl;
#endif
} //----- Fin de ~Analyzer


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

bool Analyzer::cropBeforeChar ( string & str, char c ) const
// Algorithme :
// On cherche le premier caractère c dans la chaîne de caractères str
// Si on le trouve, on coupe la chaîne de caractères avant ce caractère
{
    size_t pos = str.find(c);
    bool charPresent = pos != string::npos;
    if (charPresent) {
        str = str.substr(0, pos);
    }
    return charPresent;
} //----- Fin de Méthode

string Analyzer::removeParametersFromUrl ( string url ) const
// Algorithme :
// On cherche le premier caractère ? ou ; dans la chaîne de caractères url
// Si on le trouve, on coupe la chaîne de caractères après ce caractère
{
    char parametersDelimiters[] = {'?', ';'};
    // note : certains paramètres sont indiqués par un ;
    // exemple : /cas/themes/insa/media/favicon.ico;jsessionid=7F43502204EF9681222840C501D14A9A.dsi-vm04
    for (char delimiter: parametersDelimiters) {
        if (cropBeforeChar(url, delimiter)) {
            break;
        }
    }
    return url;
} //----- Fin de Méthode

