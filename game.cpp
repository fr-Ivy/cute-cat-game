#include "game.h"
#include "surface.h"
#include "Player.h"
#include <cstdio> //printf

namespace Tmpl8
{
	constexpr int MAP_ROWS = 16;
	constexpr int MAP_COLS = 26;
	constexpr int TILE_SIZE = 16;
	constexpr int SCALE = 5;
	constexpr int RENDER_TILE_SIZE = TILE_SIZE * SCALE;


	//map
	static char map[MAP_ROWS][MAP_COLS * 3 + 1] =
	{
		"aa ba ba ba ba ba ba ba ba ba ba ba ba ba ba ba ba ba ba ba ba ba ba ba ba ca",
		"ab bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb cb",
		"ab bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb cb",
		"ab bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb cb",
		"ab bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb cb",
		"ab bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb cb",
		"ab bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb cb",
		"ab bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb cb",
		"ab bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb cb",
		"ab bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb cb",
		"ab bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb cb",
		"ab bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb cb",
		"ab bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb cb",
		"ab bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb cb",
		"ab bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb bb cb",
		"ac bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc cc"

	};
	//assets
	Surface grass("assets/the_cat_pack/Tilesets/Grass.png");

	Sprite cat_forward(new Surface("assets/the_cat_pack/Characters/walking_cat3.png"), 16);

	void Game::Init()
	{
		player = Player(&cat_forward, 0, 0);
	}
	

	void Game::Shutdown()
	{
	}

	void drawTile(int tx, int ty, Surface* screen, Surface& tiles, int x, int y)
	{
		int tilesetWidth = tiles.GetWidth();
		int screenWidth = screen->GetWidth();

		Pixel* srcBase = tiles.GetBuffer() + tx * TILE_SIZE + (ty * TILE_SIZE) * tilesetWidth;

		for (int i = 0; i < TILE_SIZE; i++)
		{
			for (int j = 0; j < TILE_SIZE; j++)
			{
				Pixel p = srcBase[j + i * tilesetWidth];

				for (int dy = 0; dy < SCALE; dy++)
				{
					for (int dx = 0; dx < SCALE; dx++)
					{
						int screenX = x + j * SCALE + dx;
						int screenY = y + i * SCALE + dy;
						screen->GetBuffer()[screenX + screenY * screenWidth] = p;
					}
				}
			}
		}
	}


	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);

		for (int y = 0; y < MAP_ROWS; y++)
			for (int x = 0; x < MAP_COLS; x++)
			{
				int tx = map[y][x * 3] - 'a';
				int ty = map[y][x * 3 + 1] - 'a';
				drawTile(tx, ty, screen, grass, x * RENDER_TILE_SIZE, y * RENDER_TILE_SIZE);
			}

		player.moving(deltaTime);
		player.draw(*screen);
	}
};