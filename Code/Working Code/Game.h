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
	const float SQURE_TO_OFFSET_RATIO = 5.0f;
	const int MAP_HEIGHT = 22;
	const int MAP_WIDTH = 10;
	const float SQUARE_SIZE = 35.0f;

	const float SQUARE_OFFSET = SQUARE_SIZE / SQURE_TO_OFFSET_RATIO;
	float windowWidth = (SQUARE_SIZE + SQUARE_OFFSET) * MAP_WIDTH + SQUARE_OFFSET;
	float windowHeight = (SQUARE_SIZE + SQUARE_OFFSET) * MAP_HEIGHT + SQUARE_OFFSET;

	const float DEFAULT_SPEED = 0.60f;

	bool selfGenerate = true;
	RenderWindow* window = nullptr;

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
	bool canRotate = true, hardDropping = false;

	//MUSIC Objects
	MusicPlayer mPlayer;
public:
	Game();
	Game(RenderWindow& w);
	~Game();
	void initialize();
	void GameLoop();
	void checkForInput();
	int getScore() const;
	bool loadFont(std::string, Text&);
	void advanceGameState();
	int hardDrop();
	void draw();
};