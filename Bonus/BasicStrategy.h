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
    const static std::string alphabet[26];
};


#endif //Q3_BASICSTRATEGY_H
