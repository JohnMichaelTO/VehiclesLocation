#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include "Fonctions.h"
#include "ClassVehicule.h"
#include "ClassExemplaires.h"

using namespace std;

// Variable globale pour affecter un ID unique pour chaque nouveau exemplaire
unsigned int ClassExemplaires::ID = 0;

// Constructeur & Destructeur
ClassExemplaires::ClassExemplaires(ClassVehicules *listeV)
{
    _listeVehicules = listeV;
}

ClassExemplaires::~ClassExemplaires()
{
}

bool ClassExemplaires::Charger(std::string url)
{
    string ligne, memoire("");
    unsigned int nbLigne(0);

    // Chargement du fichier
    ifstream fichier(url.c_str(), ios::in);

    if(fichier)
    {
        while(getline(fichier, ligne))
        {
            if(ligne != "" && ligne != "\n")
            {
                nbLigne++;
                memoire += ligne + '\n';
            }
        }
        fichier.close();
    }
    else
    {
        cout << "ERREUR : Fichier " << url << " inexistant" << endl;
        fichier.clear();
        return false;
    }

    vector<string> TabTemp = cut(memoire, "\n");
    vector< vector<string> > tableau;
    tableau.resize(nbLigne);

    for(unsigned int i = 0; i < nbLigne; i++)
    {
        tableau[i] = cut(TabTemp[i], "|");
    }

    for(unsigned int i = 0; i < nbLigne; i++)
    {
        unsigned int numero;
        ClassVehicule *vehicule;
        std::string marque, modele;
        unsigned int Km;
        std::string couleur;
        bool disponible;

        for(unsigned int j = 0; j < tableau[0].size(); j++)
        {
            switch(j)
            {
                case 0:
                    numero = StringToInt(tableau[i][j]);
                    break;
                case 1:
                    marque = tableau[i][j];
                    break;
                case 2:
                    modele = tableau[i][j];
                    break;
                case 3:
                    Km = StringToInt(tableau[i][j]);
                    break;
                case 4:
                    couleur = tableau[i][j];
                    break;
                case 5:
                    if(tableau[i][j] == "1") disponible = true;
                    else disponible = false;
                    break;
            }
        }
        vehicule = _listeVehicules->getbyMarqueModele(marque, modele);
        Ajouter(numero, vehicule, Km, couleur, disponible);
    }
    _url = url;

    return true;
}

bool ClassExemplaires::Sauvegarder(std::string url)
{
    // Chargement du fichier à sauvegarder
    ofstream fichier(url.c_str());

    if(fichier)
    {
        for(_it = _liste.begin(); _it != _liste.end(); _it++)
        {
            fichier << _it->second->getNumero() << "|" << _it->second->getVehicule()->getMarque() << "|";
            fichier << _it->second->getVehicule()->getModele() << "|";
            fichier << _it->second->getKm() << "|" << _it->second->getCouleur() << "|";
            fichier << _it->second->getDisponibilite() << "\n";
        }
    }
    else
    {
        // cout << "Erreur dans l'ouverture du fichier : " << url << endl;
        fichier.clear();
        return false;
    }

    fichier.close();
    return true;
}

bool ClassExemplaires::Ajouter(unsigned int numero, ClassVehicule *vehicule, unsigned int Km, std::string couleur, bool disponible)
{
    // Incrémentation du numéro qui doit être unique
    if(numero > ID) setID(numero);
    if(numero == ID) incrementID();

    std::string cle = MajToMin(IntToString(numero) + "_" + vehicule->getMarque() + "_" + vehicule->getModele() + "_" + IntToString(Km) + "_" + couleur + "_disp" + BoolToString(disponible));

    if(!VerifExist(cle))
    {
        _liste[cle] = new ClassExemplaire(numero, vehicule, Km, couleur, disponible);
    }
    else return false;

    return true;
}

bool ClassExemplaires::Modifier(ClassExemplaire e, unsigned int numero, ClassVehicule *vehicule, unsigned int Km, std::string couleur, bool disponible)
{
    std::string cle = MajToMin(IntToString(e.getNumero()) + "_" + e.getVehicule()->getMarque() + "_" + e.getVehicule()->getModele() + "_" + IntToString(e.getKm()) + "_" + e.getCouleur() + "_disp" + BoolToString(e.getDisponibilite()));
    _it = _liste.find(cle);

    if(_it == _liste.end())
    {
        return false;
    }
    else
    {
        std::string cle = MajToMin(IntToString(numero) + "_" + vehicule->getMarque() + "_" + vehicule->getModele() + "_" + IntToString(Km) + "_" + couleur + "_disp" + BoolToString(disponible));
        if(!VerifExist(cle))
        {
            _it->second->setExemplaire(numero, vehicule, Km, couleur, disponible);
            _liste[cle] = _it->second;
            _liste.erase(_it);
        }
    }
    Sauvegarder(_url);
    return true;
}

bool ClassExemplaires::Supprimer(ClassExemplaire e)
{
    std::string cle = MajToMin(IntToString(e.getNumero()) + "_" + e.getVehicule()->getMarque() + "_" + e.getVehicule()->getModele() + "_" + IntToString(e.getKm()) + "_" + e.getCouleur() + "_disp" + BoolToString(e.getDisponibilite()));
    _it = _liste.find(cle);

    if(_it == _liste.end())
    {
        return false;
    }
    else
    {
        _liste.erase(_it);
    }
    return true;
}

void ClassExemplaires::RechercherParKm(std::string Km)
{
    _searchListe.clear();
    for(_it = _liste.begin(); _it != _liste.end(); _it++)
    {
        if(_it->first.find(MajToMin(Km)) != std::string::npos)
        {
            _searchListe[_it->first] = _it->second;
        }
    }
}

bool ClassExemplaires::VerifExist(std::string cle)
{
    std::map<std::string, ClassExemplaire*>::iterator it;
    for(it = _liste.begin(); it != _liste.end(); it++)
    {
        if(it->first.find(MajToMin(cle)) != std::string::npos)
        {
            return true;
        }
    }
    return false;
}

ClassExemplaire* ClassExemplaires::getByID(unsigned int id)
{
    std::map<std::string, ClassExemplaire*>::iterator it;
    for(it = _liste.begin(); it != _liste.end(); it++)
    {
        if(it->first.find(MajToMin(IntToString(id) + "_")) != std::string::npos)
        {
            return it->second;
        }
    }
    return NULL;
}

void ClassExemplaires::RechercherParMarqueDisponibilite(std::string marque, bool disponible)
{
    _searchListe.clear();
    for(_it = _liste.begin(); _it != _liste.end(); _it++)
    {
        if(_it->first.find(MajToMin(marque)) != std::string::npos && _it->first.find(MajToMin("disp" + BoolToString(disponible))) != std::string::npos)
        {
            _searchListe[_it->first] = _it->second;
        }
    }
}
