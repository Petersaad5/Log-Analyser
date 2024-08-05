/*************************************************************************
                           main  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;

#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>
#include <vector>
#include <unordered_set>

//------------------------------------------------------ Include personnel
#include "Analyzer.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

int main(int argc, char *argv[])
{
    vector<string> inputFiles; // Liste des fichiers à analyser
    string pathToOutGraphFile = ""; // Chemin vers le fichier de sortie du graphe
    bool excludeSpecialExtensions = false; // Si on doit exclure les extensions spéciales
    bool progressBar = false; // Si on doit afficher une barre de progression
    int hour = -1; // Heure à laquelle on doit se limiter
    int limit = -1; // Nombre de résultats à afficher
    
    try {
        const vector<string> args(argv + 1, argv + argc); // Liste des arguments passés au programme

        vector<string>::const_iterator it = args.begin();

        // On parcourt les arguments
        while (it != args.end()) {

            // On affiche l'aide
            if (*it == "-h" || *it == "--help") {
                cout << "Usage: analog [OPTION]... [FILE]...\n";
                cout << "\n";
                cout << "Options:\n";
                cout << "  -h, --help                           Print this help\n";
                cout << "  -g, --graph <FILE>                   Write GraphViz format graph of analyzed graph to a file\n";
                cout << "  -e, --exclude-special-extensions     Exclude logs to urls with extensions defined in config file\n";
                cout << "  -t, --time <HOUR>                    Only consider logs in the time interval [hour, hour+1[\n";
                cout << "  -l, --limit <NUMBER>                 Choose the number of line displayed in most consulted urls (default 10)\n";
                cout << "  -p, --progress                       Show a progress bar during file reading\n";
                cout << flush;

                return EXIT_SUCCESS;
            }
            
            // On récupère le chemin vers le fichier de sortie du graphe
            else if (*it == "-g" || *it == "--graph") {
                if (pathToOutGraphFile != "") {
                    throw runtime_error("cannot use -g/--graph param twice!");
                }
                it++;
                if (it == args.end()) {
                    throw runtime_error("invalid param for -g/--graph option");
                }
                pathToOutGraphFile = *it;
            }
            
            // On exclut les extensions spéciales
            else if (*it == "-e" || *it == "--exclude-special-extensions") {
                if (excludeSpecialExtensions) {
                    cerr << "Warning: ok ok you really want to exclude those extensions" << endl;
                }
                excludeSpecialExtensions = true;
            }

            // On affiche une barre de progression
            else if (*it == "-p" || *it == "--progress") {
                if (progressBar) {
                    cerr << "Warning: you use -g/--progress param twice." << endl;
                }
                progressBar = true;
            }

            // On récupère l'heure à laquelle on doit se limiter
            else if (*it == "-t" || *it == "--time") {
                if (hour != -1) {
                    throw runtime_error("cannot use -t/--time param twice!");
                }
                it++;
                if (it == args.end() || !regex_match(*it, regex("^[\\d]+$"))) {
                    throw runtime_error("invalid param for -t/--time option");
                }
                hour = stoi(*it);
                if ( hour < 0 || hour > 23 ) {
                    throw runtime_error("invalid hour (must be between 0 and 23)");
                }
            }

            // On récupère le nombre de résultats à afficher
            else if (*it == "-l" || *it == "--limit") {
                if (limit != -1) {
                    throw runtime_error("cannot use -l/--limit param twice!");
                }
                it++;
                if (it == args.end() || !regex_match(*it, regex("^[\\d]+$"))) {
                    throw runtime_error("invalid param for -l/--limit option");
                }
                limit = stoi(*it);
            }

            // On récupère le nom des fichiers à analyser
            else {
                if (! filesystem::exists(*it)) {
                    if (it->at(0) == '-') {
                        throw runtime_error("This option (" + *it + ") is not valid");
                    } else {
                        throw runtime_error("No such file (" + *it + ")");
                    }
                    
                }
                inputFiles.push_back(*it);
            }

            it++;
        }
    }
    // En cas d'erreur, on affiche l'erreur et on quitte le programme
    catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
        return EXIT_FAILURE;
    }
    
    // On récupère les domaines locaux et les extensions à exclure du fichier de config

    const string relativePathToExe = argv[0];
    // On ouvre le fichier de config
    ifstream configFile (filesystem::path(relativePathToExe).parent_path().string() + "/analog.conf");
    if (! configFile.good()) {
        cerr << "Warning: config file not found" << endl;
    }

    unordered_set<string> localDomains;
    unordered_set<string> extentionsToExclude;
    string line;

    while (getline(configFile, line)) { // On parcourt le fichier de config

        // On récupère les domaines locaux
        if (pathToOutGraphFile != "" && regex_search(line, regex("^local-domain *="))) {
            string::const_iterator start = line.begin() + line.find('=') + 1;
            string::const_iterator end = start;
            while (end != line.end() && *end != '#') end++;
            regex nonWhitespaceRegex("\\S+");
            sregex_iterator match(start, end, nonWhitespaceRegex);
            sregex_iterator lastMatch;
            while (match != lastMatch) {
                localDomains.insert(match->str());
                match++;
            }
        }

        // On récupère les extensions à exclure
        else if (excludeSpecialExtensions && regex_search(line, regex("^extensions-excluded *="))) {
            string::const_iterator start = line.begin() + line.find('=') + 1;
            string::const_iterator end = start;
            while (end != line.end() && *end != '#') end++;
            regex nonWhitespaceRegex("\\S+");
            sregex_iterator match(start, end, nonWhitespaceRegex);
            sregex_iterator lastMatch;
            while (match != lastMatch) {
                string extention = match->str();
                for (char & c: extention) c = tolower(c);

                extentionsToExclude.insert(extention);
                match++;
            }
        }
    }

    // On lance l'analyse
    if (inputFiles.size() > 0) {
        Analyzer analyzer(inputFiles, localDomains, extentionsToExclude, hour, progressBar);
        if (hour != -1) { // Si on a limité l'heure
            cout << "Info : only hits between " << hour << "h and " << hour+1 << "h have been taken into account" << "\n" << endl;
        }
        if (excludeSpecialExtensions) { // Si on a exclu les extensions spéciales
            cout << "Info : special extensions defined in config file were ignored" << "\n" << endl;
        }
        if (pathToOutGraphFile != "") { // Si on a demandé à générer un graphe
            cout << "Dot-file " << pathToOutGraphFile << " generated" << "\n" << endl;
            ofstream outGraphFile (pathToOutGraphFile);
            analyzer.ConsultationGraph(outGraphFile);
            outGraphFile.close();
        }

        // On affiche les résultats
        analyzer.MostConsulted(limit == -1 ? 10 : limit);
    }

    return EXIT_SUCCESS;
} //----- fin de main
