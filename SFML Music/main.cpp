//
//  main.cpp
//  SFML Music
//  Created by Meng-Ci Wang
//

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cmath>

using namespace sf;
using std::cout;
using std::endl;
using std::string;


int main() {
    
    

}

// function to control volume by press key up and dowm
void keypressVolume (sf::Music music) {
    sf::Event event;
    if (event.type == sf::Event::EventType::KeyPressed) {
        if (event.key.code == sf::Keyboard::Key::Down) {
            music.setVolume(music.getVolume() - 10);
        }
        
        if (event.key.code == sf::Keyboard::Key::Up) {
            music.setVolume(music.getVolume() + 10);
        }
    }
}


// function to play music before start the game (when user reading/choose the menu): use with "Tetris10ATYPE.ogg" for start game music
void startGame (const std::string& fileName) {
    sf::SoundBuffer startBuffer;
    // music play fileName : "Tetris10ATYPE.ogg"
    if (!startBuffer.loadFromFile(fileName)) {
        std::cout << "Can not open start game music file " << fileName << endl;
        return;
    } else {
        std::cout << "Play start game music from: " << fileName << std::endl;
    }
    
    startBuffer.loadFromFile(fileName);
    sf::Sound startSound;
    startSound.setBuffer(startBuffer);

}


// function to play music in whole game: use with "Tetris.ogg" for game music
void playMusic(const std::string& fileName) {
    sf::Music music;
    // music play fileName : "Tetris.ogg"
    if (!music.openFromFile(fileName)) {
        std::cout << "Can not open game music file " << fileName << endl;
        return;
    } else {
        std::cout << "Play game music from: " << fileName << std::endl;
    }

    if (music.openFromFile(fileName)) {
        music.setVolume(40);
        music.play();
    }
}


// function to play sound effects when the blocks got cancel: use with "Tetris_DX.ogg" for cancel blocks sound effects
void cancelBlocks (const std::string& fileName) {
    sf::SoundBuffer cancelBuffer;
    // music play fileName : "Tetris_DX.ogg"
    if (!cancelBuffer.loadFromFile(fileName)) {
        std::cout << "Can not open cancel block music file " << fileName << endl;
        return;
    } else {
        std::cout << "Play cancel block music from: " << fileName << std::endl;
    }
    
    
    cancelBuffer.loadFromFile(fileName);
    sf::Sound cancelSound;
    cancelSound.setBuffer(cancelBuffer);
    cancelSound.setVolume(100.0f);
}





// function to play sound effects when game is over: use with "Tetris_Jingle.ogg" for game over sound effects
void gameOver (const std::string& fileName) {
    sf::SoundBuffer gameOverBuffer;
    // music play fileName : "Tetris_DX.ogg"
    if (!gameOverBuffer.loadFromFile(fileName)) {
        std::cout << "Can not open game over music file " << fileName << endl;
        return;
    } else {
        std::cout << "Play game over music from: " << fileName << std::endl;
    }
    
    
    gameOverBuffer.loadFromFile(fileName);
    sf::Sound gameOverlSound;
    gameOverlSound.setBuffer(gameOverBuffer);
    gameOverlSound.setVolume(100.0f);
}
