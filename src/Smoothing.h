#pragma once
#include <cmath>

namespace Smoothing {
    inline float Lerp(float start_value, float end_value, float pct) {
        return (start_value + (end_value - start_value) * pct);
    }

    inline float EaseIn(float t) {
        return t * t;
    }

    inline float Flip(float x) {
        return 1 - x;
    }

    inline float Square(float x) {
        return std::sqrt(x);
    }

    inline float EaseOut(float t) {
        return Flip(Square(Flip(t)));
    }
}