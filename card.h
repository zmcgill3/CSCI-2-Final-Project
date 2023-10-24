#pragma once
#include <map> //Used for to string function
#include <string>

enum cardSuit
{
    DIAMOND,
    CLUB,
    HEART,
    SPADE
};
const cardSuit suitList[4] = {DIAMOND, CLUB, HEART, SPADE};
// Array used to intialize the deck with a for loop

enum cardColor // Makes checking rules for tableaus easy with if color != color
{
    RED,
    BLACK
};

enum cardRank
{
    ACE = 1, // Was easier to do % math with ace equal to one since adding 0 doesn't change the value
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
};
// Enumeration used in tandem with an array for more readable code

// Array is used for initializing the 52 card deck
const cardRank rankList[13] = {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
// This array is also used to intialize the deck
const std::string unicodeList[4] = {"\u2666", "\u2663", "\u2665", "\u2660"};

class card
{
public:
    card(cardRank, cardSuit);
    cardRank getRank();
    cardSuit getSuit();
    cardColor getColor();
    void setRank(cardRank);
    void setSuit(cardSuit);
    void setUnicode(std::string);
    void toString();

protected:
    cardRank rank;
    cardSuit suit;
    cardColor color;
    std::string unicode;
};