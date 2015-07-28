//
// Created by Christopher Luc on 15-07-28.
//

#ifndef Q3_FREQUENCYLENGTHSTRATEGY_H
#define Q3_FREQUENCYLENGTHSTRATEGY_H

#include "Strategy.h"
#include <array>

class FrequencyLengthStrategy : public Strategy{
public:
    virtual std::string nextGuess(State state);
private:
    const std::array<std::string, 26> five = {"s", "e", "a", "r", "o", "i", "l", "t", "n", "u", "d", "c", "y", "p", "h", "g", "b", "k", "f", "w", "v", "z", "x", "j", "q" }; //5
    const std::array<std::string, 26> six = {"e", "s", "a", "r", "i", "o", "l", "n", "t", "d", "u", "c", "m", "p", "h", "b", "y", "k", "f", "w", "v", "z", "x", "j", "q" }; //6
    const std::array<std::string, 26> seven = {"e", "s", "i", "a", "r", "n", "t", "o", "l", "d", "u", "c", "g", "p", "h", "b", "y", "f", "k", "w", "v", "z", "x", "j", "q" }; //7
    const std::array<std::string, 26> eight = {"e", "s", "i", "a", "r", "n", "t", "o", "l", "d", "c", "u", "g", "m", "h", "b", "y", "f", "k", "w", "v", "z", "x", "q", "j" }; //8
    const std::array<std::string, 26> nine = {"e", "s", "i", "r", "a", "n", "t", "o", "l", "c", "d", "u", "g", "m", "h", "b", "y", "f", "v", "k", "w", "z", "x", "q", "j" }; //9
    const std::array<std::string, 26> ten = {"e", "i", "s", "r", "a", "n", "t", "o", "l", "c", "d", "u", "g", "m", "h", "b", "y", "f", "v", "k", "w", "z", "x", "q", "j" }; //10
    const std::array<std::string, 26> eleven = {"e", "i", "s", "n", "a", "r", "t", "o", "l", "c", "u", "d", "p", "m", "h", "b", "y", "f", "v", "k", "w", "z", "x", "q", "j" }; //11
    const std::array<std::string, 26> twelve = {"e", "i", "s", "n", "t", "a", "r", "o", "l", "c", "p", "u", "m", "d", "h", "y", "b", "v", "f", "z", "k", "w", "x", "q", "j" }; //12
    const std::array<std::string, 26> thirteen = {"i", "e", "n", "t", "s", "a", "o", "r", "l", "c", "p", "u", "m", "g", "h", "y", "b", "v", "f", "z", "x", "k", "w", "q", "j" }; //13
    const std::array<std::string, 26> fourteen = {"i", "e", "t", "s", "n", "a", "o", "r", "l", "c", "p", "u", "m", "d", "g", "y", "b", "v", "f", "z", "x", "k", "w", "q", "j" }; //14
    const std::array<std::string, 26> fifteen = {"i", "e", "t", "n", "s", "o", "a", "r", "l", "c", "p", "u", "m", "d", "g", "y", "b", "v", "f", "z", "x", "w", "k", "q", "j" }; //15
    const std::array<std::string, 26> sixteen = {"i", "e", "t", "s", "n", "a", "a", "r", "l", "c", "p", "u", "m", "h", "y", "g", "b", "v", "f", "z", "x", "w", "q", "k", "j" }; //16
    const std::array<std::string, 26> seventeen = {"i", "e", "t", "n", "s", "o", "l", "r", "l", "c", "p", "u", "m", "h", "g", "y", "b", "v", "f", "z", "x", "q", "w", "k", "l" }; //17
    const std::array<std::string, 26> eighteen = {"i", "s", "e", "t", "o", "n", "r", "a", "l", "c", "p", "m", "u", "h", "g", "y", "b", "v", "z", "f", "x", "q", "w", "j", "j" }; //18
    const std::array<std::array<std::string, 26>, 14> frequencies = {five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen, seventeen, eighteen};


};


#endif //Q3_FREQUENCYLENGTHSTRATEGY_H
