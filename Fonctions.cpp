#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// Fonction de découpe d'une chaîne en un tableau par le biais d'un délimiteur
std::vector<string> cut(const string &chaine, const string &delimiteur)
{
    int lChaine(chaine.size()), lDelimiteur(delimiteur.size()), i(0), j(0), k;
    std::vector<string> tab;

    if(lDelimiteur == 0) return tab;

    while(i < lChaine)
    {
        k = 0;
        while ((i + k) < lChaine && k < lDelimiteur && chaine[i + k] == delimiteur[k]) k++;

        if(k == lDelimiteur)
        {
            tab.push_back(chaine.substr(j, i - j));
            i += lDelimiteur;
            j = i;
        }
        else
        {
            i++;
        }
    }
    tab.push_back(chaine.substr(j, i - j));
    return tab;
}

// Conversion string to int
unsigned int StringToInt(std::string input)
{
    std::istringstream temp(input);
    unsigned int nb;
    temp >> nb;
    return nb;
}

// Conversion int to string
std::string IntToString(unsigned int input)
{
    std::ostringstream temp;
    temp << input;
    std::string out = temp.str();
    return out;
}

// Conversion majuscules -> minuscules
std::string MajToMin(std::string input)
{
    for(unsigned int i = 0; i < input.size(); i++)
    {
        input[i] = tolower(input[i]);
    }
    return input;
}

// Retourne le nombre d'occurence d'un caractère
unsigned int CountCaractere(std::string input, char c)
{
    unsigned int cpt(0);
    for(unsigned int i = 0; i < input.size(); i++)
    {
        if(input[i] == c) cpt++;
    }
    return cpt;
}

// Conversion bool to string
std::string BoolToString(bool input)
{
    if(input) return "1";
    return "0";
}

// Conversion bool to string
bool StringToBool(std::string input)
{
    if(input == "oui" || input == "1" || input == "Bon état") return true;
    return false;
}

// Conversion double to string
std::string DoubleToString(double input)
{
    std::ostringstream temp;
    temp << input;
    std::string out = temp.str();
    return out;
}
