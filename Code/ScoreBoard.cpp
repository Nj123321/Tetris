#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(string n, int s, string b): boardName(b), playerName(n), score(s){
    ifstream boardIn(boardName, ios::binary);
    if(!boardIn){
        std::cerr << "Unable to open Score Board to Read: " << boardName << endl;
        exit(1);
    }
    int scoreBuffer;
    size_t size;
    string nameBuffer;
    int i = 0;
    while(i < 10 && boardIn.read(reinterpret_cast<char*>(&scoreBuffer), sizeof(scoreBuffer))){
        boardIn.read(reinterpret_cast<char*>(&size), sizeof(size));
        nameBuffer.resize(size);
        boardIn.read(const_cast<char*>(nameBuffer.c_str()), size);
        
        board.insert(pair<int, string>(scoreBuffer, nameBuffer));
        i++;
    }
    boardIn.close();
    ptr = board.end(); // signifies score is not on leaderboard
    update(0);
}

ScoreBoard::~ScoreBoard(){
    ofstream boardOut(boardName, ios::binary);
    if(!boardOut){
        std::cerr << "Unable to open Score Board to Update: " << boardName << endl;
        exit(1);
    }
    int i = 0;
    for(auto it = board.begin(); it != board.end() && i < 10; it++){
        boardOut.write(reinterpret_cast<const char*>(&(it->first)), sizeof(int));
        size_t size = it->second.size();
        boardOut.write(reinterpret_cast<const char*>(&(size)), sizeof(size));
        boardOut.write(it->second.c_str(), size);
        
        i++;
    }
    boardOut.close();
}

void ScoreBoard::update(int scoreU){
    score += scoreU;
    if(board.empty()){ // edge case
        ptr = board.insert(pair<int, string>(score, playerName));
        return;
    }
    if(ptr != board.end())    // remove previous score from map or lowest score if its the first time
        board.erase(ptr);
    ptr = board.insert(pair<int, string>(score, playerName)); // insert & update tracker
}