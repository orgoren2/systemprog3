#include <iostream>
using namespace std;
#include "Structure.hpp"
#include "Settlement.hpp"

namespace ariel
{
    // Override the getType method to return "settlement"
    string Settlement::getType()
    {
        return "settlement";
    }
}
