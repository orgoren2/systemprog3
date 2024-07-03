#pragma once
#ifndef SETTLEMENT_HPP
#define SETTLEMENT_HPP

#include <iostream>
#include <string>
using namespace std;
#include "Structure.hpp"

namespace ariel
{
    class Settlement : public Structure
    {
    public:
        Settlement(Player &owner) : Structure(owner) {}
        ~Settlement() override = default;
        string getType() override;
    };
}

#endif // SETTLEMENT_HPP
