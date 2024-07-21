#include <iostream>
using namespace std;
#include "Vertex.hpp"
#include "Road.hpp"
#include "Player.hpp"
#include "Edge.hpp"

namespace ariel
{
   

    // Setter for road
    void Edge::setRoad(Road* road)
    {
        this->road = road;
    }

    // Getter for road
    Road* Edge::getRoad()
    {
        return this->road;
    }

    // Getter for first vertex
    Vertex* Edge::getFirstVertex()
    {
        return this->firstVertex;
    }

    // Getter for second vertex
    Vertex* Edge::getSecondVertex()
    {
        return this->secondVertex;
    }
}
