#include <iostream>
using namespace std;
#pragma once

class Player
{
public:
	float		x;
	float		y;
	float		z;
	Cube		character;
	Graphics    graphics;
	glm::mat4	pos_player;

	Player();
	//~Player();
	void init();
	void render_character();
};