#pragma once
#include "surface.h"

using namespace Tmpl8;

class map
{
public:
    static constexpr int MAP_ROWS = 16;
    static constexpr int MAP_COLS = 26;
    static constexpr int TILE_SIZE = 16;
    static constexpr int SCALE = 5;
    static constexpr int RENDER_TILE_SIZE = TILE_SIZE * SCALE;

    map();

    void DrawLayer(Surface* screen, Surface& tiles, char layer[MAP_ROWS][MAP_COLS * 3 + 1]);
    void Draw(Surface* screen, Surface& tiles1, Surface& tiles2);

private:
    char layer1[MAP_ROWS][MAP_COLS * 3 + 1];
    char layer2[MAP_ROWS][MAP_COLS * 3 + 1];
};

