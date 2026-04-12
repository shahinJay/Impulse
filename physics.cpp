#include "physics.h"
#include <math.h>
#include <vector>

#include "vector.h"
#include "state.h"
#include "space.h"


Physics::Physics(Space& space):space(space) {

}

vec2 Physics::compute_accel(const vec2& position) {
	
	double dist = distance(position, this->space.earth.state.position);
	vec2 dir = direction(position, this->space.earth.state.position);
	vec2 accel = scale_vec(dir, (this->G * this->space.earth.mass) / (dist * dist));

	return accel;
}

state Physics::derive(const state& yn) {
	state d;
	d.position = yn.velocity;
	d.velocity = compute_accel(yn.position);
	return d;
}

void Physics::circularize(const state& yn) {
	
}

void Physics::apply_gravity() {
	
	state *yn = &this->space.moon.state;
	// USING RK4 integration method
	double delta = 1.0 / 60.0;


	state k1, k2, k3, k4;
	state sum;

	k1 = scale_state(derive(*yn), delta);
	k2 = scale_state(derive(add_states(*yn, scale_state(k1, 0.5f))), delta);
	k3 = scale_state(derive(add_states(*yn, scale_state(k2, 0.5f))), delta);
	k4 = scale_state(derive(add_states(*yn, k3)), delta);

	sum = scale_state(add_states(k1, add_states(scale_state(k2, 2), add_states(scale_state(k3, 2), k4))), 1.0f/6.0f);

	
	*yn = add_states(*yn, sum);
	
}