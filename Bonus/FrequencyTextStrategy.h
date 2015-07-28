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
    const static std::string alphabetByGreatestFrequency[26];
};


#endif //Q3_FREQUENCYOFLETTERSSTRATEGY_H
