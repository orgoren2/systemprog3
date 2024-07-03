#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <map>
#include <vector>
using namespace std;
#include "Cards.hpp"
#include "Catan.hpp"

namespace ariel
{
    class Catan;

    class Player
    {
    private:
        int victoryPoints;
        string name;
        int age;
        map<string, int> resources;
        map<string, int> cards;
        Catan *game;

    public:
        Player() : name(""), age(0), victoryPoints(0), game(nullptr) {}
        Player(string name, int age);

        // Initialize resources
        void initializeResources();

        // Initialize cards
        void initializeCards();

        // Gameplay functions
        void firstTurn(size_t firstSettlement, size_t firstRoad1,size_t firstRoad2, size_t secondSettlement, size_t secondRoad1,size_t secondRoad2);
        int rollDice();
        void tradeWithBank(string playerResource, string wantedResource);
        void tradeResourcesWithPlayers(Player &otherPlayer, string playerResource, string otherResource, int giveQuantity, int takeQuantity);
        void tradeCardsWithPlayers(Player &otherPlayer, string playerCard, string otherResource, int giveQuantity, int takeQuantity);
        void buyDevelopmentCard();
        void useMonopolyCard(string wantedResource);
        void useBuildRoadsCard(size_t sV1, size_t fV1, size_t sV2, size_t fV2);
        void useAbundantYearCard(string firstWantedCard, string secondWantedCard);
        void placeSettlement(size_t vertexNum);
        void placeCity(size_t vertexNum);
        void placeRoad(size_t firstVertex, size_t secondVertex);

        // Setters and getters
        void setGame(Catan &game);
        string getPlayerName() const;
        int getPlayerAge() const;
        int getVictoryPoints() const;
        void addVictoryPoints(int num);
        void reduceVictoryPoints(int num);
        void addResource(string resource, int amount);
        void reduceResource(string resource, int amount);
        int getResourceCount(string resource);
        void addCard(string card);
        void reduceCardCount(string card, int amount);
        int getCardCount(string card);
    };
}

#endif // PLAYER_HPP
