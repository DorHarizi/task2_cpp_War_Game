#include "game.hpp"
using namespace ariel;

namespace ariel{
    Game::Game(Player &player1, Player &player2){
        p1 = player1;
        p2 = player2;
        lastTurn = "";
        status = "";
    }

    void Game::playTurn(){}
    void Game::printLastTurn(){}
    void Game::playAll(){}
    void Game::printWiner(){}
    void Game::printLog(){}
    void Game::printStats(){}
}