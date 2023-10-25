#include "raylib.h"

enum GameScreen
{
	LOGO,
	TITLE,
	GAMEPLAY,
	ENDING
};

class Game
{
private:
	GameScreen screen;
	int framesCounter;

public:
	Game();
	
	void Initialize();
	void RunLoop();

private:
	void ProcessInput();
	void Update();
	void Draw();

	void ShowLogo(int timeInSeconds);
};