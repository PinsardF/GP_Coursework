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
glm::vec3 velocity;//
//glm::vec3 acceleration;
bool isalive;
Line visualParticle;

/*Particle::Particle(int input_timetolive, glm::vec3 input_vector, bool input_isalive) {
	timetolive = input_timetolive;
	position.x = input_vector.x;
	position.y = input_vector.y;
	position.z = input_vector.z;
	isalive = input_isalive;
}*/

Particle::Particle(int input_timetolive, glm::vec3 input_position, glm::vec3 input_velocity, bool input_isalive) {
	timetolive = input_timetolive;
	position.x = input_position.x;
	position.y = input_position.y;
	position.z = input_position.z;
	velocity.x = input_velocity.x;
	velocity.y = input_velocity.y;
	velocity.z = input_velocity.z;
	isalive = input_isalive;
}

//Particle::Particle() : timetolive(200), position(glm::vec3(0.0f, 0.0f, 0.0f)), isalive(true) {}

Particle::Particle() : timetolive(200), position(glm::vec3(0.0f, 0.0f, 0.0f)), velocity(glm::vec3(0.0f,0.0f,0.0f)),
isalive(true) {}

void Particle::init() {
	visualParticle.Load();
	float color_a = rand() % 100;//choosing random colors
	color_a /= 100;
	float color_b = rand() % 100;
	color_b /= 100;
	float color_c = rand() % 100;
	color_c /= 100;
	float color_d = rand() % 100;
	color_d /= 100;
	visualParticle.fillColor = glm::vec4(/*1.0f, 1.0f, 1.0f, 1.0f*/color_a,color_b,color_c,color_d);
	visualParticle.lineColor = glm::vec4(/*0.2f, 1.0f, 0.8f, 1.0f*/color_a, color_b, color_c, color_d);
	visualParticle.lineWidth = 5.0f;
}

/*void Particle::update(Graphics graphics) {
	if (timetolive > 0.0f) {//if the particle's lifetime isn't over...
		int x_rand = rand() % 10;//it randomly deviates on the x and z axis
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
		timetolive--;//lifetime decreases
		glm::mat4 mv_particle =//we calculate the new projection of the particle
			glm::translate(position) *
			glm::scale(glm::vec3(200.0f, 200.0f, 0.03f)) *
			glm::mat4(1.0f);
		visualParticle.mv_matrix = graphics.viewMatrix * mv_particle;
		visualParticle.proj_matrix = graphics.proj_matrix;
	}
}*/

void Particle::update(Graphics graphics) {
	if (timetolive > 0.0f) {//if the particle's lifetime isn't over...
		float x_deviation = rand() % 10;//it randomly deviates on the x and z axis
		float x_sign = rand() % 2;
		if (x_sign > 0) x_deviation = -x_deviation;
		x_deviation /= 100;
		float z_deviation = rand() % 10;
		float z_sign = rand() % 2;
		if (z_sign > 0) z_deviation = -z_deviation;
		z_deviation /= 100;
		velocity = glm::vec3(x_deviation, 0.01f, z_deviation);
		position.x += velocity.x;
		position.y += velocity.y;
		position.z += velocity.z;
		timetolive--;//lifetime decreases
		glm::mat4 mv_particle =//we calculate the new projection of the particle
			glm::translate(position) *
			glm::scale(glm::vec3(200.0f, 200.0f, 0.03f)) *
			glm::mat4(1.0f);
		visualParticle.mv_matrix = graphics.viewMatrix * mv_particle;
		visualParticle.proj_matrix = graphics.proj_matrix;
	}
}
