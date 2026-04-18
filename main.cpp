#include <iostream>
#include "raylib.h"
#include <vector>
#include <string.h>

#include "vector.h"
#include "space.h"
#include "camera.h"

#include "physics.h"


int main() {
    vec2 window_size{ 1080, 720 };
    vec2 screen_center = { window_size.x / 2 , window_size.y / 2 };
    cam2 camera;

    Space space;
    space.generate_space();
    Physics physics(space);

    double scale = 1.00;

    InitWindow(window_size.x, window_size.y, "Impulse: 2D Orbital Dynamics and Mission Control Simulator");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        
        camera.take_input();
        scale = camera.zoom;
        physics.apply_gravity(space.bodies);

        space.draw(camera.position, scale, screen_center);
        
        EndDrawing();
    }


    CloseWindow();
    return 0;
}