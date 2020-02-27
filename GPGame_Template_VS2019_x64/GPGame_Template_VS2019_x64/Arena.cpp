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

Cube wall_N[19];
Cube wall_S[19];
Cube wall_E[17];
Cube wall_O[17];
Cube arena;

Arena::Arena() {}

/*Player::~Player()
{
	delete this;
}*/

void Arena::init() {
	Cube* visualArena = new Cube;
	arena = *visualArena;
	arena.Load();
	arena.fillColor = glm::vec4(130.0f, 96.0f, 61.0f, 1.0f);    // White Colour

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

	for (int i = 0; i < size(wall_N); i++) {
		wall_N[i].Draw();
		wall_S[i].Draw();
	}

	for (int i = 0; i < size(wall_E); i++) {
		wall_E[i].Draw();
		wall_O[i].Draw();
	}
}