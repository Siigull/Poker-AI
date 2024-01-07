#include "base.h"
#include "card.h"

bool Card::operator< (const Card& card) const
{
    return (value < card.value);
}

Card::Card() {
    
}

Card::Card(Suit suit_, int value_) {
    suit = suit_;
    value = value_;
}

std::string Card::to_string() {
    // static std::vector<std::string> cards = {"🂡", }§
    std::string suits[4] = {"♥", "♦", "♠", "♣"};
    std::string values = "TJQKA";

    std::string x;
    
    if(value >= 10) {
        x += values[value - 10];
    } else {
        x += std::to_string(value);
    }

    x += suits[suit];

    return x;
}
