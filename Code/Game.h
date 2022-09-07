#pragma once

#include "GameMap.h"
#include "Debug.h"
#include "GameGraphics.h"
#include "MusicPlayer.h"
#include "TextBox.h"
#include <string>
#include <iostream>

using namespace sf;

class Game
{
private:
	enum class GameState {
		Paused,
		Playing,
		GameOver,
		InMenu,
		Debug,
		GetUser
	};
	GameState gameState;

	//WINDOW SETTINGS
	//the window size is based on square size and the width and height
	const float SQURE_TO_OFFSET_RATIO = 5.0f;
	const int MAP_HEIGHT = 22;
	const int MAP_WIDTH = 10;
	const float SQUARE_SIZE = 35.0f;
	const float DEFAULT_SPEED = 0.60f;
	const int DEFAULT_FRAMERATE = 60;
	string playerName = "Unkown";
	bool flag = true;

	const float SQUARE_OFFSET = SQUARE_SIZE / SQURE_TO_OFFSET_RATIO;
	float windowWidth = (SQUARE_SIZE + SQUARE_OFFSET) * MAP_WIDTH + SQUARE_OFFSET;
	float windowHeight = (SQUARE_SIZE + SQUARE_OFFSET) * MAP_HEIGHT + SQUARE_OFFSET;

	bool selfGenerate = true;
	RenderWindow* window = nullptr;

	//MAP Setting
	GameMap map = GameMap(MAP_HEIGHT, MAP_WIDTH);
	GameObject* currObj;

	//GAME PLAY Setings
	int score = 0;
	float dropTimer = 0.0f, delay = float(DEFAULT_SPEED), shiftTimer = 0.0f;
	const float DEFAULT_DAS_TIMER = 0.2f;
	const float DEFAULT_AS_TIMER = 0.05f;
	int dx = 0;
	Clock clock;
	bool hardDropping = false, isFastFalling = false, delayingAutoShift = false, isAutoShifting = false;
	unsigned int currentJoystickID = 0;
	const float DEFAULT_DEADZONE = 15;
	

	//MUSIC Objects
	MusicPlayer mPlayer;

	// graphics
	GameGraphics drawer;
	
	// helper
	void gameLoop();
	void advanceGameState();
	void checkForSingleKeyInput();
	void checkForReleaseKeyInput();
	void checkForSingleJoyInput();
	void checkForSingleJoyMove();
	void checkForHeldInput();
	int hardDrop();
public:
	Game();
	Game(RenderWindow& w);
	~Game();
	void playGame();
};
