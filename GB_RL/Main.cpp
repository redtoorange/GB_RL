#include "MainMenuScreen.h"
#include "Game.h"
#include <iostream>
#include <vector>
#include "MapGenerator.h"
using namespace std;



int main()
{
	srand(time(nullptr));
//	MapGenerator generator{5, 5, 80, 80, 5, 10, 3, 10};
//	auto map = generator.create();
//
//	for( auto& x : map)
//	{
//		for( auto& t : x)
//		{
//			cout << static_cast<char>(t);
//		}
//		cout << endl;
//	}

//	tgui::Theme blackTheme{"assets/UISkins/sgx-ui.txt"};
//	tgui::Theme::setDefault(&blackTheme);
//
	Game game;
	game.begin();

	return 0;
}
