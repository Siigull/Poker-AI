#include "deck.h"
#include "base.h"

Card Deck::pop() {
    if(top)
        return cards[--top];

    assert(false);
}

void Deck::deal_game(std::vector<std::pair<Player*, bool> >& players, int count) {
    for(int i=0; i < count; i++) 
    {
        for(auto p: players) 
        {
            deal(*(p.first), 1);
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
            cards[suit_index*13 + i - 2] = Card((Suit)suit_index, i);
        }
    }

    top = 52;

    shuffle();
}
