#pragma once
#include "vector.h"

#include <raylib.h>
#include <vector>
#include "state.h"

class Space {
public:

	struct body {
		state state;
		double mass;
		double radius;
		Color color;
	};

	body earth;
	body moon;

	std::vector<body> bodies;

	Space();

	void set_earth();
	void set_moon();

	void generate_space();

	void draw(vec2& cam_pos, double& scale, vec2& screen_center);
};