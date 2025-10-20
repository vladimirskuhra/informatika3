#ifndef GAME_OF_LIFE_HPP
#define GAME_OF_LIFE_HPP
#include "display.hpp"
using asciid::Display;

namespace gol {
class GameOfLife {
public:
    ~GameOfLife();

    static GameOfLife* createToad();
    static GameOfLife* createDieHard();
    static GameOfLife* createEmpty();
    static GameOfLife* createByUser();

    bool cellExists(int row, int col) const;
    void setCellAlive(int row, int col);
    void tick();
    void run(int tickCount);
    void printState() const;
private:
    GameOfLife();
    asciid::Display* m_activeDisplay;
    asciid::Display* m_bufferDisplay;
    void evaluateNextState();
    void swapDisplays(asciid::Display*& d1, asciid::Display*& d2);
    int calcLivingNeighbours(int row, int col) const;
};
} // namespace gol

#endif // GAME_OF_LIFE_HPP