    #pragma once
    #ifndef TILE_HPP
    #define TILE_HPP

    #include <iostream>
    #include <map>
    #include <vector>
    using namespace std;
    #include "Vertex.hpp"

    namespace ariel
    {
        class Vertex;

        class Tile
        {
        private:
            string land;
            int landNumber;
            vector<Vertex *> adjacentVertices;

        public:
            Tile(string land, int landNumber);
            ~Tile();
            string getLand();
            int getLandNumber();
            void setAdjacentVertices(vector<Vertex *> &adjacentVertices);
            vector<Vertex *> &getAdjacentVertices();
        };
    }

    #endif // TILE_HPP
