#include <iostream>
#include <cstdlib>
#include <ctime>

std::string_view getLevel(int level)
{
    switch (level)
    {
    case 1: return "Easy";
    case 2: return "Medium";
    case 3: return "Hard";
    default: return "???";
    }
}

int getNumberOfTries(int level)
{
    switch (level)
    {
    case 1: return 10;
    case 2: return 5;
    case 3: return 3;
    default: return 0;
    }
}

int getUserGuess()
{
    int x {};
    std::cout << "Enter your guess: ";
    std::cin >> x;
    return x;
}

void guessingGame(int level)
{
    std::srand(std::time(nullptr));     // use current time as seed for random number generation
    int guess {};
    int randomNumber { 1 + (std::rand() % 100) };
    int count {0};           // to keep track of user's guess
    bool hasWon {false};    // flag to check to 
    int numberOfTries {getNumberOfTries(level)};
    std::cout << "Great! You have selected the " << getLevel(level) << " difficulty level.\n";
    std::cout << "Let's start the game!\n";
    std::cout << std::endl;

    while (!hasWon &&numberOfTries != 0)
    {   
        guess = getUserGuess();
        ++count;
        if (guess == randomNumber){
            hasWon = true;
        }
        else if (guess < randomNumber){
            std::cout << "Incorrect! The number is greater than " << guess << ".\n";
            numberOfTries--;
        }
        else {
            std::cout << "Incorrect! The number is less than " << guess << ".\n";
            numberOfTries--;
        }
    }

    if (hasWon){
        std::cout << "Congratulations! You guessed the correct number in " << count << " attempts.\n";
    }
    else {
        std::cout << "You failed after " << count << " tries.\n";
        std::cout << "The correct number is " << randomNumber << '\n';
    }
}


int main()
{
    std::cout << "Welcome to the Number Guessing Game!\n";
    std::cout << "I'm thinking of a number between 1 and 100.\n";
    // std::cout << "You have 5 chances to guess the correct number.\n";
    std::cout << std::endl;
    
    int userChoice {};
    do
    {
        std::cout << "Please select the difficulty level:\n";
        std::cout << "1. Easy (10 chances)\n";
        std::cout << "2. Medium (5 chances)\n";
        std::cout << "3. Hard (3 chances)\n";
        std::cout << std::endl;

        std::cout << "Enter your choice: ";
        std::cin >> userChoice;
        std::cout << std::endl;
    } while (userChoice < 1 || userChoice > 3);

    guessingGame(userChoice);

    return 0;
}
