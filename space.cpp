#include "space.h"
#include <raylib.h>
#include <iostream>

Space::Space() {
	set_earth();
	set_moon();
}

void Space::set_earth() {
	earth.state.position = { 300, 300 };
	earth.mass = 5e4;
	earth.radius = 60;
	earth.color = BLUE;
}

void Space::set_moon() {
	moon.state.position = { 0,300 };
	moon.state.velocity = { 0, 90 };
	moon.state.position.x = earth.state.position.x + (60.32 * earth.radius);
	moon.mass = 1e4;
	moon.radius = earth.radius / 2;
	moon.color = GRAY;
}

// "Mankind was born on Earth. It was never meant to die here." 

void Space::draw(vec2& cam_pos, double& scale, vec2& screen_center) {

	DrawCircle(scale * (earth.state.position.x - cam_pos.x) + screen_center.x, scale * (earth.state.position.y -  cam_pos.y ) + screen_center.y, scale * earth.radius, earth.color);
	DrawCircle(scale * (moon.state.position.x - cam_pos.x) + screen_center.x, scale * (moon.state.position.y - cam_pos.y) + screen_center.y, scale * moon.radius, moon.color);

}