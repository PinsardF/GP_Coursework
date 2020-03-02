#include "Missile.h"
#include <glm\gtx\transform.hpp>
#include "ExplosionEmitter.h"

Sphere missileBody;
glm::vec3 pos_missile;
glm::vec3 vel_missile;
int missileTimeToLive;
int missileLoadingTime;
ExplosionEmitter explosion;

Missile::Missile(glm::vec3 spawnPoint) {
	pos_missile = spawnPoint;
	vel_missile = glm::vec3(0.0f, 0.0f, 0.0f);
	missileTimeToLive = 200;
	missileLoadingTime = 100;
}

void Missile::init() {
	missileBody.Load();
	/*missileBody.fillColor = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);//YELLOW
	missileBody.lineColor = glm::vec4(0.8f, 0.8f, 0.0f, 1.0f);//YELLOW*/
	missileBody.fillColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

void Missile::render_missile(Graphics graphics) {
	if (missileTimeToLive > 0) {
		glm::mat4 mv_missile =
			glm::translate(pos_missile) *
			glm::scale(glm::vec3(0.9f, 0.9f, 0.9f)) *
			glm::mat4(1.0f);
		missileBody.mv_matrix = graphics.viewMatrix * mv_missile;
		missileBody.proj_matrix = graphics.proj_matrix;
		missileBody.Draw();
	}
}

void Missile::update_missile(Graphics graphics) {
	if (missileLoadingTime > 0) {
		missileLoadingTime--;
	}
	else if (missileLoadingTime == 0){
		missileBody.fillColor = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);//YELLOW
		missileLoadingTime--;
	}
	else {
		if (missileTimeToLive > 5) {
			pos_missile += vel_missile;
			//pos_missile -= glm::vec3(0.5f,0.0f,0.5f);
			vel_missile = glm::vec3(0.0f, 0.0f, 0.0f);
			missileTimeToLive--;
		}
		else if (missileTimeToLive == 5) {
			explosion = ExplosionEmitter(pos_missile);
			explosion.initExplosion();
			missileTimeToLive--;
		}
		else if (missileTimeToLive >= 0) {
			missileTimeToLive--;
		}
	}
}

void Missile::pathfinding(Player player) {
	glm::vec3 targetPath = player.pos_player - pos_missile;
	float xPath = targetPath.x / sqrt((targetPath.x * targetPath.x) + (targetPath.z * targetPath.z));
	float zPath = targetPath.z / sqrt((targetPath.x * targetPath.x) + (targetPath.z * targetPath.z));
	vel_missile.x = xPath / 11.0f;
	vel_missile.z = zPath / 11.0f;

	/*
	Node: int x, int y, float f(), bool available, bool explored, int origin_x, int origin_z;
	Node map[34][34];
	for(int i=0;i<34;i++){
		for(int j=0;j<34;j++){
			map[i][j].x = i;
			map[i][j].y = j;
			map[i][j].explored = false;
			map[i][j].path = false;
		}
		//si c'est pas un mur : map[i][j].available = true; sinon map[i][j].available = false;
	}
	std::vector<Node> path_nodes;
	std::vector<Node> explored_nodes;
	std::vector<Node> final_path;
	bool done = false;
	this_x = missile.pos_missile.x;//calcul pour transformer la position en cases
	this_y = missile.pos_missile.y;//idem
	this_node = map[this_x]{this_y];
	Node old_node = this_node;
	while(!done){//While player isn't reached....
		for(int add_x=-1;add_x<1;add_x++){//for each neighbor cell
			for(int add_y = -1; add_x < 1; add_y++){
			if(map[this_x + add_x][this_y + add_y].available){
					if(x+add_x == missile.pos_missile.x && y+add_y == missile.pos_missile.y){//calcul pour transformer la position en cases
						map[x+add_x][y+add_y].x = old_node.x;
						map[x+add_x][y+add_y].y = old_node.y;
						path_nodes.add(map[x+add_x][y+add_y]);
						done = true;
					} else {
						if(!map[this_x + add_x][this_y + add_y].explored){
							explored_nodes.push_back(map[this_x + add_x][this_y + add_y]);
						}
					}
				}
			}
		}

		min_f = 0.0f;//find the minimum f
		for(int i=0;i<explored_nodes.size();i++){
			if(explored_nodes[i].f() < min_f){
				min_f = explored_nodes[i].f();
			}	
		}

		for(int i=0;i<explored_nodes.size();i++){//find the node with the minimum f previously determindes
			if(explored_nodes[i].f() <= min_f){
				min_f = map[this_x + add_x][this_y + add_y].f;
				min_node = map[this_x + add_x][this_y + add_y];
			}
		}
		this_node = min_node;
		path_nodes.push_back(this_node);
	}
	//We have all the cells found
	bool reached = false;
	Node previous_node = map[player.pos_player.x][player.pos_player.y];//calcul blablabla
	float new_x = 0.0f;
	float new_z = 0.0f;
	while(!reached){
		new_x = previous_node.origin_x;
		new_z = previous_node.origin_z;
		if(new_x = missile.pos_missile.x && new_z = missile.pos_missile.z){//calcul
			missile.cel = glm::vec3(new_x,0.0f,new_z);
			reached;
		} else{
			previous_node = map[new_x][new_z];
		}
	}
	*/
}
