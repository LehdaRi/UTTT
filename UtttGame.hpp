#ifndef UTTTGAME_HPP
#define UTTTGAME_HPP


#include <vector>


class UtttGame {
public:
    UtttGame(void);

    std::vector<unsigned> play(unsigned player, unsigned coord);
    std::vector<unsigned> play(unsigned player, unsigned x, unsigned y);

    std::vector<unsigned> getSlotsAvailable(unsigned sgx, unsigned sgy) const;
    std::vector<unsigned> getSlotsAvailable(void) const;

    short getWinner(void) const;

    void printGame(void) const;
    void printSmallGames(void) const;

private:
    short board_[81];
    short smallGamesWon_[3][3];
    short winner_;
    unsigned lastPlayed_;

    void checkSmallGame(unsigned sgx, unsigned sgy);
    void checkGame(void);
};


#endif // UTTTGAME_HPP

