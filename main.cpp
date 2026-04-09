#include <iostream>
#include "raylib.h"
#include <vector>

Vector2 window_size = { 500,500 };

struct state {
    Vector2 velocity;
    Vector2 position;
};

struct body {
    state state;
    float size = 15;
    Color color = RAYWHITE;
};

// VECTOR MATH -----------------------------------------------------------------------------------
Vector2 add_vecs(Vector2 a, Vector2 b) {
    Vector2 res;

    res.x = a.x + b.x;
    res.y = a.y + b.y;

    return res;
}

Vector2 scale_vec(Vector2 a, double c) {
    Vector2 res;

    res.x = a.x * c;
    res.y = a.y * c;

    return res;
}

double length(Vector2 a) {
    return sqrt((a.x * a.x) + (a.y * a.y));
}

double distance(Vector2 a, Vector2 b) {
    double dist = sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
    return dist;
}

Vector2 normalize(Vector2 a) {
    Vector2 normalized = scale_vec(a , 1/length(a));
    return normalized;
}

Vector2 direction(Vector2 from, Vector2 to) {
    Vector2 dir = Vector2(to.x - from.x, to.y - from.y);
    return normalize(dir);
}

//----------------------------------------------------------------------------------------------------

//STATE MATH ------------------------------------------------------------------------------------------
state add_states(state a, state b) {
    state res;

    res.position = add_vecs(a.position, b.position);
    res.velocity = add_vecs(a.velocity, b.velocity);

    return res;
}

state scale_state(state a, double c){

    state res;

    res.position = scale_vec(a.position, c);
    res.velocity = scale_vec(a.velocity, c);

    return res;
}
//---------------------------------------------------------------------------------------------------------

Vector2 apply_gravity(Vector2 position) {
    Vector2 earth_pos = { window_size.x/2, window_size.y/2 };
    double M = 6e5;
    double G = 6e2;

    double r = distance(position, earth_pos);

    Vector2 dir = direction(position, earth_pos);

    Vector2 accel = scale_vec(dir, ((G * M) / ((r * r)+0.001)));
    
    return accel;
}

state derive(state current) {
    state der;
    der.position = current.velocity;
    der.velocity = apply_gravity(current.position);

    return der;
}

state apply_rk4(state yn) {
    double delta = 0.001;
    state k1, k2, k3, k4;

    k1 = scale_state(derive(yn), delta);
    k2 = scale_state(derive(add_states(yn, scale_state(k1, 0.5f))), delta);
    k3 = scale_state(derive(add_states(yn, scale_state(k2, 0.5f))), delta);
    k4 = scale_state(derive(add_states(yn, k3)), delta);

    state weighted_sum = scale_state(add_states(add_states(add_states(k1, scale_state(k2, 2)), scale_state(k3, 2)), k4), 1.0/6.0);
    yn = add_states(yn, weighted_sum);

    return yn;
}

int main() {
    InitWindow(window_size.x, window_size.y, "Impulse: Orbital Dynamics and Mission Control Simulator");
    SetTargetFPS(60);


    body body1;
    body1.state.position = { 140, 250 };
    body1.state.velocity = { 0, 900 };

    body body2;
    body2.state.position = { 400, 240 };
    body2.state.velocity = { -150, -900 };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawCircle(body1.state.position.x, body1.state.position.y, body1.size, body1.color);
        DrawCircle(body2.state.position.x, body2.state.position.y, body2.size, body2.color);

        body1.state = apply_rk4(body1.state);
        body2.state = apply_rk4(body2.state);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
