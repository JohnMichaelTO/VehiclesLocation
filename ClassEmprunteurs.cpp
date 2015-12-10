#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include "Fonctions.h"
#include "ClassAdresse.h"
#include "ClassEmprunteur.h"
#include "ClassEmprunteurs.h"

using namespace std;

// Variable globale pour affecter un ID unique pour chaque nouvel emprunteur
unsigned int ClassEmprunteurs::IDEmprunteur = 0;

// Constructeur & Destructeur
ClassEmprunteurs::ClassEmprunteurs()
{
}

ClassEmprunteurs::~ClassEmprunteurs()
{
}

bool ClassEmprunteurs::Charger(std::string url)
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
        ClassEmprunteur nouveau;
        ClassAdresse adresse;
        for(unsigned int j = 0; j < tableau[0].size(); j++)
        {
            switch(j)
            {
                case 0:
                    nouveau.setID(StringToInt(tableau[i][j]));
                    break;
                case 1:
                    nouveau.setNom(tableau[i][j]);
                    break;
                case 2:
                    nouveau.setPrenom(tableau[i][j]);
                    break;
                case 3:
                    nouveau.setAge(StringToInt(tableau[i][j]));
                    break;
                case 4:
                    adresse.setNumero(tableau[i][j]);
                    break;
                case 5:
                    adresse.setRue(tableau[i][j]);
                    break;
                case 6:
                    adresse.setCP(tableau[i][j]);
                    break;
                case 7:
                    adresse.setVille(tableau[i][j]);
                    break;
            }
        }
        nouveau.setAdresse(adresse);
        Ajouter(nouveau.getID(), nouveau.getNom(), nouveau.getPrenom(), nouveau.getAdresse(), nouveau.getAge());
    }
    _url = url;

    return true;
}

bool ClassEmprunteurs::Sauvegarder(std::string url)
{
    // Chargement du fichier à sauvegarder
    ofstream fichier(url.c_str());

    if(fichier)
    {
        for(_it = _liste.begin(); _it != _liste.end(); _it++)
        {
            fichier << _it->second->getID() << "|";
            fichier << _it->second->getNom() << "|" << _it->second->getPrenom() << "|" << _it->second->getAge() << "|";
            fichier << _it->second->getAdresse().getNumero() << "|" << _it->second->getAdresse().getRue() << "|";
            fichier << _it->second->getAdresse().getCP() << "|" << _it->second->getAdresse().getVille() << "\n";
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

bool ClassEmprunteurs::Ajouter(unsigned int id, std::string nom, std::string prenom, ClassAdresse adresse, unsigned int age)
{
    // Incrémentation de l'ID qui doit être unique
    if(id > IDEmprunteur) setID(id);
    if(id == IDEmprunteur) incrementID();

    std::string cle = MajToMin(nom + "_" + prenom + "_" + IntToString(age));
    if(!VerifExist(cle, adresse))
    {
        cle = MajToMin(IntToString(id) + "_" + cle);
        _liste[cle] = new ClassEmprunteur(id, nom, prenom, adresse, age);
    }
    else return false;

    return true;
}

bool ClassEmprunteurs::Modifier(ClassEmprunteur base, unsigned int id, std::string nom, std::string prenom, ClassAdresse adresse, unsigned int age)
{
    std::string cle = MajToMin(IntToString(base.getID()) + "_" + base.getNom() + "_" + base.getPrenom() + "_" + IntToString(base.getAge()));
    _it = _liste.find(cle);

    if(_it == _liste.end())
    {
        return false;
    }
    else
    {
        std::string cle = MajToMin(nom + "_" + prenom + "_" + IntToString(age));
        if(!VerifExist(cle, adresse))
        {
            cle = MajToMin(IntToString(id) + "_" + cle);
            _it->second->setEmprunteur(id, nom, prenom, adresse, age);
            _liste[cle] = _it->second;
            _liste.erase(_it);
        }
    }
    Sauvegarder(_url);
    return true;
}

bool ClassEmprunteurs::Supprimer(ClassEmprunteur e)
{
    std::string cle = MajToMin(IntToString(e.getID()) + "_" + e.getNom() + "_" + e.getPrenom() + "_" + IntToString(e.getAge()));
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

void ClassEmprunteurs::RechercherParNom(std::string nom)
{
    _searchListe.clear();
    for(_it = _liste.begin(); _it != _liste.end(); _it++)
    {
        if(_it->first.find(MajToMin(nom)) != std::string::npos)
        {
            _searchListe[_it->first] = _it->second;
        }
    }
}

bool ClassEmprunteurs::VerifExist(std::string cle, ClassAdresse adresse)
{
    std::map<std::string, ClassEmprunteur*>::iterator it;
    for(it = _liste.begin(); it != _liste.end(); it++)
    {
        if(it->first.find(MajToMin(cle)) != std::string::npos)
        {
            if(it->second->getAdresse() == adresse) return true;
        }
    }
    return false;
}

void ClassEmprunteurs::Afficher()
{
    for(_it = _liste.begin(); _it != _liste.end(); _it++)
    {
        cout << "cle : " << _it->first << endl;
        _it->second->Afficher();
    }
}

void ClassEmprunteurs::AfficherResult()
{
    for(_it = _searchListe.begin(); _it != _searchListe.end(); _it++)
    {
        cout << "cle : " << _it->first << endl;
        _it->second->Afficher();
    }
}

ClassEmprunteur* ClassEmprunteurs::getByID(unsigned int id)
{
    std::map<std::string, ClassEmprunteur*>::iterator it;
    for(it = _liste.begin(); it != _liste.end(); it++)
    {
        if(it->first.find(MajToMin(IntToString(id) + "_")) != std::string::npos)
        {
            return it->second;
        }
    }
    return NULL;
}
