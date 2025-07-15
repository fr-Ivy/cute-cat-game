#include "game.h"
#include "surface.h"
#include <cstdio> //printf

namespace Tmpl8
{
	//assets
	Sprite cat_forward(new Surface("assets/the_cat_pack/Characters/cat_forward.png"), 4);

	void Game::Init()
	{
	}
	

	void Game::Shutdown()
	{
	}



	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);
		cat_forward.Draw(screen, 50, 50);
	}
};