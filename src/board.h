#ifndef BOARD_H
#define BOARD_H

#include "base.h"
#include "player.h"
#include "card.h"
#include "deck.h"

class Board {
    std::map<Player*, int> bank;
    
    public:
        int phase = 0;
        Card cards[5];
        int n_cards = 0;
        int bb = 10;
        int curr_bb = 0;
        std::vector<std::pair<Player*, bool> > players;
        int total_players;
        std::map<Player*, int> round_bank;
        int total_bank();
        void print_all_players();
        void print_board(int index);
        void init();
        void add_card(Card card);
        void add_player(Player* player);
        void fold_player(int n);
        void bet(Player* player, int amount);
        void next_turn();
        bool next_phase(Deck& deck);
        void deal_cards(Deck& deck, int count);
        int next_player(int index);
        int previous_player(int index);
        int remaining_players();
        void showdown();
        Board();
        int get_player_hand_value(Player* player);

    private:
        bool more_than(Player* player1, Player* player2);

};

#endif //BOARD_h