# JTMS-14
# a11_p1.py
# Faraz Ahmad
# fahmad@jacobs-university.de

from cards import Deck, Card

class Deadoralive(object):
    def __init__(self):
        self._deck = Deck()
        self._deck.shuffle()
        self.player_wins = 0
        self.dealer_wins = 0

    # game implementation
    def play(self):
        while len(self._deck) > 0:

            #draw a card
            player_card = self._deck.deal()
            dealer_card = self._deck.deal()

            if player_card is None or dealer_card is None:
                break

            print(f"Player draws: {player_card}")
            print(f"Dealer draws: {dealer_card}")

            if player_card.rank > dealer_card.rank:
                self.player_wins += 1
                print("Player wins this round.")
            elif player_card.rank < dealer_card.rank:
                self.dealer_wins += 1
                print("Dealer wins this round.")
            else:
                # Ranks are equal, check suits
                player_suit_priority = Card.SUITS.index(player_card.suit)
                dealer_suit_priority = Card.SUITS.index(dealer_card.suit)
                
                if player_suit_priority < dealer_suit_priority:
                    self.player_wins += 1
                    print("Player wins this round.")
                else:
                    self.dealer_wins += 1
                    print("Dealer wins this round.")

        # Game over, print results
        print("\nGame over!")
        print(f"Player wins: {self.player_wins}")
        print(f"Dealer wins: {self.dealer_wins}")

def main():
    game = Deadoralive()
    game.play()

main()