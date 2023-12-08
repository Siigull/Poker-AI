#include <algorithm>
#include <random>
#include <iostream>

class Deck {
    Card cards[52];

    public:
        void shuffle();
        void init();

};

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 rng(rd());

    std::shuffle(cards, cards + 52, rng);
}

void Deck::init() {
    cards = {{A, }};
}

class Player {

}

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


int main() {

    Deck deck;

    return 0;
}