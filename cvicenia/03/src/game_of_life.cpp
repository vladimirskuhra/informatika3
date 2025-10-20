#include "game_of_life.hpp"
#include <thread>
#include <chrono>
#include <cstdlib> // pre system("cls")
#include "ui_utils.hpp"

namespace gol {

GameOfLife::GameOfLife()
    : m_activeDisplay(new asciid::Display()),
      m_bufferDisplay(new asciid::Display()) {}

GameOfLife::~GameOfLife() {
    delete m_activeDisplay;
    delete m_bufferDisplay;
}

bool GameOfLife::cellExists(int row, int col) const {
    return row >= 0 && row < m_activeDisplay->getRowCount() &&
           col >= 0 && col < m_activeDisplay->getColCount();
}

void GameOfLife::setCellAlive(int row, int col) {
    if (cellExists(row, col)) {
        m_activeDisplay->turnPixelOn(row, col);
    }
}

void GameOfLife::printState() const {
    m_activeDisplay->print();
}

int GameOfLife::calcLivingNeighbours(int row, int col) const {
    int count = 0;
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;
            int nr = row + dr;
            int nc = col + dc;
            if (cellExists(nr, nc) && m_activeDisplay->isPixelOn(nr, nc)) {
                ++count;
            }
        }
    }
    return count;
}

void GameOfLife::evaluateNextState() {
    for (int r = 0; r < m_activeDisplay->getRowCount(); ++r) {
        for (int c = 0; c < m_activeDisplay->getColCount(); ++c) {
            int neighbours = calcLivingNeighbours(r, c);
            bool alive = m_activeDisplay->isPixelOn(r, c);
            if (alive) {
                if (neighbours == 2 || neighbours == 3)
                    m_bufferDisplay->turnPixelOn(r, c);
                else
                    m_bufferDisplay->turnPixelOff(r, c);
            } else {
                if (neighbours == 3)
                    m_bufferDisplay->turnPixelOn(r, c);
                else
                    m_bufferDisplay->turnPixelOff(r, c);
            }
        }
    }
}

void GameOfLife::swapDisplays(asciid::Display*& d1, asciid::Display*& d2) {
    asciid::Display* temp = d1;
    d1 = d2;
    d2 = temp;
}

GameOfLife* GameOfLife::createEmpty() {
    return new GameOfLife();
}

GameOfLife* GameOfLife::createToad() {
    GameOfLife* game = new GameOfLife();
    // Toad pattern (3x4)
    int r = 5, c = 5;
    game->setCellAlive(r, c+1);
    game->setCellAlive(r, c+2);
    game->setCellAlive(r, c+3);
    game->setCellAlive(r+1, c);
    game->setCellAlive(r+1, c+1);
    game->setCellAlive(r+1, c+2);
    return game;
}

GameOfLife* GameOfLife::createDieHard() {
    GameOfLife* game = new GameOfLife();
    // Diehard pattern
    int r = 5, c = 5;
    game->setCellAlive(r, c+6);
    game->setCellAlive(r+1, c);
    game->setCellAlive(r+1, c+1);
    game->setCellAlive(r+2, c+1);
    game->setCellAlive(r+2, c+5);
    game->setCellAlive(r+2, c+6);
    game->setCellAlive(r+2, c+7);
    return game;
}

GameOfLife* GameOfLife::createByUser() {
    GameOfLife* game = new GameOfLife();
    int rows = uiutils::readInt("Zadajte počet riadkov");
    int cols = uiutils::readInt("Zadajte počet stĺpcov");
    int cells = uiutils::readInt("Zadajte počet živých buniek");
    for (int i = 0; i < cells; ++i) {
        int r = uiutils::readInt("Zadajte riadok bunky");
        int c = uiutils::readInt("Zadajte stĺpec bunky");
        game->setCellAlive(r, c);
    }
    return game;
}

void GameOfLife::tick() {
    // Najprv vyčistíme buffer
    for (int r = 0; r < m_bufferDisplay->getRowCount(); ++r)
        for (int c = 0; c < m_bufferDisplay->getColCount(); ++c)
            m_bufferDisplay->turnPixelOff(r, c);

    this->evaluateNextState();
    this->swapDisplays(m_activeDisplay, m_bufferDisplay);
}

void GameOfLife::run(int tickCount) {
    for (int i = 0; i < tickCount; ++i) {
        system("cls");
        printState();
        tick();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

} // namespace gol
