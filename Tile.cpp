#include <iostream>
using namespace std;
#include "Tile.hpp"

namespace ariel
{
    // Constructor initializing land and landNumber
    Tile::Tile(string land, int landNumber)
    {
        this->land = land;
        this->landNumber = landNumber;
    }

    // Destructor
    Tile::~Tile()
    {
        adjacentVertices.clear();
    }

    // Get the type of land
    string Tile::getLand()
    {
        return this->land;
    }

    // Get the number associated with the land
    int Tile::getLandNumber()
    {
        return this->landNumber;
    }

    // Set the adjacent vertices
    void Tile::setAdjacentVertices(vector<Vertex*>& adjacentVertices)
    {
        this->adjacentVertices = adjacentVertices;
    }

    // Get the adjacent vertices
    vector<Vertex*>& Tile::getAdjacentVertices()
    {
        return this->adjacentVertices;
    }
}
