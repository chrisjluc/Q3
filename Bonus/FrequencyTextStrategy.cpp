//
// Created by Christopher Luc on 15-07-28.
//

#include "FrequencyTextStrategy.h"

const std::string FrequencyTextStrategy::alphabetByGreatestFrequency[26] = {"E", "T", "A", "O", "I", "N", "S", "H", "R", "D", "L", "U", "C", "M", "F", "W", "Y", "P", "V", "B", "G", "K", "Q", "J", "X", "Z" };

std::string FrequencyTextStrategy::nextGuess(State state) {
    return alphabetByGreatestFrequency[state.numberOfLettersGuessed()];
}
