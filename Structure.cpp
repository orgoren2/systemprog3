#include <iostream>
using namespace std;
#include "Player.hpp"  
#include "Structure.hpp"  

namespace ariel
{
    // Constructor initializing owner
    Structure::Structure(Player& owner) : owner(&owner) {}

    // Get the owner of the structure
    Player* Structure::getOwner() 
    {
        return this->owner;
    }
    // Get the type of the structure (default implementation)
    string Structure::getType()
    {
        return string();
    }
}