#include "base.h"
#include "board.h"
#include "deck.h"
#include "player.h"
#include "card.h"

#define FOLD -1

int main() {
    Deck deck;

    Player *p1 = new Human_Player("Daniel", 1000);
    Player *p2 = new Human_Player("Krysa", 1000);
    Player *p3 = new Human_Player("Pes", 1000);
    Player *p4 = new Human_Player("Kocka", 1000);
    // Player *p4 = new AI_Player("Kocka", 1000);

    Board board;
    board.add_player(p1);
    board.add_player(p2);
    board.add_player(p3);
    board.add_player(p4);

    bool game = true;
    
    while(game) {
        deck.init();
        board.init();

        //preflop
        int last_player = board.curr_bb;
        int small_blind_player = board.previous_player(last_player);
        int curr_bet = board.bb;

        deck.deal_game(board.players, 2);

        board.bet(board.players[last_player].first, std::min(curr_bet, board.players[last_player].first->bank));
        board.bet(board.players[small_blind_player].first, std::min(curr_bet / 2, board.players[small_blind_player].first->bank));

        for(int phase = 0; phase < 4; phase++) {
            for(int i = board.next_player(last_player); ; i = board.next_player(i)){
                if(i == -1) {
                    break;
                }

                Player* curr_player = board.players[i].first;

                system("clear");
    
                board.print_board(i);
            
                //TODO(change make move to be implemented in board)
                int move = curr_player->make_move(curr_bet - board.round_bank[curr_player]);

                if(move == FOLD) {
                    board.fold_player(i);
                } else {
                    if(move + board.round_bank[curr_player] > curr_bet) {
                        last_player = board.previous_player(i);
                        curr_bet = move + board.round_bank[curr_player];
                    }

                    board.bet(curr_player, move);
                }

                if(i == last_player) break;
            }
            
            curr_bet = 0;
            
            if(!board.next_phase(deck)) break;
        }
               
        board.showdown();
        board.print_all_players();

        board.next_turn();

        char x;
        while(1) {
            std::cout << "next round(y/n):";
            std::cin >> x;

            if(x != 'y' && x != 'n') {
                std::cout << "Bad input\n";
            } else {
                break;
            }
        }

        if(x == 'n') break;
    }


    return 0;
}