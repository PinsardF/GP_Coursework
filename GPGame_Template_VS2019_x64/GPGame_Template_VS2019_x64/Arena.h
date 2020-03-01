#include <iostream>
#include "BoundaryBox.h"
using namespace std;
#pragma once

class Arena
{
public:
	char walls[4] = { 'N','S','E','O' };
	Cube wall_N[17];
	Cube wall_S[17];
	Cube wall_E[17];
	Cube wall_O[17];
	std::vector <char> flashingCubesChar;
	std::vector <int> flashingCubesInt;
	std::vector <int> flashingCubesTime;
	Cube arena;
	std::vector<Cube> flashing_cubes;
	BoundaryBox northWallBox;
	BoundaryBox southWallBox;
	BoundaryBox eastWallBox;
	BoundaryBox westWallBox;
	char shot_direction;
	int th_cube;
	int step;
	int frozen;
	int flashing_time;
	int flash;

	Arena();
	//~Arena();
	void init();
	void render_arena(Graphics graphics);
	void update_arena(Graphics graphics);
	void color_a_cube(int index, glm::vec4 color);
	void flashing_cube();
};