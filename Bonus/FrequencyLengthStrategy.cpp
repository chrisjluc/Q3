//
// Created by Christopher Luc on 15-07-28.
//

#include "FrequencyLengthStrategy.h"

std::string FrequencyLengthStrategy::nextGuess(State state) {
    return frequencies[state.sizeOfWord() - 5][state.numberOfLettersGuessed()];
}