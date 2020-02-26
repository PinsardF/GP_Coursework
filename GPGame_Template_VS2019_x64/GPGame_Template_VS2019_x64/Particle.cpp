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
#include "Particle.h"

int timetolive;
glm::vec3 position;
//glm::vec3 speed;
//glm::vec3 acceleration;
bool isalive;
Line visualParticle;

Particle::Particle(int input_timetolive, glm::vec3 input_vector, bool input_isalive) {
	timetolive = input_timetolive;
	position.x = input_vector.x;
	position.y = input_vector.y;
	position.z = input_vector.z;
	isalive = input_isalive;
}

Particle::Particle() : timetolive(200), position(glm::vec3(0.0f, 0.0f, 0.0f)), isalive(true) {}

void Particle::init() {
	visualParticle.Load();
	visualParticle.fillColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	visualParticle.lineColor = glm::vec4(0.2f, 1.0f, 0.8f, 1.0f);
	visualParticle.lineWidth = 5.0f;
}

glm::mat4 Particle::update() {
	if (timetolive > 0.0f) {
		int x_rand = rand() % 10;
		float x_deviation = 0.0f;
		switch (x_rand) {
		case 0:
			x_deviation = 0.03f;
			break;
		case 1:
			x_deviation = -0.03f;
			break;
		default:
			break;
		}
		int z_rand = rand() % 10;
		float z_deviation = 0.0f;
		switch (z_rand) {
		case 0:
			z_deviation = 0.03f;
			break;
		case 1:
			z_deviation = -0.03f;
			break;
		default:
			break;
		}

		position.x += x_deviation;
		position.y += 0.01f;
		position.z += z_deviation;
		timetolive--;
		glm::mat4 mv_particle =
			glm::translate(position) *
			glm::scale(glm::vec3(200.0f, 200.0f, 0.03f)) *
			glm::mat4(1.0f);
		return mv_particle;
	}
}

void Particle::destroy() {//unused for now
	delete this;
}
