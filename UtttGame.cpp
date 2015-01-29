#include "UtttGame.hpp"

#include <cstdio>


UtttGame::UtttGame(void) :
    board_{ },
    smallGamesWon_{ },
    winner_(0),
    history_(0)
{}

std::vector<unsigned> UtttGame::play(unsigned player, unsigned coord) {
    auto sgx = (coord % 9)/3;
    auto sgy = coord / 27;
    if (smallGamesWon_[sgx][sgy] == 0 && board_[coord] == 0) {
        board_[coord] = player;
        history_.push_back(coord);
    }

    checkSmallGame(sgx, sgy);
    checkGame();

    if (winner_ != 0)
        return std::vector<unsigned>();

    auto sgx2 = coord % 3;
    auto sgy2 = (coord / 9) % 3;

    if (smallGamesWon_[sgx2][sgy2] == 0)
        return getSlotsAvailable(sgx2, sgy2);
    else
        return getSlotsAvailable();
}

std::vector<unsigned> UtttGame::play(unsigned player, unsigned x, unsigned y) {
    auto sgx = x/3;
    auto sgy = y/3;
    auto coord = 9*y + x;
    if (smallGamesWon_[sgx][sgy] == 0 && board_[coord] == 0) {
        board_[coord] = player;
        history_.push_back(9*y + x);
    }

    checkSmallGame(sgx, sgy);
    checkGame();

    if (winner_ != 0)
        return std::vector<unsigned>();

    auto sgx2 = coord % 3;
    auto sgy2 = (coord / 9) % 3;

    if (smallGamesWon_[sgx2][sgy2] == 0)
        return getSlotsAvailable(sgx2, sgy2);
    else
        return getSlotsAvailable();
}

std::vector<unsigned> UtttGame::getSlotsAvailable(unsigned sgx, unsigned sgy) const {
    auto b = 27*sgy + 3*sgx;

    std::vector<unsigned> out;
    for (unsigned y=0; y<3; ++y)
        for (unsigned x=0; x<3; ++x)
            if (board_[b + 9*y + x] == 0)
                out.push_back(b + 9*y + x);

    return out;
}

std::vector<unsigned> UtttGame::getSlotsAvailable(void) const {
    std::vector<unsigned> out;
    for (unsigned i=0; i<81; ++i)
        if (smallGamesWon_[(i % 9)/3][i / 27] == 0 && board_[i] == 0)
            out.push_back(i);

    return out;
}

const std::vector<unsigned>& UtttGame::getHistory(void) const {
    return history_;
}

short UtttGame::getWinner(void) const {
    return winner_;
}

void UtttGame::printGame(void) const {
    for (auto y=0u; y<9; ++y) {
        for (auto x=0u; x<9; ++x)
            if (9*y + x == history_.back())
                printf("%c ", board_[9*y + x] == 0 ? '.' : board_[9*y + x] == 1 ? 'X' : 'O');
            else
                printf("%c ", board_[9*y + x] == 0 ? '.' : board_[9*y + x] == 1 ? 'x' : 'o');
        printf("\n");
    }
}

void UtttGame::printSmallGames(void) const {
    for (auto sgy=0u; sgy<3; ++sgy) {
        for (auto sgx=0u; sgx<3; ++sgx)
            printf("%c ", smallGamesWon_[sgx][sgy] == 0 ? '.' : smallGamesWon_[sgx][sgy] == 1 ? 'X' : 'O');
        printf("\n");
    }
}

void UtttGame::checkSmallGame(unsigned sgx, unsigned sgy) {
    if (smallGamesWon_[sgx][sgy] != 0)
        return;

    auto b = 27*sgy + 3*sgx;
    auto p1 = 0u;
    auto p2 = 0u;
    auto p1n = 0u;
    auto p2n = 0u;

    for (auto i=0u; i<9; ++i)
        if (board_[b + i%3 + 9*(i/3)] == 1) {
            p1 += 1 << i;
            ++p1n;
        }

    for (auto i=0u; i<9; ++i)
        if (board_[b + i%3 + 9*(i/3)] == 2) {
            p2 += 1 << i;
            ++p2n;
        }

    if ((p1 & 0x0007) == 0x0007 ||
        (p1 & 0x0038) == 0x0038 ||
        (p1 & 0x0049) == 0x0049 ||
        (p1 & 0x0054) == 0x0054 ||
        (p1 & 0x0092) == 0x0092 ||
        (p1 & 0x0111) == 0x0111 ||
        (p1 & 0x0124) == 0x0124 ||
        (p1 & 0x01c0) == 0x01c0)
        smallGamesWon_[sgx][sgy] = 1;
    else if ((p2 & 0x0007) == 0x0007 ||
             (p2 & 0x0038) == 0x0038 ||
             (p2 & 0x0049) == 0x0049 ||
             (p2 & 0x0054) == 0x0054 ||
             (p2 & 0x0092) == 0x0092 ||
             (p2 & 0x0111) == 0x0111 ||
             (p2 & 0x0124) == 0x0124 ||
             (p2 & 0x01c0) == 0x01c0)
        smallGamesWon_[sgx][sgy] = 2;
    else if (p1n + p2n == 9)
        smallGamesWon_[sgx][sgy] = 3;
}

void UtttGame::checkGame(void) {
    auto p1 = 0u;
    auto p2 = 0u;
    auto p1n = 0u;
    auto p2n = 0u;

    for (auto i=0u; i<9; ++i)
        if (smallGamesWon_[i%3][i/3] == 1) {
            p1 += 1 << i;
            ++p1n;
        }

    for (auto i=0u; i<9; ++i)
        if (smallGamesWon_[i%3][i/3] == 2) {
            p2 += 1 << i;
            ++p2n;
        }

    if ((p1 & 0x0007) == 0x0007 ||
        (p1 & 0x0038) == 0x0038 ||
        (p1 & 0x0049) == 0x0049 ||
        (p1 & 0x0054) == 0x0054 ||
        (p1 & 0x0092) == 0x0092 ||
        (p1 & 0x0111) == 0x0111 ||
        (p1 & 0x0124) == 0x0124 ||
        (p1 & 0x01c0) == 0x01c0)
        winner_ = 1;
    else if ((p2 & 0x0007) == 0x0007 ||
             (p2 & 0x0038) == 0x0038 ||
             (p2 & 0x0049) == 0x0049 ||
             (p2 & 0x0054) == 0x0054 ||
             (p2 & 0x0092) == 0x0092 ||
             (p2 & 0x0111) == 0x0111 ||
             (p2 & 0x0124) == 0x0124 ||
             (p2 & 0x01c0) == 0x01c0)
        winner_ = 2;
    else if (p1n + p2n == 9) {
        if (p1n > p2n)
            winner_ = 1;
        else
            winner_ = 2;
    }
    else if (getSlotsAvailable().size() == 0)
        winner_ = 3;
}
