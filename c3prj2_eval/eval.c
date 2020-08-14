#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) {
  const card_t * const * hand1 = vp1;
  const card_t * const * hand2 = vp2;
  if ((** hand1).value > (** hand2).value)
    {
      return 1;
    } else {
    if ((** hand1).suit > (**hand2).suit)
      {
	return -1;
      }
    else if ((**hand1).suit < (**hand2).suit)
      {
	return 1;
      }
  }
  return 0;
}

suit_t flush_suit(deck_t * hand) {

  size_t hand_size = hand->n_cards;
  card_t ** card_total = hand->cards;
  int s =0;
  int h =0;
  int c =0;
  int d =0;

  for (int i =0;i < hand_size;i++)
    {
      card_t current_card = **(card_total+i);
      switch (current_card.suit)
	{
	case SPADES:
	  s++;
	  break;
	case HEARTS:
	  h++;
	  break;
	case DIAMONDS:
	  d++;
	  break;
	case CLUBS:
	  c++;
	  break;
	default:
	  break;
	}
    }
  if (s>=5)
    {
      return SPADES;
    }
  if (h>=5)
    {
      return HEARTS;
    }
  if (d>=5)
    {
      return DIAMONDS;
    }
  if (c>=5)
    {
      return CLUBS;
    }
  return NUM_SUITS;
}

unsigned get_largest_element(unsigned * arr, size_t n) {
  unsigned largest = arr[0];
  for (int i =0; i<n;i++)
    {
      if (arr[i]>largest)
	{
	  largest = arr[i];
	}
    }
  return largest;

}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  size_t index = -1;
  for (size_t i =0; i<n;i++)
    {
      if (match_counts[i] == n_of_akind)
	{
	  index =i;
	  break;
	}
    }
  assert (index !=-1);
  return index;
}
ssize_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {

  ssize_t index = -1;
  card_t ** card_in_hand = hand->cards;
  size_t size = hand->n_cards;
  unsigned current_value = (**(card_in_hand+match_idx)).value;
  unsigned match_temp;
  unsigned value_temp;
  for (size_t i =0; i<size; i++)
    {
      match_temp = match_counts[i];
      value_temp = (**(card_in_hand+i)).value;
      if ((match_temp)>1 &&(value_temp!=current_value))
	{
	  index = i;
	  return index;
	}
    }
  return -1;
}


int is_ace_low_straight_at(deck_t * hand, size_t index, suit_t fs)
{
  //return 0 when no ace_low straight, 1 when there is ace low
  card_t ** hand_card = hand->cards;
  size_t size = hand->n_cards;
  // check whether the value at idx is ace
  if ((**(hand_card+index)).value != VALUE_ACE)
    {
      return 0;
    }
  // first_value =ace and do not care suit
  if (fs == NUM_SUITS)
    {
      int count = 1;
      size_t idx_temp =0;
      // find whether 5 exist
      for ( size_t i = index+1; i < size;i++)
	{
	  if ((**(hand_card+i)).value == 5)
	    {
	      idx_temp = i;
	      break;
	    }
	}
      if ((idx_temp==0)||idx_temp>3) {return 0;}
      count++;
      //A A 5 5 4 3 2
      // check whether 4 3 2 is follwoing 5
      unsigned current_card_value = (**(hand_card+idx_temp)).value;
      for (size_t m =idx_temp;m<size;m++)
	{
	  if ((**(hand_card+m)).value == current_card_value){continue;}
	  if ((**(hand_card+m)).value == current_card_value -1)
	    {
	      current_card_value = (**(hand_card+m)).value ;
	      count++;
	    }
	}
      if (count>=5){return 1;}
      else {return 0;}
    }

  // take in the consideration of suit and has already check the ace at the index)
  if ((**(hand_card+index)).suit != fs){return 0;}
  int count2 =1;
  size_t idx2 = 0;
  //As Ks Qs Js 0s 9s 8s
  //find where is 5
  for (size_t k=index+1;k<size;k++)
    {
      if ((**(hand_card+k)).value == 5 && (**(hand_card+k)).suit == fs)
	{
	  idx2 = k;
	  break;
	}
    }
  if ((idx2== 0)||idx2>3) {return 0;}
  count2++;
  unsigned card_curr_value = (**(hand_card+idx2)).value;
  for (size_t j=idx2+1;j<size;j++)
    {
      //Ac As Kc Ks Qs Js 0s 2---6
      if ((**(hand_card+j)).suit != fs){continue;}
      if ((**(hand_card+j)).value == card_curr_value -1)
	{
	  card_curr_value = (**(hand_card+j)).value ;
	  count2++;
	}
    }
  if (count2==5){return 1;}
  else {return 0;}

}





int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  if (is_ace_low_straight_at(hand,index,fs)==1){return -1;}
  int count = 1;
  // for fs =NUM
  card_t ** hand_card = hand->cards;
  size_t size = hand->n_cards;
  if (fs == NUM_SUITS)
    {
      unsigned card_curr_value1 = (**(hand_card+index)).value;
      for (size_t i=index;i<size;i++)
	{
	  //Ac As Kc Ks Qs Js 0s 2---6
	  //As Jd 9h 8c 7d 6c 5d 2---6
	  if ((**(hand_card+i)).value == card_curr_value1){continue;}
	  if ((**(hand_card+i)).value == card_curr_value1 -1)
	    {
	      card_curr_value1= (**(hand_card+i)).value ;
	      count++;
	    }
	}
      if (count >=5){return 1;}
      else {return 0;}
    }
  // for fs =others
  else
    {
      if ((**(hand_card+index)).suit != fs ){return 0;}
      unsigned card_curr_value = (**(hand_card+index)).value;
      for (size_t j=index+1;j<size;j++)
	{
	  //Ac As Kc Ks Qs Js 0s 2---6
	  if ((**(hand_card+j)).suit != fs){continue;}
	  if ((**(hand_card+j)).value == card_curr_value -1)
	    {
	      card_curr_value = (**(hand_card+j)).value ;
	      count++;
	    }

	}
      if(count>=5){return 1;}
      else {return 0;}

    }
}

hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {

  hand_eval_t ans;

  ans.ranking = what;
  card_t ** card_in_hand = hand->cards;
  size_t hand_size = hand->n_cards;
  unsigned count = n;

  for (unsigned i = 0;i<n;i++)
    {
      ans.cards[i] = *(card_in_hand+idx+i);
    }
  for (size_t j=0;j<idx;j++)
    {
      ans.cards[j+n] = *(card_in_hand+j);
      count++;
      if (count==5){break;}
    }
  if (count<5)
    {
      for ( size_t k = idx +n;k<hand_size;k++)
	{
	  ans.cards[count] = *(card_in_hand+k);
	  count++;
	  if (count==5){break;}
	}
    }
  return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {
  qsort(hand1->cards, hand1 -> n_cards, sizeof(card_t), card_ptr_comp);
  qsort(hand2->cards, hand2 -> n_cards, sizeof(card_t), card_ptr_comp);
  hand_eval_t hand11= evaluate_hand(hand1);
  hand_eval_t hand22= evaluate_hand(hand2);
  if (hand11.ranking < hand22.ranking) return 1;
  else if (hand11.ranking > hand22.ranking) return -1;
  else {
    for (size_t i=0 ;i<5;i++){
      card_t * card1=hand11.cards[i];
      card_t * card2=hand22.cards[i];
      if (card1 -> value > card2->value) return 1;
      else if  (card1->value < card2->value) return -1;
      else continue;
    }
  }
  
  return 0;
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand) ;

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
