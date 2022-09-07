#pragma once

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
        int minimumScore;
    public:
        ScoreBoard(string n, string = "Group4ScoreBoard.txt", int s = 0);
        ~ScoreBoard();
        bool update(int);
        const multimap<int, string> getBoard() const {return board;}
        int getScore() const {return score;}
};

