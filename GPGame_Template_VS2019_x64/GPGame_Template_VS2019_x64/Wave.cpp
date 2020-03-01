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
#include "Wave.h"

Cube projectiles[10];

Wave::Wave() { }

void Wave::init() {

	for (int i = 0; i < size(projectiles); i++) {
		projectiles[i].fillColor = glm::vec4(250.0f, 0.0f, 0.0f, 1.0f);    // Black Colour
		projectiles[i].Load();
	}
}