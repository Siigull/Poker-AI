#ifndef DECK_H
#define DECK_H

#include "card.h"
#include "player.h"

class Deck {
    int top = 52;

    public:
        Card cards[52];
        void shuffle();
        void init();
        Deck();
        void deal(Player& player, int count);
        void deal_game(std::vector<std::pair<Player*, bool> >& players, int count);
        Card deal_card();
        Card pop();

};

#endif //DECK_H