#pragma once

#include <math.h>
#include <vector>

#include "vector.h"
#include "state.h"
#include "space.h"


//импулсь

class Physics {
public:
	const double G = 6e3;

	Space& space;
	
	Physics(Space& space);

	vec2 compute_accel(const vec2& position);

	state derive(const state& yn);

	void circularize(const state& yn);

	void apply_gravity();

};