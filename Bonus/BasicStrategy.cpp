//
// Created by Christopher Luc on 15-07-28.
//

#include "BasicStrategy.h"

std::string BasicStrategy::nextGuess(State state) {
    return alphabet[state.numberOfLettersGuessed()];
}
