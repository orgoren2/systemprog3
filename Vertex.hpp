#pragma once
#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>
#include <vector>
using namespace std;
#include "Tile.hpp"
#include "Structure.hpp"

namespace ariel
{
    class Structure;
    class Vertex
    {
    private:
        Structure *structure;
        int vertexNumber;

    public:
        Vertex(int vertexNumber) : vertexNumber(vertexNumber), structure(nullptr){};
        ~Vertex();
        void setStructure(Structure *structure);
        Structure *getStructure();
        int getVertexNumber();
    };
}

#endif // VERTEX_HPP
