#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

// Fonction de d�coupe d'une cha�ne en un tableau par le biais d'un d�limiteur
std::vector<std::string> cut(const std::string &chaine, const std::string &delimiteur);

// Conversion string to int
unsigned int StringToInt(std::string input);

// Conversion int to string
std::string IntToString(unsigned int input);

// Conversion majuscules -> minuscules
std::string MajToMin(std::string input);

// Retourne le nombre d'occurence d'un caract�re
unsigned int CountCaractere(std::string input, char c);

// Conversion bool to string
std::string BoolToString(bool input);

// Conversion bool to string
bool StringToBool(std::string input);

// Conversion double to string
std::string DoubleToString(double input);

#endif // FONCTIONS_H_INCLUDED
