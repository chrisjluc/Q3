//
// Created by Christopher Luc on 15-07-28.
//

#ifndef Q3_BASICSTRATEGY_H
#define Q3_BASICSTRATEGY_H


#include "Strategy.h"

class BasicStrategy : public Strategy{
public:
    virtual std::string nextGuess(State state);
private:
    const std::string alphabet[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
};


#endif //Q3_BASICSTRATEGY_H
