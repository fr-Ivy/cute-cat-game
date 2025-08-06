#pragma once
#include "Surface.h"

namespace Tmpl8 { class Game; }

class Player
{
public:
	Player() = default;
	Player(Tmpl8::Sprite* sprite, float x, float y);
	void keyUp(int key);
	void keyDown(int key);
	void moving(float deltaTime);
	void draw(Tmpl8::Surface& surface);

private:
	float x = 0;
	float y = 0;
	int frame = 0;
	Tmpl8::Sprite* sprite = nullptr;

	//keys
	bool W = false;
	bool A = false;
	bool S = false;
	bool D = false;
	float frameSeconds = 0.1f;
};

