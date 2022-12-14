#include "Game.h"
#include "Button.h"

Game::Game() : window(new RenderWindow(VideoMode(static_cast<unsigned>(windowWidth), static_cast<unsigned>(windowHeight))
	, "Tetris", sf::Style::Close)), drawer(window, &map, SQUARE_OFFSET)
{
	srand(static_cast<unsigned>(time(nullptr)));
	currObj = map.spawn();
	gameState = GameState::Playing;
}

Game::Game(RenderWindow& w) :
	SQUARE_SIZE((w.getSize().y / MAP_HEIGHT < w.getSize().x / MAP_WIDTH) ?
	(w.getSize().y * SQURE_TO_OFFSET_RATIO) / (MAP_HEIGHT * (SQURE_TO_OFFSET_RATIO + 1) + 1)
		: (w.getSize().x * SQURE_TO_OFFSET_RATIO) / (MAP_WIDTH * (SQURE_TO_OFFSET_RATIO + 1) + 1))
	, windowWidth(static_cast<float>(w.getSize().x)), windowHeight(static_cast<float>(w.getSize().y))
	, window(&w), drawer(window, &map, SQUARE_OFFSET)
{
	selfGenerate = false;
	srand(static_cast<unsigned>(time(nullptr)));
	currObj = map.spawn();
	gameState = GameState::InMenu;
}

Game::~Game()
{
	if (selfGenerate && window != nullptr) delete window;
}

void Game::playGame()
{
	map.setSqsSize(SQUARE_SIZE);
	mPlayer.playMusic();
	window->setKeyRepeatEnabled(false); //Keys are only processed once when held down (Certain keys have special-case because of this)
	window->setFramerateLimit(DEFAULT_FRAMERATE);
	while (window->isOpen())
	{
		gameLoop();
	}
	mPlayer.pauseMusic();
}

void Game::gameLoop()
{
	Font f;
	f.loadFromFile("Font/minercraftory.regular.ttf");
	Button q("Quit", 15, sf::Color::Yellow, { 70, 50 }, sf::Color::Black);
	q.setFont(f);
	Button c("Cancel", 15, sf::Color::White, { 70, 50 }, sf::Color::Black);
	c.setFont(f);
	Button r("Retry", 15, sf::Color::Yellow, { 70, 50 }, sf::Color::Black);
	r.setFont(f);

	Event evnt;
	switch (gameState)
	{
	case GameState::InMenu:
	{
		q.setPosition({ (windowWidth / 2) - 35, windowHeight - 55});
		// draw menu Once
		if (flag) {
			q.drawTo(*window);
			drawer.drawMenu();
			window->display();
			flag = false;
		}
		// look for spacebar
		while (window->pollEvent(evnt))
		{
			if (evnt.type == sf::Event::MouseMoved)
			{
				while (q.isMouseover(*window))
				{
					q.setBackColor(sf::Color::White);
					q.setTxtColor(sf::Color::Black);
					q.drawTo(*window);
					drawer.drawMenu();
					window->display();
					if (q.isCliked(*window))
					{
						window->close();
						break;
					}
				}
				flag = true;
			}
			if (evnt.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Space)) {
				gameState = GameState::GetUser;
				flag = true;
			}
			else if (evnt.type == Event::Closed)
				window->close();
		}
		break;
	}
	case GameState::GetUser:
	{
		TextBox textB(30, sf::Color::White, true);
		textB.setFont(drawer.getFont());
		textB.setPosition(Vector2f(0, windowHeight / 2));
		c.setPosition({ (windowWidth / 2) - 35, windowHeight - 55 });

		// gets user input
		while (gameState == GameState::GetUser) {
			drawer.drawUserMenu();
			textB.drawTo(*window);
			c.setTxtColor(sf::Color::White);
			c.setBackColor(sf::Color::Black);
			c.drawTo(*window);
			window->display();
			// looks for return key, otherwise displays user's input
			while (window->pollEvent(evnt)) {
				if (evnt.type == sf::Event::MouseMoved)
				{
					while (c.isMouseover(*window))
					{
						c.setBackColor(sf::Color::White);
						c.setTxtColor(sf::Color::Black);
						c.drawTo(*window);
						window->display();
						if (c.isCliked(*window))
						{
							window->clear();
							gameState = GameState::InMenu;
							break;
						}
					}
					flag = true;
				}
				if (evnt.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Return)) {
					flag = true;
					gameState = GameState::Playing;
					break;
				}
				else if (evnt.type == Event::TextEntered && !Keyboard::isKeyPressed(Keyboard::Space)) {
					textB.typeOn(evnt);
				}
				else if (evnt.type == Event::Closed)
					window->close();
			}
		}
		// update based on input
		playerName = textB.getText();
		map.loadSaveFile(playerName);
		break;
	}
	case GameState::GameOver:
	{
		while (window->pollEvent(evnt))
		{
			if (evnt.type == Event::Closed) {
				window->close();
				break;
			}
		}
		break;
	}
	case GameState::Paused:
	{
		r.setPosition({windowWidth / 2 - 75, windowHeight / 2});
		q.setPosition({ windowWidth / 2, windowHeight / 2 });

		// Pause window
		if (flag) {
			r.drawTo(*window);
			q.drawTo(*window);
			drawer.drawPauseMenu();
			mPlayer.pauseMusic();
			window->display();
			flag = false;
		}
		while (window->pollEvent(evnt)) // pause
		{
			if (evnt.type == sf::Event::MouseMoved)
			{
				while (q.isMouseover(*window))
				{
					q.setBackColor(sf::Color::White);
					q.setTxtColor(sf::Color::Black);
					q.drawTo(*window);
					window->display();
					if (q.isCliked(*window))
					{
						map.removeSaveFile(playerName);
						mPlayer.continueMusic();
						gameState = GameState::InMenu;
						window->clear();
						break;
					}
				}
				while (r.isMouseover(*window))
				{
					r.setBackColor(sf::Color::White);
					r.setTxtColor(sf::Color::Black);
					r.drawTo(*window);
					window->display();
					if (r.isCliked(*window))
					{
						map.removeSaveFile(playerName);
						mPlayer.continueMusic();
						gameState = GameState::GetUser;
						window->clear();
						break;
					}
				}
				flag = true;
			}
			else if (evnt.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape))
			{
				mPlayer.continueMusic();
				flag = true;
				gameState = GameState::Playing;
			}
			else if (evnt.type == Event::JoystickButtonPressed)
			{
				currentJoystickID = evnt.joystickButton.joystickId;
				if (Joystick::isButtonPressed(currentJoystickID, 7))
				{
					mPlayer.continueMusic();
					flag = true;
					gameState = GameState::Playing;
				}
			}
			else if (evnt.type == Event::Closed)
				map.writeSaveFile(playerName, currObj);
		}
		break;
	}
	case GameState::Debug:
	{
		Debug dMenu(&map, currObj);
		int row, col;
		Event evnt;
		// debug mode is on
		while (gameState == GameState::Debug) {
			// look for user input
			while (window->pollEvent(evnt)) {
				if (evnt.type == Event::KeyPressed) {
					if (Keyboard::isKeyPressed(Keyboard::Y)) {
						gameState = GameState::Playing;
						break;
					}
					else if (Keyboard::isKeyPressed(Keyboard::P)) {
						// get user Input
						GameObject* newObj;
						char input;
						cout << "Enter the first letter of the block in lower case: ";
						cin >> input;
						newObj = dMenu.spawn(input);
						if (newObj) {
							delete currObj;
							currObj = newObj;
							drawer.drawMap();
							window->display();
						}
					}
				}
				else if (evnt.type == Event::JoystickButtonPressed)
				{
					currentJoystickID = evnt.joystickButton.joystickId;
					if (Joystick::isButtonPressed(currentJoystickID, 6))
					{
						gameState = GameState::Playing;
						break;
					}
				}
				// move to cursor if it is pressed
				if (Mouse::isButtonPressed(sf::Mouse::Left)) {
					Vector2i mousePos = Mouse::getPosition(*window);
					row = mousePos.y / (static_cast<int>(map.getSquareSize()) + static_cast<int>(SQUARE_OFFSET));
					col = mousePos.x / (static_cast<int>(map.getSquareSize()) + static_cast<int>(SQUARE_OFFSET));
					dMenu.moveBlock(row, col);
					drawer.drawMap();
					window->display();
				}
			}
		}
	}
	break;
	case GameState::Playing:
	{
		float eTime = clock.getElapsedTime().asSeconds();
		clock.restart();
		dropTimer += eTime;
		while (window->pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case Event::Closed:
				window->close();
				map.writeSaveFile(playerName, currObj);
				break;
			case Event::KeyPressed:
				checkForSingleKeyInput(); //get actions, inputs are only Read Once
				break;
			case Event::KeyReleased:
				checkForReleaseKeyInput(); //Used for DAS
				break;
			case Event::JoystickButtonPressed:
				currentJoystickID = evnt.joystickButton.joystickId; //update Joystick ID
				checkForSingleJoyInput(); //get button actions, Joystick inputs are only Read Once
				break;
			case Event::JoystickMoved:
				if (evnt.joystickMove.position > DEFAULT_DEADZONE || evnt.joystickMove.position < -DEFAULT_DEADZONE)
				{
					currentJoystickID = evnt.joystickMove.joystickId;
					checkForSingleJoyMove(); //get axis actions, Joystick inputs are only Read Once
				}
				break;
			default:
				break;
			}
		}
		checkForHeldInput(); //Special-Case inputs acted upon when held down
		if (delayingAutoShift) //DAS is enabled, movement input is held down
		{
			shiftTimer += eTime;
			if (shiftTimer >= DEFAULT_DAS_TIMER)
			{
				delayingAutoShift = false;
				shiftTimer = 0.0f;
			}
		}
		else if (isAutoShifting) //Finished DAS, begin Auto Shifting, movement input is held down
		{
			shiftTimer += eTime;
			if (shiftTimer >= DEFAULT_AS_TIMER)
			{
				shiftTimer = 0.0f;
				isAutoShifting = false;
			}
			else
			{
				dx = 0;
			}
		}
		if (gameState == GameState::Playing)
		{
			advanceGameState();
			//Update Screen
			if (gameState != GameState::GameOver)
			{
				window->clear();
				drawer.drawMap();
				drawer.drawScore(score);
				window->display();
			}
		}
	}
	break;
	}
}

void Game::checkForSingleKeyInput()
{
	//Keyboard Inputs inside this function are only read once when held down
	if (Keyboard::isKeyPressed(Keyboard::Escape)) // pausing
	{
		gameState = GameState::Paused;
	}
	if (Keyboard::isKeyPressed(Keyboard::Y)) {
		gameState = GameState::Debug;
	}
	//Volume
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		mPlayer.adjVolume(5);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		mPlayer.adjVolume(-5);
	}
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		hardDropping = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		map.rotate(currObj);
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		dx = -1;
		delayingAutoShift = true;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D))
	{
		dx = 1;
		delayingAutoShift = true;
	}
}

void Game::checkForReleaseKeyInput()
{
	if (!Keyboard::isKeyPressed(Keyboard::A))
	{
		delayingAutoShift = false;
		shiftTimer = 0;
	}
	else if (!Keyboard::isKeyPressed(Keyboard::D))
	{
		delayingAutoShift = false;
		shiftTimer = 0;
	}
}

void Game::checkForSingleJoyInput()
{
	//Joystick Inputs inside this function are only read once
	if (Joystick::isButtonPressed(currentJoystickID, 7)) //pausing, 7 = start button
	{
		gameState = GameState::Paused;
	}
	if (Joystick::isButtonPressed(currentJoystickID, 6)) //pausing, 7 = start button
	{
		gameState = GameState::Debug;
	}
	if (Joystick::isButtonPressed(currentJoystickID, 0) || Joystick::isButtonPressed(currentJoystickID, 1)
		|| Joystick::isButtonPressed(currentJoystickID, 2) || Joystick::isButtonPressed(currentJoystickID, 3))
		//rotate, 0 = A button, 1 = B button, 2 = X button, 3 = Y Button, all face buttons
	{
		hardDropping = true;
	}
}

void Game::checkForSingleJoyMove()
{
	//Joystick Inputs inside this function are only read once
	if (Joystick::getAxisPosition(currentJoystickID, Joystick::Axis::PovY) > DEFAULT_DEADZONE) //d-pad up
	{
		map.rotate(currObj);
	}
	if (Joystick::getAxisPosition(currentJoystickID, Joystick::Axis::PovX) < -DEFAULT_DEADZONE) //d-pad left
	{
		dx = -1;
		delayingAutoShift = true;
	}
	else if (Joystick::getAxisPosition(currentJoystickID, Joystick::Axis::PovX) > DEFAULT_DEADZONE) //d-pad right
	{
		dx = 1;
		delayingAutoShift = true;
	}
	else if (Joystick::getAxisPosition(currentJoystickID, Joystick::Axis::PovX) >= -DEFAULT_DEADZONE
		|| Joystick::getAxisPosition(currentJoystickID, Joystick::Axis::PovX) <= DEFAULT_DEADZONE) //d-pad neutral position
	{
		delayingAutoShift = false;
		shiftTimer = 0;
	}
}

void Game::checkForHeldInput()
{
	//Held Down Inputs are continously read
	//Block Movement
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		isFastFalling = true;
	}
	if (!delayingAutoShift && Keyboard::isKeyPressed(Keyboard::A))
	{
		dx = -1;
		isAutoShifting = true;
	}
	else if (!delayingAutoShift && Keyboard::isKeyPressed(Keyboard::D))
	{
		dx = 1;
		isAutoShifting = true;
	}
	if (Joystick::isConnected(currentJoystickID))
	{
		if (Joystick::getAxisPosition(currentJoystickID, Joystick::Axis::PovY) < -DEFAULT_DEADZONE) //d-pad down
		{
			isFastFalling = true;
		}
		if (!delayingAutoShift && Joystick::getAxisPosition(currentJoystickID, Joystick::Axis::PovX) < -DEFAULT_DEADZONE) //d-pad left
		{
			dx = -1;
			isAutoShifting = true;
		}
		if (!delayingAutoShift && Joystick::getAxisPosition(currentJoystickID, Joystick::Axis::PovX) > DEFAULT_DEADZONE) //d-pad right
		{
			dx = 1;
			isAutoShifting = true;
		}
	}
}

void Game::advanceGameState()
{
	int oldScore = score;
	map.updateObj(currObj, 0, dx, score);
	if (isFastFalling)
	{
		delay /= 15;
	}

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
			map.removeSaveFile(playerName);
			ScoreBoard board(playerName, score);
			end.display(*window, drawer, board);
			gameState = GameState::GameOver;
			mPlayer.gameOver();
		}
	}
	//gravity
	else if (dropTimer > delay)
	{
		if (isFastFalling)
		{
			score++;
		}
		if (!map.updateObj(currObj, +1, 0, score)) //reach the bottom
		{
			if (score != oldScore) mPlayer.cancelBlocks();
			delete currObj;
			try {
				currObj = map.spawn();//throw exception if cant spawn
			}
			catch (MapEx::GameOver end)
			{
				map.removeSaveFile(playerName);
				ScoreBoard board(playerName, score);
				end.display(*window, drawer, board);
				gameState = GameState::GameOver;
				mPlayer.gameOver();
			}
		}
		dropTimer = 0;
	}
	//reset value
	dx = 0;
	isFastFalling = false;
	delay = DEFAULT_SPEED / static_cast<float>(score / 1000 + 1);
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
