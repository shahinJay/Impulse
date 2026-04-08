#include <iostream>
#include "raylib.h"

struct vec2 {
    double x = 0;
    double y = 0;
};

void apply_gravity(vec2& position) {
    double G = 5 * 10e2;
    double M = 12 * 10e4;

    double r = position.y - 450;

    double delta = 0.001;
    
    vec2 accel;
    accel.x = (position.x / position.x + 0.001) * (G * M) / (r * r);
    accel.y = (position.y/ position.y + 0.001) * (G * M) / (r * r);

    vec2 velo;
    velo.x += accel.x * delta;
    velo.y += accel.y * delta;

    position.x += velo.x * delta;
    position.y += velo.y * delta;

    std::cout << position.y << std::endl;
}

int main() {
    InitWindow(800, 450, "Impulse: Orbital Dynamics and Mission Control Simulator");
    SetTargetFPS(60);
    
    vec2 position;
    position.x = 400;
    position.y = 20;
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawCircle(position.x, position.y, 30, RAYWHITE);

        apply_gravity(position);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
