//
// Created by Christopher Luc on 15-07-28.
//

#ifndef Q3_FREQUENCYLENGTHSTRATEGY_H
#define Q3_FREQUENCYLENGTHSTRATEGY_H

#include "Strategy.h"
#include <array>

class FrequencyLengthStrategy : public Strategy {
public:
    virtual std::string nextGuess(State state);

private:
    const static std::array<std::string, 26> five;
    const static std::array<std::string, 26> six;
    const static std::array<std::string, 26> seven;
    const static std::array<std::string, 26> eight;
    const static std::array<std::string, 26> nine;
    const static std::array<std::string, 26> ten;
    const static std::array<std::string, 26> eleven;
    const static std::array<std::string, 26> twelve;
    const static std::array<std::string, 26> thirteen;
    const static std::array<std::string, 26> fourteen;
    const static std::array<std::string, 26> fifteen;
    const static std::array<std::string, 26> sixteen;
    const static std::array<std::string, 26> seventeen;
    const static std::array<std::string, 26> eighteen;
    const static std::array<std::array<std::string, 26>, 14> frequencies;


};


#endif //Q3_FREQUENCYLENGTHSTRATEGY_H
