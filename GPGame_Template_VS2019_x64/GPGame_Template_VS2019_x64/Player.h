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
	glm::mat4 move_cube;

	Player(float input_x, float input_y, float input_z);
	~Player();
	void init();
	void set_in_space();
	void render_character();
	void move();
};