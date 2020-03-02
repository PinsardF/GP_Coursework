#include "shapes.h"
#include "BoundaryBox.h"
#include "graphics.h"
#include <glm\gtx\transform.hpp>

using namespace std;
#pragma once

class Arena{
public:
	Cube myFloor;//Object floor
	Cube wall_N[17];//Cubes composing the walls
	Cube wall_S[17];
	Cube wall_E[17];
	Cube wall_O[17];
	std::vector <char> flashingCubesChar;//for each flashing cube, there is a char ('N','E','S','W') for the direction,
	std::vector <int> flashingCubesInt;//an int giving its coordinates,
	std::vector <int> flashingCubesTime;//and its flashing time
	Cube arena;//The arena itself
	BoundaryBox northWallBox;//The hitbox for each wall
	BoundaryBox southWallBox;
	BoundaryBox eastWallBox;
	BoundaryBox westWallBox;

	Arena();//Constructor
	void init();//Initialisation of the arena
	void render_arena(Graphics graphics);//Rendering of the arena
	void update_arena(Graphics graphics);//Update of the arena at each frame
	void color_a_cube(int index, glm::vec4 color);//Colors a selected cubes in the walls
	void flashing_cube();//Determines which cubes must flash
};