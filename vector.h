#pragma once
#include <math.h>

struct vec2 {
    double x;
    double y;
};

inline bool compare_vecs(vec2 a, vec2 b) {
    return ((a.x == b.x) && (a.y == b.y));
}

inline vec2 add_vecs(vec2 a, vec2 b) {
    return { a.x + b.x, a.y + b.y };
}

inline vec2 scale_vec(vec2 a, double c) {
    vec2 res{ 0,0 };

    res.x = a.x * c;
    res.y = a.y * c;

    return res;
}

inline double length(vec2 a) {
    return sqrt((a.x * a.x) + (a.y * a.y));
}

inline double distance(vec2 a, vec2 b) {
    double dist = sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
    return dist;
}

inline vec2 normalize(vec2 a) {
    if (length(a) > 0.001)
        return scale_vec(a, 1 / length(a));
    return { 0,0 };
}

inline vec2 direction(vec2 from, vec2 to) {
    vec2 dir = vec2(to.x - from.x, to.y - from.y);
    return normalize(dir);
}
