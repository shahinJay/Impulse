#pragma once
#include "vector.h"

struct state {
	vec2 position{ 0, 0 };
	vec2 velocity{ 0, 0 };
};

inline bool compare_states(const state& a, const state& b) {
	bool res = (compare_vecs(a.position, b.position) && 
				(compare_vecs(a.velocity, b.velocity)));

	return res;
}

inline state add_states(const state& a, const state& b) {
	state res;

	res.position = add_vecs(a.position, b.position);
	res.velocity = add_vecs(a.velocity, b.velocity);

	return res;
}

inline state scale_state(const state& a, double c) {
	state res;

	res.position = scale_vec(a.position, c);
	res.velocity = scale_vec(a.velocity, c);

	return res;
}

inline void log_state(const state& state) {
	std::cout << " -> position:  ";
	std::cout << state.position.x;
	std::cout << " ,  ";
	std::cout << state.position.y;
	std::cout << " || velocity:  ";
	std::cout << state.velocity.x;
	std::cout << " ,  ";
	std::cout << state.velocity.y;
	std::cout << " |||" << std::endl;
}

