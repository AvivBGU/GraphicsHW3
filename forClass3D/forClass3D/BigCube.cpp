#include "BigCube.h"
#define DIST_BETWEEN_CUBES 1.1
#define SMALL_CUBE_SIZE 2.0

using namespace glm;
BigCube::BigCube(int cubeSize) :cubeSize{ cubeSize }, cube_matrix{NULL}, index_matrix{NULL} {
	if (cubeSize < 1) {
		//TODO
	}
	cube_matrix = new Displayable_object**[cubeSize];
	index_matrix = new vec3**[cubeSize];
	float middle_alignment;
	for (int i = 0; i < cubeSize; i++) {
		cube_matrix[i] = new Displayable_object*[cubeSize];
		index_matrix[i] = new vec3*[cubeSize];
		for (int j = 0; j < cubeSize; j++) {
			cube_matrix[i][j] = new Displayable_object[cubeSize];
			index_matrix[i][j] = new vec3[cubeSize];
			for (int k = 0; k < cubeSize; k++) {
				if (cubeSize % 2 == 0) {
					middle_alignment = (cubeSize - 1.0f) / 2.0f;
				}
				else {
					middle_alignment = int(cubeSize / 2);
				}
				cube_matrix[i][j][k].move_object(((vec3(i, j, k) - vec3(middle_alignment))*(float)(SMALL_CUBE_SIZE*DIST_BETWEEN_CUBES)));
				index_matrix[i][j][k] = vec3(i, j, k);
			}
		}
	}
}

BigCube::~BigCube() {
	//THIS IS MOCK
}

void BigCube::rotate_index(int face_index) {
	//THIS IS MOCK
}

void BigCube::move_cube(vec3 direction) {
	//THIS IS MOCK
}