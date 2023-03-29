#include "card.hpp"
#include <string>
#include<iostream>

using namespace std;
using namespace ariel;

namespace ariel{
    
    Card::Card(int newValue, string newType, string newName) {
        value = newValue;
        type = newType;
        name = newName;
    }

    void Card::setValue(int newValue) {
        value = newValue;
    }

    void Card::setType(string newType) {
        type = newType;
    }

    void Card::setName(string newName) {
        name = newName;
    }

    bool Card::operator<(const Card &Crad2){return this->value < Crad2.value;}
    bool Card::operator==(const Card &Crad2){return this->value == Crad2.value;}

    string Card::to_string() {
        string str = std::to_string(value);
        // [Card: ("Queen", Diamonds, 12)]
        return "[Card: ("+name+","+type+","+str+")]";
    }
}