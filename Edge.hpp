#pragma once
#ifndef EDGE_HPP
#define EDGE_HPP

#include <iostream>
#include <vector>
using namespace std;
#include "Vertex.hpp"
#include "Road.hpp"
#include "Player.hpp"

namespace ariel
{
    class Vertex;
    class Player;

    class Edge
    {
    private:
        Vertex *firstVertex;
        Vertex *secondVertex;
        Road *road;

    public:
        Edge(Vertex &firstVertex, Vertex &secondVertex);
        Edge(Vertex *firstVertex, Vertex *secondVertex);
        
        // Getters and setters
        void setRoad(Road *road);
        Road *getRoad();
        Vertex *getFirstVertex();
        Vertex *getSecondVertex();
    };
}

#endif // EDGE_HPP
