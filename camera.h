#pragma once
#include "vector.h"
#include <raylib.h>

class cam2 {
public:
		vec2 position{ 0,0 };
		float zoom = 1;

		void take_input();
};