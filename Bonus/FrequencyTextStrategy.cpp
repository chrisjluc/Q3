//
// Created by Christopher Luc on 15-07-28.
//

#include "FrequencyTextStrategy.h"

std::string FrequencyTextStrategy::nextGuess(State state) {
    return alphabetByGreatestFrequency[state.numberOfLettersGuessed()];
}
