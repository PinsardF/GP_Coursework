#include <iostream>
using namespace std;
#pragma once

class Arena
{
public:
	Cube wall_N[19];
	Cube wall_S[19];
	Cube wall_E[17];
	Cube wall_O[17];
	Cube arena;

	Arena();
	//~Arena();
	void init();
	void render_arena();
};