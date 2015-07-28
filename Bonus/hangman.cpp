#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <assert.h>
#include "Strategy.h"
#include "BasicStrategy.h"
#include "FrequencyTextStrategy.h"
#include "FrequencyLengthStrategy.h"


using namespace std;

// Check if char is in the vector
bool isCharInVector(char c, vector<char> v) {
    return find_if(v.begin(), v.end(),
                   [c](char x) { return toupper(c) == x || tolower(c) == x; }) != v.end();
}

// Counts how many letters in the gameword have been guessed
int count(vector<char> lettersGuessed, string word) {
    return (int) count_if(word.begin(), word.end(), [lettersGuessed](char c) {
        return isCharInVector(c, lettersGuessed);
    });
}

int main(int argc, char **argv) {
    // Define constants
    const char PLAY_AGAIN = 'y';
    const string newFile = "gamewords";


    // Define variables we will need
    int seed = 0;
    int lives = 5;
    vector<string> words;
    vector<char> lettersGuessed;
    char userPlayAgain = 'y';

    // Process file of words
    if (argc >= 2) {
        // Read in file
        char *filename = argv[1];
        ifstream infile;
        infile.open(filename);
        // Loop through all words in file
        if (!infile.is_open()) {
            cout << "Error: Could not open file \"" << filename << "\"." << endl;
            return 0;
        }
        while (!infile.eof()) {
            string word;
            getline(infile, word);
            words.push_back(word);

        }
        infile.close();
    } else {
        cout << "Error: No input file specified." << endl;
        return 0;
    }

    // Remove invalid words that have size < 6 or don't consist of all alphabetic characters
    auto end = std::remove_if(words.begin(), words.end(), [](string word) {
        return word.length() < 6 || !std::all_of(word.begin(), word.end(), [](char c) { return isalpha(c); });
    });
    words.erase(end, words.end());

    // Make sure we have at least 1 word
    int numWords = words.size();
    if (numWords == 0) {
        cout << "Error: Pool of game words is empty." << endl;
        return 0;
    }

    // Write filtered words to a file
    ofstream outfile;
    outfile.open(newFile);
    std::for_each(words.begin(), words.end(), [&outfile](string word) {
        outfile << word << endl;
    });
    outfile.close();


    // Get the seed
    if (argc >= 3) {
        char *seedChars = argv[2];
        seed = atoi(seedChars);
    }
    mt19937 rng(seed);

    // Process file of words
    Strategy *strategy;
    if (argc >= 4) {
        int choice = atoi(argv[3]);
        if (choice == 1) {
            strategy = new BasicStrategy();
        } else if (choice == 2) {
            strategy = new FrequencyTextStrategy();
        } else if (choice == 3) {
            strategy = new FrequencyLengthStrategy();
        } else {
            cout << "Error: Invalid strategy specified" << endl;
            return 0;
        }
    } else {
        cout << "Error: No strategy specified." << endl;
        return 0;
    }
    int max = 0;
    for (auto it = words.begin(); it != words.end(); ++it) {
        if ((*it).length() > max)
            max = (*it).length();
    }
    cout << max;

    // Main loop for the player wanting to play multiple games of hangman
    while (tolower(userPlayAgain) == PLAY_AGAIN) {

        // Set new game
        lives = 5;
        lettersGuessed.clear();
        string gameWord = words.at(rng() % numWords);
        State state = State(gameWord.length());

        // Game loop
        while (lives > 0) {

            cout << "Word: ";

            // Print the game word replaced by - for unguessed letters
            for_each(gameWord.begin(), gameWord.end(), [lettersGuessed](char c) {
                if (isCharInVector(c, lettersGuessed)) {
                    cout << c;
                } else {
                    cout << "-";
                }
            });

            cout << endl << "Letters used:";
            // Print the letters guessed with spaces in between
            for_each(lettersGuessed.begin(), lettersGuessed.end(), [](char c) {
                cout << " " << c;
            });
            cout << endl;

            // Print out number of lives the player has left
            if (lives == 1) {
                cout << "You have 1 life left.\n";
            } else {
                cout << "You have " << lives << " lives left.\n";
            }

            // Prompt for a guess
            cout << "Next guess: ";

            // Process the guess
            string guess = strategy->nextGuess(state);

            if (guess.length() > 1) {
                // The player has attempted to guess the entire gameWord
                if (guess == gameWord) {
                    cout << "You WIN!" << endl;
                } else {
                    cout << "You LOSE!  The word was \"" << gameWord << "\"." << endl;
                }
                break;
            } else {
                // Convert guess to lowercase
                char guessChar = tolower(*guess.c_str());

                // Check if the player has already guessed the letter
                if (isCharInVector(guessChar, lettersGuessed)) {
                    cout << "You already guessed letter \"" << guessChar << "\"." << endl;
                } else {
                    state.addLetter(guessChar);
                    // Number of characters in the word the player has guessed
                    int sizeBeforeGuess = count(lettersGuessed, gameWord);

                    lettersGuessed.push_back(guessChar);

                    // Number of characters in the word the player has guessed, including the most recent guess
                    int sizeAfterGuess = count(lettersGuessed, gameWord);

                    // The guessed character isn't in the gameWord if the size doesn't change
                    if (sizeAfterGuess == sizeBeforeGuess) {
                        lives--;

                    } else if (sizeAfterGuess > sizeBeforeGuess) {
                        // Guessed a correct letter

                        // If the number of letters in the words are all guessed, the player has won.
                        if (sizeAfterGuess == gameWord.size()) {
                            cout << "You WIN!  The word was \"" << gameWord << "\"." << endl;
                            break;
                        }
                    } else {
                        assert(false);
                    }
                }
            }

            if (lives == 0) {
                cout << "You LOSE!  The word was \"" << gameWord << "\"." << endl;
            }
        }
        cout << "Do you want to play again? [Y/N] ";
        cin >> userPlayAgain;
    }

    return 0;
}