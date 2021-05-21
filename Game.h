#pragma once

#include "Common.h"
#include "Camera.h"
#include "Sprite.h"
#include "Shader.h"

class Game
{
public:
	Game(const Display& display);
	~Game() = default;

	void update(float delta);
	void render();

private:
	Camera mCamera;
	Shader mBasicShader;
	list<scope<Sprite>> mSprites;
};

