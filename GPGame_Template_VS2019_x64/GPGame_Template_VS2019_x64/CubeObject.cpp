#include "CubeObject.h"

glm::vec3 cubePosition;
glm::vec3 cubeVelocity;
glm::vec3 cubeAcceleration;
int cubeWeight;
Cube cubeBody;
BoundaryBox cubeBox;

CubeObject::CubeObject(glm::vec3 input_position, glm::vec3 input_velocity, 
	glm::vec3 input_acceleration, int input_weight, Cube input_body){
	cubePosition = input_position;
	cubeVelocity = input_velocity;
	cubeAcceleration = input_acceleration;
	cubeWeight = input_weight;
	cubeBody = input_body;
}

CubeObject::CubeObject() : cubePosition(glm::vec3(0.0f, 0.0f, 0.0f)), cubeVelocity(glm::vec3(0.0f, 0.0f, 0.0f)),
cubeAcceleration(glm::vec3(0.0f, 0.0f, 0.0f)), cubeWeight(1) {}

void CubeObject::init() {
	cubeBody.Load();
}

void CubeObject::collide(BoundaryBox object) {
	if (cubeBox.detect_collision(object)) {
		glm::vec3 center = cubeBox.center_of_collision(object);
		float x = center.x - cubePosition.x;
		float y = center.y - cubePosition.y;
		float z = center.z - cubePosition.z;
		float length = sqrt((x * x) + (y * y) + (z * z));
		x /= length;
		y /= length;
		z /= length;
		glm::vec3 force = glm::vec3(x, y, z);
		react(force);
	}
}

void CubeObject::react(glm::vec3 force) {
	cubeVelocity.x += force.x;
	cubeVelocity.y += force.y;
	cubeVelocity.z += force.z;
}

void CubeObject::update(Graphics graphics) {
	cubePosition.x += cubeVelocity.x;
	cubePosition.y += cubeVelocity.y;
	cubePosition.z += cubeVelocity.z;
	glm::mat4 mv_cube = glm::translate(cubePosition) *glm::mat4(1.0f);
	cubeBody.mv_matrix = graphics.viewMatrix * mv_cube;
	cubeBody.proj_matrix = graphics.proj_matrix;
	cubeBody.Draw();
}
