#pragma once
#include "vector.h"

#include <raylib.h>

class Space {
public:
	
	vec2 earth_pos{ 200,300 };
	vec2 moon_pos;

	double earth_radius = 15;
	double moon_radius;

	Color earth_color = BLUE;
	Color moon_color = GRAY;

	void draw(vec2& global_offset);

};