/*
class Bomb: public GameObject{
    private:
    coords origin;
    int width;
    public:
    Bomb(int w, coords start): origin(start), width(w){ if(w%2 != 1}{throw "error"}}
    ~Bomb(){}
    virtual void update(int rowU, int colU){
        origin.row += rowU;
        origin.col += colU;
    }
    virtual void rotateCW(){}
    virtual coords* getCoords(int i){return &origin;}
    virtual int getType(){return -1;}
    virtual coords* getBounds(int i){} // temp
}*/
/*
class ScoreBoard{
    private:
        string fname;
    public:
        ScoreBoard(string n): fname(n){}
        ~ScoreBoard(){
            fstream board;
            board.open(fname);
            if(!board){
                throw UNABLE;
            }
            board.close();
        };
        void update(int s){currScore += s;}
};
class ScoreTracker{
    private:
        string name;
        int currScore;
        ScoreBoard scores;
    public:
        ScoreTracker(string n, int c, string fname): name(n), currScore(c), scores(fname){}
        ~ScoreTracker(){scores.update(n, c;)}
        string getName(){return name;}
        int getScore(){return currScore;}
};*/