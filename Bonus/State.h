//
// Created by Christopher Luc on 15-07-28.
//

#ifndef Q3_STATE_H
#define Q3_STATE_H


#include <vector>

class State {
public:
    State(int sizeOfWord);
    void addLetter(char);
    int numberOfLettersGuessed() const;
    int sizeOfWord() const;
private:
    std::vector<char> lettersGuessed_;
    int sizeOfWord_;
};


#endif //Q3_STATE_H
