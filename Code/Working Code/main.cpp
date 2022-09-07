
#include <string>
#include "Game.h"

using namespace std;
int main()
{
	unsigned sqW = 35;
	unsigned windowHeight = sqW*22;
	unsigned windowWidth = sqW * 10;
	
	bool wantToPlay = true;
	while (wantToPlay)
	{
		sf::RenderWindow test(VideoMode(windowWidth, windowHeight), "SFML Practice", sf::Style::Close);
		Game game(test);
		game.initialize();
		string play = "";
		cout << "GG, Your Final Score: " << game.getScore() << endl;
		cout << "Continue(Type no to quit)? ";
		cin >> play;
		if (play.compare("no") == 0) wantToPlay = false;
	}
	return 0;
}


