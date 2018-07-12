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

#ifndef STRING_H
#define STRING_H

#include <string>

typedef uint8_t byte;

class String : public std::string
{
    public:

        // Constructeurs
        String();
        String(std::string const& str);
        String(unsigned int n, char c);
        template<typename T>
        String(T* c) : std::string(c) {}
        template<typename T>
        String(T nombre) : std::string(std::to_string(nombre)) {}

        // Destructeur
        virtual ~String();

        // Méthodes à adapter
        char charAt(unsigned int indice) const;
        int compareTo(String const& str) const;
        template<typename T>
        bool concat (T* c) {append(c); return true;}
        template<typename T>
        bool concat (T nombre) {append(std::to_string(nombre)); return true;}
        bool concat(std::string str);
        int indexOf(char c, unsigned int indice=0) const;
        int indexOf(const char* c, unsigned int indice=0) const;
        int indexOf(String const& str, unsigned int indice=0) const;
        unsigned int length() const;
        void remove(unsigned int debut, unsigned int nbr);
        String substring(unsigned int debut, unsigned int fin) const;
        long int toInt() const;

        String& operator=(std::string const& str);
        String& operator=(const char c[]);

        String operator+(long unsigned int arg);
        template<typename T>
        String operator+(T arg) {
            std::string* str_this = static_cast<std::string*>(this);
            return *str_this+arg;
        }
};

#endif // STRING_H
