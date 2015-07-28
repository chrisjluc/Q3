//
// Created by Christopher Luc on 15-07-28.
//

#ifndef Q3_FREQUENCYOFLETTERSSTRATEGY_H
#define Q3_FREQUENCYOFLETTERSSTRATEGY_H


#include "Strategy.h"

class FrequencyTextStrategy: public Strategy {
public:
    virtual std::string nextGuess(State state);
private:
    const std::string alphabetByGreatestFrequency[26] = {"E", "T", "A", "O", "I", "N", "S", "H", "R", "D", "L", "U", "C", "M", "F", "W", "Y", "P", "V", "B", "G", "K", "Q", "J", "X", "Z" };
};


#endif //Q3_FREQUENCYOFLETTERSSTRATEGY_H
