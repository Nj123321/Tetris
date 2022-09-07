#include "GameGraphics.h"
#include "GameMap.h"

GameGraphics::GameGraphics(RenderWindow* wP, const GameMap* mP, float off):
windowPtr(wP), mapPtr(mP), gameH(static_cast<float>(wP->getSize().y)), gameW(static_cast<float>(wP->getSize().x)), offset(off){
	// load in neccessary textures
    sand.loadFromFile("Texture/sand.jpg");
    redSand.loadFromFile("Texture/redSand.png");
    bomb.loadFromFile("Texture/bomb.png");
    soulSand.loadFromFile("Texture/soulSand.png");
    clay.loadFromFile("Texture/clay.jpg");
    background.loadFromFile("Texture/Background.jpg");
    explosion.loadFromFile("Texture/boom.png");
    startingScreen.loadFromFile("Texture/Starting.jpg");
    gold.loadFromFile("Texture/Gold.jpg");
    gameFont.loadFromFile("Font/minercraftory.regular.ttf");
}

void GameGraphics::drawMap(){
	RectangleShape back(Vector2f(gameW, gameH));
	back.setTexture(&background);
	windowPtr->draw(back);
    for (int i = 0; i < mapPtr->getMapHeight(); i++)
	{
		// fill with gold if it is at the Game Over Level
		if(i == mapPtr->spawnH){
			sf::RectangleShape temp(Vector2f(mapPtr->squares_size, mapPtr->squares_size));
			temp.setTexture(&gold);
			for(int k = 0; k < mapPtr->getMapWidth(); k++){
				float xPos = offset + (mapPtr->squares_size + offset) * k;
				float yPos = offset + (mapPtr->squares_size + offset) * i;
				temp.setPosition(xPos, yPos);
				windowPtr->draw(temp);
			}
			continue;
		}
		// color in blocks
		for (int k = 0; k < mapPtr->getMapWidth(); k++)
		{
			if (mapPtr->haveSqAt(i, k))
			{
				sf::RectangleShape temp(sf::Vector2f(mapPtr->squares_size, mapPtr->squares_size));
				temp.setOutlineColor(sf::Color::Black);
				temp.setOutlineThickness(offset);
				switch (mapPtr->map[i][k]->getColor())
				{
				case 0:
					temp.setTexture(&sand);
					break;
				case 1:
					temp.setTexture(&redSand);
					break;
				case 2:
					temp.setTexture(&soulSand);
					break;
				case 3:
					temp.setTexture(&clay);
					break;
				case 6: // bomb texture exploding
					temp.setTexture(&explosion);
					break;
				case 7: // bomb real texture
					temp.setTexture(&bomb);
					break;
				}
				float xPos = offset + (mapPtr->squares_size + offset) * k;
				float yPos = offset + (mapPtr->squares_size + offset) * i;
				temp.setPosition(xPos, yPos);
				windowPtr->draw(temp);
			}
		}
	}
}

void GameGraphics::drawPauseMenu(){
    Text pause("PAUSED", gameFont, 30);
	pause.setFillColor(Color::Red);
	pause.setPosition(0,gameH - 40);
    windowPtr->draw(pause);
}

void GameGraphics::drawMenu(){
	// rules, tips
	sf::RectangleShape img(sf::Vector2f(gameW, gameH - 60));
	img.setTexture(&startingScreen);
	windowPtr->draw(img);

	// game name
	Text text("QuickSand!", gameFont, 50);
	text.setFillColor(sf::Color::Yellow);
	windowPtr->draw(text);
}

void GameGraphics::drawGameOver(const ScoreBoard& board, int displayNumber){
	// display game over message
    Text gg("GAME OVER", gameFont, static_cast<unsigned>(mapPtr->squares_size));
    gg.setFillColor(sf::Color::Yellow);
    gg.setStyle(sf::Text::Bold);
	windowPtr->draw(gg);
	// display scoreboard
    const multimap<int, string> b = board.getBoard();
    auto it = b.crbegin();
    float height = (windowPtr->getSize().y - mapPtr->squares_size)/(displayNumber);
    Text text;
    text.setFont(gameFont);
    text.setCharacterSize(20);
    string buffer;
    for(int i = 0; i < displayNumber && it != b.crend(); i++){
        buffer = "Number " + to_string(i + 1);
        buffer += "    " + to_string(it->first) + " " + it->second;
		cout << it->first << " " << it->second << endl;
        text.setString(buffer);
        text.setPosition(0, i*(height+5) + mapPtr->squares_size);
        windowPtr->draw(text);
        it++;
    }
	for(auto i = b.crbegin(); i != b.crend(); i++){
		cout << i->first << " " << i->second << endl;
	}
}

void GameGraphics::drawScore(int s){
    Text scoreText;
    scoreText.setString(to_string(s));
	scoreText.setFont(gameFont);
	scoreText.setCharacterSize(static_cast<unsigned>(mapPtr->squares_size));
    scoreText.setPosition(mapPtr->squares_size, mapPtr->squares_size);
    windowPtr->draw(scoreText);
}

void GameGraphics::drawUserMenu(){
	RectangleShape back(Vector2f(gameW, gameH));
	back.setTexture(&background);
	windowPtr->draw(back);
    Text instruc("Please Enter A UserName: ", gameFont, 20);
	instruc.setPosition(0,40);
	windowPtr->draw(instruc);
}