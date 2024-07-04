/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include "Catan.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"
#include "Road.hpp"
#include "Structure.hpp"
#include "Settlement.hpp"
#include "City.hpp"

using namespace std;
using namespace ariel;
int main()
{
    Player p1("Amit",22);
    Player p2("Yossi",25);
    Player p3("Dana",30);
    Board board;
    Cards cardsPack;
    Catan catan(p1, p2, p3, board,cardsPack);
    catan.setPlayerTurnsOrder();// Should print the players turns order, Dana is starting the game, Yossi will play next and then Amit will play
    p3.firstTurn(10,10,11,12,12,13);
    catan.endTurn();

    p2.firstTurn(30,30,31,32,32,33);
    catan.endTurn();
    
    p1.firstTurn(49,49,50,51,51,52);
    catan.endTurn();
    
    p3.rollDice();
    p3.tradeResourcesWithPlayers(p1, "Iron", "Oats",1,1);
    p3.placeSettlement(24);
    catan.checkVictory(p3);
    catan.endTurn();
    
    p2.rollDice();
    p2.buyDevelopmentCard();
    p2.placeRoad(29,30);
    catan.checkVictory(p2);
    catan.endTurn();
    
    p1.rollDice();
    p1.buyDevelopmentCard();
    p1.placeRoad(48,49);
    catan.checkVictory(p1);
    catan.endTurn();






}