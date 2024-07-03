#include <iostream>
using namespace std;
#include "Player.hpp"
#include "Road.hpp"

namespace ariel
{
    // Get the owner of the road
    Player* Road::getOwner()
    {
        return this->owner;
    }
}
