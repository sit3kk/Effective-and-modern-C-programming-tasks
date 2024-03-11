#include <iostream>
#include <algorithm>
#include <memory>
#include "MyString.h"


class String{
    using string = emcpp::MyString;
//    using string = std::string;
    std::shared_ptr<string> pStr;

/// Store a pointer to dynamically allocated string!

public:
    String() : pStr(std::make_shared<string>()) {}     /// creates an empty string

    String(const char * str) : pStr(std::make_shared<string>(str)) {}         /// copy C-string

    String(const String & ) = default;            /// no copy

    String& operator=(const String & s) = default; /// no copy

    /// makes a copy of a string if it has more than one reference.
    void set(int index, char ch) {
        
        if (!pStr.unique()) {
            pStr = std::make_shared<string>(*pStr);
        }
        (*pStr)[index] = ch;
    }

    /// no copy
    char get(int index) const {
        return (*pStr)[index];
    }
    /// creates a new string only if both strings are non empty
    friend String operator+(String a, String b) {

        if (a.pStr->empty()) return b;
        if (b.pStr->empty()) return a;
        return String((*a.pStr + *b.pStr).c_str());
        
    }

    
    friend std::ostream & operator<< (std::ostream & out, String s) {
        out << *(s.pStr); 
        return out;
    }
};
