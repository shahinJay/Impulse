#include <iostream>
#include "raylib.h"
#include <vector>
#include <string.h>

#include "vector.h"
#include "space.h"

void camera_controller(vec2& global_offset) {
    static Vector2 start_pos{ 0,0 };
    static Vector2 end_pos{ 0,0 };

    static bool is_dragging;

    vec2 offset{ 0,0 };

    
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        start_pos = GetMousePosition();
        is_dragging = true;
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && is_dragging) {
        end_pos = GetMousePosition();

        is_dragging = false;

        vec2 s_p;
        s_p.x = start_pos.x;
        s_p.y = start_pos.y;

        vec2 e_p;
        e_p.x = end_pos.x;
        e_p.y = end_pos.y;


        vec2 dir = direction(s_p, e_p);
        double dist = distance(s_p, e_p);

        offset = scale_vec(dir, dist * GetFrameTime() * 2);

        std::cout << s_p.x;
        std::cout << " , ";
        std::cout << s_p.y;
        std::cout << " -> ";
        std::cout << e_p.x;
        std::cout << " , ";
        std::cout << e_p.y;
        std::cout << " DIST ";
        std::cout << dist;
        std::cout << " = ";
        std::cout << offset.x;
        std::cout << " , ";
        std::cout << offset.y << std::endl;

        global_offset = add_vecs(global_offset, offset);
    }
   
}

int main() {
    vec2 window_size{ 700, 700 };
    Space space;
    vec2 global_offset{ 0,0 };


    InitWindow(window_size.x, window_size.y, "Impulse: Orbital Dynamics and Mission Control Simulator");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        camera_controller(global_offset);
        space.draw(global_offset);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}