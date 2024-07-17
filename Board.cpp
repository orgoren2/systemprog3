#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>

using namespace std;
#include "Board.hpp"
#include "Player.hpp"
#include "Catan.hpp"
#include "Tile.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Settlement.hpp"
#include "City.hpp"
#include "Road.hpp"

using namespace ariel;

Board::Board() : tiles(19, nullptr), vertices(54, nullptr), edges()
{
    initializeBoard();
}

// Destructor
Board::~Board()
{
    // Free memory for tiles
    for (size_t i = 0; i < 19; ++i)
    {
        delete this->tiles[i];
    }

    // Free memory for vertices
    for (size_t i = 0; i < 54; ++i)
    {
        delete this->vertices[i];
    }

    // Free memory for edges
    for (size_t i = 0; i < 54; ++i)
    {
        for (size_t j = 0; j < edges[i].size(); ++j)
        {
            delete this->edges[i][j];
        }
    }
}

// Initialize the board with tiles, vertices, and edges
void Board::initializeBoard()
{
    // Data for tiles: land type and number
    vector<pair<string, int>> tilesData = {
        {"Mountain", 10}, {"Meadow", 2}, {"Forest", 9}, 
        {"Agricultural land", 12}, {"Brick hills", 6}, 
        {"Meadow", 4}, {"Brick hills", 10}, {"Agricultural land", 9},
         {"Forest", 11}, {"Desert", 0}, {"Forest", 3}, {"Mountain", 8},
          {"Forest", 8}, {"Mountain", 3}, {"Agricultural land", 4}, 
          {"Meadow", 5}, {"Brick hills", 5}, {"Agricultural land", 6}, 
          {"Meadow", 7}};

    // Data for vertices of each tile
    vector<vector<size_t>> tilesVertices = {
        {0, 1, 2, 10, 9, 8}, {2, 3, 4, 12, 11, 10}, {4, 5, 6, 14, 13, 12}, 
        {7, 8, 9, 19, 18, 17}, {9, 10, 11, 21, 20, 19}, {11, 12, 13, 23, 22, 21},
        {13, 14, 15, 25, 24, 23}, {16, 17, 18, 29, 28, 27}, {18, 19, 20, 31, 30, 29}, 
        {20, 21, 22, 33, 32, 31}, {22, 23, 24, 35, 34, 33}, {24, 25, 26, 37, 36, 35}, 
        {28, 29, 30, 40, 39, 38}, {30, 31, 32, 42, 41, 40}, {32, 33, 34, 42, 43, 44}, 
        {34, 35, 36, 46, 45, 44}, {39, 40, 41, 49, 48, 47}, {41, 42, 43, 51, 50, 49}, 
        {43, 44, 45, 53, 52, 51}};

    // Data for edges connecting vertices
    vector<pair<size_t, size_t>> edgeVertices = {
        {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, 
        {0, 8}, {2, 10}, {4, 12}, {6, 14}, {7, 8}, {8, 9}, 
        {9, 10}, {10, 11}, {11, 12}, {12, 13}, {13, 14}, {14, 15},
         {7, 17}, {9, 19}, {11, 21}, {13, 23}, {15, 25}, {16, 17}, 
         {17, 18}, {18, 19}, {19, 20}, {20, 21}, {21, 22}, {22, 23}, 
         {23, 24}, {24, 25}, {25, 26}, {16, 27}, {18, 29}, {20, 31}, 
         {22, 33}, {24, 35}, {26, 37}, {27, 28}, {28, 29}, {29, 30}, 
         {30, 31}, {31, 32}, {32, 33}, {33, 34}, {34, 35}, {35, 36}, 
         {36, 37}, {28, 38}, {30, 40}, {32, 42}, {34, 44}, {36, 46}, 
         {38, 39}, {39, 40}, {40, 41}, {41, 42}, {42, 43}, {43, 44}, 
         {44, 45}, {45, 46}, {39, 47}, {41, 49}, {43, 51}, {45, 53}, 
         {47, 48}, {48, 49}, {49, 50}, {50, 51}, {51, 52}, {52, 53}};

    // Initialize vertices for the board
    for (size_t i = 0; i < 54; i++)
    {
        this->vertices[i] = new Vertex(i);
    }

    // Initialize tiles on the board
    for (size_t i = 0; i < 19; i++)
    {
        // Create a new tile with its data
        this->tiles[i] = new Tile(tilesData[i].first, tilesData[i].second);

        // Gather vertices adjacent to the current tile and set them for the tile
        vector<Vertex *> tiles_Vertices;
        for (size_t j = 0; j < 6; j++)
        {
            tiles_Vertices.push_back(this->vertices[tilesVertices[i][j]]);
        }
        this->tiles[i]->setAdjacentVertices(tiles_Vertices);
    }

    // Initialize edges on the board
    for (size_t i = 0; i < 72; i++)
    {
        for (size_t j = 0; j < 72; j++)
        {
            // Check if the current edge belongs to the vertex i
            if (edgeVertices[j].first == i || edgeVertices[j].second == i)
            {
                // Insert the current edge into the edges vector
                this->edges[i].push_back(new Edge(this->vertices[edgeVertices[j].first], this->vertices[edgeVertices[j].second]));
            }
        }
    }
}

// Distribute resources based on the dice roll
void Board::distribueResourcesByDice(int diceRoll)
{
    string land;
    // Iterate through all tiles on the board
    for (size_t i = 0; i < this->tiles.size(); i++)
    {
        // Check if the current tile's land number matches the dice roll
        if (this->tiles[i]->getLandNumber() == diceRoll &&this->tiles[i]->getLand() != "Desert")
        {
            // Set land as the correct resource the players should get
            land = setResourceToLand(this->tiles[i]->getLand());

            // Get all vertices adjacent to the current tile
            vector<Vertex*> adjacentVertices = this->tiles[i]->getAdjacentVertices();

            // Iterate through all adjacent vertices
            for (size_t j = 0; j < adjacentVertices.size(); j++)
            {
                
                // Get the structure (if any) on the current vertex
                Structure *structure = adjacentVertices[j]->getStructure();

                // If there is a structure on the vertex
                if (structure != nullptr)
                {
                    // Check if the structure is a settlement
                    if (structure->getType() == "settlement")
                    {
                        cout<<structure->getOwner()->getPlayerName()<<" got 1 "<<land<<" card from the dice roll!"<<endl;
                        // Add 1 land resource to the owner of the settlement
                        structure->getOwner()->addResource(land, 1);
                        
                    }
                    // Check if the structure is a city
                    else if (structure->getType() == "city")
                    {
                        cout<<structure->getOwner()->getPlayerName()<<" got 2 "<<land<<" card from the dice roll!!"<<endl;
                        // Add 2 land resources to the owner of the city
                        structure->getOwner()->addResource(land, 2);
                    }
                }
            }
        }
    }
}
//Side function for the distribute resource by dice function
string Board::setResourceToLand(string land)
{
    if (land == "Mountain")
    {
        return "Iron";
    }
    else if (land == "Brick hills")
    {
        return "Brick";
    }
    else if (land == "Meadow")
    {
    
        return "Wool";
    }
    else if (land == "Forest")
    {
        return "Wood";
    }
    return "Oats";
    
  
}

//Getters
vector<Vertex *> Board::getBoardVertices()
{
    return this->vertices;
}

map<size_t, vector<Edge *>> Board::getBoardEdge()
{
    return this->edges;
}

vector<Tile *> Board::getBoartTiles(){
    return this->tiles;
}


// Place a settlement on the board
bool Board::placeSettlement(Player &player, size_t vertexNum)
{
    // If the player entered invalid input, throw an exception
    if (vertexNum > 53 || vertexNum < 0)
    {
        cout<<"Invalid input, vertex index between 0 to 53"<<endl;
        return false;
    }

    // Check if the vertex already has a structure
    if (this->vertices[vertexNum]->getStructure() != nullptr)
    {
        cout<<"This place is not available"<<endl;
        return false;
    }

    // Check adjacent vertices for existing settlements
    for (auto &edge : this->edges[vertexNum])
    {
        Vertex *firstVertex = edge->getFirstVertex();
        Vertex *secondVertex = edge->getSecondVertex();

        if ((firstVertex == this->vertices[vertexNum] && secondVertex->getStructure() != nullptr) ||
            (secondVertex == this->vertices[vertexNum] && firstVertex->getStructure() != nullptr))
        {
            cout<<"This place is not available due to an adjacent settlement"<<endl;
            return false;
        }
    }

    // Create a new settlement and set it on the vertex
    Structure *settlement = new Settlement(player);
    this->vertices[vertexNum]->setStructure(settlement);
    cout<<player.getPlayerName()<<" placed settlement successfully on vertex "<<vertexNum<<endl;
    return true;
}

// Upgrade a settlement to a city on the board
bool Board::placeCity(Player &player, size_t vertexNum)
{
    // If the player entered invalid input, throww an exception
    if (vertexNum > 53 || vertexNum < 0)
    {
        cout<<"invalid input, vertex index between 0 to 53"<<endl;
        return false;
    }

    // Check if the vertex has a settlement owned by the player
    if (!this->vertices[vertexNum]->getStructure() || 
        this->vertices[vertexNum]->getStructure()->getType() != "settlement" ||
        this->vertices[vertexNum]->getStructure()->getOwner()->getPlayerName() != player.getPlayerName())
    {
        cout<<"You can build a city only on an existing settlement"<<endl;
        return false;
    }

    // Create a new city and set it on the vertex
    Structure *city = new City(player);
    this->vertices[vertexNum]->setStructure(city);
    cout<<player.getPlayerName()<<" placed city successfully on vertex "<<vertexNum<<endl;
    return true;
}

bool Board::placeRoad(Player &player, size_t firstVertex, size_t secondVertex)
{
    // If the player entered invalid input, throw an exception
    if (firstVertex > 53 || firstVertex < 0 || secondVertex > 53 || secondVertex < 0)
    {
        cout<<"Invalid input, vertices indexes between 0 to 53"<<endl;
        return false;
    }

    // Check if there is a structure belonging to the player in either vertex
    bool validPlacement = false;
    if (this->vertices[firstVertex]->getStructure() &&
        this->vertices[firstVertex]->getStructure()->getOwner()->getPlayerName() == player.getPlayerName())
    {
        validPlacement = true;
    }

    if (this->vertices[secondVertex]->getStructure() &&
        this->vertices[secondVertex]->getStructure()->getOwner()->getPlayerName() == player.getPlayerName())
    {
        validPlacement = true;
    }

    // Check if there is an existing road connected to either vertex
    for (auto &edge : this->edges[firstVertex])
    {
        Road *road = edge->getRoad();
        if (road && road->getOwner()->getPlayerName() == player.getPlayerName())
        {
            validPlacement = true;
            break;
        }
    }

    for (auto &edge : this->edges[secondVertex])
    {
        Road *road = edge->getRoad();
        if (road && road->getOwner()->getPlayerName() == player.getPlayerName())
        {
            validPlacement = true;
            break;
        }
    }

    if (!validPlacement)
    {
        cout<<"You can place a road only if the edge is connected to one of your structures or roads!"<<endl;
        return false;
    }
    
    // Search for the edge connecting the two vertices and ensure it's not already occupied
    bool edgeFound = false;
    for (auto &edge : this->edges[firstVertex])
    {
        if ((edge->getFirstVertex() == this->vertices[firstVertex] && edge->getSecondVertex() == this->vertices[secondVertex]) ||
            (edge->getFirstVertex() == this->vertices[secondVertex] && edge->getSecondVertex() == this->vertices[firstVertex]))
        {
            edgeFound = true;
            if (edge->getRoad() != nullptr)
            {
                cout<<"There is already a road on this edge!"<<endl;
                return false;
            }
            // Create a new road and set it on the edge
            Road road (player);
            edge->setRoad(road);
            cout <<player.getPlayerName()<< " placed road successfully between vertices " << firstVertex << " and " << secondVertex << endl;
            return true;
        }
    }

    if (!edgeFound)
    {
        cout<<"No edge connects these two vertices!"<<endl;
    }
    return false;
}
