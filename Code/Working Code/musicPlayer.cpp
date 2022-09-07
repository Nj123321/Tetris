#include "musicPlayer.h"


MusicPlayer::MusicPlayer(float startVolume)
{
    mainVolume = startVolume;
}

// function to control volume by press key up and dowm

void MusicPlayer::adjVolume(int dir) {
    if (mainVolume + dir >= 0 && mainVolume + dir <= 100)
    {
        mainVolume += dir;
        std::cout << "New Volume: " << mainVolume << std::endl;


        music.setVolume(mainVolume);
        startSound.setVolume(mainVolume);
        cancelSound.setVolume(mainVolume);
        gameOverlSound.setVolume(mainVolume);
    }
}


// function to play music before start the game (when user reading/choose the menu): use with "Tetris10ATYPE.ogg" for start game music
void MusicPlayer::startGame(const std::string& fileName) {
    // music play fileName : "Tetris10ATYPE.ogg"
    if (!startBuffer.loadFromFile(fileName)) {
        std::cout << "Can not open start game music file " << fileName << std::endl;
        return;
    }
    else {
        //std::cout << "Play start game music from: " << fileName << std::endl;
    }
    startBuffer.loadFromFile(fileName);
    startSound.setBuffer(startBuffer);
    startSound.setVolume(mainVolume);
    startSound.play();
}


// function to play music in whole game: use with "Tetris.ogg" for game music
void MusicPlayer::playMusic(const std::string& fileName) {
    // music play fileName : "Tetris.ogg"
    if (!music.openFromFile(fileName)) {
        std::cout << "Can not open game music file " << fileName << std::endl;
        return;
    }
    else {
        //std::cout << "Play game music from: " << fileName << std::endl;
    }

    if (music.openFromFile(fileName)) {
        music.setVolume(mainVolume);
        music.play();
        music.setLoop(true);
    }
}

void MusicPlayer::continueMusic()
{
    music.play();
}
void MusicPlayer::pauseMusic()
{
    music.pause();
}


// function to play sound effects when the blocks got cancel: use with "Tetris_DX.ogg" for cancel blocks sound effects
void MusicPlayer::cancelBlocks(const std::string& fileName)
{
    // music play fileName : "Tetris_DX.ogg"
    if (!cancelBuffer.loadFromFile(fileName)) {
        std::cout << "Can not open cancel block music file " << fileName << std::endl;
        return;
    }
    else {
        //std::cout << "Play cancel block music from: " << fileName << std::endl;
    }
    cancelBuffer.loadFromFile(fileName);
    cancelSound.setBuffer(cancelBuffer);
    cancelSound.setVolume(mainVolume);
    cancelSound.play();
}





// function to play sound effects when game is over: use with "Tetris_Jingle.ogg" for game over sound effects
void MusicPlayer::gameOver(const std::string& fileName) {
    // music play fileName : "Tetris_DX.ogg"
    if (!gameOverBuffer.loadFromFile(fileName)) {
        std::cout << "Can not open game over music file " << fileName << std::endl;
        return;
    }
    else {
        //std::cout << "Play game over music from: " << fileName << std::endl;
    }

    music.stop();
    gameOverBuffer.loadFromFile(fileName);
    gameOverlSound.setBuffer(gameOverBuffer);
    gameOverlSound.setVolume(mainVolume);
    gameOverlSound.play();
}