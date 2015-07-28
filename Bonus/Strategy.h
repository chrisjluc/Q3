//
// Created by Christopher Luc on 15-07-28.
//

#ifndef Q3_STRATEGY_H
#define Q3_STRATEGY_H

#include <string>
#include "State.h"

class Strategy {
public:
    virtual std::string nextGuess(State);
};


#endif //Q3_STRATEGY_H
