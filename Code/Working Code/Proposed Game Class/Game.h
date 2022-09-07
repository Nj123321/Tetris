#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "gameMap.h"
#include "Block.h"
#include "musicPlayer.h"
using namespace sf;

class Game
{
private:
	enum class GameState {
		Paused,
		Playing,
		GameOver,
		InMenu,
		Uninitialized
	};
	GameState gameState;

	//WINDOW SETTINGS
	//the window size is based on square size and the width and height
	static const float SQUARE_SIZE;
	static const int MAP_HEIGHT;
	static const int MAP_WIDTH;

	static const float SQUARE_OFFSET;
	static const float windowWidth;
	static const float windowHeight;

	static const float DEFAULT_SPEED;

	static RenderWindow window;

	//MAP Setting

	GameMap map = GameMap(MAP_HEIGHT, MAP_WIDTH);
	GameMap backgroudMap = GameMap(MAP_HEIGHT, MAP_WIDTH);
	GameObject* currObj;

	//Font and Text
	Font font;
	Text scoreText;
	Text pauseText;

	//GAME PLAY Setings
	int score = 0;
	float timer = 0.0f, delay = float(DEFAULT_SPEED);
	int dx = 0;
	unsigned int currentJoystickID = 0;
	Clock clock;
	bool canRotate = true;

	//MUSIC Objects
	MusicPlayer mPlayer;
public:
	Game();
	void initialize();
	void GameLoop();
	void checkForInput();
	bool loadFont(std::string, Text&);
	void advanceGameState();
	void hardDrop();
	void draw();
};