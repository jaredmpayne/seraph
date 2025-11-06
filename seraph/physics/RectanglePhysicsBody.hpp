#pragma once

#include <seraph/core/Rectangle.hpp>
#include <seraph/core/Size.hpp>
#include <seraph/physics/PhysicsBody.hpp>

class RectanglePhysicsBody : public PhysicsBody {

public:

    constexpr RectanglePhysicsBody(const Size &size) noexcept :
        RectanglePhysicsBody(Rectangle(Point(), size)) { }

    constexpr RectanglePhysicsBody(const Rectangle &rectangle) noexcept :
        m_rectangle(rectangle) { }

    const Rectangle &rectangle() const noexcept {
        return m_rectangle;
    }

    void set_rectangle(const Rectangle &rectangle) noexcept {
        m_rectangle = rectangle;
    }

    virtual bool is_colliding(const PhysicsBody &other) const noexcept override;

private:

    Rectangle m_rectangle;
};
