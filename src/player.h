#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "card.h"

class Player {
    public:
        std::string name = "anon";
        int bank;
        Card hand[2];
        int n_cards = 0;

        Player(int bank_);
        Player(std::string name_, int bank_);
        void add_card(Card card);
        virtual int make_move(int bet) = 0;
        std::string to_string();
};

class AI_Player: public Player {
    public:
        int make_move(int bet);
        AI_Player(std::string name_, int bank_) : Player(name_, bank_) {}
        AI_Player(int bank_) : Player(bank_) {}
};

class Human_Player: public Player {
    public:
        int make_move(int bet);
        Human_Player(std::string name_, int bank_) : Player(name_, bank_) {}
        Human_Player(int bank_) : Player(bank_) {}
};

#endif // PLAYER_H
