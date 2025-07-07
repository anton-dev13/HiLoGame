/*
 * Hi-Lo Number Guessing Game
 *
 * Description:
 * This program implements a simple Hi-Lo number guessing game.
 * The computer randomly selects an integer between 1 and 100,
 * and the user has up to 7 attempts to guess the correct number.
 *
 * After each guess, the program provides feedback indicating whether
 * the guess was too high or too low. If the user guesses the number
 * correctly, they win. If they use all 7 guesses without success, they lose,
 * and the program reveals the correct number.
 *
 * At the end of each game, the user is prompted to play again. If the user
 * inputs anything other than 'y' or 'n', they are repeatedly prompted until
 * a valid response is received.
 *
 * Note:
 * - The program uses the `Random.h` header for generating random numbers.
 * - It assumes the user always enters valid numeric input when guessing.
 */

#include <iostream>

#include "Random.h"

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool handleFailedExtraction()
{
    if (std::cin.fail())
    {
        if (std::cin.eof())
        {
            std::exit(0);
        }
        std::cin.clear();
        ignoreLine();
        return true;
    }
    return false;
}

void playGame(int min, int max, int guesses)
{
    int secretNumber{ Random::get(min, max) };
    std::cout << "Let's play a game. I'm thinking of a number between ";
    std::cout << min << " and " << max << ". You have "<< guesses << " tries to guess what it is.\n";

    bool bWin {};
    for (int i{}; i < guesses; i++)
    {
        std::cout << "Guess #" << i + 1 << ": ";
        int guess{};
        std::cin >> guess;

        if (handleFailedExtraction() || guess > max || guess < min)
        {
            std::cout << "Invalid input! Please try again\n";
            i--;
            continue;
        }

        ignoreLine();

        if (guess > secretNumber)
            std::cout << "Your guess is too high.\n";
        else if (guess < secretNumber)
            std::cout << "Your guess is too low.\n";
        else
        {
            bWin = true;
            break;
        }

    }

    if (bWin)
    {
        std::cout << "Correct! You win!\n";
    }
    else
    {
        std::cout << "Sorry, you lose. The correct number was " << secretNumber << ".\n";
    }
}

bool playAgain()
{
    char op{};
    do
    {
        std::cout << "Would you like to play again (y/n)? ";
        std::cin >> op;

        ignoreLine();

        if (op == 'y')
            return true;

        if (op == 'n')
            return false;

        std::cout << "Invalid input! Please try again\n";

    } while (op != 'y' || op != 'n');
    return true;
}

int main()
{
    constexpr int min { 1 };
    constexpr int max { 100 };
    constexpr int guesses { 7 };

    do
    {
        playGame(min, max, guesses);
    } while (playAgain());

    std::cout << "Thanks for playing.\n";

    return EXIT_SUCCESS;
}