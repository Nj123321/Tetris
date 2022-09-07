//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <iostream>
//#include <string>
//#include "gameMap.h"
//#include "Block.h"
//#include "musicPlayer.h"
#include "Game.h"


int main()
{
	Game game;
	game.initialize();
	return 0;
	////WINDOW SETTINGS
	////the window size is based on square size and the width and height
	//float SQUARE_SIZE = 35.0f;
	//int MAP_HEIGHT = 22;
	//int MAP_WIDTH = 10;

	//float SQUARE_OFFSET = SQUARE_SIZE / 5.0f;
	//float windowWidth = (SQUARE_SIZE+ SQUARE_OFFSET) * MAP_WIDTH+ SQUARE_OFFSET;
	//float windowHeight = (SQUARE_SIZE + SQUARE_OFFSET) * MAP_HEIGHT + SQUARE_OFFSET;

	//float DEFAULT_SPEED = 0.60f;


	////Screen Settings
	//srand(static_cast<unsigned>(time(nullptr)));
	//RenderWindow window(VideoMode(static_cast<unsigned>(windowWidth), static_cast<unsigned>(windowHeight)), "Tetris Game", sf::Style::Close);

	////MAP SETTING
	//Event evnt;

	//GameMap map = GameMap(MAP_HEIGHT, MAP_WIDTH);
	//map.setSqsSize(SQUARE_SIZE);
	//GameObject* currObj = map.spawn();

	//GameMap backgroudMap = GameMap(MAP_HEIGHT, MAP_WIDTH);
	//backgroudMap.setSqsSize(SQUARE_SIZE);
	//backgroudMap.fillMap(-1);

	////Score Setup
	////when press s to move down, +1 point for each block speed up
	////clear a row should +100 but NOT IMPLEMENTED
	////NEED TO SCALE SPEED WITH SCORE
	//Font newfont;
	//std::string fontFile = "Font/minercraftory.regular.ttf";
	//if (!newfont.loadFromFile(fontFile.c_str()))
	//{
	//	cout << "Can find font File:" << fontFile << endl;
	//}
	//int score = 0;
	//sf::Text scoreText;
	//scoreText.setFont(newfont);
	//scoreText.setString(to_string(score));
	//scoreText.setCharacterSize(static_cast<unsigned>(SQUARE_SIZE));
	//scoreText.setFillColor(Color::White);
	//scoreText.setStyle(sf::Text::Bold);

	////PAUSE text
	//sf::Text pause;
	//pause.setFont(newfont);
	//pause.setString("PAUSED");
	//pause.setCharacterSize(static_cast<unsigned>(SQUARE_SIZE));
	//pause.setFillColor(Color::White);
	//pause.setStyle(sf::Text::Bold);
	//pause.setPosition((SQUARE_SIZE + SQUARE_OFFSET) * 3 + SQUARE_OFFSET, (windowWidth / 3));

	////GAME PLAY SETTINGS
	//float timer = 0.0f, delay = float(DEFAULT_SPEED);
	//int dx = 0;
	//Clock clock;

	//bool isPause = false;
	//bool canRotate = true;

	////MUSIC SETTINGS
	//MusicPlayer mPlayer;
	//bool justStartedGame = true;

	//while (window.isOpen())
	//{
	//	if (justStartedGame)
	//	{
	//		mPlayer.playMusic();
	//		justStartedGame = false;
	//	}
	//	float eTime = clock.getElapsedTime().asSeconds();
	//	clock.restart();
	//	timer += eTime;

	//	while (window.pollEvent(evnt))
	//	{
	//		switch (evnt.type)
	//		{
	//		case Event::Closed:
	//			window.close();

	//			break;
	//		case Event::KeyPressed:
	//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	//			{
	//				if (!isPause) 
	//				{
	//					mPlayer.pauseMusic();
	//					window.clear();
	//					backgroudMap.drawMap(window, SQUARE_OFFSET, SQUARE_OFFSET, SQUARE_OFFSET);
	//					map.drawMap(window, SQUARE_OFFSET, SQUARE_OFFSET, SQUARE_OFFSET);
	//					window.draw(pause);
	//					window.draw(scoreText);
	//					window.display();
	//					std::cout << "Game Paused" << std::endl;
	//				}
	//				else
	//				{
	//					mPlayer.playMusic();
	//					std::cout << "Game Resumed" << std::endl;
	//				}
	//				isPause = ! isPause;
	//			}
	//			if (!isPause)
	//			{
	//				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	//				{
	//					mPlayer.adjVolume(5);
	//				}
	//				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	//				{
	//					mPlayer.adjVolume(-5);
	//				}
	//				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	//				{
	//					delay /= 10;
	//					score++;
	//				}
	//				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//				{
	//					dx = -1;
	//				}
	//				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	//				{
	//					dx = 1;
	//				}
	//				if (canRotate && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	//				{
	//					map.rotate(currObj);
	//					canRotate = false;
	//				}
	//				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	//				{
	//					cout << *(reinterpret_cast<Block*>(currObj));
	//				}
	//			}
	//			
	//		default:
	//			break;
	//		}
	//	}
	//	if (!isPause) 
	//	{
	//		map.updateObj(currObj, 0, dx);
	//		//gravity
	//		if (timer > delay)
	//		{
	//			//reach the bottom
	//			if (!map.updateObj(currObj, +1, 0))
	//			{
	//				/*int levelCleared = map.update();
	//				if (levelCleared != 0) mPlayer.cancelBlocks();
	//				score += (levelCleared / map.getMapWidth()) * 100;*/

	//				delete currObj;
	//				try {
	//					currObj = map.spawn();//throw exception if cant spawn
	//				}
	//				catch (MapEx::GameOver end)
	//				{
	//					end.display(window, newfont, SQUARE_SIZE, windowWidth, windowHeight);
	//					break;
	//				}
	//			}
	//			timer = 0;
	//		}

	//		scoreText.setString(to_string(score));
	//		scoreText.setPosition(SQUARE_SIZE, SQUARE_SIZE);

	//		//update Screen
	//		window.clear();
	//		backgroudMap.drawMap(window, SQUARE_OFFSET, SQUARE_OFFSET, SQUARE_OFFSET);
	//		map.drawMap(window, SQUARE_OFFSET, SQUARE_OFFSET, SQUARE_OFFSET);
	//		window.draw(scoreText);
	//		window.display();

	//		//reset value
	//		dx = 0;
	//		delay = DEFAULT_SPEED / static_cast<float>(score / 1000 + 1);
	//		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	//		{
	//			canRotate = true;
	//		}
	//	}
	//	
	//	//std::cout << score << std::endl;
	//}
	//mPlayer.gameOver();
	//system("pause");
	return 0;

}


