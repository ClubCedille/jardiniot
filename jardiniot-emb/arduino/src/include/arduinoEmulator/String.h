// https://github.com/GRV96/ArduinoString/blob/master/include/String.h
#ifndef STRING_H
#define STRING_H

#include <string>

//typedef uint8_t byte;
typedef unsigned char byte;

class String : public std::string
{
    public:

        // Constructeurs
        String();
        String(std::string const& str);
        String(unsigned int n, char c);
        template<typename T>
        String(T* c) : std::string(c) {};
        template<typename T>
        String(T nombre) : std::string(std::to_string(nombre)) {};

        // Destructeur
        virtual ~String();

        // M�thodes � adapter
        char charAt(unsigned int indice) const;
        int compareTo(String const& str) const;
        bool concat(int nombre);
        bool concat(double nombre);
        bool concat(const char* s);
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

    private:

        /**
        * \brief Instructions � effectuer pour instancier une cha�ne de
        *       caract�res � partir d'un nombre, quel que soit son type.
        * \param nombre
        *       Nombre � convertir en cha�ne de caract�res
        */
        template<typename T>
        void convertirNombre(T nombre);

        /**
        * \brief Efface les z�ros � la fin d'une cha�ne de caract�res
        *       repr�sentant un nombre. Utilis�e si le nombre n'est pas entier.
        * \param nbStr
        *       Cha�ne de caract�res repr�sentant un nombre non entier.
        */
        static void eliminerZeros(std::string& nbStr);
};

#endif // STRING_H
