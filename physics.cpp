#include "physics.h"
#include <math.h>
#include <vector>

#include "vector.h"
#include "state.h"
#include "space.h"


Physics::Physics(Space& space):space(space) {

}


vec2 Physics::compute_accel(const vec2& position, Space::body& other) {

	double dist = distance(position, other.state.position);
	vec2 dir = direction(position, other.state.position);
	vec2 accel = scale_vec(dir, (this->G * other.mass) / ((dist * dist) + 0.001));

	return accel;
}


void Physics::apply_gravity(std::vector<Space::body>& bodies) {

	std::vector<state> old_states;
	for (auto& b : bodies) old_states.push_back(b.state);

	std::vector<vec2> accels(bodies.size(), { 0,0 });

	for (int y = 0; y < bodies.size(); y++) {
		for (int z = 0; z < bodies.size(); z++) {
			if (&bodies[y] == &bodies[z]) continue;

			accels[y] = add_vecs(compute_accel(old_states[y].position, bodies[z]), accels[y]);

		}
	}

	for (int i = 0; i < bodies.size(); i++) {
		bodies[i].state.velocity = add_vecs(old_states[i].velocity, scale_vec(accels[i], hardcoded_delta));
		bodies[i].state.position = add_vecs(old_states[i].position, scale_vec(bodies[i].state.velocity, hardcoded_delta));

		//std::cout << bodies[i].state.position.x << std::endl;
	}

	accels.clear();
	old_states.clear();
}