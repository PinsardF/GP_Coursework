// Standard C++ libraries
#include <iostream>
#include <vector>
using namespace std;
#include <string>

// Helper graphic libraries
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "graphics.h"
#include "shapes.h"
#include <vector>
#include "Arena.h"

Cube	wall_N[19];
Cube	wall_S[19];
Cube	wall_E[17];
Cube	wall_O[17];
Cube	myFloor;
Cube	arena;
char	shot_direction;
glm::vec4 original_cube_color; // Original cubes' color

Arena::Arena() {
	shot_direction = 'v'; // No direction chosen ('v' = 'vide' = 'empty')
	original_cube_color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

/*Player::~Player()
{
	delete this;
}*/

void Arena::init() {
	arena.Load();
	arena.fillColor = glm::vec4(130.0f, 96.0f, 61.0f, 1.0f);    // White Colour

	myFloor.Load();
	myFloor.fillColor = glm::vec4(130.0f / 255.0f, 96.0f / 255.0f, 61.0f / 255.0f, 1.0f);    // Sand Colour
	myFloor.lineColor = glm::vec4(130.0f / 255.0f, 96.0f / 255.0f, 61.0f / 255.0f, 1.0f);    // Sand again

	for (int i = 0; i < size(wall_N); i++) {
		wall_N[i].fillColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);    // Black Colour
		wall_S[i].fillColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);    // Black Colour

		wall_N[i].Load();
		wall_S[i].Load();
	}

	for (int i = 0; i < size(wall_E); i++) {
		wall_E[i].fillColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);    // Black Colour
		wall_O[i].fillColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);    // Black Colour

		wall_E[i].Load();
		wall_O[i].Load();
	}
}

void Arena::render_arena() {
	arena.Draw();
	myFloor.Draw();

	for (int i = 0; i < size(wall_N); i++) {
		wall_N[i].Draw();
		wall_S[i].Draw();
	}

	for (int i = 0; i < size(wall_E); i++) {
		wall_E[i].Draw();
		wall_O[i].Draw();
	}
}

void Arena::color_a_cube(int th_cube, glm::vec4 color) {
	switch (shot_direction) {
	case 'S':
		wall_S[th_cube].fillColor = color; // Dark red color;
		break;
	case 'N':
		wall_N[th_cube].fillColor = color; // Dark red color;
		break;
	case 'E':
		wall_E[th_cube].fillColor = color; // Dark red color;
		break;
	case 'O':
		wall_O[th_cube].fillColor = color; // Dark red color;
		break;
	default:
		cout << "A problem has been occured" << endl;
	}
}