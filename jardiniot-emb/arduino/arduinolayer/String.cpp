// Copyright (C) 2018 Guyllaume Rousseau
// Copyright (C) 2018 Io Andes Daza-Dillon
//
// JardinIoT is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// JardinIoT is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with JardinIoT.  If not, see <http://www.gnu.org/licenses/>.

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

bool String::concat(std::string str)
{
    this->append(str);
    return true;
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
    return substr(debut, fin-debut);
}

long int String::toInt() const
{
    return std::stoi(*this);
}

String& String::operator=(std::string const& str)
{
    auto this_str = static_cast<std::string*>(this);
    *this_str = str;
    return *this;
}

String& String::operator=(const char c[])
{
    auto this_str = static_cast<std::string*>(this);
    *this_str = c;
    return *this;
}

String String::operator+(long unsigned int arg)
{
    return *this+std::to_string(arg);
}
