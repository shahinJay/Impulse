#include "camera.h"
#include "vector.h"
#include <raylib.h>
#include <iostream>


void cam2::take_input() {

	static vec2 s_p, e_p;
	static Vector2 start_pos;
	static Vector2 end_pos;

	static bool is_dragging = false;

	if (IsKeyDown(KEY_W)) {

		this->zoom *= 1.05;
	}
	if (IsKeyDown(KEY_S)) {
		this->zoom *= 0.95;
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		start_pos = GetMousePosition();
		is_dragging = true;
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && is_dragging) {

		end_pos = GetMousePosition();

		vec2 delta = { end_pos.x - start_pos.x , end_pos.y - start_pos.y };

		this->position.x -= delta.x / (this->zoom );
		this->position.y -= delta.y / (this->zoom );

		start_pos = end_pos;
	}
	else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		is_dragging = false;
	}
	
}