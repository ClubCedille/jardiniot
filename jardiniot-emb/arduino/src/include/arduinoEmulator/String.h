#ifndef STRING_H
#define STRING_H

#include <sstream>
#include <string>

typedef unsigned int byte;
typedef bool boolean;

class String
{
public:
    String(){};
    String(std::string str) {this->str = str;};
    String(char *str) {this->str = str;};
    String(byte n) {this->str = this->numberToString(n);};

    int toInt() {std::stringstream ss(this->str); int num; ss>>num; return num;};
    int indexOf(char c) const {return this->str.find(c);};
    String substring(size_t pos = 0, size_t len = std::string::npos) const {return this->str.substr(pos, len);};
    void remove(size_t pos = 0, size_t len = std::string::npos) {this->str.erase(pos, len);};
    bool concat(std::string str2) {this->str.append(str2); return true;}; // bool juste pour correspondre à la fonction du arduino
    std::string operator+(std::string str2) {return this->str+str2;};
    bool concat(int n) {this->str.append(numberToString(n)); return true;};
    size_t length() {return this->str.length();};
    char operator[](std::size_t i) {return this->str[i];};

    bool operator==(std::string str2) {return this->str == str2;};
    bool compareTo(std::string str2) {return this->str == str2;};
    bool operator!=(String str2) {return !(str2 == this->str);};
    friend std::ostream &operator<<(std::ostream &os, const String str) {os<<(str.str); return os;};


    std::string str;

private:
    std::string numberToString(int n) {
        std::ostringstream oss;
        oss << n;
        return oss.str();
    };
};

std::string operator+(std::string str, String str2);

#endif // STRING_H
