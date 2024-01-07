#include "board.h"
#include "base.h"
#include <functional>


//combination checker was tested 

bool has_royal_flush(std::vector<Card>& hand) {
    return false;
}

//& in hand missing by purpose
int has_straight_flush(std::vector<Card> hand) {
    int count = 0;

    if(hand[hand.size()-1].value == 14) {
        hand.insert(hand.begin(), Card((Suit)1, 1));
    }
    
    for(int i=hand.size()-1; i > 0; i--) {
        if(hand[i].value == hand[i-1].value + 1) {
            if(hand[i].suit == hand[i-1].suit) {
                count++;
                if(count == 4) return hand[i + 4].value - 2;
            }
        } else if(hand[i].value != hand[i-1].value) {
            count = 0;
        }
    }

    return 0;
}

int has_four(std::vector<Card>& hand) {
    for(int i=0; i < hand.size() - 1; i++) {
        for(int j=0; j+i < hand.size() - 1; j++) {
            if(hand[i+j].value != hand[i+j+1].value) break;

            int kicker = 0;
            if(j+i+1 < hand.size() - 1) kicker = hand[hand.size()-1].value - 2;
            else kicker = hand[j+i-3].value - 2;
            
            if(j == 2) return (hand[j].value - 2) * 13 + kicker;
        }
    }

    return 0;
}

int has_full_house(std::vector<Card>& hand) {
    int three_value = 0;
    int two_value = 0;
    
    for(int i=hand.size()-1; i > 0; i--) {
        int j = i;
        for(; j > 0; j--) {
            if(hand[j].value != hand[j-1].value) break;
        }

        if(i - j >= 2) {
            if(three_value) {
                if(!two_value) two_value = hand[i].value;
            } else {
                three_value = hand[i].value;
            }
        }

        if(i - j == 1) {
            if(!two_value) two_value = hand[i].value;
        }

        i = j;
    }

    if(two_value && three_value) {
        return (three_value - 2) * 13 + two_value - 2;
    }

    return 0;
}

int has_flush(std::vector<Card>& hand) {
    int suit_counts[4] = {0,0,0,0};

    for(Card c: hand) {
        suit_counts[c.suit]++;
    }

    for(int i=0; i < 4; i++) {
        if(suit_counts[i] >= 5) return true;
    }

    return false;
}

//& missing in hand by purpose
int has_straight(std::vector<Card> hand) {
    int count = 0;
    
    if(hand[hand.size()-1].value == 14) {
        hand.insert(hand.begin(), Card((Suit)1, 1));
    }

    for(int i=hand.size()-1; i > 0; i--) {
        if(hand[i].value == hand[i-1].value + 1) {
            count++;
            if(count == 4) {
                return hand[i + 3].value - 2;
            }
        } else if(hand[i].value != hand[i-1].value) {
            count = 0;
        }
    }

    return 0;
}

int has_three(std::vector<Card>& hand) {
    int count = 0;
    
    for(int i=0; i < hand.size() - 1; i++) {
        if(hand[i].value == hand[i+1].value) {
            count++;
            if(count == 2) {
                int three_value = hand[i].value - 2;
                
                hand.erase(hand.begin() + i - 1, hand.begin() + i + 1);
                
                return (three_value * 169) + ((hand[hand.size() - 1].value - 2) * 13) + ((hand[hand.size() - 2].value - 2));
            }
        } else {
            count = 0;
        }
    }

    return 0;
}

int has_two_pair(std::vector<Card>& hand) {
    int pair_count = 0;
    int pair_values[2] = {0, 0};
    int kicker = 0;

    for(int i=hand.size() - 1; i > 0; i--) {
        if(hand[i].value == hand[i-1].value) {
            pair_values[pair_count++] = hand[i].value - 2;
            if(pair_count == 2){
                if(!kicker)
                    kicker = hand[i-2].value;
                break;
            }
            i--;
        } else if(!kicker){
            kicker = hand[i].value;
        }
    }

    if(pair_count >= 2) return (pair_values[0] * 169) + (pair_values[1] * 13) + (kicker - 2);
    return 0;
}

int has_pair(std::vector<Card>& hand) {
    for(int i=0; i < hand.size(); i++) {
        if(hand[i].value == hand[i+1].value) {
            int pair_value = hand[i].value - 2;
            hand.erase(hand.begin() + i, hand.begin() + i + 1);
            return (pair_value * 2197) + ((hand[hand.size() - 1].value - 2) * 169) + ((hand[hand.size() - 2].value - 2) * 13) + (hand[hand.size() - 3].value - 2);
        }
    }

    return 0;
}

int get_high(Player* player) {
    if(player->hand[0].value > player->hand[1].value) {
        return (player->hand[0].value - 2) * 13 + player->hand[1].value - 2;
    } else {
        return (player->hand[1].value - 2) * 13 + player->hand[0].value - 2;
    }
}

int Board::get_player_hand_value(Player* player) {
    std::vector<Card> hand;

    hand.insert(hand.begin(), &player->hand[0], &player->hand[2]);
    hand.insert(hand.begin() + 2, &cards[0], &cards[n_cards]);
    std::sort(hand.begin(), hand.end());

    int x = 0;
    // Just combinatorics. The value of kickers and the combinations is taken
    // into the number in order of significance
    // Example two-pair: [max_pair_value] + (bigger_pair_value*169) + (smaller_pair_value*13) + kicker

    if(has_royal_flush(hand))          return 33478;
    if((x = has_straight_flush(hand))) return 33465 + x;
    if((x = has_four(hand)))           return 33296 + x;
    if((x = has_full_house(hand)))     return 33127 + x;
    if(has_flush(hand))                return 33126;
    if((x = has_straight(hand)))       return 33113 + x;
    if((x = has_three(hand)))          return 30916 + x; // 12*13^2 + 12*13 + 12 + 1
    if((x = has_two_pair(hand)))       return 28719 + x; // 12*13^3 + 12*13^2 + 12*13 + 12 + 1 + 1
    if((x = has_pair(hand)))           return 169 + x;
    else                               return get_high(player);
}

void Board::showdown() {
    std::vector<std::pair<int, Player*> > player_hand_vals;

    for(auto pl: players) {
        if(pl.second) {
            player_hand_vals.push_back({get_player_hand_value(pl.first), pl.first});
        }
    }

    std::sort(player_hand_vals.begin(), player_hand_vals.end());


    for(int i=player_hand_vals.size() - 1; i > 0; i--) {
        if(player_hand_vals[i].first != player_hand_vals[i-1].first) {
            player_hand_vals.erase(player_hand_vals.begin(), player_hand_vals.begin() + i - 1);
        }
    }

    for(auto pl: player_hand_vals) {
        pl.second->bank += total_bank() / player_hand_vals.size();
    }
}

void Board::deal_cards(Deck& deck, int count) {
    for(int i=0; i < count; i++) {
        add_card(deck.pop());
    }    
}

bool Board::next_phase(Deck& deck) {
    if(phase > 3) return false;
    if(remaining_players() == 1) return false;
    
    round_bank.clear();
    
    phase++;

    if(phase == 1) {
        deal_cards(deck, 3);
    } else {
        deal_cards(deck, 1);
    }

    return true;
}

void Board::print_all_players() {
    for(int i=0; i < total_players; i++) {
        std::cout << players[i].first->name << "(" << players[i].first->bank  << ")|";

        for(auto c: players[i].first->hand) {
            std::cout << c.to_string() << " ";
        }
        for(auto c: cards) {
            std::cout << c.to_string() << " ";
        }

        std::cout << "\n";
    }
}

void Board::print_board(int index) {
    std::vector<std::vector<char> > board(11, std::vector<char>(70, ' '));

    int ti[4][2] = {{8, 24}, {4, 0}, {0, 24}, {4, 50}}; //text indexes (top left of text)

    //player info
    for(int i=0; i < 4; i++, index = next_player(index)) {
        std::string x = players[index].first->to_string();
        for(int j=0; j < x.size(); j++) {
            board[ti[i][0]][ti[i][1] + j] = x[j];
        }

        x = std::to_string(round_bank[players[index].first]) + "C";
        for(int j=0; j < x.size(); j++) {
            board[ti[i][0]+1][ti[i][1] + j] = x[j];
        }
    }

    //players cards
    std::string player_cards = players[index].first->hand[0].to_string() + " " + players[index].first->hand[1].to_string(); 
    for(int i=0; i < player_cards.size(); i++) {
        board[ti[0][0]+2][ti[0][1] + i] = player_cards[i];
    }
    
    //board cards
    std::string board_cards;
    for(int i=0; i < n_cards; i++) {
        board_cards += cards[i].to_string() + " ";
    }
    for(int i=0; i < board_cards.size(); i++) {
        board[ti[1][0]][ti[0][1] + i] = board_cards[i];
    }
    
    
    //print resulting board
    for(int i=0; i < board.size(); i++) {
        for(int j=0; j < board[0].size(); j++) {
            std::cout << board[i][j];
        }
        std::cout << "\n";
    }
    
}

int Board::previous_player(int index) {
    if(remaining_players() == 1) return -1;

    for(int i=index-1; ; i--) {
        if(i < 0) i = total_players - 1;

        if(players[i].second) return i;
    }
}

int Board::next_player(int index) {
    if(remaining_players() == 1) return -1;
    
    for(int i = (index+1) % total_players ;; i = ++i % total_players) {
        if(players[i].second) return i;
    }
}

void Board::bet(Player* player, int amount) {
    bank[player] += amount;
    round_bank[player] += amount;
    player->bank -= amount;
}

void Board::fold_player(int i) {
     players[i].second = false;   
}

int Board::remaining_players() {
    int amount = 0;
    for(auto pl: players) {
        if(pl.second)
            amount++;
    }

    return amount;
}

void Board::next_turn() {
    init();
    curr_bb++;
    curr_bb %= total_players;
}

Board::Board() {
    init();
}

void Board::add_player(Player* player) {
    players.push_back({player, true});
    total_players++;
}

void Board::add_card(Card card) {
    if(n_cards > 4) return;

    cards[n_cards++] = card;
}

int Board::total_bank() {
    int ammount = 0;

    for(auto i: bank)
    {
        ammount += i.second;
    }

    return ammount;
}

void Board::init() {
    bank.clear();
    round_bank.clear();
    for(auto pl: players){
        pl.second = true;
    }
    n_cards = 0;
    phase = 0;
}
