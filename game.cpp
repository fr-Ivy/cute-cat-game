#include "game.h"
#include "surface.h"
#include "Player.h"
#include "map.h"
#include <cstdio> //printf

namespace Tmpl8
{
	//assets
	Surface grass("assets/the_cat_pack/Tilesets/Grass.png");
	Surface hills("assets/the_cat_pack/Tilesets/Hills.png");
	//Surface grass("assets/the_cat_pack/Tilesets/Grass.png");
	//Surface grass("assets/the_cat_pack/Tilesets/Grass.png");
	//Surface grass("assets/the_cat_pack/Tilesets/Grass.png");

	Sprite cat_forward(new Surface("assets/the_cat_pack/Characters/walking_cat3.png"), 16);
	map gameMap(grass, hills);

	void Game::Init()
	{
		player = Player(&cat_forward, 0, 0);
	}
	

	void Game::Shutdown()
	{
	}


	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);
		gameMap.Draw(screen, grass);

		player.moving(deltaTime);
		player.draw(*screen);
	}
};