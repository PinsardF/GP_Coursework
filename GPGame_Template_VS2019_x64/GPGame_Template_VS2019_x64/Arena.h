#include <iostream>
using namespace std;
#pragma once

class Arena
{
public:
	char walls[4] = { 'N','S','E','O' };
	Cube wall_N[19];
	Cube wall_S[19];
	Cube wall_E[17];
	Cube wall_O[17];
	Cube arena;
	char shot_direction;
	int th_cube;
	int step;

	Arena();
	//~Arena();
	void init();
	void render_arena();
	void update_arena();
};