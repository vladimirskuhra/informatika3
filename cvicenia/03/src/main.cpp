#include "game_of_life.hpp"

int main() {
    gol::GameOfLife* game = gol::GameOfLife::createToad(); // alebo createDieHard, createEmpty
    game->run(20); 
    delete game;
    return 0;
}