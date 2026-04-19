#include "physics.h"
#include <math.h>
#include <vector>

#include "vector.h"
#include "state.h"
#include "space.h"


Physics::Physics(Space& space):space(space) {

}

void Physics::circularize(Space::body& b, Space::body& c) {
	// setting initial velocity to circularize body 'B' around body 'C'

	vec2 diff = b.state.position - c.state.position;
	vec2 dir{ -diff.y, diff.x };
	dir = normalize(dir);
	double dist = distance(b.state.position, c.state.position);

	b.state.velocity = dir * (std::sqrt((G * c.mass) / dist));
}


vec2 Physics::compute_accel(const vec2& position, Space::body& other) {

	double dist = distance(position, other.state.position);
	vec2 dir = direction(position, other.state.position);
	vec2 accel = scale_vec(dir, (this->G * other.mass) / ((dist * dist) + 0.001));

	return accel;
}

state Physics::derive(const state& yn, Space::body& other) {
	state d;
	d.position = yn.velocity;
	d.velocity = compute_accel(yn.position, other);

	return d;
}

void Physics::apply_gravity(std::vector<Space::body>& bodies) {
	// Applying gravity using rk4 integration method

	std::vector<state> old_states;
	for (auto& b : bodies) old_states.push_back(b.state);
	
	std::vector<state> new_states = old_states;

	for (int y = 0; y < bodies.size(); y++) {

		for (int z = 0; z < bodies.size(); z++) {
			if (&bodies[y] == &bodies[z]) continue;

			state k1, k2, k3, k4;
			state sum;

			//k1 
			k1 = derive(old_states[y], bodies[z]) * hardcoded_delta;

			//k2
			k2 = (derive(old_states[y] + (k1 * 0.5f), bodies[z])) * hardcoded_delta;
			
			//k3
			k3 = (derive(old_states[y] + (k2 * 0.5f), bodies[z])) * hardcoded_delta;

			//k4
			k4 = (derive(old_states[y] + k3, bodies[z])) * hardcoded_delta;


			//weighted sum
			sum = (k1 + (k2 * 2) + (k3 * 2) + k4) * (1.0f / 6.0f);


			//updating new state
			new_states[y] = new_states[y] + sum;

		}
	}

	for (int i = 0; i < bodies.size(); i++) {
		bodies[i].state = new_states[i];
	}
}