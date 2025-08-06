#include "Player.h"
#define WIN32_LEAN_AND_MEAN
#include <SDL.h>


Player::Player(Tmpl8::Sprite* sprite, float x, float y)
{
	this->x = x;
	this->y = y;
	this->sprite = sprite;
}

void Player::keyUp(int key)
{
	switch (key)
	{
	case SDL_SCANCODE_W:
	case SDL_SCANCODE_UP:
		W = false;
		break;
	case SDL_SCANCODE_A:
	case SDL_SCANCODE_LEFT:
		A = false;
		break;
	case SDL_SCANCODE_S:
	case SDL_SCANCODE_DOWN:
		S = false;
		break;
	case SDL_SCANCODE_D:
	case SDL_SCANCODE_RIGHT:
		D = false;
		break;
	}
}

void Player::keyDown(int key)
{
	switch (key)
	{
	case SDL_SCANCODE_W:
	case SDL_SCANCODE_UP:
		W = true;
		break;
	case SDL_SCANCODE_A:
	case SDL_SCANCODE_LEFT:
		A = true;
		break;
	case SDL_SCANCODE_S:
	case SDL_SCANCODE_DOWN:
		S = true;
		break;
	case SDL_SCANCODE_D:
	case SDL_SCANCODE_RIGHT:
		D = true;
		break;
	}
}

void Player::moving(float deltaTime)
{
	//bool isMoving = W || A || S || D;
	deltaTime /= 1000.0f;
	float speed = 200.0f;
	frameSeconds -= deltaTime;

	if (W)
	{
		y -= speed * deltaTime;

		if (frameSeconds <= 0.0f)
		{
			frame = ((frame + 1) % 4) + 8;
			sprite->SetFrame(frame);
			frameSeconds = 0.1f;
		}
	}

	if (A)
	{
		x -= speed * deltaTime;
		if (frameSeconds <= 0.0f)
		{
			frame = ((frame + 1) % 4) + 4;
			sprite->SetFrame(frame);
			frameSeconds = 0.1f;
		}
	}

	if (S)
	{
		y += speed * deltaTime;
		if (frameSeconds <= 0.0f)
		{
			frame = ((frame + 1) % 4);
			sprite->SetFrame(frame);
			frameSeconds = 0.1f;
		}
	}

	if (D)
	{
		x += speed * deltaTime;
		if (frameSeconds <= 0.0f)
		{
			frame = ((frame + 1) % 4) + 12;
			sprite->SetFrame(frame);
			frameSeconds = 0.1f;
		}
	}
}

void Player::draw(Tmpl8::Surface& surface)
{
	if (sprite)
	{
		sprite->Draw(&surface, x, y);
	}
}