/* Program name: pile.cpp
 * Author: Zachary McGill
 * Date last updated: 5/11/2023
 * Purpose: Program will simulate a game of canfield solitaire using object oriented programming
 */
#include "pile.h"
#include <iostream>
#include <random>

pile::pile()
{
    this->cardVector = cardVector;
}

void pile::setCardVector(std::vector<card> cardVector)
{
    this->cardVector = cardVector;
}

std::vector<card> pile::getCardVector()
{
    return this->cardVector;
}

void pile::resetPile()
{
    cardVector.clear();
}

deck::deck()
{
    for (int i = 0; i < 4; i++) // Entire 52 card deck is intialized
    {
        for (int j = 0; j < 13; j++)
        {
            this->cardVector.push_back(card(rankList[j], suitList[i]));
        }
    }
    shuffle(cardVector.begin(), cardVector.end(), std::default_random_engine(7)); // Shuffles the cards around with a constant seed
    // Could seed the random engine with srand and time to make it truly random for more realistic application, but it's impractical for a graded assignment.
    this->numCards = 52;
    this->cardShowing = 53;
}

void deck::reset() // Used for play again
{
    this->cardVector.clear();
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            this->cardVector.push_back(card(rankList[j], suitList[i]));
        }
    }
    this->numCards = 52;
    this->cardShowing = 53;
}

int deck::getShowingCardNum()
{
    return this->cardShowing;
}

card deck::playCardStart() // Only used for initializing other piles
{
    card returnCard = this->cardVector[(this->numCards - 1)]; // Copies top card to be returned at end of function
    this->cardVector.pop_back();                              // Deletes top card
    this->numCards -= 1;                                      // Lowers number of cards by one
    this->cardShowing = this->cardShowing - 1;                // Lowers the card showing by 1
    return returnCard;
}

void deck::draw()
{
    if (this->cardShowing == 1) // Proper math to allow for a 3 card draw that follows correct rules
    {
        this->cardShowing = this->numCards + 1;
    }
    else
    {
        this->cardShowing = this->cardShowing - 3;
        if (this->cardShowing <= 0)
        {
            this->cardShowing = 1;
        }
    }
}

int deck::getNumCards()
{
    return this->numCards;
}

void deck::toString()
{
    if (numCards == 0 || this->cardShowing > this->numCards)
        std::cout << "    ";
    else
    {
        this->cardVector[cardShowing - 1].toString();
        std::cout << "  ";
    }
}

void deck::toString2()
{
    for (int i = 0; i < 3; i++)
    {
        if (numCards == 0 || (this->cardShowing + i) > this->numCards)
            std::cout << "    ";
        else
        {
            this->cardVector[cardShowing - 1 + i].toString();
            std::cout << "  ";
        }
    }
}

card deck::getTopCard()
{
    return this->cardVector[cardShowing - 1];
}

card deck::playCard()
{
    card returnCard = this->cardVector[(this->cardShowing - 1)];
    this->cardVector.erase(cardVector.begin() + cardShowing - 1);
    this->numCards -= 1;
    return returnCard;
}

replenishPile::replenishPile(deck &theDeck)
{
    for (int i = 0; i < 13; i++)
    {
        this->cardVector.push_back(theDeck.playCardStart());
    }
    this->numCards = 13;
}

void replenishPile::reset(deck &theDeck)
{
    for (int i = 0; i < 13; i++)
    {
        this->cardVector.push_back(theDeck.playCardStart());
    }
    this->numCards = 13;
}

card replenishPile::playCard()
{
    card returnCard = this->cardVector[numCards - 1];
    this->cardVector.pop_back();
    this->numCards = this->numCards - 1;
    return returnCard;
}

void replenishPile::toString()
{
    if (numCards == 0)
    {
        std::cout << "    ";
    }
    else
    {
        this->cardVector[numCards - 1].toString();
    }
}

card replenishPile::getTopCard()
{
    return this->cardVector[numCards - 1];
}

int replenishPile::getNumCards()
{
    return this->numCards;
}

tableauPile::tableauPile(deck &theDeck)
{
    this->cardVector.push_back(theDeck.playCardStart());
    this->numCards = 1;
}

card tableauPile::playCard()
{
    card returnCard = this->cardVector[numCards - 1];
    this->cardVector.pop_back();
    this->numCards = this->numCards - 1;
    return returnCard;
}

void tableauPile::toString()
{
    if (numCards == 0)
    {
        std::cout << "    ";
    }
    else
    {
        this->cardVector[numCards - 1].toString();
    }
}

void tableauPile::toString2()
{
    if (numCards == 0)
        std::cout << "    ";
    else
        this->cardVector[0].toString();
}

card tableauPile::getTopCard()
{
    return this->cardVector[numCards - 1];
}

card tableauPile::getBottomCard()
{
    return this->cardVector[0];
}

void tableauPile::reset(deck &theDeck)
{
    this->cardVector.clear();
    this->cardVector.push_back(theDeck.playCardStart());
    this->numCards = 1;
}

void tableauPile::obtainCard(card c)
{
    this->cardVector.push_back(c);
    this->numCards += 1;
}

int tableauPile::getNumCards()
{
    return this->numCards;
}

foundationPile::foundationPile()
{
    this->numCards = 0;
}

foundationPile::foundationPile(cardRank rank)
{
    this->foundationCard = rank;
    this->numCards = 0;
}

foundationPile::foundationPile(deck &theDeck)
{
    this->cardVector.push_back(theDeck.playCardStart());
    this->foundationCard = this->cardVector[0].getRank();
    this->numCards = 1;
}

void foundationPile::obtainCard(card newCard)
{
    this->cardVector.push_back(newCard);
    this->numCards += 1;
}

void foundationPile::toString()
{
    if (numCards == 0)
    {
        std::cout << "    ";
    }
    else
    {
        this->cardVector[numCards - 1].toString();
    }
}

card foundationPile::getTopCard()
{
    return this->cardVector[numCards - 1];
}

void foundationPile::reset(deck &theDeck)
{
    cardVector.clear();
    this->cardVector.push_back(theDeck.playCardStart());
    this->foundationCard = this->cardVector[0].getRank();
    this->numCards = 1;
}

void foundationPile::reset(cardRank r)
{
    cardVector.clear();
    this->foundationCard = r;
    this->numCards = 0;
}

int foundationPile::getNumCards()
{
    return this->numCards;
}

cardRank foundationPile::getFoundationCardRank()
{
    return this->foundationCard;
}
