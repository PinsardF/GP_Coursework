#include <iostream>
using namespace std;
#pragma once

class Arena
{
public:
	Cube	wall_N[19];
	Cube	wall_S[19];
	Cube	wall_E[17];
	Cube	wall_O[17];
	Cube	arena;
	Cube	myFloor;
	char shot_direction;
	glm::vec4 original_cube_color;

	Arena();
	//~Arena();
	void init();
	void render_arena();
	void color_a_cube(int th_cube, glm::vec4 color);
};