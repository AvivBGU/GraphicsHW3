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
#define x_axis glm::vec3(1,0,0)
#define y_axis glm::vec3(0,1,0)
#define z_axis glm::vec3(0,0,1)
#define x_axis_ind 0
#define	y_axis_ind 1
#define z_axis_ind 2

using namespace glm;

class BigCube {
public:
	//Constructor
	BigCube(int cubeSize);
	virtual ~BigCube();
	void rotate_index(vec3 axis, int wall_index);
	void move_cube(vec3 direction);

	void change_rotation_angle(float angle_mult) {
		if (rotation_degrees*angle_mult < 180) {
			rotation_degrees *= angle_mult;
		}
		else {
			rotation_degrees = 180;
		}
	}

	void change_rotation_direction() {
		rotation_direction *= -1;
	}

	vec3& get_index_vec(int i, int j, int k) const {
		return index_matrix[i][j][k];
	}

	Displayable_object& get_small_cube(int i, int j, int k) const {
		return cube_matrix[i][j][k];
	}

	int get_cube_size() {
		return cubeSize;
	}

private:
	float rotation_degrees = 45.0f;
	int rotation_direction = 1;
	const int cubeSize;
	Displayable_object*** cube_matrix;
	vec3*** index_matrix;
	float** wall_angles;
	bool verify_wall_position(int wall_index);
	void update_wall_pos(int axis, int wall_index, float angle);
	void transpose_indexes(int axis, int face_index);
	void switch_index_rows(int axis, int face_index);
	void switch_index_cols(int axis, int face_index);

};
#endif