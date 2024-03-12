#ifndef DUNGEONS_AND_DRAGONS_GAME_HPP
#define DUNGEONS_AND_DRAGONS_GAME_HPP

#include "Player.hpp"
#include "Map.hpp"
#include "Dragon.hpp"
#include "functions.hpp"

class Game
{
private:
    unsigned int level;
    Player player;
    Map map;

    void addTreasures();

    void addDragons();

    Direction parseDirection(const std::string& input);

    void ensureValidResponse(std::string& input, const Item& item);

    void movePlayer(const Direction& direction);

    void fight();

    void determineFirstToAttack(Entity*& first, Entity*& second, Entity*& dragon);

    void fightAftermath();

    void treasureHandler();

    bool finalDestinationHandler();

    void gameLoop();

public:
    Game(const Map& _map, const Player& _player);

    void start();

    void save();

    void load(const std::string& file);
};


#endif //DUNGEONS_AND_DRAGONS_GAME_HPP
