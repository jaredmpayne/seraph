#include <seraph/physics/RectanglePhysicsBody.hpp>

bool RectanglePhysicsBody::is_colliding(const PhysicsBody &other) const noexcept {
    if (const auto *body = dynamic_cast<const RectanglePhysicsBody *>(&other)) {
        const auto rect1 = rectangle();
        const auto rect2 = body->rectangle();
        if (rect1.min_x() > rect2.max_x() || rect2.min_x() > rect1.max_x()) {
            return false;
        }
        if (rect1.max_y() > rect2.min_y() || rect2.max_y() > rect1.min_y()) {
            return false;
        }
        return true;
    }
    return false;
}
