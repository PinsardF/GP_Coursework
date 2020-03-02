#pragma once
#include "Player.h"
class Node{
public:
	int x;
	int z;
	bool available;
	bool explored;
	bool path;
	int origin_x;
	int origin_z;

	float f(Player player, float x_missile, float z_missile);
};

