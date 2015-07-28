//
// Created by Christopher Luc on 15-07-28.
//

#include "State.h"

State::State(int sizeOfWord) : sizeOfWord_(sizeOfWord){

}

void State::addLetter(char c) {
    lettersGuessed_.push_back(c);
}

int State::sizeOfWord() const {
    return sizeOfWord_;
}

int State::numberOfLettersGuessed() const {
    return (int) lettersGuessed_.size();
}
