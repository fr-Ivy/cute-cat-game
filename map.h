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

    void Draw(Surface* screen, Surface& tiles);

private:
    char layer1[MAP_ROWS][MAP_COLS * 3 + 1];
};
