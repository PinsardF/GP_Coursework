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

Cube    myFloor;
char walls[4] = { 'N','S','E','O' };
Cube wall_N[17];
Cube wall_S[17];
Cube wall_E[17];
Cube wall_O[17];
std::vector <char> flashingCubesChar;
std::vector <int> flashingCubesInt;
std::vector <int> flashingCubesTime;
BoundaryBox northWallBox;
BoundaryBox southWallBox;
BoundaryBox eastWallBox;
BoundaryBox westWallBox;
char shot_direction;

Arena::Arena() {
	shot_direction = 'v';
}

/*Player::~Player()
{
	delete this;
}*/

void Arena::init() {

	frozen = 0;
	flash = 0;
	flashing_time = 0;
	myFloor.Load();
	myFloor.fillColor = glm::vec4(130.0f / 255.0f, 96.0f / 255.0f, 61.0f / 255.0f, 1.0f);    // Sand Colour
	myFloor.lineColor = glm::vec4(130.0f / 255.0f, 96.0f / 255.0f, 61.0f / 255.0f, 1.0f);    // Sand again

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

void Arena::render_arena(Graphics graphics) {
	myFloor.mv_matrix = graphics.viewMatrix *
		glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)) *
		glm::scale(glm::vec3(1000.0f, 0.001f, 1000.0f)) *
		glm::mat4(1.0f);
	myFloor.proj_matrix = graphics.proj_matrix;
	myFloor.Draw();

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

	glm::mat4 mv_matrix_arena =
		glm::translate(glm::vec3(0.0f, 0.003f, 0.0f)) *
		glm::scale(glm::vec3(17.0f, 0.001f, 17.0f)) *
		glm::mat4(1.0f);
	arena.mv_matrix = graphics.viewMatrix * mv_matrix_arena;
	arena.proj_matrix = graphics.proj_matrix;

	glm::mat4 mv_matrix_wall_N, mv_matrix_wall_S, mv_matrix_wall_E, mv_matrix_wall_O;
	float original_x = 8.0f;
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

void Arena::color_a_cube(int index, glm::vec4 color) {
	switch (flashingCubesChar[index]) {
	case 'N':
		wall_S[flashingCubesInt[index]].fillColor = color; // Dark red color;
		break;
	case 'S':
		wall_N[flashingCubesInt[index]].fillColor = color; // Dark red color;
		break;
	case 'W':
		wall_E[flashingCubesInt[index]].fillColor = color; // Dark red color;
		break;
	case 'E':
		wall_O[flashingCubesInt[index]].fillColor = color; // Dark red color;
		break;
	default:
		cout << "A problem has occured" << endl;
	}
}

void Arena::flashing_cube() {

	for (int i = 0; i < flashingCubesInt.size(); i++) {
		if (flashingCubesTime[i] == 120 || flashingCubesTime[i] == 40) {
			color_a_cube(i, glm::vec4(150.0f, 0.0f, 0.0f, 1.0f));
		}
		else if (flashingCubesTime[i] == 80) {
			color_a_cube(i, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		}
		else if (flashingCubesTime[i] == 0) {
			color_a_cube(i, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
			flashingCubesChar[i] = 'X';
		}
		flashingCubesTime[i] --;
	}

	for (int i = 0; i < flashingCubesInt.size(); i++) {
		if (flashingCubesChar[i] == 'X') {
			flashingCubesChar.erase(flashingCubesChar.begin() + i);
			flashingCubesInt.erase(flashingCubesInt.begin() + i);
			flashingCubesTime.erase(flashingCubesTime.begin() + i);
			i--;
		}
	}
}