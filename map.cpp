#include "map.h"

map::map()
{
    const char temp1[MAP_ROWS][MAP_COLS * 3 + 1] =
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

    const char temp2[MAP_ROWS][MAP_COLS * 3 + 1] =
    {
        "zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz ",
        "zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz ",
        "zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz ",
        "zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz ",
        "zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz ",
        "zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz ",
        "zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz ",
        "zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz ",
        "zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz ",
        "zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz ",
        "zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz ",
        "zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz ",
        "zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz ",
        "zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz ",
        "zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz ",
        "zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz zz "

    };


    for (int r = 0; r < MAP_ROWS; r++)
        for (int c = 0; c < MAP_COLS * 3 + 1; c++)
            layer1[r][c] = temp1[r][c];

    for (int r = 0; r < MAP_ROWS; r++)
        for (int c = 0; c < MAP_COLS * 3 + 1; c++)
            layer2[r][c] = temp2[r][c];
}

void map::DrawLayer(Surface* screen, Surface& tiles, char layer[MAP_ROWS][MAP_COLS * 3 + 1])
{
    int tilesetWidth = tiles.GetWidth();
    int screenWidth = screen->GetWidth();

    for (int y = 0; y < MAP_ROWS; y++)
    {
        for (int x = 0; x < MAP_COLS; x++)
        {

            int tx = layer[y][x * 3] - 'a';
            int ty = layer[y][x * 3 + 1] - 'a';


            if (tx == ('z' - 'a') && ty == ('z' - 'a'))
                continue;

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

void map::Draw(Surface* screen, Surface& tiles1, Surface& tiles2)
{
    DrawLayer(screen, tiles1, layer1);
    DrawLayer(screen, tiles2, layer2);
}

