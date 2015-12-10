#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include "Fonctions.h"
#include "ClassAdresse.h"
#include "ClassVehicule.h"
#include "ClassVehicules.h"
#include "ClassAuto.h"
#include "ClassMoto.h"

#define DAUTO 10
#define DMOTO 8

// Variable globale pour affecter un ID unique pour chaque nouveau véhicule
unsigned int ClassVehicules::IDVehicule = 0;

// Constructeur & Destructeur
ClassVehicules::ClassVehicules()
{
}

ClassVehicules::~ClassVehicules()
{
}

bool ClassVehicules::Charger(std::string url)
{
    string ligne, memoire("");
    unsigned int nbLigneV(0), nbLigneM(0);

    // Chargement du fichier
    ifstream fichier(url.c_str(), ios::in);

    if(fichier)
    {
        while(getline(fichier, ligne))
        {
            if(ligne != "" && ligne != "\n")
            {
                if(CountCaractere(ligne, '|') == DAUTO) nbLigneV++;
                if(CountCaractere(ligne, '|') == DMOTO) nbLigneM++;
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
    vector< vector<string> > voiture, moto;
    voiture.resize(nbLigneV);
    moto.resize(nbLigneM);

    unsigned Vi(0), Mi(0);
    for(unsigned int i = 0; i < (nbLigneV + nbLigneM); i++)
    {
        if(CountCaractere(TabTemp[i], '|') == DAUTO)
        {
            voiture[Vi] = cut(TabTemp[i], "|");
            Vi++;
        }

        if(CountCaractere(TabTemp[i], '|') == DMOTO)
        {
            moto[Mi] = cut(TabTemp[i], "|");
            Mi++;
        }
    }

    for(unsigned int i = 0; i < nbLigneV; i++)
    {
        ClassAuto nAuto;
        for(unsigned int j = 0; j < voiture[0].size(); j++)
        {
            switch(j)
            {
                case 0:
                    nAuto.setID(StringToInt(voiture[i][j]));
                    break;
                case 1:
                    nAuto.setMarque(voiture[i][j]);
                    break;
                case 2:
                    nAuto.setModele(voiture[i][j]);
                    break;
                case 3:
                    nAuto.setType(voiture[i][j]);
                    break;
                case 4:
                    nAuto.setNbRoues(StringToInt(voiture[i][j]));
                    break;
                case 5:
                    nAuto.setPoids(StringToInt(voiture[i][j]));
                    break;
                case 6:
                    nAuto.setECO2(voiture[i][j]);
                    break;
                case 7:
                    nAuto.setPrix(StringToInt(voiture[i][j]));
                    break;
                case 8:
                    nAuto.setTypePropulsion(voiture[i][j]);
                    break;
                case 9:
                    nAuto.setNbPortes(StringToInt(voiture[i][j]));
                    break;
                case 10:
                    nAuto.setNbSieges(StringToInt(voiture[i][j]));
                    break;
            }
        }
        Ajouter(nAuto.getID(), nAuto.getMarque(), nAuto.getModele(), nAuto.getType(), nAuto.getNbRoues(), nAuto.getPoids(), nAuto.getECO2(), nAuto.getPrix(), nAuto.getTypePropulsion(), nAuto.getNbPortes(), nAuto.getNbSieges());
    }

    for(unsigned int i = 0; i < nbLigneM; i++)
    {
        ClassMoto nMoto;
        for(unsigned int j = 0; j < moto[0].size(); j++)
        {
            switch(j)
            {
                case 0:
                    nMoto.setID(StringToInt(moto[i][j]));
                    break;
                case 1:
                    nMoto.setMarque(moto[i][j]);
                    break;
                case 2:
                    nMoto.setModele(moto[i][j]);
                    break;
                case 3:
                    nMoto.setType(moto[i][j]);
                    break;
                case 4:
                    nMoto.setNbRoues(StringToInt(moto[i][j]));
                    break;
                case 5:
                    nMoto.setPoids(StringToInt(moto[i][j]));
                    break;
                case 6:
                    nMoto.setECO2(moto[i][j]);
                    break;
                case 7:
                    nMoto.setPrix(StringToInt(moto[i][j]));
                    break;
                case 8:
                    nMoto.setCylindree(StringToInt(moto[i][j]));
                    break;
            }
        }
        Ajouter(nMoto.getID(), nMoto.getMarque(), nMoto.getModele(), nMoto.getType(), nMoto.getNbRoues(), nMoto.getPoids(), nMoto.getECO2(), nMoto.getPrix(), nMoto.getCylindree());
    }

    _url = url;

    return true;
}

bool ClassVehicules::Sauvegarder(std::string url)
{
    // Chargement du fichier à sauvegarder
    ofstream fichier(url.c_str());

    if(fichier)
    {
        for(_it = _liste.begin(); _it != _liste.end(); _it++)
        {
            fichier << _it->second->getID() << "|";
            fichier << _it->second->getMarque() << "|" << _it->second->getModele() << "|" << _it->second->getType() << "|";
            fichier << _it->second->getNbRoues() << "|" << _it->second->getPoids() << "|";
            fichier << _it->second->getECO2() << "|" << _it->second->getPrix() << "|";

            if(_it->second->what() == 1) // Voiture
            {
                fichier << _it->second->getTypePropulsion() << "|" << _it->second->getNbPortes() << "|" << _it->second->getNbSieges() << "\n";
            }
            else // Moto
            {
                fichier << _it->second->getCylindree() << "\n";
            }
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

bool ClassVehicules::Ajouter(unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, std::string typePropulsion, unsigned int nbPortes, unsigned int nbSieges)
{
    // Incrémentation de l'ID qui doit être unique
    if(id > IDVehicule) setID(id);
    if(id == IDVehicule) incrementID();

    std::string cle = MajToMin(marque + "_" + modele + "_" + type);
    if(!VerifExist(cle, nbRoues, poids, eCO2, prix, typePropulsion, nbPortes, nbSieges))
    {
        cle = MajToMin(IntToString(id) + "_" + cle);
        _liste[cle] = new ClassAuto(id, marque, modele, type, nbRoues, poids, eCO2, prix, typePropulsion, nbPortes, nbSieges);
    }
    else return false;

    return true;
}

bool ClassVehicules::Ajouter(unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, unsigned int cylindree)
{
    // Incrémentation de l'ID qui doit être unique
    if(id > IDVehicule) setID(id);
    if(id == IDVehicule) incrementID();

    std::string cle = MajToMin(marque + "_" + modele + "_" + type);
    if(!VerifExist(cle, nbRoues, poids, eCO2, prix, cylindree))
    {
        cle = MajToMin(IntToString(id) + "_" + cle);
        _liste[cle] = new ClassMoto(id, marque, modele, type, nbRoues, poids, eCO2, prix, cylindree);
    }
    else return false;

    return true;
}

bool ClassVehicules::Modifier(ClassAuto base, unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, std::string typePropulsion, unsigned int nbPortes, unsigned int nbSieges)
{
    std::string cle = MajToMin(IntToString(base.getID()) + "_" + base.getMarque() + "_" + base.getModele() + "_" + base.getType());
    _it = _liste.find(cle);

    if(_it == _liste.end())
    {
        return false;
    }
    else
    {
        std::string cle = MajToMin(marque + "_" + modele + "_" + type + "_");
        if(!VerifExist(cle, nbRoues, poids, eCO2, prix, typePropulsion, nbPortes, nbSieges))
        {
            cle = MajToMin(IntToString(id) + "_" + cle);
            _it->second->setAuto(id, marque, modele, type, nbRoues, poids, eCO2, prix, typePropulsion, nbPortes, nbSieges);
            _liste[cle] = _it->second;
            _liste.erase(_it);
        }
    }
    Sauvegarder(_url);
    return true;
}

bool ClassVehicules::Modifier(ClassMoto base, unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, unsigned int cylindree)
{
    std::string cle = MajToMin(IntToString(base.getID()) + "_" + base.getMarque() + "_" + base.getModele() + "_" + base.getType());
    _it = _liste.find(cle);

    if(_it == _liste.end())
    {
        return false;
    }
    else
    {
        std::string cle = MajToMin(marque + "_" + modele + "_" + type);
        if(!VerifExist(cle, nbRoues, poids, eCO2, prix, cylindree))
        {
            cle = MajToMin(IntToString(id) + "_" + cle);
            _it->second->setMoto(id, marque, modele, type, nbRoues, poids, eCO2, prix, cylindree);
            _liste[cle] = _it->second;
            _liste.erase(_it);
        }
    }
    Sauvegarder(_url);
    return true;
}

bool ClassVehicules::Supprimer(unsigned int id, std::string marque, std::string modele, std::string type)
{
    std::string cle = MajToMin(IntToString(id) + "_" + marque + "_" + modele + "_" + type);
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

void ClassVehicules::RechercherParMarque(std::string marque)
{
    _searchListe.clear();
    for(_it = _liste.begin(); _it != _liste.end(); _it++)
    {
        if(_it->first.find(MajToMin(marque)) != std::string::npos)
        {
            _searchListe[_it->first] = _it->second;
        }
    }
}

bool ClassVehicules::VerifExist(std::string cle, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, std::string typePropulsion, unsigned int nbPortes, unsigned int nbSieges)
{
    std::map<std::string, ClassVehicule*>::iterator it;
    for(it = _liste.begin(); it != _liste.end(); it++)
    {
        if(it->first.find(MajToMin(cle)) != std::string::npos)
        {
            if(it->second->getNbRoues() == nbRoues && it->second->getPoids() == poids &&
                    it->second->getECO2() == eCO2 && it->second->getPrix() == prix &&
                    it->second->getTypePropulsion() == typePropulsion && it->second->getNbPortes() == nbPortes &&
                    it->second->getNbSieges() == nbSieges) return true;
        }
    }
    return false;
}

bool ClassVehicules::VerifExist(std::string cle, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, unsigned int cylindree)
{
    std::map<std::string, ClassVehicule*>::iterator it;
    for(it = _liste.begin(); it != _liste.end(); it++)
    {
        if(it->first.find(MajToMin(cle)) != std::string::npos)
        {
            if(it->second->getNbRoues() == nbRoues && it->second->getPoids() == poids &&
                    it->second->getECO2() == eCO2 && it->second->getPrix() == prix &&
                    it->second->getCylindree() == cylindree) return true;
        }
    }
    return false;
}

void ClassVehicules::Afficher()
{
    for(_it = _liste.begin(); _it != _liste.end(); _it++)
    {
        cout << "cle : " << _it->first << endl;
        _it->second->Afficher();
    }
}

void ClassVehicules::AfficherResult()
{
    for(_it = _searchListe.begin(); _it != _searchListe.end(); _it++)
    {
        cout << "cle : " << _it->first << endl;
        _it->second->Afficher();
    }
}

ClassVehicule* ClassVehicules::getbyMarqueModele(std::string marque, std::string modele)
{
    std::map<std::string, ClassVehicule*>::iterator it;
    for(it = _liste.begin(); it != _liste.end(); it++)
    {
        if(it->first.find(MajToMin(marque + "_" + modele)) != std::string::npos)
        {
            return it->second;
        }
    }
    return NULL;
}

unsigned int ClassVehicules::getPrixByMarqueModele(std::string marque, std::string modele)
{
    std::map<std::string, ClassVehicule*>::iterator it;
    for(it = _liste.begin(); it != _liste.end(); it++)
    {
        if(it->first.find(MajToMin(marque + "_" + modele)) != std::string::npos)
        {
            return it->second->getPrix();
        }
    }
    return 0;
}
