#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#include "Player.hpp"
#include "Cards.hpp"
using namespace ariel;


Player::Player(string name, int age) : name(name), age(age), victoryPoints(0), game(nullptr)
{
    initializeResources();
    initializeCards();
}

// Initialize player's resources with default values
void Player::initializeResources()
{
    this->resources["Wood"] = 1;
    this->resources["Brick"] = 1;
    this->resources["Wool"] = 1;
    this->resources["Oats"] = 1;
    this->resources["Iron"] = 1;
}

// Initialize player's cards with default values
void Player::initializeCards()
{
    this->cards["knight card"] = 0;
    this->cards["victory card"] = 0;
    this->cards["biggest army card"] = 0;
    this->cards["monopoly card"] = 0;
    this->cards["build roads card"] = 0;
    this->cards["abundant year card"] = 0;
    this->cards["victory point card"] = 0;
}

void Player::firstTurn(size_t firstSettlement, size_t firstRoad1,size_t firstRoad2, size_t secondSettlement, size_t secondRoad1,size_t secondRoad2){
    this->game->firstTurn(*this, firstSettlement, firstRoad1, firstRoad2, secondSettlement,secondRoad1,secondRoad2);
}

// Roll the dice for the player using the game instance
int Player::rollDice()
{
   return this->game->rollDice(*this);
}

// Buy a development card using the game instance
bool Player::buyDevelopmentCard()
{
    return this->game->buyDevelopmentCard(*this);
}

// Use a monopoly card using the game instance
bool Player::useMonopolyCard(string wantedResource)
{
    return this->game->useMonopolyCard(*this, wantedResource);
}

// Use a build roads card using the game instance
bool Player::useBuildRoadsCard(size_t sV1, size_t fV1, size_t sV2, size_t fV2)
{
    return this->game->useBuildRoadsCard(*this, sV1, fV1, sV2, fV2);
}

// Use an abundant year card using the game instance
bool Player::useAbundantYearCard(string firstWantedCard, string secondWantedCard)
{
    return this->game->useAbundantYearCard(*this, firstWantedCard, secondWantedCard);
}

// Place a settlement using the game instance
bool Player::placeSettlement(size_t vertexNum)
{
    return this->game->placeSettlement(*this, vertexNum);
}

// Place a city using the game instance
bool Player::placeCity(size_t vertexNum)
{
    return this->game->placeCity(*this, vertexNum);
}

// Place a road using the game instance
bool Player::placeRoad(size_t firstVertex, size_t secondVertex)
{
    return this->game->placeRoad(*this, firstVertex, secondVertex);
}

// Trade with the bank using the game instance
bool Player::tradeWithBank(string playerResource, string wantedResource)
{
    return this->game->tradeWithBank(*this, playerResource, wantedResource);
}

// Trade resources with other players using the game instance
bool Player::tradeResourcesWithPlayers(Player& otherPlayer, string playerResource, string otherResource, int giveQuantity, int takeQuantity)
{
    return this->game->tradeResourcesWithPlayers(*this, otherPlayer, playerResource, otherResource, giveQuantity, takeQuantity);
}

// Trade cards with other players using the game instance
bool Player::tradeCardsWithPlayers(Player& otherPlayer, string playerCard, string otherResource, int giveQuantity, int takeQuantity)
{
    return this->game->tradeCardsWithPlayers(*this, otherPlayer, playerCard, otherResource, giveQuantity, takeQuantity);
}

// Set the game instance for the player
void Player::setGame(Catan& game)
{
    this->game = &game;
}

// Get the player's name
string Player::getPlayerName() const
{
    return this->name;
}

// Get the player's age
int Player::getPlayerAge() const
{
    return this->age;
}

// Get the player's victory points
int Player::getVictoryPoints() const
{
    return this->victoryPoints;
}

// Add victory points to the player
void Player::addVictoryPoints(int num)
{
    this->victoryPoints += num;
}

// Reduce victory points for the player
void Player::reduceVictoryPoints(int num)
{
    this->victoryPoints -= num;
}

// Get the count of a specific resource
int Player::getResourceCount(string resource)
{
    return this->resources[resource];
}

// Add a specified amount of a resource to the player
void Player::addResource(string resource, int amount)
{
    this->resources[resource] += amount;
}

// Reduce a specified amount of a resource for the player
void Player::reduceResource(string resource, int amount)
{
    this->resources[resource] -= amount;
}

// Get the count of a specific card
int Player::getCardCount(string card)
{
    return this->cards[card];
}

// Add a card to the player's collection
void Player::addCard(string card)
{
    this->cards[card] += 1;
}

// Reduce the count of a specific card for the player
void Player::reduceCardCount(string card, int amount)
{
    this->cards[card] -= amount;
}
