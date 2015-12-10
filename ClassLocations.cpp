#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include "Fonctions.h"
#include "ClassVehicule.h"
#include "ClassExemplaires.h"
#include "ClassEmprunteurs.h"
#include "ClassLocations.h"

using namespace std;

// Variable globale pour affecter un ID unique pour chaque emprunteur
unsigned int ClassLocations::IDLocation = 0;

ClassLocations::ClassLocations(ClassExemplaires *listEx, ClassEmprunteurs *listEm)
{
    _listExemplaires = listEx;
    _listEmprunteurs = listEm;
}

ClassLocations::~ClassLocations()
{
}

bool ClassLocations::Charger(std::string url)
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
        unsigned int idLoc, idV, idEm;
        ClassEmprunteur *emprunteur;
        ClassExemplaire *exemplaire;
        ClassDate dateD, dateF, dateR;
        bool assurance;
        unsigned int niveauCarburant;
        bool etatVehicule;

        for(unsigned int j = 0; j < tableau[0].size(); j++)
        {
            switch(j)
            {
                case 0:
                    idLoc = StringToInt(tableau[i][j]);
                    break;
                case 1:
                    idV = StringToInt(tableau[i][j]);
                    break;
                case 2:
                    dateD.setJour(StringToInt(tableau[i][j]));
                    break;
                case 3:
                    dateD.setMois(StringToInt(tableau[i][j]));
                    break;
                case 4:
                    dateD.setAnnee(StringToInt(tableau[i][j]));
                    break;
                case 5:
                    dateF.setJour(StringToInt(tableau[i][j]));
                    break;
                case 6:
                    dateF.setMois(StringToInt(tableau[i][j]));
                    break;
                case 7:
                    dateF.setAnnee(StringToInt(tableau[i][j]));
                    break;
                case 8:
                    dateR.setJour(StringToInt(tableau[i][j]));
                    break;
                case 9:
                    dateR.setMois(StringToInt(tableau[i][j]));
                    break;
                case 10:
                    dateR.setAnnee(StringToInt(tableau[i][j]));
                    break;
                case 11:
                    assurance = StringToBool(tableau[i][j]);
                    break;
                case 12:
                    idEm = StringToInt(tableau[i][j]);
                    break;
                case 13:
                    niveauCarburant = StringToInt(tableau[i][j]);
                    break;
                case 14:
                    etatVehicule = StringToBool(tableau[i][j]);
                    break;
            }
        }

        emprunteur = _listEmprunteurs->getByID(idEm);
        exemplaire = _listExemplaires->getByID(idV);
        Ajouter(idLoc, dateD, dateF, dateR, emprunteur, exemplaire, assurance, niveauCarburant, etatVehicule);
    }
    _url = url;

    return true;
}

bool ClassLocations::Sauvegarder(std::string url)
{
    // Chargement du fichier à sauvegarder
    ofstream fichier(url.c_str());

    if(fichier)
    {
        for(_it = _liste.begin(); _it != _liste.end(); _it++)
        {
            fichier << _it->second->getID() << "|" << _it->second->getExemplaire()->getNumero() << "|";
            fichier << _it->second->getDateD().getJour() << "|" << _it->second->getDateD().getMois() << "|";
            fichier << _it->second->getDateD().getAnnee() << "|" << _it->second->getDateF().getJour() << "|";
            fichier << _it->second->getDateF().getMois() << "|" << _it->second->getDateF().getAnnee() << "|";
            fichier << _it->second->getDateR().getJour() << "|" << _it->second->getDateR().getMois() << "|";
            fichier << _it->second->getDateR().getAnnee() << "|" << _it->second->getAssurance() << "|";
            fichier << _it->second->getEmprunteur()->getID() << "|";
            fichier << _it->second->getNiveauCarburant() << "|";
            fichier << _it->second->getEtatVehicule() << "\n";
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

bool ClassLocations::Ajouter(unsigned int id, ClassDate dateD, ClassDate dateF, ClassDate dateR, ClassEmprunteur *emprunteur, ClassExemplaire *exemplaire, bool assurance, unsigned int niveauCarburant, bool etatVehicule)
{
    // Incrémentation de l'ID qui doit être unique
    if(id > IDLocation) setID(id);
    if(id == IDLocation) incrementID();

    std::string cle = MajToMin(IntToString(id) + "_" + emprunteur->getNom() + "_" + emprunteur->getPrenom() + "_" + exemplaire->getVehicule()->getMarque() + "_" + exemplaire->getVehicule()->getModele());

    if(!VerifExist(cle, dateD, dateF, dateR, emprunteur, exemplaire, assurance, niveauCarburant, etatVehicule))
    {
        _liste[cle] = new ClassLocation(id, dateD, dateF, dateR, emprunteur, exemplaire, assurance, niveauCarburant, etatVehicule);
    }
    else return false;

    return true;
}

bool ClassLocations::Modifier(ClassLocation e, unsigned int id, ClassDate dateD, ClassDate dateF, ClassDate dateR, ClassEmprunteur *emprunteur, ClassExemplaire *exemplaire, bool assurance, unsigned int niveauCarburant, bool etatVehicule)
{
    std::string cle = MajToMin(IntToString(e.getID()) + "_" + e.getEmprunteur()->getNom() + "_" + e.getEmprunteur()->getPrenom() + "_" + e.getExemplaire()->getVehicule()->getMarque() + "_" + e.getExemplaire()->getVehicule()->getModele());
    _it = _liste.find(cle);

    if(_it == _liste.end())
    {
        return false;
    }
    else
    {
        std::string cle = MajToMin(IntToString(id) + "_" + emprunteur->getNom() + "_" + emprunteur->getPrenom() + "_" + exemplaire->getVehicule()->getMarque() + "_" + exemplaire->getVehicule()->getModele());
        if(!VerifExist(cle, dateD, dateF, dateR, emprunteur, exemplaire, assurance, niveauCarburant, etatVehicule))
        {
            _it->second->setLocation(id, dateD, dateF, dateR, emprunteur, exemplaire, assurance, niveauCarburant, etatVehicule);
            _liste[cle] = _it->second;
            if(_it->first != cle) _liste.erase(_it);
        }
    }
    Sauvegarder(_url);
    return true;
}

bool ClassLocations::Supprimer(ClassLocation e)
{

    std::string cle = MajToMin(IntToString(e.getID()) + "_" + e.getEmprunteur()->getNom() + "_" + e.getEmprunteur()->getPrenom() + "_" + e.getExemplaire()->getVehicule()->getMarque() + "_" + e.getExemplaire()->getVehicule()->getModele());
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

void ClassLocations::RechercherParLocation(std::string nom)
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

bool ClassLocations::VerifExist(std::string cle, ClassDate dateD, ClassDate dateF, ClassDate dateR, ClassEmprunteur *emprunteur, ClassExemplaire *exemplaire, bool assurance, unsigned int niveauCarburant, bool etatVehicule)
{
    std::map<std::string, ClassLocation*>::iterator it;
    for(it = _liste.begin(); it != _liste.end(); it++)
    {
        if(it->first.find(MajToMin(cle)) != std::string::npos)
        {
            if(it->second->getDateD() == dateD && it->second->getDateF() == dateF &&
                    it->second->getDateR() == dateR && it->second->getEmprunteur() == emprunteur &&
                    it->second->getExemplaire() == exemplaire && it->second->getAssurance() == assurance &&
                    it->second->getNiveauCarburant() == niveauCarburant && it->second->getEtatVehicule() == etatVehicule)
            return true;
        }
    }
    return false;
}
