#include "Node.h"
//UNUSED
int x;
int z;
bool available;//Is the node available ? (not a wall)
bool explored;//Has the node been explored yet ?
bool path;//Has the node been chosen as the path ?
int origin_x;//Position of the node that got this node discovered
int origin_z;

float Node::f(Player player, float x_missile, float z_missile) {
	float g_x = abs(player.pos_player.x - x);
	float g_z = abs(player.pos_player.z - z);
	float g = sqrt((g_x * g_x) + (g_z * g_z));

	float h_x = abs(x - x_missile);
	float h_z = abs(z - z_missile);
	float h = sqrt((h_x * h_x) + (h_z * h_z));

	return g + h;
}
