#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

template <typename T>
class Node{
    public: 
        Node() = default;
        T value;
        Node* next;
};

template <typename T>
class LL{
    public:
        Node<T>* head;
        Node<T>* tail;
        int size;
    public:
        LL(): head(nullptr), tail(nullptr), size(0){
        }
        ~LL(){
            Node<T>* temp;
            while(head != nullptr){
                temp = head->next;
                delete head;
                head = temp;
            }
        }
        void add(T value){
            if(head == nullptr && tail == nullptr){
                head = new Node<T>;
                head->value = value;
                head->next = nullptr;
                tail = head;
            }else{
                Node<T>* newVal = new Node<T>;
                newVal->value = value;
                newVal->next = tail->next;
                tail->next = newVal;
                tail = newVal;
            }
            size++;
        }
        T remove(T& value){
            Node<T>* prevPtr = nullptr;
            Node<T>* currPtr = head;
            while(currPtr != nullptr && currPtr->value != value){
                prevPtr = currPtr;
                currPtr = currPtr->next;
            }
            if(currPtr == nullptr)
                throw "Value Not Found"; // temp
            T removedValue = currPtr->value;
            if(currPtr == head){
                if(tail == head){
                    tail = nullptr;
                }
                Node<T>* temp;
                temp = head -> next;
                delete head;
                head = temp;
            }else{
                if(currPtr == tail)
                    tail = prevPtr;
                prevPtr->next = currPtr->next;
                delete currPtr;
            }
            size--;
            return removedValue;
        }
        Node<T>* find(const T& value){
            Node<T>* currptr = head;
            while(currptr != nullptr){
                if(currptr->value == value){
                    return currptr;
                }
                currptr = currptr -> next;
            }
            return nullptr;
        }
        int getSize(){
            return size;
        }
        T randomlyRemove(int t){
            if(t >= size)
                throw "Cannot remove index ";
            Node<T>* currptr = head;
            for(int i = 0 ; i != t; i++){
                currptr = currptr -> next;
            }
            return remove(currptr -> value);
        }
};

namespace vocabulary{
    int empty = 0;
    int red = 1;
    int blue = 2;
    int green = 3;
}

using namespace vocabulary;

struct coords{
    int row = 0;
    int col = 0;

    bool operator==(const coords& other) const {
    return row == other.row && col == other.col;
    }
    bool operator!=(const coords& other) const {
    return !(*this == other);
    }
    coords& operator=(const coords& rhs){
        row = rhs.row;
        col = rhs.col;
        return *this;
    }
};

class GameObject{
    public:
        // virtual ~GameObject() = 0;
        virtual void update(int, int) = 0;
        virtual coords* getCoords(int) = 0;
};

class Map{
    private:
        int W;
        int H;
        int** table;
        bool noObstuction(const coords& pos){
            if (pos.row < H && pos.row >= 0 && pos.col < W && pos.col >= 0){
                if(table[pos.row][pos.col] == empty)
                    return true;
            }
            return false;
        }
    public:
        Map(const int wi, const int hi): W(wi), H(hi), table(new int*[hi]){
            for(int i = 0; i < hi; i++){
                table[i] = new int[wi];
                for(int j = 0; j < wi; j++){
                    table[i][j] = 0;
                }
            }
        }
        ~Map(){
            return;
            for(int i = 0; i < H; i++){
                cout << i;
                delete[] table[i]; //exception?
            }
            delete[] table;
        }
        void clear(){
            for(int i = 0; i < H; i++){
                for(int j = 0; j < W; j++){
                    table[i][j] = 0;
                }
            }
        }
        bool update(GameObject* obj, int rowU, int colU){
            coords* ptr = obj->getCoords(0);
            for(int i = 1; ptr != nullptr; i++){
                table[ptr -> row][ptr -> col] = 0;
                ptr = obj->getCoords(i);
            }
            coords buffer;
            ptr = obj->getCoords(0);
            for(int i = 1; ptr != nullptr; i++){
                buffer = *ptr;
                buffer.row += rowU;
                buffer.col += colU;
                if(!noObstuction(buffer)){
                    ptr = obj->getCoords(0);
                    for(int i = 1; ptr != nullptr; i++){
                        table[ptr -> row][ptr -> col] = 1;
                        ptr = obj->getCoords(i);
                    }
                    return false;
                }
                ptr = obj->getCoords(i);
            }
            obj->update(rowU, colU);
            ptr = obj->getCoords(0);
            for(int i = 1; ptr != nullptr; i++){
                table[ptr -> row][ptr -> col] = 1;
                ptr = obj->getCoords(i);
            }
            return true;
        }
        void print(){
            for(int i = 0; i < H; i++){
                for(int j = 0; j < W; j++){
                    if(table[i][j] != 0)
                        cout << table[i][j];
                    else
                        cout << " ";
                }
                cout << endl;
            }
        }
        int getW(){return W;}
        int getH(){return H;}
};

class Block: public GameObject{
    private:
        const static int numberOfBlocks = 10;
        coords* blockArea;
        coords origin;
        bool find(coords find){
            for(int i = 0; i < numberOfBlocks; i++){
                if(blockArea[i] == find)
                    return true;
            }
            return false;
        }
    public:
        Block(Map& board, int width, int height, coords start):
        blockArea(new coords[numberOfBlocks]), origin(start){
            for(int i = 0; i < 10; i++){blockArea[i].row = 0; blockArea[i].col = 0;}
            blockArea[0] = start;
            coords temp;
            LL<coords> frontier;
            for(int i = 0; i < numberOfBlocks - 1; i++){
                temp = blockArea[i];
                temp.row -= 1;
                if(!frontier.find(temp) && !find(temp) && (abs(temp.row - start.row) <= height) && (abs(temp.col - start.col) <= width))
                    frontier.add(temp);
                temp.row += 2;
                if(!frontier.find(temp) && !find(temp) && (abs(temp.row - start.row) <= height) && (abs(temp.col - start.col) <= width))
                    frontier.add(temp);
                temp.row -= 1;
                temp.col -= 1;
                if(!frontier.find(temp) && !find(temp) && (abs(temp.row - start.row) <= height) && (abs(temp.col - start.col) <= width))
                    frontier.add(temp);
                temp.col += 2;
                if(!frontier.find(temp) && !find(temp) && (abs(temp.row - start.row) <= height) && (abs(temp.col - start.col) <= width))
                    frontier.add(temp);
                try{
                    blockArea[i + 1] = frontier.randomlyRemove(rand()%(frontier.getSize()));
                }catch(string err){
                    cerr << err;
                    return;
                }
            }
        }
        ~Block(){
            delete[] blockArea;
        }
        void update(int rowU, int colU) override{
            for(int i = 0; i < numberOfBlocks; i++){
                blockArea[i].row += rowU;
                blockArea[i].col += colU;
            }
        }
        void rotateCW(){
            for(int i = 0; i < numberOfBlocks; i++){
                
            }
        }
        coords* getCoords(int i) override{return (i < numberOfBlocks && i >= 0)? &blockArea[i] : nullptr;}
};

int main(){

    srand(time(0));
    int width = 20;
    int height = 20;
    coords spawn;
    spawn.row = 2; spawn.col = 6;
    Map m(width, height);
    char inp  = 'r';
    GameObject* obj = new Block(m, 4, 1, spawn);
    m.update(obj, 0, 0);
    while(inp != 'q'){
        m.print();
        cout << "------------------------" << endl;
        cin >> inp;
        switch(inp){
            case 'a':
                m.update(obj, 0, -1);
                break;
            case 'd':
                m.update(obj, 0, 1);
                break;
        }
        if(!m.update(obj, 1, 0)){
            delete obj;
            obj = new Block(m, 4, 1, spawn);
            m.update(obj, 0, 0);
        } 
    }  
    return 0;
}