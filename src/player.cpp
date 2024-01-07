#include "card.h"
#include "base.h"
#include "player.h"

#include <map>

typedef struct State {
    int player_banks[4] = {0,0,0,0}; // negative value == player folded
    uint8_t players; //bit 0 player 0...
    uint8_t n_players;
    uint8_t last_player;
    uint8_t curr_player;
} State;

typedef struct Node {
    int value = 0;
    int n_iters = 0;

    Node* parent = NULL;
    Node* leaf[5] = {NULL, NULL, NULL, NULL, NULL};
    int n_leafs;

    State state;
} Node;

Node* get_biggest_node(std::map<Node*, int>& ucb) {
    int max = INT_MAX;
    Node* max_node;
    
    for(auto node: ucb) {
        if(node.second > max) {
            max = node.second;
            max_node = node.first;
        }
    }

    return max_node;
}

int next_player(uint8_t players, uint8_t player_index, uint8_t n_players) {
    for(int i = (player_index + 1) % n_players; i != player_index; i = ++i % n_players) {
        if((players >> i) & 1) return i;
    }

    return -1;
}

int previous_player(uint8_t players, uint8_t player_index, uint8_t n_players) {
    
    
    for(int i = (player_index - 1) % n_players; i != player_index; i = --i % n_players) {
        if((players >> i) & 1) return i;
    }

    return -1;
}

void add_children(Node* node) {
    int curr_player = next_player(node->state.players, node->state.curr_player, node->state.n_players);
    int bet = 0;
    
    int pot = 0;
    int i = curr_player;

    do {
        i = next_player(node->state.players, curr_player, node->state.n_players);
        pot += node->state.player_banks[i];
        if(bet < node->state.player_banks[i]) {
            bet = node->state.player_banks[i];
        }
    } while(i != curr_player);
    
    Node* new_node_call = new Node;
    node->leaf[0] = new_node_call;
    new_node_call->state.player_banks[curr_player] += bet;
    if(node->state.last_player == node->state.curr_player) {
        
    }

    Node* new_node_4 = new Node;
    node->leaf[1] = new_node_4;
    new_node_4->state.player_banks[curr_player] += pot/4;

    
    Node* new_node_2 = new Node;
    node->leaf[0] = new_node_2;
    new_node_2->state.player_banks[curr_player] += pot/2;

    
    Node* new_node_1 = new Node;
    node->leaf[0] = new_node_1;
    new_node_1->state.player_banks[curr_player] += pot;

    
    Node* new_node_fold = new Node;
    node->leaf[0] = new_node_fold;
    new_node_fold->state.player_banks[curr_player] += 0;
}

int rollout() {
    
}

int AI_Player::make_move(int bet) {
    Node moves[5];
    // std::map<Node*, int> ucb;

    // for(int i=0; i < 5; i++) {
    //     ucb[&moves[i]] = INT_MAX;
    // }

    // for(int i=0; i < 1000; i++) {
    //     Node* vis = get_biggest_node(ucb);
    //     if(vis->n_iters > 1) {
    //         add_children(vis, vis->state.pot, vis->state.bet);
    //     }
        
    // }
    
    return bet;
}

///////////////////////////////////

int Human_Player::make_move(int bet) {
    int move = -1;
    std::cout << "\n" << name << " bank:" << bank << "C\n";

    if(bet >= bank) {
        while(1) {
            std::cout << "1: All in\n" << "2: Fold\n";
            std::cin >> move;

            if(move < 1 || move > 2) {
                std::cout << "Not a valid move";
            } else {
                break;
            }
        }

        if(move == 1) return bank;
        else return -1;
    }

    while(1) {
        std::cout << "1: Call " << bet << "\n" << "2: Fold\n" << "3: Raise\n";
        std::cout << "Move:";
        std::cin >> move;
        if(move < 1 || move > 3) {
            std::cout << "Not a valid move\n";
        } else {
            break;
        }
    }

    if(move == 1) {
        return bet;
    } else if(move == 2) {
        return -1;
    } else {
        int raise = 0;
        while(1) {
            std::cout << "Raise amount:";
            std::cin >> raise;
            if(raise <= bet) {
                std::cout << "Raise has to be bigger than bet\n";
            } else if(raise > bank){
                std::cout << "You dont have enough money\n";
            } else {
                break;
            }
        }
        
        return raise;
    }
}

/////////////////////////////////

void Player::add_card(Card card) {
    if(n_cards > 1) return;

    hand[n_cards++] = card;
}

Player::Player(int bank_) {
    bank = bank_;
}

Player::Player(std::string name_, int bank_) {
    name = name_;
    bank = bank_;
}

std::string Player::to_string() {
    std::string x;
    x += name + " bank:" + std::to_string(bank);

    return x;
}

std::ostream& operator<<(std::ostream& strm, const Player& p) {
    return strm << p.name << ":" << p.bank;
}
