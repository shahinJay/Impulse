#pragma once

#include <math.h>
#include <vector>

#include "vector.h"
#include "state.h"
#include "space.h"


//импулсь

class Physics {
public:
	const double G = 6e4;
	double hardcoded_delta = 0.001;

	Space& space;
	
	Physics(Space& space);


	vec2 compute_accel(const vec2& position, Space::body& other);

	void apply_gravity(std::vector<Space::body>& bodies);

};