#pragma once
#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;
#include "Player.hpp"
#include "Tile.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"

namespace ariel
{

    class Tile;
    class Vertex;
    class Edge;
    class Board
    {
    private:
        vector<Tile *> tiles;
        vector<Vertex *> vertices;
        map<size_t, vector<Edge *>> edges;
        

    public:
        Board();
        void initializeBoard();
        void distribueResourcesByDice(int diceRoll);
        bool placeSettlement(Player &player, size_t vertexNum);
        bool placeCity(Player &player, size_t vertexNum);
        bool placeRoad(Player &player, size_t firstVertex, size_t secondVertex);
        vector<Vertex *> getBoardVertices();
        map<size_t, vector<Edge *>> getBoardEdge();
        vector<Tile *> getBoartTiles();
        string setResourceToLand(string land);
    };
}

#endif // BOARD_HPP
