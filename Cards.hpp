#pragma once
#ifndef CARDS_HPP
#define CARDS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

namespace ariel
{
    class Cards
    {
    private:
        map<string, int> cardsPack;
        vector<string> cardsKind;
        int biggestArmyCard;

    public:
        Cards();
        void initializeCardsPack();
        map<string, int> getCardsPack();
        vector<string> getCardsKind();
        void increaseCardQuantity(string card);
        void increaseBiggestArmyCardQuantity();
        void decreaseCardQuantity(string card);
        bool decreaseBiggestArmyCardQuantity();
        string drawCard();
    };
}

#endif // CARDS_HPP
