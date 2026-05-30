#include <seraph/node/Node.hpp>

#include <algorithm>
#include <memory>
#include <optional>
#include <ranges>
#include <string>
#include <vector>

#include <seraph/core/Point.hpp>
#include <seraph/core/Rectangle.hpp>
#include <seraph/core/Vector.hpp>
#include <seraph/core/Window.hpp>
#include <seraph/physics/PhysicsBody.hpp>

std::optional<float> PhysicsBody::rotation() const noexcept {
    if (const auto n = node()) {
        return n->rotation();
    }
    return std::nullopt;
}
