#include "space.h"
#include <raylib.h>
#include <vector>
#include <iostream>

#include <fstream>
#include <string>

#include "physics.h"


Space::Space() {

}

void Space::set_earth() {
	earth.state.position = { 0, 0 };
	earth.mass = 5e4;
	earth.radius = 60;
	earth.color = BLUE;
	bodies.push_back(earth);
}

void Space::set_moon() {	
	moon.state.velocity = { 0, 0 };
	moon.state.position.x = earth.state.position.x + (6 * earth.radius);
	//moon.state.position = { 200, 500 };

	moon.mass = 7e2;
	moon.radius = earth.radius / 2;
	moon.color = GRAY;
	bodies.push_back(moon);
}

// "Mankind was born on Earth. It was never meant to die here." 

void Space::generate_space() {
	set_earth();
	set_moon();

}

void Space::draw(vec2& cam_pos, double& scale, vec2& screen_center) {

	for (auto& b : bodies) {
		DrawCircle(scale * (b.state.position.x - cam_pos.x) + screen_center.x, 
			scale * (b.state.position.y - cam_pos.y) + screen_center.y, scale * b.radius, b.color);
	}

}