#ifndef CARD_H
#define CARD_H

#include <string>

typedef enum {
    HEARTS = 0,
    DIAMONDS = 1,
    SPADES = 2,
    CLUBS = 3
} Suit;

class Card {

    public:
        Suit suit;
        int value;
        std::string to_string();
        Card(Suit suit_, int value_);
        Card();
        bool operator<(const Card& card) const;

};

#endif //CARD_H
