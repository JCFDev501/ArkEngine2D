#include "Game.h"

int main()
{
	Game game;

	game.InitializeApp("PrototypeGameTest", "Assets/Assets.zip", 1024, 768, "Assets/Localization.txt");

	game.RunEngine();

	game.De_initialize();

	return 0;
}
