#include <iostream>
#include <vector>
using namespace std;
#include "Tile.hpp"
#include "Structure.hpp" 
#include "Vertex.hpp"

namespace ariel
{
    // Destructor 
    Vertex::~Vertex()
    {
        delete structure; 
    }

    // Set the structure for the vertex
    void Vertex::setStructure(Structure *structure)
    {
        this->structure = structure;
    }

    // Get the structure associated with the vertex
    Structure *Vertex::getStructure()
    {
        return this->structure;
    }

    // Get the vertex number
    int Vertex::getVertexNumber()
    {
        return this->vertexNumber;
    }
}
