#include "String.h"

String::String(): std::string()
{
    // Appelle le constructeur de std::string.
}

String::String(std::string const& str): std::string(str)
{
    // Appelle le constructeur de std::string.
}

String::String(unsigned int n, char c): std::string(n, c)
{
    // Appelle le constructeur de std::string.
}

String::String(const char c[]): std::string(c)
{
    // Appelle le constructeur de std::string.
}

String::String(int nombre)
{
    std::string nbStr = std::to_string(nombre);
    eliminerZeros(nbStr);
    append(nbStr);
}

String::String(double nombre)
{
    std::string nbStr = std::to_string(nombre);
    eliminerZeros(nbStr);
    append(nbStr);
}

String::~String()
{
    //dtor
}

char String::charAt(unsigned int indice) const
{
    return at(indice);
}

int String::compareTo(String const& str) const
{
    return compare(str);
}

void String::concat(int nombre)
{
    this->append(std::to_string(nombre));
}

void String::concat(double nombre)
{
    std::string nbStr = std::to_string(nombre);
    eliminerZeros(nbStr);
    this->append(nbStr);
}

void String::concat(const char* s)
{
    this->append(s);
}

void String::concat(std::string str)
{
    this->append(str);
}

int String::indexOf(char c, unsigned int indice) const
{
    return find(c, indice);
}

int String::indexOf(const char* c, unsigned int indice) const
{
    return find(*c, indice);
}

int String::indexOf(String const& str, unsigned int indice) const
{
    return find(str, indice);
}

unsigned int String::length() const
{
    return size();
}

void String::remove(unsigned int debut, unsigned int nbr)
{
    *this = erase(debut, nbr);
}

String String::substring(unsigned int debut, unsigned int fin) const
{
    String s = substr(debut, fin-debut+1);
    return s;
}

long int String::toInt() const
{
    /*
    * Pour utiliser std::stoi(const string&  str)
    * Settings -> Compiler -> Compiler settings -> Compiler Flags
    * -> cocher "Have g++ follow the C++11 ISO C++ language standard [-std=c++11]"
    */
    return std::stoi(*this);
}

void String::eliminerZeros(std::string& nbStr)
{
    for(int i = nbStr.size()-1; i>=0; i--)
    {
        if(nbStr.at(i) == '0')
        {
            nbStr.pop_back();
        }
        else
        {
            break;
        }
    }
}

String& String::operator =(std::string const& str)
{
    String s = String(str);
    return s;
}

String& String::operator =(const char c[])
{
    String s = String(c);
    return s;
}

/*
String& operator+(std::string const& str1, std::string const& str2)
{
    String somme = str1;
    somme += str2;
    return somme;
}

String& operator+(std::string const& str, const char c[])
{
    String nouvelle = c;
    return str + nouvelle;
}

String& operator+(const char c[], std::string const& str)
{
    String nouvelle = c;
    return nouvelle + str;
} //*/

/*
String& operator+(const char c1[], const char c2[]) const
{
    String str1 = c1;
    String str2 = c2;
    return str1 + str2;
} //*/

/*
String& String::operator+(const char c[]) const
{
    String str1 = *this;
    String str2 = c;
    return str1 + str2;
} //*/
