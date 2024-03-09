#pragma once
#include <iostream>
#include "Box.h"

// Exercise: modify code so that appropriate constructor and operators are called using just default and delete keyword.
class Container : public Box {
public:
    static bool verbose;
    Container(int content):Box(content) {};                  // implement
    Container(const Container & container) = delete;     // disable
 	Container & operator=(const Container &container) = delete; // disable

	Container(Container && container): Box(std::move(container)) {};           // enable
  	Container & operator=(Container &&container)
    {
        if (this != &container) 
        {
            Box::operator=(std::move(container));
        };

        return *this;
        
    };       // enable
    ~Container();                                      // enable

    friend Container operator+(const Container & p1, const Container & p2);
    friend std::ostream & operator << (std::ostream & out, const Container & p){
        return (out << " [" << p.getContent() << "] ");
    }
};
bool Container::verbose = false;

inline Container operator+(const Container & p1, const Container & p2){
    Container suma(p1.getContent() + p2.getContent());
    return suma;
}