#pragma once

#include <cmath>

class Math {

public:

    static constexpr float epsilon() noexcept {
        return 1.0e-6f;
    }

    static constexpr bool is_approximately(float x, float y, float tolerance = epsilon()) noexcept {
        return std::abs(x - y) <= tolerance;
    }
};
