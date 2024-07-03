#pragma once
#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include <iostream>
#include <string>
using namespace std;
#include "Player.hpp"

namespace ariel
{
    class Player;
    class Structure
    {
    protected:
        Player *owner;

    public:
        Structure() : owner(nullptr) {}; 
        Structure(Player &owner);
        Player* getOwner();
        virtual string getType();  
        virtual ~Structure() = default; 
    };
}

#endif // STRUCTURE_HPP
