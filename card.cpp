/* Program name: card.cpp
 * Author: Zachary McGill
 * Date last updated: 5/11/2023
 * Purpose: Program will simulate a game of canfield solitaire using object oriented programming
 */
#include "card.h"
#include <iostream>

static std::map<cardRank, std::string> rankToString =
    {
        {ACE, "A"},
        {TWO, "2"},
        {THREE, "3"},
        {FOUR, "4"},
        {FIVE, "5"},
        {SIX, "6"},
        {SEVEN, "7"},
        {EIGHT, "8"},
        {NINE, "9"},
        {TEN, "10"},
        {JACK, "J"},
        {QUEEN, "Q"},
        {KING, "K"}};

card::card(cardRank rank, cardSuit suit) // Constructor for a card
{
    this->rank = rank;
    this->suit = suit;
    if (suit == DIAMOND) // Intializes unicode art to match card suit
    {
        this->unicode = "\u2666";
    }
    else if (suit == CLUB) // Intializes unicode art to match card suit
    {
        this->unicode = "\u2663";
    }
    else if (suit == HEART) // Intializes unicode art to match card suit
    {
        this->unicode = "\u2665";
    }
    else if (suit == SPADE) // Intializes unicode art to match card suit
    {
        this->unicode = "\u2660";
    }
    if (suit == DIAMOND || suit == HEART) // Intializes color instead of making another array and for loop
    {
        this->color = RED;
    }
    else
    {
        this->color = BLACK;
    }
}

cardRank card::getRank()
{
    return this->rank;
}

cardSuit card::getSuit()
{
    return this->suit;
}

cardColor card::getColor()
{
    return this->color;
}

void card::setRank(cardRank rank)
{
    this->rank = rank;
}

void card::setSuit(cardSuit suit)
{
    this->suit = suit;
}

void card::setUnicode(std::string unicode)
{
    this->unicode = unicode;
}

void card::toString()
{
    std::cout << rankToString.at(getRank()) << this->unicode; // Extracts getRank() by character and passes it to the map. I found the member function at() while doing some online research and I don't understand it 100% but it was really helpful
}
