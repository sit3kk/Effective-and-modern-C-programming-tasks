#include <iostream>
#include <algorithm>
#include <memory>
#include "MyString.h"

class String
{
    using string = emcpp::MyString;
    std::shared_ptr<string> str;

public:
    String()
        : str(std::make_shared<string>()) {}

    String(const char *str)
        : str(std::make_shared<string>(str)) {}

    String(const String &s)
        : str(s.str) {}

    String operator=(const String &s)
    {
        if (this != &s)
        {
            this->str = s.str;
        }
        return *this;
    }

    void set(int index, char ch)
    {
        if (this->str.use_count() > 1)
        {
            this->str = std::make_shared<string>(*str);
        }
        (*this->str)[index] = ch;
    }

    char get(int index) const
    {
        if (index < 0 || index >= str->length())
        {
            return '\0';
        }
        return (*this->str)[index];
    }

    friend String operator+(String a, String b)
    {
        if (a.str->length() == 0)
        {
            return b;
        }
        if (b.str->length() == 0)
        {
            return a;
        }
        return String((*a.str + *b.str).c_str());
    }

    friend std::ostream &operator<<(std::ostream &out, String s)
    {
        out << *s.str;
        return out;
    }
};