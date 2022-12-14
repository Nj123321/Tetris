#pragma once

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

class ScoreBoard{
    private:
        multimap<int, string> board;
        multimap<int, string>::iterator ptr;
        string boardName;
        string playerName;
        int score;
    public:
        ScoreBoard(string, int = 0, string = "Group2ScoreBoard.bin");
        ~ScoreBoard();
        void update(int);
        const multimap<int, string> getBoard() const {return board;}
        int getScore() const {return score;}
};

