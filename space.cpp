#include "space.h"
#include <raylib.h>

void Space::draw(vec2& global_offset) {

	moon_radius = earth_radius / 2;
	moon_pos.x = earth_pos.x + (30 * earth_radius);
	moon_pos.y = earth_pos.y;

	earth_pos = add_vecs(global_offset, earth_pos);
	moon_pos = add_vecs(global_offset, moon_pos);
	
	DrawCircle(earth_pos.x, earth_pos.y, earth_radius, earth_color);

	DrawCircle(moon_pos.x, moon_pos.y, moon_radius, moon_color);

}