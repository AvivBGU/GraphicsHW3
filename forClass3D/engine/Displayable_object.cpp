#include "Displayable_object.h"
using namespace glm;


void Displayable_object::rotate_object(float degrees, vec3 axis) {
	rotation =  glm::rotate(degrees, axis)*rotation;

}

mat4 Displayable_object::get_result() {
	mat4 result = first_translate * rotation * second_translate;
	return (result);
}

void Displayable_object::move_object(vec3 direction) {
	second_translate = translate(second_translate, direction);
}