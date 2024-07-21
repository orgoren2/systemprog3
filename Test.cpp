// Id-9115
// Email address- orgoren3146@gmail.com

#include <iostream>
#include <vector>

using namespace std;
#include "doctest.h"
#include "Board.hpp"
#include "Cards.hpp"
#include "Catan.hpp"
#include "Player.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Road.hpp"
#include "Structure.hpp"
#include "Settlement.hpp"
#include "City.hpp"
using namespace ariel;
using namespace doctest;

TEST_CASE("set players turn order test")
{
    Player p1("Amit", 27);
    Player p2("Moshe", 22);
    Player p3("Or", 25);
    Board board;
    Cards cardsPack;
    Catan catan(p1, p2, p3, board, cardsPack);
    catan.setPlayerTurnsOrder();
    vector<Player *> players = catan.getPlayersOrder();
    CHECK((players[0]->getPlayerName() == "Amit") == true);
    CHECK((players[1]->getPlayerName() == "Or") == true);
    CHECK((players[2]->getPlayerName() == "Moshe") == true);

    SUBCASE("current player test")
    {

        CHECK((catan.getCurrentPlayer().getPlayerName() == "Amit") == true);
    }
}

TEST_CASE("Testing check victory")
{
    Player p1("Amit", 25);
    Player p2("Moshe", 22);
    Player p3("Or", 32);
    Board board;
    Cards cardsPack;
    Catan catan(p1, p2, p3, board, cardsPack);
    catan.setPlayerTurnsOrder();
    // When the game starts each player has 2 victory points
    CHECK(catan.checkVictory(p3) == false);
    p3.addVictoryPoints(12);
    // p1 now have 14 victory points, which means he won the game
    CHECK(catan.checkVictory(p3) == true);
}

TEST_CASE("Testing end turn")
{
    Player p1("Amit", 25);
    Player p2("Moshe", 22);
    Player p3("Or", 32);
    Board board;
    Cards cardsPack;
    Catan catan(p1, p2, p3, board, cardsPack);
    catan.setPlayerTurnsOrder();
    // The oldest player is Or, he should start the game
    CHECK((catan.getCurrentPlayer().getPlayerName() == "Or") == true);
    catan.endTurn();
    // The next player by the age suppust to be Amit
    CHECK((catan.getCurrentPlayer().getPlayerName() == "Amit") == true);
}

TEST_CASE("Testing roll dice")
{
    Player p1("Amit", 25);
    Player p2("Moshe", 22);
    Player p3("Or", 32);
    Board board;
    Cards cardsPack;
    Catan catan(p1, p2, p3, board, cardsPack);
    catan.setPlayerTurnsOrder();
    for (int i = 0; i < 100; i++)
    {
        int num = p3.rollDice();
        CHECK((num > 12) == false);
        CHECK((num < 2) == false);
    }
}

TEST_CASE("Testing first turn")
{
    Player p1("Amit", 25);
    Player p2("Moshe", 22);
    Player p3("Or", 32);
    Board board;
    Cards cardsPack;
    Catan catan(p1, p2, p3, board, cardsPack);
    catan.setPlayerTurnsOrder();
    p3.firstTurn(10, 10, 11, 20, 20, 21);
    CHECK((catan.getBoardVertices()[10]->getStructure()->getOwner()->getPlayerName() == "Or") == true);
    CHECK((catan.getBoardVertices()[20]->getStructure()->getOwner()->getPlayerName() == "Or") == true);
    for (size_t i = 0; i < catan.getBoardEdge()[10].size(); i++)
    {
        if (catan.getBoardEdge()[10][i]->getFirstVertex()->getVertexNumber() == 10 && catan.getBoardEdge()[10][i]->getSecondVertex()->getVertexNumber() == 11 ||
            catan.getBoardEdge()[10][i]->getFirstVertex()->getVertexNumber() == 11 && catan.getBoardEdge()[10][i]->getSecondVertex()->getVertexNumber() == 10)
        {
            CHECK((catan.getBoardEdge()[10][i]->getRoad()->getOwner()->getPlayerName() == "Or") == true);
        }
    }
    for (size_t i = 0; i < catan.getBoardEdge()[20].size(); i++)
    {
        if (catan.getBoardEdge()[20][i]->getFirstVertex()->getVertexNumber() == 20 && catan.getBoardEdge()[20][i]->getSecondVertex()->getVertexNumber() == 21 ||
            catan.getBoardEdge()[20][i]->getFirstVertex()->getVertexNumber() == 21 && catan.getBoardEdge()[20][i]->getSecondVertex()->getVertexNumber() == 20)
        {
            CHECK((catan.getBoardEdge()[20][i]->getRoad()->getOwner()->getPlayerName() == "Or") == true);
        }
    }
}


TEST_CASE("Testing buying development card when the player doesn't have enough resources")
{
    Player p1("Amit", 25);
    Player p2("Moshe", 22);
    Player p3("Or", 32);
    Board board;
    Cards cardsPack;
    Catan catan(p1, p2, p3, board, cardsPack);
    catan.setPlayerTurnsOrder();
    p3.reduceResource("Iron", 1);
    // Should raise an exception, player doesn't have enough Iron cards for buying development card
    CHECK(p3.buyDevelopmentCard()==false);

    SUBCASE("Testing buying development card when the player have enough resources")
    {
        Player p1("Amit", 25);
        Player p2("Moshe", 22);
        Player p3("Or", 32);
        Board board;
        Cards cardsPack;
        Catan catan(p1, p2, p3, board, cardsPack);
        catan.setPlayerTurnsOrder();
        p3.addResource("Iron",1);
        p3.addResource("Wool",1);
        p3.addResource("Oats",1);
        CHECK(p3.buyDevelopmentCard()==true);
        int temp = 0;
        // Checking if the player got one of the development cards
        if (p3.getCardCount("knight card") > 0 || p3.getCardCount("victory point card") > 0 || p3.getCardCount("abundant year card") > 0 || p3.getCardCount("monopoly card") > 0 ||
            p3.getCardCount("build roads card") > 0)
        {
            temp++;
        }

        CHECK((temp == 1) == true);
    }
}

TEST_CASE("Trading tests")
{
    // Test trade with bank when player doesn't have enough resources to trade

    Player p1("Amit", 27);
    Player p2("Moshe", 22);
    Player p3("Or", 25);
    Board board;
    Cards cardsPack;
    Catan catan(p1, p2, p3, board, cardsPack);
    catan.setPlayerTurnsOrder();
    // Should return false, the player has only one from each resource and trading with the bank is in ratio 4:1
    CHECK(p1.tradeWithBank("Oats", "Brick")==false);

    SUBCASE("Test trade with bank when player have enough resources to trade")
    {
        p1.addResource("Brick", 7);
        CHECK(p1.tradeWithBank("Brick", "Oats")==true);
        CHECK((p1.getResourceCount("Brick") == 3) == true);

        CHECK((p1.getResourceCount("Oats") == 1) == true);
    }

    SUBCASE("Test trade resources with players when the players doesn't have enough resources")
    {
        p3.addResource("Brick", 5);

        // Test when p3 has enough resources but p1 doesn't
        CHECK(p1.tradeResourcesWithPlayers(p3, "Oats", "Brick", 4, 5)==false);
        // Test when p1 has enough resources but p3 doesn't
        CHECK(p1.tradeResourcesWithPlayers(p3, "Brick", "Wood", 1, 5)==false);
    }

    SUBCASE("Test trade resources with friends when the players have enough resources")
    {

        p3.addResource("Brick", 5);
        p1.addResource("Oats",1);
        CHECK(p1.tradeResourcesWithPlayers(p3, "Oats", "Brick", 1, 5)==true);
        CHECK((p1.getResourceCount("Oats") == 0) == true);
        CHECK((p1.getResourceCount("Brick") == 5) == true);
        CHECK((p3.getResourceCount("Oats") == 1) == true);
        CHECK((p3.getResourceCount("Brick") == 0) == true);
    }

    SUBCASE("Test trade cards with friends when the players doesn't have enough resources")
    {

        p3.addCard("knight card");
        cardsPack.decreaseCardQuantity("knight card");
        // Test when p3 has enough resources but p2 doesn't cards
        CHECK(p2.tradeCardsWithPlayers(p3, "knight card", "Brick", 4, 1)==false);
        // Test when p2 has enough cards but p3 doesn't have enough resources
        CHECK(p2.tradeCardsWithPlayers(p3, "knight card", "Wood", 1, 5)==false);
    }

    SUBCASE("Test trade cards with players when the players have enough resources")
    {
        p3.addResource("Brick", 2);
        p1.addCard("knight card");
        CHECK(p1.tradeCardsWithPlayers(p3, "knight card", "Brick", 1, 1)==true);
        CHECK((p1.getCardCount("knight card") == 0) == true);
        CHECK((p3.getCardCount("knight card") == 1) == true);
        CHECK((p1.getResourceCount("Brick") == 1) == true);
        CHECK((p3.getResourceCount("Brick") == 1) == true);
    }
}

TEST_CASE("Testing use monopoly card when the player doesn't have the card")
{
    Player p1("Amit", 27);
    Player p2("Moshe", 22);
    Player p3("Or", 25);
    Board board;
    Cards cardsPack;
    Catan catan(p1, p2, p3, board, cardsPack);
    catan.setPlayerTurnsOrder();
    CHECK(p1.useMonopolyCard("Brick")==false);

    SUBCASE("Testing use monopoly card when the player have the card")
    {
        p1.addCard("monopoly card");
        p2.addResource("Brick",1);
        p3.addResource("Brick",1);
        CHECK(p1.useMonopolyCard("Brick")==true);
        CHECK((p1.getResourceCount("Brick") == 2) == true);
        CHECK((p1.getCardCount("monopoly card") == 0) == true);
        CHECK((p2.getResourceCount("Brick") == 0) == true);
        CHECK((p3.getResourceCount("Brick") == 0) == true);
    }
}


TEST_CASE("Testing use build roads card when the player doesn't have the card")
{
    Player p1("Amit", 27);
    Player p2("Moshe", 22);
    Player p3("Or", 25);
    Board board;
    Cards cardsPack;
    Catan catan(p1, p2, p3, board, cardsPack);
    catan.setPlayerTurnsOrder();
    p1.addResource("Brick",1);
    p1.addResource("Wood",1);
    p1.addResource("Wool",1);
    p1.addResource("Oats",1);

    p1.placeSettlement(10);
    CHECK(p1.useBuildRoadsCard(10, 11, 9, 10) == false);
    SUBCASE("Testing use build roads card when the player have the card")
    {
        
        p1.addCard("build roads card");
        p1.addResource("Brick",2);
        p1.addResource("Wood",2);

        CHECK(p1.useBuildRoadsCard(10, 11, 9, 10) == true);
        for (size_t i = 0; i < catan.getBoardEdge()[10].size(); i++)
        {
            if (catan.getBoardEdge()[10][i]->getFirstVertex()->getVertexNumber() == 10 && catan.getBoardEdge()[10][i]->getSecondVertex()->getVertexNumber() == 11 ||
                catan.getBoardEdge()[10][i]->getFirstVertex()->getVertexNumber() == 11 && catan.getBoardEdge()[10][i]->getSecondVertex()->getVertexNumber() == 10)
            {
                CHECK((catan.getBoardEdge()[10][i]->getRoad()->getOwner()->getPlayerName() == "Amit") == true);
            }
        }
    }
}


TEST_CASE("set resource to land test")
{

    Board board;
    CHECK((board.setResourceToLand("Brick hills") == "Brick") == true);
    CHECK((board.setResourceToLand("Meadow") == "Wool") == true);
    CHECK((board.setResourceToLand("Mountain") == "Iron") == true);
    CHECK((board.setResourceToLand("Forest") == "Wood") == true);
    CHECK((board.setResourceToLand("Agricultural land") == "Oats") == true);
}

TEST_CASE("Testing use abundant year card when the player doesn't hasve the card")
{
    Player p1("Amit", 27);
    Player p2("Moshe", 22);
    Player p3("Or", 25);
    Board board;
    Cards cardsPack;
    Catan catan(p1, p2, p3, board, cardsPack);
    catan.setPlayerTurnsOrder();
    CHECK(p1.useAbundantYearCard("Brick", "Oats")==false);

    SUBCASE("Testing use abundant year card when the player has the card")
    {
        p1.addCard("abundant year card");
        CHECK(p1.useAbundantYearCard("Brick", "Oats")==true);
        CHECK((p1.getResourceCount("Brick") == 1) == true);
        CHECK((p1.getResourceCount("Oats") == 1) == true);
    }


}

TEST_CASE("Testing initialize Resources")
{
    Player p1("Amit", 25);
    CHECK((p1.getResourceCount("Brick") == 0) == true);
    CHECK((p1.getResourceCount("Wood") == 0) == true);
    CHECK((p1.getResourceCount("Wool") == 0) == true);
    CHECK((p1.getResourceCount("Oats") == 0) == true);
    CHECK((p1.getResourceCount("Iron") == 0) == true);
}

TEST_CASE("Testing initialize cards")
{
    Player p1("Amit", 25);
    CHECK((p1.getCardCount("knight card") == 0) == true);
    CHECK((p1.getCardCount("monopoly card") == 0) == true);
    CHECK((p1.getCardCount("biggest army card") == 0) == true);
    CHECK((p1.getCardCount("build roads card") == 0) == true);
    CHECK((p1.getCardCount("abundant year card") == 0) == true);
    CHECK((p1.getCardCount("victory card") == 0) == true);
}

TEST_CASE("Player's getters and setters tests")
{
    Player p1("Amit", 25);
    CHECK((p1.getPlayerAge() == 25) == true);
    CHECK((p1.getPlayerName() == "Amit") == true);
    p1.addCard("knight card");
    CHECK((p1.getCardCount("knight card") == 1) == true);
    p1.reduceCardCount("knight card", 1);
    CHECK((p1.getCardCount("knight card") == 0) == true);
    p1.addResource("Oats", 1);
    CHECK((p1.getResourceCount("Oats") == 1) == true);
    p1.reduceResource("Oats", 1);
    CHECK((p1.getResourceCount("Oats") == 0) == true);
    p1.addVictoryPoints(2);
    CHECK((p1.getVictoryPoints() == 2) == true);
    p1.reduceVictoryPoints(2);
    CHECK((p1.getVictoryPoints() == 0) == true);
}

TEST_CASE("Testing initialize cards pack")
{
    Cards cards;
    CHECK((cards.getCardsPack()["knight card"] == 10) == true);
    CHECK((cards.getCardsKind()[0] == ("knight card")) == true);
}

TEST_CASE("Draw card test")
{
    Cards cards;
    string s = cards.drawCard();
    int t = 0;
    if (s == "knight card" || s == "victory point card" || s == "abundant year card" || s == "monopoly card" ||
        s == "build roads card")
    {
        t++;
    }
    CHECK((t == 1) == true);
}

TEST_CASE("Place settlement test when the player doesn't have enough resorces")
{
    Player p1("Amit", 27);
    Player p2("Moshe", 22);
    Player p3("Or", 25);
    Board board;
    Cards cardsPack;
    Catan catan(p1, p2, p3, board, cardsPack);
    catan.setPlayerTurnsOrder();
    p1.reduceResource("Brick", 1);
    CHECK(p1.placeSettlement(10)==false);
}

TEST_CASE("Place settlement test when there is another players settlement in the adjacent vertex")
{
    Player p1("Amit", 27);
    Player p2("Moshe", 22);
    Player p3("Or", 25);
    Board board;
    Cards cardsPack;
    Catan catan(p1, p2, p3, board, cardsPack);
    catan.setPlayerTurnsOrder();
    p1.addResource("Brick", 2);
    p1.addResource("Wood", 2);
    p1.addResource("Wool", 2);
    p1.addResource("Oats", 2);
    CHECK(p1.placeSettlement(10)==true);
    catan.endTurn();
    CHECK(p3.placeSettlement(11)==false);
}

TEST_CASE("Place settlement test")
{
    Player p1("Amit", 27);
    Player p2("Moshe", 22);
    Player p3("Or", 25);
    Board board;
    Cards cardsPack;
    Catan catan(p1, p2, p3, board, cardsPack);
    catan.setPlayerTurnsOrder();
    p1.addResource("Brick", 2);
    p1.addResource("Wood", 2);
    p1.addResource("Wool", 2);
    p1.addResource("Oats", 2);
    CHECK(p1.placeSettlement(10)==true);
    CHECK(catan.getBoardVertices()[10]->getStructure()->getOwner()->getPlayerName() == "Amit");
}

TEST_CASE("Place road test when the player doesn't have enough resorces")
{
    Player p1("Amit", 27);
    Player p2("Moshe", 22);
    Player p3("Or", 25);
    Board board;
    Cards cardsPack;
    Catan catan(p1, p2, p3, board, cardsPack);
    catan.setPlayerTurnsOrder();
    p1.reduceResource("Brick", 1);
    CHECK(p1.placeRoad(0, 1)==false);
}

TEST_CASE("Place road test when there is not connected settlement or road")
{
    Player p1("Amit", 27);
    Player p2("Moshe", 22);
    Player p3("Or", 25);
    Board board;
    Cards cardsPack;
    Catan catan(p1, p2, p3, board, cardsPack);
    catan.setPlayerTurnsOrder();
    CHECK(p1.placeRoad(0, 1)==false);
}

TEST_CASE("Place road test when there is connected settlement or road")
{
    Player p1("Amit", 27);
    Player p2("Moshe", 22);
    Player p3("Or", 25);
    Board board;
    Cards cardsPack;
    Catan catan(p1, p2, p3, board, cardsPack);
    catan.setPlayerTurnsOrder();
    p1.addResource("Brick", 2);
    p1.addResource("Wood", 2);
    p1.addResource("Wool", 2);
    p1.addResource("Oats", 2);
    CHECK(p1.placeRoad(10, 11)==false);
    CHECK(p1.placeRoad(11, 12)==false);
    p1.placeSettlement(10);
    CHECK(p1.placeRoad(10, 11)==true);
    for (size_t i = 0; i < catan.getBoardEdge()[10].size(); i++)
    {
        if (catan.getBoardEdge()[10][i]->getFirstVertex()->getVertexNumber() == 10 && catan.getBoardEdge()[10][i]->getSecondVertex()->getVertexNumber() == 11 ||
            catan.getBoardEdge()[10][i]->getFirstVertex()->getVertexNumber() == 11 && catan.getBoardEdge()[10][i]->getSecondVertex()->getVertexNumber() == 10)
        {
            CHECK((catan.getBoardEdge()[10][i]->getRoad()->getOwner()->getPlayerName() == "Amit") == true);
        }
    }

    catan.endTurn();
    p3.addResource("Brick", 2);
    p3.addResource("Wood", 2);
    p3.addResource("Wool", 2);
    p3.addResource("Oats", 2);
    p3.placeSettlement(21);
    CHECK(p3.placeRoad(11, 21)==true);
}

TEST_CASE("Place city test when the player doesn't have enough resorces")
{
    Player p1("Amit", 27);
    Player p2("Moshe", 22);
    Player p3("Or", 25);
    Board board;
    Cards cardsPack;
    Catan catan(p1, p2, p3, board, cardsPack);
    catan.setPlayerTurnsOrder();
    CHECK(p1.placeCity(10)==false);
}

TEST_CASE("Place city test when the place wasn't one of the player's settlements")
{
    Player p1("Amit", 27);
    Player p2("Moshe", 22);
    Player p3("Or", 25);
    Board board;
    Cards cardsPack;
    Catan catan(p1, p2, p3, board, cardsPack);
    catan.setPlayerTurnsOrder();
    p1.addResource("Iron", 5);
    p1.addResource("Oats", 5);
    CHECK(p1.placeCity(10)==false);
}

TEST_CASE("Place city test when the place is one of the player's settlements")
{
    Player p1("Amit", 27);
    Player p2("Moshe", 22);
    Player p3("Or", 25);
    Board board;
    Cards cardsPack;
    Catan catan(p1, p2, p3, board, cardsPack);
    catan.setPlayerTurnsOrder();
    p1.addResource("Iron", 5);
    p1.addResource("Oats", 5);
    p1.addResource("Brick", 2);
    p1.addResource("Wood", 2);
    p1.addResource("Wool", 2);
   
    p1.placeSettlement(10);
    CHECK(p1.placeCity(10)==true);
    CHECK((catan.getBoardVertices()[10]->getStructure()->getOwner()->getPlayerName() == p1.getPlayerName()) == true);
}

TEST_CASE("Ditribute resource by dice test")
{

    Player p1("Amit", 27);
    Player p2("Moshe", 22);
    Player p3("Or", 25);
    Board board;
    Cards cardsPack;
    Catan catan(p1, p2, p3, board, cardsPack);
    catan.setPlayerTurnsOrder();

    p1.addResource("Brick", 15);
    p1.addResource("Wool", 15);
    p1.addResource("Wood", 15);
    p1.addResource("Oats", 15);
    p1.addResource("Iron", 15);

    p1.placeSettlement(10);
    p1.placeSettlement(12);
    p1.placeSettlement(24);
    p1.placeSettlement(22);
    p1.placeSettlement(20);
    p1.placeSettlement(18);
    p1.placeSettlement(44);
    p1.placeSettlement(42);
    p1.placeSettlement(40);

    int brick1 = p1.getResourceCount("Brick");
    int oats1 = p1.getResourceCount("Oats");
    int wool1 = p1.getResourceCount("Wool");
    int wood1 = p1.getResourceCount("Wood");
    int iron1 = p1.getResourceCount("Iron");
    p1.rollDice();

    int brick2 = p1.getResourceCount("Brick");
    int oats2 = p1.getResourceCount("Oats");
    int wool2 = p1.getResourceCount("Wool");
    int wood2 = p1.getResourceCount("Wood");
    int iron2 = p1.getResourceCount("Iron");

    bool resourcesIncreased = (brick1 < brick2) || (oats1 < oats2) || (wool1 < wool2) || (wood1 < wood2) || (iron1 < iron2);

    CHECK(resourcesIncreased == true);
}

TEST_CASE("Set and get structure vertex test")
{
    Player p1("Or", 26);
    Structure *structure = new City(p1);
    Vertex v(1);
    v.setStructure(structure);
    CHECK((v.getStructure()->getOwner()->getPlayerName() == "Or") == true);
    CHECK((v.getVertexNumber() == 1) == true);
}

TEST_CASE("Tile set and get test")
{
    Tile t1("Meadow", 2);
    vector<Vertex*> adjacentVertices;
    Vertex first(1);
    Vertex second(2);
    adjacentVertices.push_back(&first);
    adjacentVertices.push_back(&second);
    t1.setAdjacentVertices(adjacentVertices);
    CHECK((t1.getLand() == "Meadow") == true);
    CHECK((t1.getLandNumber() == 2) == true);
    CHECK((t1.getAdjacentVertices()[0]->getVertexNumber() == 1) == true);
    CHECK((t1.getAdjacentVertices()[1]->getVertexNumber() == 2) == true);
}

TEST_CASE("Structure getters and setters test")
{
    Player p1("Or", 26);
    Player p2("Amit", 22);
    Player p3("Moshe", 28);
    Structure s(p1);
    CHECK((s.getOwner()->getPlayerName() == "Or") == true);
    City c(p2);
    CHECK((c.getType() == "city") == true);
    Settlement s1(p3);
    CHECK((s1.getType() == "settlement") == true);
}

TEST_CASE("Road set and get test")
{
    Player p1("Or", 26);
    Road r(p1);
    CHECK((r.getOwner()->getPlayerName() == "Or") == true);
}

TEST_CASE("Edge getters and setters test")
{
    Player p1("Or", 26);
    Road *r=new Road(p1);
    Vertex v1(1);
    Vertex v2(2);
    Edge e(v1, v2);
    CHECK((e.getFirstVertex()->getVertexNumber() == 1) == true);
    e.setRoad(r);
    CHECK((e.getRoad()->getOwner()->getPlayerName() == "Or") == true);
    
}