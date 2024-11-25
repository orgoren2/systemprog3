# Exercise 3- Catan game
This project is an implementation of the catan game.
There are 3 players in this game, each player in his turn can trade resource or development cards and build roads, settlements and cities.
# Classes

## Player Class 
The Player class represents a player in the Catan game.

### Methods:

* Player(string name, int age): Initializes a player with a name, age, victory points, and initializes resources and cards.
* initializeResources(): Initializes the player's resources with default values.
* initializeCards(): Initializes the player's cards with default values.
* firstTurn(): Initiates the player's first turn with initial placements.
* rollDice(): Rolls the dice for the player.
* tradeWithBank(): Initiates a trade with the bank.
* tradeResourcesWithPlayers(): Initiates a trade of resources with another player.
* tradeCardsWithPlayers(): Initiates a trade of cards with another player.
* buyDevelopmentCard(): Buys a development card.
* useMonopolyCard(): Uses a monopoly card.
* useBuildRoadsCard(): Uses a build roads card.
* useAbundantYearCard(): Uses an abundant year card.
* placeSettlement(): Places a settlement.
* placeCity(): Upgrades a settlement to a city.
* placeRoad(): Places a road.
* getPlayerName() const: Returns the player's name.
* getPlayerAge() const: Returns the player's age.
* getVictoryPoints() const: Returns the player's victory points.
* getResourceCount(string resource): Returns the count of a specific resource.
* getCardCount(string card): Returns the count of a specific card.
* addVictoryPoints(): Adds victory points to the player.
* reduceVictoryPoints(): Reduces victory points from the player.
* addResource(): Adds a specified amount of a resource to the player.
* reduceResource(): Reduces a specified amount of a resource from the player.
* addCard(): Adds a card to the player's collection.
* reduceCardCount(): Reduces the count of a specific card from the player.
* setGame(Catan &game): Sets the game instance for the player.

## Catan Class

The Catan class manages the core game logic for a Catan board game simulation.
### Methods:
* Catan(Player &p1, Player &p2, Player &p3, Board &board, Cards &cardsPack): Initializes the game with three players, a board, and a deck of cards.
* ~Catan(): Destructor to clean up player data.
* setPlayerTurnsOrder(): Sets the turn order based on player ages.
* setBoard(Board &board): Sets the game board.
* checkVictory(Player &player) const: Checks if a player has won based on victory points.
* endTurn(): Ends the current player's turn and moves to the next player.
* rollDice(Player &player): Rolls dice and distributes resources based on the roll.
* buyDevelopmentCard(Player &player): Allows a player to buy a development card.
* useMonopolyCard(Player &player, string wantedResource): Uses a monopoly card to gather resources from all players.
* useBuildRoadsCard(Player &player, size_t sV1, size_t fV1, size_t sV2, size_t fV2): Allows a player to build roads without resources.
* useAbundantYearCard(Player &player, string firstWantedCard, string secondWantedCard): Allows a player to choose two resources without cost.
* tradeWithBank(Player &player, string playerResource, string wantedResource): Allows a player to trade with the bank.
* tradeResourcesWithPlayers(Player &player, Player &otherPlayer, string playerResource, string otherResource, int giveQuantity, int takeQuantity): Allows a player to trade resources with another player.
* tradeCardsWithPlayers(Player &player, Player &otherPlayer, string playerCard, string otherResource, int giveQuantity, int takeQuantity): Allows a player to trade cards with another player.
* firstTurn(Player& player, size_t firstSettlement, size_t firstRoad1, size_t firstRoad2, size_t secondSettlement, size_t secondRoad1, size_t secondRoad2): Sets up initial settlements and roads for players at the start of the game.
* placeSettlement(Player &player, size_t vertexNum): Allows a player to place a settlement on the board.
* placeCity(Player &player, size_t vertexNum): Allows a player to upgrade a settlement to a city.
* placeRoad(Player &player, size_t firstVertex, size_t secondVertex): Allows a player to place a road on the board.
* getCurrentPlayer(): Returns the current player.
* getPlayersOrder(): Returns the order of players.
* getBoardVertices(): Returns all vertices on the board.
* getBoardEdge(): Returns all edges on the board.

## Board Class

The Board class represents the game board in a Catan-like board game. It manages tiles, vertices, edges, and game mechanics related to resource distribution and player actions.
### Methods:
* Board(): Constructor that initializes the board with tiles, vertices, and edges.
* ~Board(): Destructor that cleans up dynamically allocated memory for tiles, vertices, and edges.
* initializeBoard(): Sets up the initial configuration of tiles, vertices, and edges based on predefined data.
* distribueResourcesByDice(int diceRoll): Distributes resources to players based on a dice roll.
* placeSettlement(Player& player, size_t vertexNum): Allows a player to place a settlement on a specified vertex.
* placeCity(Player& player, size_t vertexNum): Allows a player to upgrade a settlement to a city on a specified vertex.
* placeRoad(Player& player, size_t firstVertex, size_t secondVertex): Allows a player to place a road between two vertices.
* vector<Vertex*> getBoardVertices(): Returns all vertices on the board.
* map<size_t, vector<Edge*>> getBoardEdge(): Returns all edges on the board.
* vector<Tile*> getBoardTiles(): Returns all tiles on the board.
* string setResourceToLand(string land): Maps tile land types to resource types for resource distribution.

## Cards Class

The Cards class represents a deck of cards used in the Catan-like board game. It manages different types of cards, their quantities, and operations related to drawing and manipulating cards during gameplay.

### Methods:
* Cards(): Constructor that initializes the cards pack with default quantities.
* initializeCardsPack(): Initializes the cards pack with predefined types and quantities.
* map<string, int> getCardsPack(): Returns the current state of the cards pack.
* vector<string> getCardsKind(): Returns the list of available card types.
* string drawCard(): Draws a random card from the deck, ensuring there are remaining cards of that type.
* void increaseCardQuantity(string card): Increases the quantity of a specific card in the deck.
* void increaseBiggestArmyCardQuantity(): Increases the quantity of the "biggest army" card.
* void decreaseCardQuantity(string card): Decreases the quantity of a specific card in the deck.
* bool decreaseBiggestArmyCardQuantity(): Decreases the quantity of the "biggest army" card if available.

## Edge Class

The Edge class represents an edge connecting two vertices on the game board. It manages information about the vertices it connects and whether it contains a road.
### Methods:
* Edge(Vertex* firstVertex, Vertex* secondVertex): Constructor to initialize the edge with pointers to its connecting vertices.
* void setRoad(Road* road): Sets the road on the edge.
* Road* getRoad(): Retrieves the road placed on the edge (if any).
* Vertex* getFirstVertex(): Retrieves the first vertex connected by the edge.
* Vertex* getSecondVertex(): Retrieves the second vertex connected by the edge.

## Tile Class

The Tile class represents a tile on the game board in a Catan-like game. Each tile has a type of land and a number associated with it, along with vertices adjacent to it.
### Methods:
* Tile(string land, int landNumber): Constructor to initialize the tile with a specified type of land and number.
* ~Tile(): Destructor to clean up resources associated with the tile.
* string getLand(): Retrieves the type of land on the tile.
* int getLandNumber(): Retrieves the number associated with the tile.
* void setAdjacentVertices(vector<Vertex*>& adjacentVertices): Sets the vertices adjacent to the tile.
* vector<Vertex*>& getAdjacentVertices(): Retrieves the vertices adjacent to the tile.

## Vertex Class

The Vertex class represents a vertex on the game board in a Catan-like game. Each vertex can optionally hold a structure (such as a settlement or city) and is identified by a unique vertex number.
### Methods:
* Vertex(int vertexNumber): Constructor to initialize the vertex with a specified unique number.
* ~Vertex(): Destructor to clean up resources associated with the vertex, including any structure placed on it.
* void setStructure(Structure* structure): Sets a structure (settlement or city) on the vertex.
* Structure* getStructure(): Retrieves the structure placed on the vertex, if any.
* int getVertexNumber(): Retrieves the unique identifier of the vertex.

## Structure Classes

In the context of a Catan-like game project, the Structure, Settlement, and City classes represent various types of constructions that players can build on the game board. Each structure may have an owner, typically a player who controls it.
Structure Class

The Structure class serves as a base class for the settlement and city classes in the game. It includes functionalities common to all structures, such as tracking ownership and providing a method to retrieve the type of structure.
### Methods:
* Structure(Player& owner): Initializes the structure with a specified owner.
* virtual ~Structure() = default;: Virtual destructor for proper memory management.
* Player* getOwner(): Retrieves the owner of the structure.
* virtual string getType(): Virtual method to retrieve the type of structure (to be overridden in derived classes).

## Road Class

The Road class represents a road built by a player in your Catan-like game project. Each road may have an owner, typically a player who controls it.
### Methods:
* Road(): Initializes a road with no owner.
* Road(Player& owner): Initializes a road with a specified owner.
* Player* getOwner(): Retrieves the owner of the road.


