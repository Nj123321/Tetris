#pragma once

#include "SFML/Graphics.hpp"
#include <cstdlib>
#include <string>
#include <iostream>

namespace BlockEx {
    class InvalidSpawn {
    private:
        bool height, width;
        int advHeight, advWidth;
    public:
        InvalidSpawn(bool h, bool w, int ah, int aw) : height(h), width(w), advHeight(ah), advWidth(aw) {}
        bool heightIssue() const { return height; }
        bool widthIssue() const { return width; }
        int recommendHeight() const { return advHeight; }
        int recommendWidth() const { return advWidth; }
    };
}

namespace ListEx {
    class OutofBounds {
    private:
        std::string err;
        int index, size;
    public:
        OutofBounds(int i, int s) : err("Tried to Access Invalid Index In LinkedList "), index(i), size(s) {}
        void display(){
            std::cerr << err << "\n" << "Index: " << index <<" Size: " << size;
        }
    };
}

namespace MapEx {
    class OutOfBounds{
    private:
        int row, col;
    public:
        OutOfBounds(int r, int c): row(r), col(c){}
        int getRow() const{return row;}
        int getCol() const{return col;}
    };
    
    class InvalidOperation{
    private:
        int row, col;
    public:
        InvalidOperation(int r, int c): row(r), col(c){}
        int getRow() const{return row;}
        int getCol() const{return col;}
    };

    class GameOver {
    public:
        GameOver() {}
        void display(sf::RenderWindow& window, sf::Font& newfont, float SQUARE_SIZE, float windowWidth, float windowHeight) {
            sf::Text gg("GAME OVER", newfont, static_cast<unsigned>(SQUARE_SIZE));
            gg.setFillColor(sf::Color::Red);
            gg.setStyle(sf::Text::Bold);
            float x = windowWidth / 2 - static_cast<float>(gg.getCharacterSize() * 4.1f);
            float y = windowHeight / 2 - static_cast<float>(gg.getCharacterSize() / 2);
            gg.setPosition(x, y);

            window.draw(gg);
            window.display();
        }
    };
}