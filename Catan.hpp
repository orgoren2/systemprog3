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
    class Test;
    class Board;
    class Player;

    class Catan
    {
    private:
        Board *board;            
        Cards *cardsPack;         
        Player *currentPlayer;    
        vector<Player *> players; 
        friend class Test;
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
        void buyDevelopmentCard(Player &player);
        void useMonopolyCard(Player &player, string wantedResource);
        void useBuildRoadsCard(Player &player, size_t sV1, size_t fV1, size_t sV2, size_t fV2);
        void useAbundantYearCard(Player &player, string firstWantedCard, string secondWantedCard);
        void tradeWithBank(Player &player, string playerResource, string wantedResource);
        void tradeResourcesWithPlayers(Player &player, Player &otherPlayer, string playerResource, string otherResource, int giveQuantity, int takeQuantity);
        void tradeCardsWithPlayers(Player &player, Player &otherPlayer, string playerCard, string otherResource, int giveQuantity, int takeQuantity);


        Player &getCurrentPlayer();
        vector<Player *> getPlayersOrder();
        void firstTurn(Player& player,size_t firstSettlement, size_t firstRoad1,size_t firstRoad2, size_t secondSettlement, size_t secondRoad1,size_t secondRoad2);
        void placeSettlement(Player &player, size_t vertexNum);
        void placeCity(Player &player, size_t vertexNum);
        void placeRoad(Player &player, size_t firstVertex, size_t secondVertex);

        vector<Vertex *> getBoardVertices();
        map<size_t, vector<Edge *>> getBoardEdge();
    };
}

#endif // CATAN_HPP
