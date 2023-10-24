#pragma once
#include <vector>
#include <algorithm>
#include "card.h"

class pile // Parent class pile
{
public:
    pile();                                // Defualt constructor to make inheriting easier
    void setCardVector(std::vector<card>); // Didn't use, but can think of plenty of places where I could have, but thought of doing something else first.
    std::vector<card> getCardVector();     // Very helpful for comparing top cards of child classes
    void resetPile();                      // Useful for play again function

protected:
    std::vector<card> cardVector; // Vector that represents a pile of cards with each item being a card
    int cardShowing;              // What card is showing or the index + 1 of the card showing
    int numCards;
};

class deck : public pile
{
public:
    deck();
    card playCardStart(); // Use this function to intialize the other inherited classes, but had to create a second play card function because this one used pop_back and I needed to make a function that allowed me to remove a card from the middle of the deck. I kept this one though because I already tested all of the intializations and they were correct.
    void draw();          // Draw 3 cards
    void toString();      // Output top showing card
    void toString2();     // Output all 3 cards drawn
    card playCard();
    int getNumCards();
    card getTopCard();
    void reset();
    int getShowingCardNum(); // Return card number of the top card on the deck
};

class foundationPile : public pile
{
public:
    foundationPile();
    foundationPile(cardRank); // Used to initialize the last 3 foundation piles once the foundation rank is known
    foundationPile(deck &);   // Used to initialize the first foundation from the deck in the start
    void obtainCard(card);    // Add card to pile and change number of cards
    void toString();          // Output top card
    cardRank getFoundationCardRank();
    int getNumCards();
    card getTopCard();
    void reset(deck &theDeck); // Reset deck back to the start for play again
    void reset(cardRank r);

protected:
    cardRank foundationCard;
};

class tableauPile : public pile
{
public:
    tableauPile(deck &);
    card playCard();
    void toString();
    void toString2();
    void obtainCard(card c);
    int getNumCards();
    card getTopCard();
    card getBottomCard(); // Returns the bottom card used for checking legality of moving an entire tableau pile on to another.
    void reset(deck &theDeck);
};

class replenishPile : public pile
{
public:
    replenishPile(deck &); // No new functions for this inherited class
    card playCard();
    void toString();
    int getNumCards();
    card getTopCard();
    void reset(deck &theDeck);
};