#pragma once
#ifndef CITY_HPP
#define CITY_HPP

#include <iostream>
#include <string>
using namespace std;
#include "Structure.hpp"

namespace ariel
{
    class City : public Structure
    {
    public:
        City(Player &owner) : Structure(owner){};
        string getType() override;
    };
}

#endif // CITY_HPP
