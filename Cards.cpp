#include <iostream>
#include <map>
#include "Cards.hpp"

using namespace ariel;

Cards::Cards()
{
    initializeCardsPack();
    this->biggestArmyCard = 3; // Initialize the biggest army card count
}

// Initializing game's cards pack
void Cards::initializeCardsPack()
{
    this->cardsPack["knight card"] = 10;
    this->cardsKind.push_back("knight card");

    this->cardsPack["monopoly card"] = 10;
    this->cardsKind.push_back("monopoly card");

    this->cardsPack["build roads card"] = 10;
    this->cardsKind.push_back("build roads card");

    this->cardsPack["abundant year card"] = 10;
    this->cardsKind.push_back("abundant year card");

    this->cardsPack["victory point card"] = 4;
    this->cardsKind.push_back("victory point card");
}

// Method to draw a card randomly from the pack
string Cards::drawCard()
{
    srand(time(0));
    int index = rand() % (int)(this->cardsKind.size());
    string card = this->cardsKind[(size_t)index];

    // Ensure the drawn card has remaining quantity in the pack
    while (cardsPack[card] == 0)
    {
        index = rand() % (int)(cardsKind.size());
        card = cardsKind[(size_t)index];
    }
    return card;
}

// Method to get the current cards pack
map<string, int> Cards::getCardsPack()
{
    return this->cardsPack;
}

// Method to get the types of cards
vector<string> Cards::getCardsKind()
{
    return this->cardsKind;
}


// Method to increase the quantity of a specific card
void Cards::increaseCardQuantity(string card)
{
    this->cardsPack[card] += 1;
}

// Method to increase the quantity of the biggest army card
void Cards::increaseBiggestArmyCardQuantity()
{
    this->biggestArmyCard += 1;
}

// Method to decrease the quantity of a specific card
void Cards::decreaseCardQuantity(string card)
{
    this->cardsPack[card] -= 1;
}

// Method to decrease the quantity of the biggest army card
bool Cards::decreaseBiggestArmyCardQuantity()
{
    if (this->biggestArmyCard > 0)
    {
        this->biggestArmyCard -= 1;
        return true;
    }
    return false;
}
