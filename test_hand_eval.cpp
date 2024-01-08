#include "src/card.h"
#include "src/board.h"
#include "src/player.h"

void test() {
  Deck deck = Deck();
  deck.init();

  Board board = Board();
  board.next_phase(deck);
  board.next_phase(deck);
  board.next_phase(deck);
  board.next_phase(deck);

  Player player = Player("anon", 100);
  player.hand[0] = deck.pop();
  player.hand[1] = deck.pop();

  std::cout << player.hand[0].to_string() << " " << player.hand[1].to_string() << "|";
  for(int i=0; i < board.n_cards; i++) {
    std::cout << board.cards[i].to_string() << " ";
  }

  // fflush(stdout);

  int x = board.get_player_hand_value(&player);

  if(x == 33478) std::cout << ":" << x << "|royalflush";
  else if(x >= 33465) std::cout << ":" << x << "|straightflush";
  else if(x >= 33296) std::cout << ":" << x << "|four of a kind";
  else if(x >= 33127) std::cout << ":" << x << "|fullhouse";
  else if(x >= 33126) std::cout << ":" << x << "|flush";
  else if(x >= 33113) std::cout << ":" << x << "|straight";
  else if(x >= 30916) std::cout << ":" << x << "|three";
  else if(x >= 28719) std::cout << ":" << x << "|two pair";
  else if(x >= 169) std::cout << ":" << x << "|pair";
  else std::cout << ":" << x << "|high card";

  std::cout << "\n";
}

int main(int argc, char* argv[]) {
  int count = 100;
  if(argc == 2) {
    count = atoi(argv[1]);
  }
  
  for(int i=0; i < count; i++) {
    test();
  }

  return 0;
}
