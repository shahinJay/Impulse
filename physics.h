#pragma once

#include <math.h>
#include <vector>

#include "vector.h"
#include "state.h"
#include "space.h"


//импулсь

class Physics {
public:
	const double G = 6e6;
	double hardcoded_delta = 0.0001;

	Space& space;
	
	Physics(Space& space);

	void circularize(Space::body& b, Space::body& c);

	vec2 compute_accel(const vec2& position, Space::body& other);

	state derive(const state& yn, Space::body& other);

	void apply_gravity(std::vector<Space::body>& bodies);

};