//
// Created by Christopher Luc on 15-07-28.
//

#include "BasicStrategy.h"
const std::string BasicStrategy::alphabet[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
std::string BasicStrategy::nextGuess(State state) {
    return alphabet[state.numberOfLettersGuessed()];
}
