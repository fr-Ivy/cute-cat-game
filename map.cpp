#include "map.h"
#include <cstring> // voor memcpy

// Hulpfunctie om een tileset vooraf te schalen
Surface ScaleTileset(Surface& original, int scale)
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

            int tx = layer[y][x * 3] - 'a';
            int ty = layer[y][x * 3 + 1] - 'a';


            if (tx == ('z' - 'a') && ty == ('z' - 'a'))
                continue;

            // Startadres van de tile in de geschaalde tileset
            Pixel* srcBase = tiles.GetBuffer() + tx * RENDER_TILE_SIZE + (ty * RENDER_TILE_SIZE) * tilesetWidth;

            // Startadres op het scherm
            Pixel* dstBase = screen->GetBuffer() + x * RENDER_TILE_SIZE + (y * RENDER_TILE_SIZE) * screenWidth;

            // Kopieer hele rijen in één keer
            for (int row = 0; row < RENDER_TILE_SIZE; row++)
            {
                memcpy(dstBase + row * screenWidth,
                    srcBase + row * tilesetWidth,
                    RENDER_TILE_SIZE * sizeof(Pixel));
            }
        }
    }
}

void map::Draw(Surface* screen, Surface& tiles1, Surface& tiles2)
{
    DrawLayer(screen, tiles1, layer1);
    DrawLayer(screen, tiles2, layer2);
}
