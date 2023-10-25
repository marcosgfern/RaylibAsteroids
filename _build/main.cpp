#include "raylib.h"
#include "Game.h"

int main()
{
	Game game;

	game.Initialize();
	game.RunLoop();

	CloseWindow();
	return 0;
}