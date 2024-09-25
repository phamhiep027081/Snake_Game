#include "player.h"


int Player::getHighScore()
{
    int highScore{0};
    std::string line;
    std::ifstream filestream(recordDataFile);
    if (filestream.is_open())
    {
        if (std::getline(filestream, line))
        {
            std::istringstream linestream(line);
            if (linestream >> highScore)
            {
            }
        }
        filestream.close();
        std::cout << "reading data from high score record file ..." << std::endl;
    }
    else
    {
        std::cout << "High score record file does not exist. Creating new." << std::endl;
        std::ofstream outfile(recordDataFile);
    }
    return highScore;
}

void Player::setHighScore(const int &highScore)
{
    std::ofstream dataFile;
    dataFile.open(recordDataFile, std::ofstream::out | std::ofstream::trunc);
    if (!dataFile.is_open())
    {
        std::cout << " unable to open record file" << std::endl;
    }
    else
    {
        dataFile<<highScore;
    }
}
