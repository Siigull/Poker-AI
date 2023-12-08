#include <algorithm>
#include <random>
#include <iostream>
#include <string>
#include <cassert>
#include <map>

typedef enum {
    HEARTS,
    DIAMONDS,
    SPADES,
    CLUBS
} Suit;

typedef struct {
    Suit suit;
    int value;
} Card;

class Player {
    public:
        std::string name = "anon";
        int bank;
        Card hand[2];
        int n_cards = 0;

        Player(int bank_);
        Player(std::string name_, int bank_);
        void add_card(Card card);
};

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

std::ostream& operator<<(std::ostream& strm, const Player& p) {
    return strm << p.name << ":" << p.bank;
}

class Board {
    std::map<Player*, int> bank;
    Card cards[5];
    int n_cards = 0;
    int b_blind = 5;

    public:
        int total_bank();
        void init();
        void add_card(Card card);

};

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
    n_cards = 0;
}

class Deck {
    Card cards[52];
    int top = 52;

    public:
        void shuffle();
        void init();
        Deck();
        void deal(Player& player, int count);
        void deal_game(std::initializer_list<Player*> players, int count);
        void deal_board(Board& board, int count);

    private:
        Card pop();

};

void Deck::deal_board(Board& board, int count) {
    for(int i=0; i < 3; i++) {
        board.add_card(pop());
    }
}

Card Deck::pop() {
    if(top)
        return cards[--top];

    assert(false);
}

void Deck::deal_game(std::initializer_list<Player*> players, int count) {
    for(int i=0; i < count; i++) 
    {
        for(auto p: players) 
        {
            deal(*p, 1);
        }
    }
}

void Deck::deal(Player& player, int count) {
    for(int i=0; i < count; i++) 
    {
        player.add_card(pop());
    }
}

Deck::Deck() {
    init();
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 rng(rd());

    std::shuffle(cards, cards + 52, rng);
}

void Deck::init() {
    for(int suit_index = 0; suit_index < 4; suit_index++) 
    {
        for(int i=2; i < 15; i++) 
        {
            cards[suit_index*13 + i - 2] = {(Suit)suit_index, i};
        }
    }

    shuffle();
}

int main() {

    Deck deck;

    Player p1 = Player("Daniel", 1000);

    std::cout << p1;

    return 0;
}