#pragma once
#include "surface.h" // Voor Surface en Pixel
using namespace Tmpl8;

// Tile-instellingen
const int TILE_SIZE = 16;         // Grootte originele tile in pixels
const int SCALE = 5;              // Hoeveel keer vergroten
const int RENDER_TILE_SIZE = TILE_SIZE * SCALE;

// Map-afmetingen
const int MAP_ROWS = 16;
const int MAP_COLS = 28;

class map
{
public:
    // Constructor neemt originele tilesets
    map(Surface& tiles1, Surface& tiles2);

    // Tekent beide layers
    void Draw(Surface* screen);

private:
    // Functie om een layer te tekenen
    void DrawLayer(Surface* screen, Surface& tiles, char layer[MAP_ROWS][MAP_COLS * 3 + 1]);

    // Geschaalde tilesets (vooraf berekend, sneller tekenen)
    Surface scaledTiles1;
    Surface scaledTiles2;

    // Map-data (string-array voor tile-indexen)
    char layer1[MAP_ROWS][MAP_COLS * 3 + 1];
    char layer2[MAP_ROWS][MAP_COLS * 3 + 1];
};
