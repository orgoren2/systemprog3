    #pragma once
    #ifndef ROAD_HPP
    #define ROAD_HPP

    #include <iostream>
    using namespace std;
    #include "Player.hpp"

    namespace ariel
    {
        class Player;

        class Road
        {
        private:
            Player *owner;

        public:
            Road() : owner(nullptr) {}
            Road(Player &owner) : owner(&owner) {}
            Player *getOwner();
        };
    }

    #endif // ROAD_HPP
