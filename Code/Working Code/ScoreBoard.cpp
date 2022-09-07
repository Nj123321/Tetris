#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(string n, string b, int s): boardName(b), playerName(n), score(s){
    ifstream boardIn(boardName, ios::binary);
    if(!boardIn){
        std::cerr << "Unable to open Score Board to Read: " << boardName << endl;
        exit(1);
    }
    string nameBuffer;
    int scoreBuffer;
    while(boardIn.read(reinterpret_cast<char*>(&nameBuffer), sizeof(sizeof(nameBuffer)))){
        boardIn.read(reinterpret_cast<char*>(&scoreBuffer), sizeof(scoreBuffer));
        board.insert(pair<int, string>(scoreBuffer, nameBuffer));
    }
    boardIn.close();
    minimumScore = board.begin()->first;
    ptr = board.end(); // signifies score is not on leaderboard
}

ScoreBoard::~ScoreBoard(){
    if(score >= minimumScore){ // update if neccessary
        ofstream boardOut(boardName, ios::binary);
        if(!boardOut){
            std::cerr << "Unable to open Score Board to Update: " << boardName << endl;
            exit(1);
        }
        for(auto it = board.begin(); it != board.end(); it++){
            boardOut.write(reinterpret_cast<const char*>(&(it->first)), sizeof(it->first));
            boardOut.write(reinterpret_cast<const char*>(&(it->second)), sizeof(it->second));
        }
        boardOut.close();
    }
}

bool ScoreBoard::update(int scoreU){
    score += scoreU;
    if(score >= minimumScore){ 
        if(ptr == board.end())    // remove previous score from map or lowest score if its the first time
            board.erase(board.begin());
        else
            board.erase(ptr);
        ptr = board.insert(pair<int, string>(score, playerName)); // insert & update tracker
        return true;
    }
    return false;
}