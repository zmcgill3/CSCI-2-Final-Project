/* Program name: main.cpp
 * Author: Zachary McGill
 * Date last updated: 5/11/2023
 * Purpose: Program will simulate a game of canfield solitaire using object oriented programming
 */
#include <iostream>
#include "card.h" //Including card header file in to my main
#include "pile.h" //Including pile
#include <string> //Allows strings of characters to be saved to variables
#include <iomanip>
#include <fstream> //Used for keeping an appendable score board
#include <climits>
#include <cmath>
#include <vector>

void playFromTableau(tableauPile &t); // Used object oriented programming and functions to break each step into an idea
void playFromDeck();
void playFromReplenish(); // Use functions to gather where the user wants to from
void draw();
void showBoard(); // Shows a nice display of the board and some information
void mainMenu();  // Prompts user to get information for flow control
void pickFromTableau();
int whereToPlay(); // Returns a number that corresponds to what pile the card will be played on
tableauPile whereToPlayTableau();
foundationPile whereToPlayFoundation();
void nextPileFunc(card c); // Number mentioned above is a global variable so only a card needs to be passed and this function can play the card on to the correct pile
void win();
void playAgain();
void moveTableau(tableauPile &t); // Function for moving an entire pile
int score();                      // Creates a score for how many cards are in the foundation piles
void scoreBoard();

deck theDeck; // Intializing the 10 piles needed to play as global objects
replenishPile theReplenishPile(theDeck);
foundationPile foundationPile1(theDeck);
foundationPile foundationPile2(foundationPile1.getCardVector()[0].getRank());
foundationPile foundationPile3(foundationPile1.getCardVector()[0].getRank());
foundationPile foundationPile4(foundationPile1.getCardVector()[0].getRank());
tableauPile tableauPile1(theDeck);
tableauPile tableauPile2(theDeck);
tableauPile tableauPile3(theDeck);
tableauPile tableauPile4(theDeck);
int nextPile = 0;        // This value will be set to 1-8 depending on what pile is about to have a card played on it
int continuePlaying = 1; // Used for gameplay loop

int main()
{
    std::cout << "Hello welcome to Canfield!" << std::endl // Welcome message
              << std::endl;
    while (continuePlaying) // Gameplay loop
    {
        mainMenu(); // Prompts user with intial gameplay options and calls functions accordingly
        win();      // Checks if user has won every gameplay loop
    }
    return 0;
}

void showBoard() // Displays all piles on the part with unicode art and strings with some information
{
    std::cout << "Foundation piles-->         ";
    foundationPile1.toString();
    std::cout << "  ";
    foundationPile2.toString();
    std::cout << "  ";
    foundationPile3.toString();
    std::cout << "  ";
    foundationPile4.toString();
    std::cout << "Score: " << score();
    std::cout << std::endl;
    std::cout << "Replenish pile-->       ";
    theReplenishPile.toString();
    std::cout << "  ";
    tableauPile1.toString();
    std::cout << "  ";
    tableauPile2.toString();
    std::cout << "  ";
    tableauPile3.toString();
    std::cout << "  ";
    tableauPile4.toString();
    std::cout << "     <--Tableaus | Base cards of the tableaus--> ";
    tableauPile1.toString2();
    std::cout << "  ";
    tableauPile2.toString2();
    std::cout << "  ";
    tableauPile3.toString2();
    std::cout << "  ";
    tableauPile4.toString2();
    std::cout << std::endl;
    std::cout << "Last deck draw-->       ";
    theDeck.toString();
    std::cout << "    ";
    theDeck.toString2();
    std::cout << "   <-- Last 3 drawn" << std::endl
              << std::endl;
}

void mainMenu()
{
    showBoard(); // Shows board so user has information to make a decision
    int userSelection = 0;
    std::cout << "1. Draw 3" << std::endl;
    std::cout << "2. Play a card from the deck" << std::endl;
    std::cout << "3. Play a card or pile from a tableau" << std::endl;
    std::cout << "4. Play a card from the refresh pile" << std::endl;
    std::cout << "5. End game" << std::endl;
    std::cout << "Please select one of the options above: ";
    std::cin >> userSelection;
    std::cout << std::endl;

    while (!std::cin || (userSelection != 1 && userSelection != 2 && userSelection != 3 && userSelection != 4 && userSelection != 5)) // Fixable input validation
    {
        if (!std::cin)
        {
            std::cin.clear(); // Input validation
            std::cin.ignore(INT_MAX, '\n');
        }
        std::cout << "That is an invalid choice, please try again.";
        std::cin >> userSelection;
        std::cout << std::endl;
    }
    if (userSelection == 1) // Calls a different function for each of the users possible choices
        draw();
    if (userSelection == 2)
        playFromDeck();
    if (userSelection == 3)
        pickFromTableau();
    if (userSelection == 4)
        playFromReplenish();
    if (userSelection == 5)
    {
        std::cout << "You got " << score() << " out of 52 cards to the foundation piles!" << std::endl;
        scoreBoard();
        playAgain();
    }
}

void draw()
{
    if (theDeck.getNumCards() == 0) // Checks if deck is empty
    {
        std::cout << "Deck has zero cards remaining." << std::endl;
    }
    else
        theDeck.draw(); // If it isn't then it calls the function draw
}

void playFromReplenish()
{
    showBoard();
    int userSelection = whereToPlay(); // Asks if user wants to play a card on to a foundation or tableau

    if (theReplenishPile.getNumCards() == 0) // Checks if empty
    {
        std::cout << "Replenish pile has zero cards remaining." << std::endl;
    }
    else if (userSelection == 1) // This is for if the user wants to play on a foundation
    {
        showBoard();
        foundationPile tempFoundation = whereToPlayFoundation(); // Asks which foundation pile
        if (tempFoundation.getNumCards() == 0)                   // Checks if foundation is empty
        {
            if (tempFoundation.getFoundationCardRank() == theReplenishPile.getTopCard().getRank())
                nextPileFunc(theReplenishPile.playCard()); // Because empty played card must match first foundation card rank
            else
            {
                std::cout << "Attempted move is illegal." << std::endl;
            }
        }
        else if ((tempFoundation.getTopCard().getSuit() == theReplenishPile.getTopCard().getSuit()) && ((tempFoundation.getTopCard().getRank() + 1) % 13 == (theReplenishPile.getTopCard().getRank()))) // Checks same suit and (same rank + 1)
        {
            nextPileFunc(theReplenishPile.playCard()); // Function adds card to the correct pile using the global number saved from whereToPlayFoundation() because tempFoundation won't change the original pile unless it was referenced and referencing it caused a lot of bugs, and I came up with this clever solution that worked perfectly, but I wouldn't use it on a large team project.
        }
        else
        {
            std::cout << "Attempted move is illegal." << std::endl;
        }
    }
    else if (userSelection == 2) // This is for playing a card on to a tableau
    {
        showBoard();
        tableauPile tempTableau = whereToPlayTableau();                                                                                                                           // User chooses which tableau and a temporary copy of the pile is made
        if (tempTableau.getTopCard().getColor() != theReplenishPile.getTopCard().getColor() && tempTableau.getTopCard().getRank() - 1 == theReplenishPile.getTopCard().getRank()) // Top card of copy is used to check if the move follows the rules
        {
            nextPileFunc(theReplenishPile.playCard()); // If rules are followed card is played on to user choosen pile by passing the card as a parameter and the function uses a global variable that is set in the whereToPlay functions that also return a copy for checking if the move follows rules
        }
        else
        {
            std::cout << "Attempted move is illegal." << std::endl;
        }
    }
}

void playFromDeck() // This function is basically the same as the previous, but rule comparisons are done one a deck instead of replenish pile. I attempted to do a single playFrom function that I just passed the pile type into but realized I would have to reference the arguments and create all new virtual functions inside the class. I was okay with doing this, but then the solution I used came to me, which I thought was clever and quick and it caused everything to just work.
{
    showBoard();
    int userSelection = whereToPlay();
    if (theDeck.getNumCards() == 0)
    {
        std::cout << "Deck has zero cards remaining." << std::endl;
    }
    else if (userSelection == 1)
    {
        showBoard();
        foundationPile tempFoundation = whereToPlayFoundation();
        if (tempFoundation.getNumCards() == 0)
        {
            if (tempFoundation.getFoundationCardRank() == theDeck.getTopCard().getRank())
                nextPileFunc(theDeck.playCard());
            else
            {
                std::cout << "Attempted move is illegal." << std::endl;
            }
        }
        else if ((tempFoundation.getTopCard().getSuit() == theDeck.getTopCard().getSuit()) && ((tempFoundation.getTopCard().getRank() + 1) % 13 == (theDeck.getTopCard().getRank())))
        {
            if (theDeck.getNumCards() == 0 || theDeck.getShowingCardNum() >= theDeck.getNumCards())
            {
                std::cout << "Attempted move is illegal." << std::endl;
            }
            else
            {
                nextPileFunc(theDeck.playCard());
            }
        }
        else
        {
            std::cout << "Attempted move is illegal." << std::endl;
        }
    }
    else if (userSelection == 2)
    {
        showBoard();
        tableauPile tempTableau = whereToPlayTableau();
        if (tempTableau.getTopCard().getColor() != theDeck.getTopCard().getColor() && tempTableau.getTopCard().getRank() - 1 == theDeck.getTopCard().getRank())
        {
            if (theDeck.getNumCards() == 0 || theDeck.getShowingCardNum() >= theDeck.getNumCards())
            {
                std::cout << "Attempted move is illegal." << std::endl;
            }
            else
            {
                nextPileFunc(theDeck.playCard());
            }
        }
        else
        {
            std::cout << "Attempted move is illegal." << std::endl;
        }
    }
}

void pickFromTableau() // Simply asks the user which Tableau they want to play from
{
    showBoard();
    int userSelection = 0;
    std::cout << "1. Play the card from tableau 1"
              << "     5. Move the pile from tableau 1" << std::endl;
    std::cout << "2. Play the card from tableau 2"
              << "     6. Move the pile from tableau 2" << std::endl;
    std::cout << "3. Play the card from tableau 3"
              << "     7. Move the pile from tableau 3" << std::endl;
    std::cout << "4. Play the card from tableau 4"
              << "     8. Move the pile from tableau 4" << std::endl
              << std::endl;
    std::cout << "Please select one of the options above: ";
    std::cin >> userSelection;
    std::cout << std::endl;

    while (!std::cin || (userSelection != 1 && userSelection != 2 && userSelection != 3 && userSelection != 4 && userSelection != 5 && userSelection != 6 && userSelection != 7 && userSelection != 8))
    {
        if (!std::cin)
        {
            std::cin.clear(); // Input validation
            std::cin.ignore(INT_MAX, '\n');
        }
        std::cout << "That is an invalid choice, please try again.";
        std::cin >> userSelection;
        std::cout << std::endl;
    }
    if (userSelection == 1)
        playFromTableau(tableauPile1); // Pass the pile that corresponds with user selection to different function
    if (userSelection == 2)
        playFromTableau(tableauPile2);
    if (userSelection == 3)
        playFromTableau(tableauPile3);
    if (userSelection == 4)
        playFromTableau(tableauPile4);
    if (userSelection == 5)
        moveTableau(tableauPile1);
    if (userSelection == 6)
        moveTableau(tableauPile2);
    if (userSelection == 7)
        moveTableau(tableauPile3);
    if (userSelection == 8)
        moveTableau(tableauPile4);
}

void playFromTableau(tableauPile &t) // Does the exact same thing as play from deck or replenish except for the fact it already knows exactly what pile to play on to
{
    showBoard();
    int userSelection = whereToPlay();
    if (t.getNumCards() == 0) // Checks for zero cards remaining
    {
        std::cout << "This tableau pile has zero cards remaining." << std::endl;
    }
    else if (userSelection == 1)
    {
        showBoard();
        foundationPile tempFoundation = whereToPlayFoundation();
        if (tempFoundation.getNumCards() == 0)
        {
            if (tempFoundation.getFoundationCardRank() == t.getTopCard().getRank())
                nextPileFunc(t.playCard());
            else
            {
                std::cout << "Attempted move is illegal." << std::endl;
            }
        }
        else if ((tempFoundation.getTopCard().getSuit() == t.getTopCard().getSuit()) && ((tempFoundation.getTopCard().getRank() + 1) % 13 == (t.getTopCard().getRank())))
        {
            nextPileFunc(t.playCard());
        }
        else
        {
            std::cout << "Attempted move is illegal." << std::endl;
        }
        if (t.getNumCards() == 0) // If a last card of tableau was played this will replenish right after if replenish isn't out of card as well.
        {
            if (theReplenishPile.getNumCards() != 0)
                t.obtainCard(theReplenishPile.playCard());
        }
    }
    else if (userSelection == 2)
    {
        showBoard();
        tableauPile tempTableau = whereToPlayTableau();
        if (tempTableau.getTopCard().getColor() != t.getTopCard().getColor() && tempTableau.getTopCard().getRank() - 1 == t.getTopCard().getRank())
        {
            nextPileFunc(t.playCard());
        }
        else
        {
            std::cout << "Attempted move is illegal." << std::endl;
        }
    }
}

void moveTableau(tableauPile &t) // Move an entire pile
{
    showBoard();
    tableauPile tempTableau = whereToPlayTableau();
    if (t.getNumCards() == 0) // Check if zero
    {
        std::cout << "This tableau pile has zero cards remaining." << std::endl;
    }
    else if (tempTableau.getTopCard().getColor() != t.getBottomCard().getColor() && tempTableau.getTopCard().getRank() - 1 == t.getBottomCard().getRank()) // Checks against bottom card instead of top to move entire pile
    {
        nextPileFunc(t.playCard()); // Same function I explained in depth twice
    }
    else
    {
        std::cout << "Attempted move is illegal." << std::endl;
    }
}

int score()
{
    return foundationPile1.getNumCards() + foundationPile2.getNumCards() + foundationPile3.getNumCards() + foundationPile4.getNumCards(); // Score is calculated by adding up number of cards in all 4 foundation piles
}

void scoreBoard()
{
    std::string s;
    std::cout << "Type your name to be put on the scoreboard or type skip: ";
    std::getline(std::cin >> std::ws, s); // Getline that skips leading white space
    std::cout << std::endl;
    std::cout << std::endl;
    if (s == "skip" || s == "SKIP" || s == "Skip")
    {
        return; // Exits void function
    }
    else
    {
        std::ofstream out;
        out.open("scoreBoard.txt", std::fstream::app);  // app makes the text file appenable which allows multiple things to be written to the file since it doesn't over write itself everytime the function is called.
        out << s << " Score: " << score() << std::endl; // Adds users name and score to ongoing score board file.
        out.close();                                    // Closes file
    }
}

int whereToPlay() // Asks user if they want to play to a foundation or tableau pile.
{
    int userSelection = 0;
    std::cout << "1. Play to a foundation pile" << std::endl;
    std::cout << "2. Play to a tableau pile" << std::endl;
    std::cout << "Please select one of the options above: ";
    std::cin >> userSelection;
    std::cout << std::endl;
    while (!std::cin || (userSelection != 1 && userSelection != 2))
    {
        if (!std::cin)
        {
            std::cin.clear(); // Input validation
            std::cin.ignore(INT_MAX, '\n');
        }
        std::cout << "That is an invalid choice, please try again.";
        std::cin >> userSelection;
        std::cout << std::endl;
    }
    return userSelection;
}

foundationPile whereToPlayFoundation() // Asks which foundation pile
{
    int userSelection = 0;
    std::cout << "1. Play the card to foundation 1" << std::endl;
    std::cout << "2. Play the card to foundation 2" << std::endl;
    std::cout << "3. Play the card to foundation 3" << std::endl;
    std::cout << "4. Play the card to foundation 4" << std::endl;
    std::cout << "Please select one of the options above: ";
    std::cin >> userSelection;
    std::cout << std::endl;

    while (!std::cin || (userSelection != 1 && userSelection != 2 && userSelection != 3 && userSelection != 4))
    {
        if (!std::cin)
        {
            std::cin.clear(); // Input validation
            std::cin.ignore(INT_MAX, '\n');
        }
        std::cout << "That is an invalid choice, please try again.";
        std::cin >> userSelection;
        std::cout << std::endl;
    }
    if (userSelection == 1)
    {
        nextPile = 1; // Global variable that is used to keep track of where the next card will be played without having to pass the piles through multiple functions as references.
        return foundationPile1;
    }
    else if (userSelection == 2)
    {
        nextPile = 2;
        return foundationPile2;
    }
    else if (userSelection == 3)
    {
        nextPile = 3;
        return foundationPile3;
    }
    else
    {
        nextPile = 4;
        return foundationPile4;
    }
}

void nextPileFunc(card c) // Converts global variable nextPile back into corresponding piles
{
    if (nextPile == 1)
        foundationPile1.obtainCard(c); // Passes the played card into a member function that adds the card to the pile
    if (nextPile == 2)
        foundationPile2.obtainCard(c);
    if (nextPile == 3)
        foundationPile3.obtainCard(c);
    if (nextPile == 4)
        foundationPile4.obtainCard(c);
    if (nextPile == 5)
        tableauPile1.obtainCard(c);
    if (nextPile == 6)
        tableauPile2.obtainCard(c);
    if (nextPile == 7)
        tableauPile3.obtainCard(c);
    if (nextPile == 8)
        tableauPile4.obtainCard(c);
}

void win()
{
    if (foundationPile1.getNumCards() == 13 && foundationPile2.getNumCards() == 13 && foundationPile3.getNumCards() == 13 && foundationPile4.getNumCards() == 13) // Checks if you have won every gameplay loop
    {
        std::cout << "Congratulations you won!" << std::endl;
        scoreBoard(); // Gives user option to be placed on the score board
        playAgain();  // Gives user option to play again
    }
}

void playAgain()
{
    std::string s;
    std::cout << "Would you like to play again?" << std::endl;
    std::cout << "Type y/n: ";
    std::cin >> s;
    std::cout << std::endl;
    while (s != "y" && s != "n" && s != "Y" && s != "N" && s != "yes" && s != "no" && s != "YES")
    {
        std::cout << "Invalid response, please try again." << std::endl;
        std::cout << "Type y/n: ";
        std::cin >> s;
        std::cout << std::endl;
    }
    if (s == "y" || s == "yes" || s == "YES" || s == "Y")
    {
        theDeck.reset();                                                // Clears the vectors of cards and re initializes it, then sets number of cards accordingly
        theReplenishPile.resetPile();                                   // Clears vector of cards
        theReplenishPile.reset(theDeck);                                // Intializes vector with cards from deck
        foundationPile1.reset(theDeck);                                 // Same as replenish
        foundationPile2.reset(foundationPile1.getFoundationCardRank()); // Sets foundation card rank and sets number cards to 0
        foundationPile3.reset(foundationPile1.getFoundationCardRank()); // Same
        foundationPile4.reset(foundationPile1.getFoundationCardRank()); // Same
        tableauPile1.reset(theDeck);                                    // Same as tableau and replenish
        tableauPile2.reset(theDeck);                                    // Same
        tableauPile3.reset(theDeck);                                    // Same
        tableauPile4.reset(theDeck);                                    // Same
        std::cout << "Good luck!" << std::endl;
    }
    else
    {
        std::cout << "Good bye!\n"
                  << std::endl;
        continuePlaying = 0;
    }
}

tableauPile whereToPlayTableau() // Same as whereToPlayFoundation with a different data type
{
    int userSelection = 0;
    std::cout << "1. Play the card to tableau 1" << std::endl;
    std::cout << "2. Play the card to tableau 2" << std::endl;
    std::cout << "3. Play the card to tableau 3" << std::endl;
    std::cout << "4. Play the card to tableau 4" << std::endl;
    std::cout << "Please select one of the options above: ";
    std::cin >> userSelection;
    std::cout << std::endl;

    while (!std::cin || (userSelection != 1 && userSelection != 2 && userSelection != 3 && userSelection != 4))
    {
        if (!std::cin)
        {
            std::cin.clear(); // Input validation
            std::cin.ignore(INT_MAX, '\n');
        }
        std::cout << "That is an invalid choice, please try again.";
        std::cin >> userSelection;
        std::cout << std::endl;
    }
    if (userSelection == 1)
    {
        nextPile = 5;
        return tableauPile1;
    }
    else if (userSelection == 2)
    {
        nextPile = 6;
        return tableauPile2;
    }
    else if (userSelection == 3)
    {
        nextPile = 7;
        return tableauPile3;
    }
    else
    {
        nextPile = 8;
        return tableauPile4;
    }
}
