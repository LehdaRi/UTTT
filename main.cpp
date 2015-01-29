#include "UtttGame.hpp"

#include <iostream>
#include <random>
#include <ctime>


#define NROUNDS 1000000


std::default_random_engine rnd;


int main(void) {
    rnd.seed(time(NULL));

    unsigned nWinners[3] = {0};

    for (auto n=0u; n<NROUNDS; ++n) {
        UtttGame game;
        short player = 1;

        std::vector<unsigned> slots;
        slots.reserve(81);

        for (auto i=0u; i<81; ++i)
            slots.push_back(i);

        while (game.getWinner() == 0) {
            slots = game.play(player, slots[rnd() % slots.size()]);
            player = player ^ 0x03;
        }

        nWinners[game.getWinner()-1]++;

        printf("%0.2f%%\r", (float)(n*100)/NROUNDS);
    }

    printf("Player 1 won %u times (%0.2f%%)\n", nWinners[0], (float)(nWinners[0]*100)/NROUNDS);
    printf("Player 2 won %u times (%0.2f%%)\n", nWinners[1], (float)(nWinners[1]*100)/NROUNDS);
    printf("There was a tie %u times (%0.2f%%)\n", nWinners[2], (float)(nWinners[2]*100)/NROUNDS);

    return 0;
}
