#include "map.h"
#include <cstring> // voor memcpy

// Hulpfunctie om een tileset vooraf te schalen
Surface ScaleTileset(Surface& original, int scale)
{
    int newWidth = original.GetWidth() * scale;
    int newHeight = original.GetHeight() * scale;
    Surface scaled(newWidth, newHeight);

    for (int y = 0; y < original.GetHeight(); y++)
    {
        for (int x = 0; x < original.GetWidth(); x++)
        {
            Pixel p = original.GetBuffer()[x + y * original.GetWidth()];

            for (int dy = 0; dy < scale; dy++)
            {
                for (int dx = 0; dx < scale; dx++)
                {
                    int sx = x * scale + dx;
                    int sy = y * scale + dy;
                    scaled.GetBuffer()[sx + sy * newWidth] = p;
                }
            }
        }
    }
    return scaled;
}

// Constructor met direct schalen in initializer-list
map::map(Surface& tiles1, Surface& tiles2)
    : scaledTiles1(ScaleTileset(tiles1, SCALE)),
    scaledTiles2(ScaleTileset(tiles2, SCALE))
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

    // Map-strings kopiëren naar member-arrays
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

void map::Draw(Surface* screen)
{
    DrawLayer(screen, scaledTiles1, layer1);
    DrawLayer(screen, scaledTiles2, layer2);
}
