#include "Game.h"

Game::Game(): window(new RenderWindow(VideoMode(static_cast<unsigned>(Game::windowWidth), static_cast<unsigned>(Game::windowHeight))
	, "Tetris", sf::Style::Close))
{
	srand(static_cast<unsigned>(time(nullptr)));
	currObj = map.spawn();
	gameState = GameState::Playing;
}

Game::Game(RenderWindow& w) :window(&w)
			, SQUARE_SIZE((w.getSize().y / MAP_HEIGHT < w.getSize().x / MAP_WIDTH) ?
				(w.getSize().y * SQURE_TO_OFFSET_RATIO) / ( MAP_HEIGHT * (SQURE_TO_OFFSET_RATIO + 1) + 1)
				: (w.getSize().x * SQURE_TO_OFFSET_RATIO)/ (MAP_WIDTH * (SQURE_TO_OFFSET_RATIO + 1) + 1))
			, windowWidth(static_cast<float>(w.getSize().x)), windowHeight(static_cast<float>(w.getSize().y))
{
	selfGenerate = false;
	srand(static_cast<unsigned>(time(nullptr)));
	currObj = map.spawn();
	gameState = GameState::Playing;
}

Game::~Game() 
{
		if (selfGenerate && window != nullptr) delete window;
}

void Game::initialize()
{
	map.setSqsSize(SQUARE_SIZE);
	backgroudMap.setSqsSize(SQUARE_SIZE);
	backgroudMap.fillMap(-1);

	scoreText.setString(to_string(score));
	loadFont("Font/minercraftory.regular.ttf", scoreText);
	loadFont("Font/minercraftory.regular.ttf", pauseText);
	pauseText.setString("PAUSED");
	pauseText.setPosition((SQUARE_SIZE + SQUARE_OFFSET) * 3 + SQUARE_OFFSET, (windowWidth / 3));

	mPlayer.playMusic();

	while (window->isOpen())
	{
		GameLoop();
	}
	mPlayer.pauseMusic();
}

void Game::GameLoop()
{
	Event evnt;
	switch (gameState)
	{
	case GameState::InMenu:
		//Draw and Do menu stuff here
		break;
	case GameState::GameOver:
		while (window->pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case Event::Closed:
				window->close();
				break;
			}
		}
		break;
	case GameState::Paused:
		//Do Pause Stuff
		draw();
		while (window->pollEvent(evnt))
		{
			if (evnt.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape))
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
		while (window->pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case Event::Closed:
				window->close();
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
	//Volume
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		mPlayer.adjVolume(5);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		mPlayer.adjVolume(-5);
	}
	//Block Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		delay /= 30;
		score++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		hardDropping = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
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
	//?????
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	{
		cout << *(reinterpret_cast<Block*>(currObj));
	}
}

void Game::advanceGameState()
{
	int oldScore = score;
	map.updateObj(currObj, 0, dx, score);
	//gravity
	if (timer > delay|| hardDropping)
	{
		if (hardDropping) 
		{ 
			score += hardDrop(); 
			oldScore = score;
			if (score != oldScore) mPlayer.cancelBlocks();
			delete currObj;
			try {
				currObj = map.spawn();//throw exception if cant spawn
			}
			catch (MapEx::GameOver end)
			{
				end.display(*window, font, SQUARE_SIZE, windowWidth, windowHeight);
				gameState = GameState::GameOver;
				mPlayer.gameOver();
			}
		}
		else if (!map.updateObj(currObj, +1, 0, score)) //reach the bottom
		{
			if (score != oldScore) mPlayer.cancelBlocks();
			delete currObj;
			try {
				currObj = map.spawn();//throw exception if cant spawn
			}
			catch (MapEx::GameOver end)
			{
				end.display(*window, font, SQUARE_SIZE, windowWidth, windowHeight);
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
	delay = DEFAULT_SPEED / static_cast<float>(score / 1000 + 1);
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		canRotate = true;
	}
}

int Game::hardDrop()
{
	int lineMoved = 0;
	int oldScore = score;
	while (map.updateObj(currObj, +1, 0, score))
	{
		lineMoved++;
	}
	if (score != oldScore) mPlayer.cancelBlocks();
	hardDropping = false;
	return lineMoved;
}

int Game::getScore() const { return score; }

void Game::draw()
{
	if (gameState != GameState::GameOver)
	{
		window->clear();
		backgroudMap.drawMap(*window, SQUARE_OFFSET, SQUARE_OFFSET, SQUARE_OFFSET);
		map.drawMap(*window, SQUARE_OFFSET, SQUARE_OFFSET, SQUARE_OFFSET);
		window->draw(scoreText);
		if (gameState == GameState::Paused)
		{
			window->draw(pauseText);
		}
		window->display();
	}
}
