#include "BigCube.h"
#define DIST_BETWEEN_CUBES 1.1
#define SMALL_CUBE_SIZE 2.0
#define NUM_OF_DIMENTIONS 3
#define FPI_PRECISION 0.0001

using namespace glm;
BigCube::BigCube(int cubeSize) :cubeSize{ cubeSize }, cube_matrix{NULL}, index_matrix{NULL},
								 wall_angles{NULL}{
	if (cubeSize < 1) {
		//TODO
	}
	cube_matrix = new Displayable_object**[cubeSize];
	index_matrix = new vec3**[cubeSize];
	wall_angles = new float*[NUM_OF_DIMENTIONS];
	float middle_alignment;
	for (int i = 0; i < NUM_OF_DIMENTIONS; i++) {
		wall_angles[i] = new float[cubeSize];
		for (int j = 0; j < cubeSize; j++) {
			wall_angles[i][j] = 0;
		}
	}
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
				cube_matrix[i][j][k].move_object(((vec3(i, j, k) - 
					vec3(middle_alignment))*(float)(SMALL_CUBE_SIZE*DIST_BETWEEN_CUBES)));
				index_matrix[i][j][k] = vec3(i, j, k);
			}
		}
	}
}

BigCube::~BigCube() {
	for (int i = 0; i < cubeSize; i++) {

		for (int j = 0; j < cubeSize; j++) {
//			delete cube_matrix[i][j]; 
			delete index_matrix[i][j];
		}
		delete cube_matrix[i];
		delete index_matrix[i];
	}
	delete cube_matrix;
	delete index_matrix;
	for (int i = 0; i < 3; i++) {
		delete wall_angles[i];
	}
	delete wall_angles;
}

void BigCube::rotate_index(vec3 axis, int wall_index) {
	//Rotates given wall given an index.
	vec3 curr_index;
	int row_i = 0, row_j = 0, col_i = 0, col_j = cubeSize - 1;
	vec3 switch_helper = vec3(1);
	if (wall_index < cubeSize && wall_index >= 0) {
		if (axis == x_axis) {
			if (verify_wall_position(0)) {
				for (auto j = 0; j < cubeSize; j++) {
					for (auto k = 0; k < cubeSize; k++) {
						curr_index = index_matrix[wall_index][j][k];
						cube_matrix[(int)curr_index.x][(int)curr_index.y][(int)curr_index.z].
							rotate_object(rotation_degrees*rotation_direction, axis);
						std::cout << "The indexes spun x axis:  " << curr_index.x << "   " <<
							curr_index.y << "   " << curr_index.z << std::endl;
					}
				}
				update_wall_pos(0, wall_index, rotation_degrees * rotation_direction);
				if (wall_angles[0][wall_index] == 0) {
					transpose_indexes(0, wall_index);
					if (rotation_direction == -1) {
						switch_index_cols(0, wall_index);
					}
					else {
						switch_index_rows(0, wall_index);
					}
				}
			}
		}
		if (axis == y_axis) {
			if (verify_wall_position(1)) {
				std::cout << "Y axis: " << std::endl;
				for (auto i = 0; i < cubeSize; i++) {
					for (auto k = 0; k < cubeSize; k++) {
						curr_index = index_matrix[i][wall_index][k];
						cube_matrix[(int)curr_index.x][(int)curr_index.y][(int)curr_index.z].
							rotate_object(rotation_degrees*rotation_direction, axis);
						std::cout << "The indexes spun y axis:  " << curr_index.x << "   " <<
							curr_index.y << "   " << curr_index.z << std::endl;
					}
				}
				update_wall_pos(1, wall_index, rotation_degrees * rotation_direction);
				if (wall_angles[1][wall_index] == 0) {
					transpose_indexes(1, wall_index);
					if (rotation_direction == -1){
						switch_index_cols(1, wall_index);
					}
					else {
						switch_index_rows(1, wall_index);
					}
				}
			}
		}
		if (axis == z_axis) {
			if (verify_wall_position(2)) {
				for (auto i = 0; i < cubeSize; i++) {
					for (auto j = 0; j < cubeSize; j++) {
						curr_index = index_matrix[i][j][wall_index];
						cube_matrix[(int)curr_index.x][(int)curr_index.y][(int)curr_index.z].
							rotate_object(rotation_degrees*rotation_direction, axis);
					}
				}
				update_wall_pos(2, wall_index, rotation_degrees * rotation_direction);
				if (wall_angles[2][wall_index] == 0) {
					transpose_indexes(2, wall_index);
					if (rotation_direction == -1) {
						switch_index_cols(2, wall_index);
					}
					else {
						switch_index_rows(2, wall_index);
					}
				}

			}
		}
	}
	else {
		std::cout << "Attempting to move an illegal index" << std::endl;
	}
}

void BigCube::move_cube(vec3 direction) {
	//THIS IS MOCK
}

void BigCube::transpose_indexes(int axis, int face_index) {
	int row = 0, col = 0;
		vec3 switch_helper = vec3(1);
	switch (axis) {
		case 0: //X axis
			for (; row < cubeSize; row++){
				for (col = row; col < cubeSize; col++) {
					switch_helper = index_matrix[face_index][row][col];
					index_matrix[face_index][row][col] = index_matrix[face_index][col][row];
					index_matrix[face_index][col][row] = switch_helper;
				}
			}
			break;
		case 1: //Y axis
			for (; row < cubeSize; row++) {
				for (col = row; col < cubeSize; col++) {
					switch_helper = index_matrix[row][face_index][col];
					index_matrix[row][face_index][col] = index_matrix[col][face_index][row];
					index_matrix[col][face_index][row] = switch_helper;
				}
			}
			break;
		case 2: //Z axis
			for (; row < cubeSize; row++) {
				for (col = row; col < cubeSize; col++) {
					switch_helper = index_matrix[row][col][face_index];
					index_matrix[row][col][face_index] = index_matrix[col][row][face_index];
					index_matrix[col][row][face_index] = switch_helper;
				}
			}
			break;
		default:
			break;
	}
}

void BigCube::switch_index_rows(int axis, int face_index) {
	int row = 0, col = 0;
	vec3 switch_helper = vec3(1);
	switch (axis) {
	case 0: //X axis
		for (; row < cubeSize; row++) {
			for (; col < cubeSize; col++) {
				switch_helper = index_matrix[face_index][row][col];
				index_matrix[face_index][row][col] = index_matrix[face_index][cubeSize - 1 - row][col];
				index_matrix[face_index][cubeSize - 1 - row][col] = switch_helper;
			}
		}
		break;
	case 1: //Y axis
		for (; row < cubeSize; row++) {
			for (; col < cubeSize; col++) {
				switch_helper = index_matrix[row][face_index][col];
				index_matrix[row][face_index][col] = index_matrix[cubeSize - 1 - row][face_index][col];
				index_matrix[cubeSize - 1 - row][face_index][col] = switch_helper;
			}
		}
		break;
	case 2: //Z axis
		for (; row < cubeSize; row++) {
			for (; col < cubeSize; col++) {
				switch_helper = index_matrix[row][col][face_index];
				index_matrix[row][col][face_index] = index_matrix[cubeSize - 1 - row][col][face_index];
				index_matrix[cubeSize - 1 - row][col][face_index] = switch_helper;
			}
		}
		break;
	default:
		break;
	}
}

void BigCube::switch_index_cols(int axis, int face_index) {
	int row = 0, col = 0;
	vec3 switch_helper = vec3(1);
	switch (axis) {
	case 0: //X axis
		for (; col < cubeSize; col++) {
			for (; row < cubeSize; row++) {
				//std::cout << "Prior to switch:  " << index_matrix[face_index][row][col].x << "   " <<
				//	index_matrix[face_index][row][col].y << "   " << index_matrix[face_index][row][col].z << std::endl;
				switch_helper = index_matrix[face_index][row][col];
				index_matrix[face_index][row][col] = index_matrix[face_index][row][cubeSize - 1 - col];
				index_matrix[face_index][row][cubeSize - 1 - col] = switch_helper;
				//std::cout << "After the switch:  " << index_matrix[face_index][row][col].x << "   " <<
				//	index_matrix[face_index][row][col].y << "   " << index_matrix[face_index][row][col].z << std::endl;
			}
		}
		break;
	case 1: //Y axis
		for (; row < cubeSize; row++) {
			for (; col < cubeSize; col++) {
				switch_helper = index_matrix[col][face_index][row];
				index_matrix[col][face_index][row] = index_matrix[cubeSize - 1 - col][face_index][row];
				index_matrix[cubeSize - 1 - col][face_index][row] = switch_helper;
			}
		}
		break;
	case 2: //Z axis
		for (; row < cubeSize; row++) {
			for (; col < cubeSize; col++) {
				switch_helper = index_matrix[col][row][face_index];
				index_matrix[col][row][face_index] = index_matrix[cubeSize - 1 - col][row][face_index];
				index_matrix[cubeSize - 1 - col][row][face_index] = switch_helper;
			}
		}
		break;
	default:
		break;
	}

	
}

bool BigCube::verify_wall_position(int wall_index) {
	switch (wall_index) { //0 is x, 1 is y, 2 is z.
		case 0: {
			for (int i = 0; i < cubeSize; i++) {
				if (wall_angles[1][i] != 0 || wall_angles[2][i] != 0) {
					return false;
				}
			}
		break;
		}
		case 1: {
			for (int i = 0; i < cubeSize; i++) {
				if (wall_angles[0][i] != 0 || wall_angles[2][i] != 0) {
					return false;
				}
			}
			break;
		}
		case 2: {
			for (int i = 0; i < cubeSize; i++) {
				if (wall_angles[0][i] != 0 || wall_angles[1][i] != 0) {
					return false;
				}
			}
			break;
		}
	}
	return true;
}

void BigCube::update_wall_pos(int axis, int wall_index, float angle) {
	if (axis >= 0 && axis <= NUM_OF_DIMENTIONS && wall_index >= 0 && wall_index <= cubeSize) {
		wall_angles[axis][wall_index] = wall_angles[axis][wall_index] + angle;
		if (abs(wall_angles[axis][wall_index] - 90.0f) < FPI_PRECISION) {
			wall_angles[axis][wall_index] = 0;
		}
	}
}