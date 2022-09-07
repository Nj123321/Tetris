#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class MusicPlayer 
{
private:
    sf::Music music;
    sf::SoundBuffer startBuffer;
    sf::Sound startSound;
    sf::SoundBuffer cancelBuffer;
    sf::Sound cancelSound;
    sf::SoundBuffer gameOverBuffer;
    sf::Sound gameOverlSound;

    float mainVolume = 20;
    std::string fileLocation = "Music/";
public:
    MusicPlayer(float startVolume = 20);
    void startGame(const std::string& fileName = "Music/Tetris10ATYPE.ogg");
    void playMusic(const std::string& fileName = "Music/Tetris.ogg");
    void pauseMusic();
    void continueMusic();
    void adjVolume(int dir);
    void gameOver(const std::string& fileName = "Music/Tetris_Jingle.ogg");
    void cancelBlocks(const std::string& fileName = "Music/Tetris_DX.ogg");
};

