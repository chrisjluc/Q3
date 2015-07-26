#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <assert.h>

using namespace std;

bool isCharInVector(char c, vector<char> v) {
    return find_if(v.begin(), v.end(),
                   [c](char x) { return toupper(c) == x || tolower(c) == x; }) != v.end();
}

int count(vector<char> v1, string v2) {
    return count_if(v2.begin(), v2.end(), [v1](char c) {
        return isCharInVector(c, v1);
    });
}

int main(int argc, char **argv) {
    int seed = 0;
    int lives = 5;
    vector<string> words;
    vector<char> lettersGuessed;
    char userPlayAgain = 'y';
    const char PLAY_AGAIN = 'y';

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

    // Remove invalid words
    auto end = std::remove_if(words.begin(), words.end(), [](string word) {
        return word.length() < 6 || !std::all_of(word.begin(), word.end(), [](char c) { return isalpha(c); });
    });
    words.erase(end, words.end());

    int numWords = words.size();
    if (numWords == 0) {
        cout << "Error: Pool of game words is empty." << endl;
        return 0;
    }

    // Write filtered words to a file
    string newFile = "gamewords";
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

    while (tolower(userPlayAgain) == PLAY_AGAIN) {

        lives = 5;
        lettersGuessed.clear();
        string word = words.at(rng() % numWords);

        while (lives > 0) {
            cout << "Word: ";
            for_each(word.begin(), word.end(), [lettersGuessed](char c) {
                if (isCharInVector(c, lettersGuessed)) {
                    cout << c;
                } else {
                    cout << "-";
                }
            });
            cout << endl;
            cout << "Letters used:";
            for_each(lettersGuessed.begin(), lettersGuessed.end(), [](char c) {
                cout << " " << c;
            });
            cout << endl;
            if (lives == 1) {
                cout << "You have 1 life left.\n";
            } else {
                cout << "You have " << lives << " lives left.\n";
            }
            cout << "Next guess: ";

            // Process the guess
            string guess;
            cin >> guess;

            if (guess.length() > 1) {
                // Attempted to guess the entire word
                if (guess == word) {
                    cout << "You WIN!" << endl;
                } else {
                    cout << "You LOSE!  The word was \"" << word << "\"." << endl;
                }
                break;
            } else {
                char guessChar = tolower(*guess.c_str());
                if (!isCharInVector(guessChar, lettersGuessed)) {
                    int sizeBeforeGuess = count(lettersGuessed, word);
                    lettersGuessed.push_back(guessChar);
                    int sizeAfterGuess = count(lettersGuessed, word);
                    if (sizeAfterGuess == sizeBeforeGuess) {
                        lives--;

                    } else if (sizeAfterGuess > sizeBeforeGuess) {
                        if (sizeAfterGuess == word.size()) {
                            // Guessed the word
                            cout << "You WIN!  The word was \"" << word << "\"." << endl;
                            break;
                        }
                    } else {
                        assert(false);
                    }
                } else {
                    cout << "You already guessed letter \"" << guessChar << "\"." << endl;
                }
            }

            if (lives == 0) {
                cout << "You LOSE!  The word was \"" << word << "\"." << endl;
            }
        }
        cout << "Do you want to play again? [Y/N] ";
        cin >> userPlayAgain;
    }

    return 0;
}