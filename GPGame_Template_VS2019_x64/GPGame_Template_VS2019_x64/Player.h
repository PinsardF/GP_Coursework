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
	bool        keysStatus[1024];
	glm::mat4	pos_player;

	Player();
	//~Player();
	void init();
	void render_character();
	void set_in_space(Graphics myGraphics);
	void move();
};