#ifndef BIGCUBE_INCLUDED_H
#define BIGCUBE_INCLUDED_H

#include "glm\glm.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "obj_loader.h"
#include "stdio.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Displayable_object.h"


using namespace glm;

class BigCube {
public:
	//Constructor
	BigCube(int cubeSize);
	virtual ~BigCube();
	void rotate_index(int face_index);
	void move_cube(vec3 direction);

	void change_rotation_angle(float angle_mult) {
		if (rotation_degrees*angle_mult < 180) {
			rotation_degrees *= angle_mult;
		}
	}

	void change_rotation_direction() {
		rotation_direction *= -1;
	}
	vec3 get_index_vec(int i, int j, int k) {
		return index_matrix[i][j][k];
	}

	Displayable_object& get_small_cube(int i, int j, int k) {
		return cube_matrix[i][j][k];
	}

private:
	/*glm::mat4 First_translate;
	glm::mat4 Rotatation;
	glm::mat4 Second_translate;*/
	float rotation_degrees = 45.0f;
	int rotation_direction = 1;
	const int cubeSize;
	Displayable_object*** cube_matrix;
	vec3*** index_matrix;


};
#endif