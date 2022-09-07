#include "Game.h"

const float Game::SQUARE_SIZE = 35.0f;
const int Game::MAP_HEIGHT = 22;
const int Game::MAP_WIDTH = 10;
const float Game::SQUARE_OFFSET = SQUARE_SIZE / 5.0f;
const float Game::windowWidth = (SQUARE_SIZE + SQUARE_OFFSET) * MAP_WIDTH + SQUARE_OFFSET;
const float Game::windowHeight = (SQUARE_SIZE + SQUARE_OFFSET) * MAP_HEIGHT + SQUARE_OFFSET;
const float Game::DEFAULT_SPEED = 0.60f;

RenderWindow Game::window(VideoMode(static_cast<unsigned>(Game::windowWidth), static_cast<unsigned>(Game::windowHeight)), "SFML Practice", sf::Style::Close);


Game::Game()
{
	srand(static_cast<unsigned>(time(nullptr)));
	currObj = map.spawn();
	gameState = GameState::Playing;
}

void Game::initialize() 
{
	map.setSqsSize(SQUARE_SIZE);
	backgroudMap.setSqsSize(SQUARE_SIZE);
	backgroudMap.fillMap(-1);

	loadFont("Font/minercraftory.regular.ttf", scoreText);
	scoreText.setString(to_string(score));
	loadFont("Font/minercraftory.regular.ttf", pauseText);
	pauseText.setString("PAUSED");
	pauseText.setPosition((SQUARE_SIZE + SQUARE_OFFSET) * 3 + SQUARE_OFFSET, (windowWidth / 3));
	
	mPlayer.playMusic();
	
	while (window.isOpen())
	{
		GameLoop();
	}
}

void Game::GameLoop()
{
	switch (gameState)
	{
	case GameState::InMenu:
		//Draw and Do menu stuff here
		break;
	case GameState::Paused:
		//Do Pause Stuff
		draw();
		Event pause;
		while (window.pollEvent(pause))
		{
			if (pause.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape))
			{
				mPlayer.continueMusic();
				gameState = GameState::Playing;
				std::cout << "Game Resumed" << std::endl;
			}
		}
		break;
	case GameState::Playing:
		float eTime = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += eTime;
		Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					gameState = GameState::Paused;
					mPlayer.pauseMusic();
					std::cout << "Game Paused" << std::endl;
					break;
				}
				checkForInput();
				break;
			}
			
		}
		if (gameState == GameState::Playing)
		{
			advanceGameState();
			//Update Screen
			draw();

		}
		break;
	}
}

bool Game::loadFont(std::string fileName, Text& location)
{
	if (!font.loadFromFile(fileName.c_str()))
	{
		cout << "Can find font File:" << fileName << endl;
		return false;
	}
	location.setFont(font);
	location.setCharacterSize(static_cast<unsigned>(SQUARE_SIZE));
	location.setFillColor(Color::White);
	location.setStyle(sf::Text::Bold);
	return true;
}

void Game::checkForInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		mPlayer.adjVolume(5);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		mPlayer.adjVolume(-5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		delay /= 10;
		score++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		dx = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		dx = 1;
	}
	if (canRotate && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		map.rotate(currObj);
		canRotate = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	{
		cout << *(reinterpret_cast<Block*>(currObj));
	}
}

void Game::advanceGameState()
{
	map.updateObj(currObj, 0, dx);
	//gravity
	if (timer > delay)
	{
		//reach the bottom
		if (!map.updateObj(currObj, +1, 0))
		{
			/*int levelCleared = map.update();
			if (levelCleared != 0) mPlayer.cancelBlocks();
			score += (levelCleared / map.getMapWidth()) * 100;*/

			delete currObj;
			try {
				currObj = map.spawn();//throw exception if cant spawn
			}
			catch (MapEx::GameOver end)
			{
				end.display(window, font, SQUARE_SIZE, windowWidth, windowHeight);
				gameState = GameState::GameOver;
				mPlayer.gameOver();
			}
		}
		timer = 0;
	}

	scoreText.setString(to_string(score));
	scoreText.setPosition(SQUARE_SIZE, SQUARE_SIZE);
	//reset value
	dx = 0;
	delay = DEFAULT_SPEED / (score / 1000 + 1);
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		canRotate = true;
	}
}

void Game::draw()
{
	if (gameState != GameState::GameOver)
	{
		window.clear();
		backgroudMap.drawMap(window, SQUARE_OFFSET, SQUARE_OFFSET, SQUARE_OFFSET);
		map.drawMap(window, SQUARE_OFFSET, SQUARE_OFFSET, SQUARE_OFFSET);
		window.draw(scoreText);
		if (gameState == GameState::Paused)
		{
			window.draw(pauseText);
		}
		window.display();
	}
}