#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  int hand_cards = hand->n_cards;
  card_t ** i = hand->cards;
  for (int j = 0; j < hand_cards; j++)
    {
      print_card(**(i + j));
      printf(" ");
    }

  }

int deck_contains(deck_t * d, card_t c) {
  int hand_cards = d->n_cards;
  card_t ** index = d->cards;

  card_t cards;
  for (int i =0;i<hand_cards;i++)
    {
      cards = **(index+i);
      if ((cards.suit == c.suit) &(cards.value == c.value))
	{
	  return 1;
	}
    }
  return 0;
}

void shuffle(deck_t * d){
  int hand_size = d->n_cards;
  card_t ** card_temp = d->cards;

  for (int i = hand_size-1; i>0;i--)
    {
      int j = rand()%(i-0+1);
      card_t * temp = card_temp[j];
      card_temp[j] = card_temp[i];
      card_temp[i] = temp;
    }
}

void assert_full_deck(deck_t * d) {
  card_t ** card_temp = d->cards;
  int hand_size = d->n_cards;
  for (int i =0;i<hand_size;i++)
    {
      card_t current_card = **(card_temp+i);
      int count =0;
      for(int j=0;j<hand_size;j++)
	{
	  card_t card_to_compare = **(card_temp+j);
	  if ((current_card.suit == card_to_compare.suit) &(current_card.value == card_to_compare.value))
	    {
	      count++;
	    }
	}
      assert(count==1);

    }
}
