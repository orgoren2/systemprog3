#include <iostream>
using namespace std;
#include "City.hpp"

namespace ariel
{
    // Constructor initializing with owner
    City::City(Player &owner) : Structure(owner)
    {
    }

    // Override getType function to return "city"
    string City::getType()
    {
        return "city";
    }
}
