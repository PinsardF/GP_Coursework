#pragma once
#include "Player.h"
//UNUSED
class Node{
public:
	int x;
	int z;
	bool available;//Is the node available ? (not a wall)
	bool explored;//Has the node been explored yet ?
	bool path;//Has the node been chosen as the path ?
	int origin_x;//Position of the node that got this node discovered
	int origin_z;

	float f(Player player, float x_missile, float z_missile);//Calculates f
};

