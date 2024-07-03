#pragma once
#ifndef CATAN_HPP
#define CATAN_HPP

#include <iostream>
#include <vector>
#include <map>
using namespace std;
#include "Player.hpp"
#include "Board.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"

namespace ariel
{
    class Board;
    class Player;

    class Catan
    {
    private:
        Board *board;       
        Cards *cardsPack;         
        Player *currentPlayer;    
        vector<Player *> players; 
        void checkIncreaseBiggestArmyCard(Player &player); 
        void checkReduceBiggestArmyCard(Player &player);   
        bool isPlayersTurn(Player &player);               
       

    public:
        Catan(Player &p1, Player &p2, Player &p3, Board &board, Cards &cardsPack);
        ~Catan(); // Destructor

        void setPlayerTurnsOrder();
        void setBoard(Board &board);
        bool checkVictory(Player &player) const;
        void endTurn();
        int rollDice(Player &player);
        bool buyDevelopmentCard(Player &player);
        bool useMonopolyCard(Player &player, string wantedResource);
        bool useBuildRoadsCard(Player &player, size_t sV1, size_t fV1, size_t sV2, size_t fV2);
        bool useAbundantYearCard(Player &player, string firstWantedCard, string secondWantedCard);
        bool tradeWithBank(Player &player, string playerResource, string wantedResource);
        bool tradeResourcesWithPlayers(Player &player, Player &otherPlayer, string playerResource, string otherResource, int giveQuantity, int takeQuantity);
        bool tradeCardsWithPlayers(Player &player, Player &otherPlayer, string playerCard, string otherResource, int giveQuantity, int takeQuantity);


        Player &getCurrentPlayer();
        vector<Player *> getPlayersOrder();
        void firstTurn(Player& player,size_t firstSettlement, size_t firstRoad1,size_t firstRoad2, size_t secondSettlement, size_t secondRoad1,size_t secondRoad2);
        bool placeSettlement(Player &player, size_t vertexNum);
        bool placeCity(Player &player, size_t vertexNum);
        bool placeRoad(Player &player, size_t firstVertex, size_t secondVertex);

        vector<Vertex *> getBoardVertices();
        map<size_t, vector<Edge *>> getBoardEdge();
    };
}

#endif // CATAN_HPP
