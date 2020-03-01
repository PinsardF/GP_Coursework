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
#include <time.h>

char walls[4] = { 'N','S','E','O' };
Cube wall_N[19];
Cube wall_S[19];
Cube wall_E[17];
Cube wall_O[17];
Cube arena;
BoundaryBox northWallBox;
BoundaryBox southWallBox;
BoundaryBox eastWallBox;
BoundaryBox westWallBox;
char shot_direction;
int th_cube = 0;
int step = 0;

Arena::Arena() {
	shot_direction = 'v';
}

/*Player::~Player()
{
	delete this;
}*/

void Arena::init() {
	Cube* visualArena = new Cube;
	arena = *visualArena;
	arena.Load();
	arena.fillColor = glm::vec4(130.0f, 96.0f, 61.0f, 1.0f);    // White Colour

	northWallBox = BoundaryBox(glm::vec3(0.0f,0.5f,9.0f),glm::vec3(9.5f,1.0f,9.5f),glm::vec3(-9.5f,0.0f,8.5f));
	southWallBox = BoundaryBox(glm::vec3(0.0f, 0.5f, -9.0f), glm::vec3(9.5f, 1.0f, -8.5f), glm::vec3(-9.5f, 0.0f, -9.5f));
	eastWallBox = BoundaryBox(glm::vec3(0.0f, 0.5f, 9.0f), glm::vec3(-8.5f, 1.0f, 9.5f), glm::vec3(-9.5f, 0.0f, -9.5f));
	westWallBox = BoundaryBox(glm::vec3(0.0f, 0.5f, -9.0f), glm::vec3(9.5f, 1.0f, -9.5f), glm::vec3(8.5f, 0.0f, -9.5f));

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

void Arena::update_arena(Graphics graphics) {
	srand(time(NULL));
	if (shot_direction == 'v') { // Manage with time
		shot_direction = walls[rand() % 4];

		if (shot_direction == 'S' || shot_direction == 'N') th_cube = rand() % 19;
		else th_cube = rand() % 17;
	}

	switch (shot_direction) {//CHANGE ADD A ZERO AT EACH (X10)
	case 'S':
		if (step == 20) wall_S[th_cube].fillColor = glm::vec4(0.0f, 153.0f, 0.0f, 1.0f);
		else if (step == 40) {
			wall_S[th_cube].fillColor = glm::vec4(204.0f, 0.0f, 0.0f, 1.0f);
			step = 0;
		}
		break;
	case 'N':
		if (step == 20) wall_N[th_cube].fillColor = glm::vec4(0.0f, 153.0f, 0.0f, 1.0f);
		else if (step == 40) {
			wall_N[th_cube].fillColor = glm::vec4(204.0f, 0.0f, 0.0f, 1.0f);
			step = 0;
		}
		break;
	case 'E':
		if (step == 20) wall_E[th_cube].fillColor = glm::vec4(0.0f, 153.0f, 0.0f, 1.0f);
		else if (step == 40) {
			wall_E[th_cube].fillColor = glm::vec4(204.0f, 0.0f, 0.0f, 1.0f);
			step = 0;
		}
		break;
	case 'O':
		if (step == 20) wall_O[th_cube].fillColor = glm::vec4(0.0f, 153.0f, 0.0f, 1.0f);
		else if (step == 40) {
			wall_O[th_cube].fillColor = glm::vec4(204.0f, 0.0f, 0.0f, 1.0f);
			step = 0;
		}
		break;
	default:
		cout << shot_direction << endl;
	}

	step++;

	glm::mat4 mv_matrix_arena =
		glm::translate(glm::vec3(0.0f, 0.003f, 0.0f)) *
		glm::scale(glm::vec3(17.0f, 0.001f, 17.0f)) *
		glm::mat4(1.0f);
	arena.mv_matrix = graphics.viewMatrix * mv_matrix_arena;
	arena.proj_matrix = graphics.proj_matrix;

	glm::mat4 mv_matrix_wall_N, mv_matrix_wall_S, mv_matrix_wall_E, mv_matrix_wall_O;
	float original_x = 9.0f;
	float original_z = 8.0f;

	for (int i = 0; i < size(wall_N); i++) {
		mv_matrix_wall_N =
			glm::translate(glm::vec3(original_x, 0.5f, 9.0f)) *
			glm::mat4(1.0f);
		wall_N[i].mv_matrix = graphics.viewMatrix * mv_matrix_wall_N;
		wall_N[i].proj_matrix = graphics.proj_matrix;

		mv_matrix_wall_S =
			glm::translate(glm::vec3(original_x, 0.5f, -9.0f)) *
			glm::mat4(1.0f);
		wall_S[i].mv_matrix = graphics.viewMatrix * mv_matrix_wall_S;
		wall_S[i].proj_matrix = graphics.proj_matrix;

		original_x--;
	}

	for (int i = 0; i < size(wall_E); i++) {
		mv_matrix_wall_E =
			glm::translate(glm::vec3(-9.0f, 0.5f, original_z)) *
			glm::mat4(1.0f);
		wall_E[i].mv_matrix = graphics.viewMatrix * mv_matrix_wall_E;
		wall_E[i].proj_matrix = graphics.proj_matrix;

		mv_matrix_wall_O =
			glm::translate(glm::vec3(9.0f, 0.5f, -original_z)) *
			glm::mat4(1.0f);
		wall_O[i].mv_matrix = graphics.viewMatrix * mv_matrix_wall_O;
		wall_O[i].proj_matrix = graphics.proj_matrix;

		original_z--;
	}
}