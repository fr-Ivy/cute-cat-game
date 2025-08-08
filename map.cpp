#include "map.h"

map::map()
{
    const char temp[MAP_ROWS][MAP_COLS * 3 + 1] =
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


    for (int r = 0; r < MAP_ROWS; r++)
        for (int c = 0; c < MAP_COLS * 3 + 1; c++)
            layer1[r][c] = temp[r][c];
}

void map::Draw(Surface* screen, Surface& tiles)
{
    int tilesetWidth = tiles.GetWidth();
    int screenWidth = screen->GetWidth();


    for (int y = 0; y < MAP_ROWS; y++)
    {
        for (int x = 0; x < MAP_COLS; x++)
        {
            int tx = layer1[y][x * 3] - 'a';
            int ty = layer1[y][x * 3 + 1] - 'a';

            Pixel* srcBase = tiles.GetBuffer() + tx * TILE_SIZE + (ty * TILE_SIZE) * tilesetWidth;
            int drawX = x * RENDER_TILE_SIZE;
            int drawY = y * RENDER_TILE_SIZE;

            for (int i = 0; i < TILE_SIZE; i++)
            {
                for (int j = 0; j < TILE_SIZE; j++)
                {
                    Pixel p = srcBase[j + i * tilesetWidth];

                    for (int dy = 0; dy < SCALE; dy++)
                    {
                        for (int dx = 0; dx < SCALE; dx++)
                        {
                            int screenX = drawX + j * SCALE + dx;
                            int screenY = drawY + i * SCALE + dy;
                            screen->GetBuffer()[screenX + screenY * screenWidth] = p;
                        }
                    }
                }
            }
        }
    }
}
