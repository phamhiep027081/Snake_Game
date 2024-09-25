#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Player
{
private:
    /* data */
    std::string name;
    int score;
public:
    const std::string recordDataFile{"../high_score_record.txt"};
    Player() : name(""), score(0) {}
    Player(std::string _name, int _score) : name(_name), score(_score) {}
    // ~Player();
    int getHighScore();
    void setHighScore(const int &highScore);
};



#endif /*PLAYER_H_*/