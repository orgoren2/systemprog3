#include <iostream>
#include <stdexcept>

using namespace std;
#include "Catan.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
using namespace ariel;

Catan::Catan(Player &p1, Player &p2, Player &p3, Board &board, Cards &cardspack)
{
    this->players.push_back(&p1);
    p1.setGame(*this);
    this->players.push_back(&p2);
    p2.setGame(*this);
    this->players.push_back(&p3);
    p3.setGame(*this);
    this->currentPlayer = nullptr;
    this->board = &board;
    this->cardsPack = &cardspack;
    srand(time(0));
}


// Setting the players turns order
void Catan::setPlayerTurnsOrder()
{
    Player *temp;
    // Order the players turns by the age
    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 2; j++)
        {
            if (this->players[j]->getPlayerAge() < this->players[j + 1]->getPlayerAge())
            {
                temp = this->players[j + 1];
                this->players[j + 1] = this->players[j];
                this->players[j] = temp;
            }
        }
        this->currentPlayer = this->players[0];
    }
    // Print the turns order
    cout << this->players[0]->getPlayerName() << " is starting the game, " << this->players[1]->getPlayerName() << " will play next and  "
         << this->players[2]->getPlayerName() << " will be the last" << endl;
}

void Catan::setBoard(Board &board)
{
    this->board = &board;
}
//Check if it's the player's turn
bool Catan::isPlayersTurn(Player &player)
{
    if (this->currentPlayer->getPlayerName() != player.getPlayerName())
    {
        cout<<"It's not your turn"<<endl;
        return false;
    }
    return true;
}

// Check if the player has reached the required points for victory
bool Catan::checkVictory(Player &player) const
{
    if (player.getVictoryPoints() >= 10)
    {
        cout << player.getPlayerName() << " won the game!" << endl;
        return true;
    }
    return false;
}

// The player gets a card when buying a development card
bool Catan::buyDevelopmentCard(Player &player)
{
    if (isPlayersTurn(player))
    {
        // Checking if the player has enough resources to buy a card
        if (player.getResourceCount("Iron") < 1 || player.getResourceCount("Wool") < 1 || player.getResourceCount("Oats") < 1)
        {
            cout<<"You don't have enough resources for buying a development card"<<endl;
            return false;
        }
        string card = this->cardsPack->drawCard();

        /* Checking if the card is knight card, if it does and the player already have two knight cards,
           the player also gets the biggest army card
        */
        if (card == "knight card")
        {
            checkIncreaseBiggestArmyCard(player);
        }
        if (card == " victory point card")
        {
            player.addVictoryPoints(1);
        }
        // Reducing the chosen card from the pack
        this->cardsPack->decreaseCardQuantity(card);
        // Adding the card to the player's cards pack
        player.addCard(card);
        cout << player.getPlayerName() << " bought " << card << " card" << endl;
        return true;
    }
    return false;
}

// Side function for checking if the player needs to get the biggest army card
void Catan::checkIncreaseBiggestArmyCard(Player &player)
{
    // If the player has 2 knight cards
    if (player.getCardCount("knight card") == 2)
    {
        // If there are biggest army cards in the pack
        if (this->cardsPack->decreaseBiggestArmyCardQuantity())
        {
            // Adding the biggest army card to the player's cards pack and giving him two victory points
            player.addCard("biggest army card");
            player.addVictoryPoints(2);
        }
    }
}

// Side function for checking if we need to take the biggest army card from the player
void Catan::checkReduceBiggestArmyCard(Player &player)
{
    // If the player has 2 knight cards
    if (player.getCardCount("knight card") == 3)
    {
        // Taking the biggest army card from the player's cards pack and reducing him two victory points
        player.reduceCardCount("biggest army card", 1);
        player.reduceVictoryPoints(2);
        this->cardsPack->increaseBiggestArmyCardQuantity();
    }
}

// The player takes all the selected resource cards from other players
bool Catan::useMonopolyCard(Player &player, string wantedResource)
{
    if (isPlayersTurn(player))
    {
        // Checking if the player has monopoly card
        if (player.getCardCount("monopoly card") == 0)
        {
            cout<<" You don't have monopoly cards"<<endl;
            return false;
        }

        else
        {
            // Getting from the other players the wanted resource
            for (size_t i = 0; i < 3; i++)
            {
                if (this->players[i]->getPlayerName() != player.getPlayerName())
                {
                    // If the other player have the wanted resource, he will give it to the player
                    if (this->players[i]->getResourceCount(wantedResource) > 0)
                    {
                        this->players[i]->reduceResource(wantedResource, 1);
                        player.addResource(wantedResource, 1);
                    }
                }
                
            }
            // Returning the monopoly card to the game's card pack
            player.reduceCardCount("monopoly card", 1);
            this->cardsPack->increaseCardQuantity("monopoly card");
            return true;        
        }
    }
    return false;
}

// The player gets 2 roads without resources cost
bool Catan::useBuildRoadsCard(Player &player, size_t sV1, size_t fV1, size_t sV2, size_t fV2)
{
    if (isPlayersTurn(player))
    {
        // Checking that the player has the build roads card
        if (player.getCardCount("build roads card") == 0)
        {
            cout<<" You don't have build roads card"<<endl;
            return false;
        }
        else
        {
            this->board->placeRoad(player, sV1, fV1);
            this->board->placeRoad(player, sV2, fV2);
            // Returning the build roads card to the game's card pack
            player.reduceCardCount("build roads card", 1);
            this->cardsPack->increaseCardQuantity("build roads card");
            return true;
        }
    }
    return false;
}

// The player gets the first 2 selected cards for free
bool Catan::useAbundantYearCard(Player &player, string firstWantedCard, string secondWantedCard)
{
    if (isPlayersTurn(player))
    {
        // Checking that the player has the abundant year card
        if (player.getCardCount("abundant year card") == 0)
        {
            cout<<" You don't have abundant year cards"<<endl;
            return false;
        }
        else
        {
            // Adding the player the resources he chose
            player.addResource(firstWantedCard, 1);
            player.addResource(secondWantedCard, 1);
            // Returning the abundant year card to the game's card pack
            player.reduceCardCount("abundant year card", 1);
            this->cardsPack->increaseCardQuantity("abundant year card");
            return true;
        }
    }
    return false;
}

// The player trades 4 of their resources for 1 of the bank's resources
bool Catan::tradeWithBank(Player &player, string playerResource, string wantedResource)
{

    if (isPlayersTurn(player))
    {
        // Checking if the player has at least 4 resources cards
        if (player.getResourceCount(playerResource) < 4)
        {
            cout<<"You don't have enough resources to trade"<<endl;
            return false;
        }
        else
        {
            player.reduceResource(playerResource, 4);
            player.addResource(wantedResource, 1);
            return true;
        }
    }
    return false;
}

// Trading resources with other players
bool Catan::tradeResourcesWithPlayers(Player &player, Player &otherPlayer, string playerResource, string otherResource, int giveQuantity, int takeQuantity)
{
    if (isPlayersTurn(player))
    {
        /*
        string answer;
        cout << "Hey " << otherPlayer.getPlayerName() << ", " << player.getPlayerName() << " wants to trade with you " << giveQuantity << " " << playerResource
            << " in exchange for " << takeQuantity << " " << otherResource << ". Would you like to trade?" << endl;
        cin >> answer;
        if (answer == "yes")
        {
            */
        // Checking if the player has enough recource cards to trade
        if (player.getResourceCount(playerResource) < giveQuantity)
        {
            cout<<"You don't have enough to trade."<<endl;
            return false;
        }
        // Checking if the other player has enough recource cards to trade
        if (otherPlayer.getResourceCount(otherResource) < takeQuantity)
        {
            cout<<"The other player doesn't have enough to trade."<<endl;
            return false;
        }

        // Updating the resources of each of the players
        player.addResource(otherResource, takeQuantity);
        player.reduceResource(playerResource, giveQuantity);
        otherPlayer.addResource(playerResource, giveQuantity);
        otherPlayer.reduceResource(otherResource, takeQuantity);
        return true;
        /**
          }
         The other player doesn't want to trade
        else
        {
            cout << otherPlayer.getPlayerName() << " doesn't want to trade" << endl;
        }
    */
    }
    return false;
}

// Trading cards with other players
bool Catan::tradeCardsWithPlayers(Player &player, Player &otherPlayer, string playerCard, string otherResource, int giveQuantity, int takeQuantity)
{
    if (isPlayersTurn(player))
    {
        /*
        string answer;
        // Checking if the player has enough recource cards to trade
        cout << "Hey " << otherPlayer.getPlayerName() << ", " << player.getPlayerName() << " wants to trade with you " << giveQuantity << " "
             << playerCard << " in exchange for " << takeQuantity << " " << otherResource << ". Would you like to trade?" << endl;
        cin >> answer;
        if (answer == "yes")
        {
        */
        // Checking if both of the players has enough cards to trade
        if (player.getCardCount(playerCard) < giveQuantity)
        {
            cout<<"You don't have enough to trade."<<endl;
            return false;
        }
        if (otherPlayer.getResourceCount(otherResource) < takeQuantity)
        {
            cout<<"The other player doesn't have enough to trade."<<endl;
            return false;
        }

        // If the player wants to trade with the knight card
        if (playerCard == "knight card")
        {
            // Checking if the player need to lose the biggest army card and it the other player needs to get it
            checkReduceBiggestArmyCard(player);
            checkIncreaseBiggestArmyCard(otherPlayer);
        }

        player.reduceCardCount(playerCard, giveQuantity);
        player.addResource(otherResource, takeQuantity);
        otherPlayer.addCard(playerCard);
        otherPlayer.reduceResource(otherResource, takeQuantity);
        return true;
        /**
            }
        // The other player doesn't want to trade
        else
        {
            cout << otherPlayer.getPlayerName() << " doesn't want to trade" << endl;
        }
    */
    }
    return false;
}

// Roll a 6-sided dice
int Catan::rollDice(Player &player)
{
    if (isPlayersTurn(player))
    {
        int firstDice = rand() % 6 + 1;
        int secondDice = rand() % 6 + 1;
        int sum = firstDice + secondDice;
        this->board->distribueResourcesByDice(sum);
        return sum;
    }
    return 0;
}

// End the current player's turn and move to the next player
void Catan::endTurn()
{
    for (size_t i = 0; i < players.size(); ++i)
    {
        if (players[i] == currentPlayer)
        {
            currentPlayer = players[(i + 1) % players.size()];
            break;
        }
    }
}

Player &Catan::getCurrentPlayer()
{
    return *this->currentPlayer;
}

vector<Player *> Catan::getPlayersOrder()
{
    return this->players;
}

// Each player choose at the begining of the game 2 settlement and 2 road to set
void Catan::firstTurn(Player &player, size_t firstSettlement, size_t firstRoad1, size_t firstRoad2, size_t secondSettlement, size_t secondRoad1, size_t secondRoad2)
{
    if (isPlayersTurn(player))
    {
        this->board->placeSettlement(player, firstSettlement);
        // The player gets one resource from each land that adjacent to his settlement
        string land;
        // Iterating through all the tiles on the board
        for (size_t i = 0; i < board->getBoartTiles().size(); i++)
        {
            bool temp = false;
            // For each tile, iterating through all the vertices that adjacent to it
            for (size_t j = 0; j < board->getBoartTiles()[i]->getAdjacentVertices().size(); j++)
            {
                /*If one of the tile vertices is the vertex that the player placed settelment on,
                  the player gets the resource from the current land
                */
                if (board->getBoartTiles()[i]->getAdjacentVertices()[j]->getVertexNumber() == firstSettlement)
                {
                    land = board->setResourceToLand(board->getBoartTiles()[i]->getLand());
                    player.addResource(land, 1);
                    cout << player.getPlayerName() << " got 1 " << land << " card" << endl;
                    break;
                }
            }
        }
        // The player gets one victory point for building a settlement
        player.addVictoryPoints(1);
        this->board->placeRoad(player, firstRoad1, firstRoad2);

        this->board->placeSettlement(player, secondSettlement);
        for (size_t i = 0; i < board->getBoartTiles().size(); i++)
        {
            bool temp = false;
            // For each tile, iterating through all the vertices that adjacent to it
            for (size_t j = 0; j < board->getBoartTiles()[i]->getAdjacentVertices().size(); j++)
            {
                /*If one of the tile vertices is the vertex that the player placed settelment on,
                  the player gets the resource from the current land
                */
                if (board->getBoartTiles()[i]->getAdjacentVertices()[j]->getVertexNumber() == secondSettlement)
                {
                    land = board->setResourceToLand(board->getBoartTiles()[i]->getLand());
                    player.addResource(land, 1);
                    cout << player.getPlayerName() << " got 1 " << land << " card" << endl;
                    break;
                }
            }
        }
        // The player gets one victory point for building a settlement
        player.addVictoryPoints(1);
        this->board->placeRoad(player, secondRoad1, secondRoad2);
    }
}

bool Catan::placeSettlement(Player &player, size_t vertexNum)
{
    if (isPlayersTurn(player))
    {
        bool message=false;
        // If the player doesn't have enough resources to build a settlement
        if (this->currentPlayer->getResourceCount("Brick") < 1 || this->currentPlayer->getResourceCount("Wood") < 1 ||
            this->currentPlayer->getResourceCount("Wool") < 1 || this->currentPlayer->getResourceCount("Oats") < 1)
        {
            cout<<"You don't have enough resources to build a settlement"<<endl;
            return message;
        }
        message= this->board->placeSettlement(player, vertexNum);
        /*
        int v1;
        while(message==false){
            cout<<"The vertex you chose is not valid, please choose another one";
            cin>>v1;
            message= this->board->placeSettlement(player, v1);
        }
        */
       if(message==true){
        // The player gets one victory point for building a settlement
        player.addVictoryPoints(1);

        // Decrease the resources that the player needs to pay for building a settlement
        player.reduceResource("Brick", 1);
        player.reduceResource("Wool", 1);
        player.reduceResource("Wood", 1);
        player.reduceResource("Oats", 1);
       }
        return message;
    }
    return false;
}

bool Catan::placeCity(Player &player, size_t vertexNum)
{
    bool message=false;
    if (isPlayersTurn(player))
    {
        // If the player doesn't have enough resources to build a city, throw an exception
        if (this->currentPlayer->getResourceCount("Iron") < 3 || this->currentPlayer->getResourceCount("Oats") < 2)
        {
            cout<<"You don't have enough resources to build city"<<endl;
            return false;
        }
        message= this->board->placeCity(player, vertexNum);
        /*
        int v1;
        while(message==false){
            cout<<"The vertex you chose is not valid, please choose another one";
            cin>>v1;
            message= this->board->placeCity(player, v1);
        }
        */
       if(message==true){
        // The player gets one more victory point for upgrading from settlement to a city
        player.addVictoryPoints(1);

        // Decrease the resources that the player need to pay for building a city
        player.reduceResource("Iron", 3);
        player.reduceResource("Oats", 2);
       }
        return message;
    }
    return false;
}

bool Catan::placeRoad(Player &player, size_t firstVertex, size_t secondVertex)
{
    bool message=false;
    if (isPlayersTurn(player))
    {
        //Check if the player have enough resources to build a road
        if (this->currentPlayer->getResourceCount("Brick") < 1 || this->currentPlayer->getResourceCount("Wood") < 1)
        {
            cout<<"You don't have enough resources to build a road"<<endl;
            return message;
        }

        message= this->board->placeRoad(player, firstVertex, secondVertex);
        /*
        int v1,v2;
        while(message==false){
            cout<<"The vertices you chose is not valid";
            cin>>v1>>v2;
            message= this->board->placeCity(player, v1,v2);
        }
        */
       if(message==true){
        // Decrease the resources that the player needs to pay for building a road
        player.reduceResource("Brick", 1);
        player.reduceResource("Wood", 1);
       }
        return message;
    }
    return false;
}

vector<Vertex *> Catan::getBoardVertices()
{
    return this->board->getBoardVertices();
}
map<size_t, vector<Edge *>> Catan::getBoardEdge()
{
    return this->board->getBoardEdge();
}