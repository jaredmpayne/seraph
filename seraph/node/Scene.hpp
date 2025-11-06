#pragma once

#include <memory>

#include <seraph/core/Color.hpp>
#include <seraph/core/Rectangle.hpp>
#include <seraph/node/Node.hpp>
#include <seraph/physics/PhysicsWorld.hpp>

class Game;

/// A node representing the base of a loadable segment of the game.
class Scene : public Node {

    friend class Game;

public:

    constexpr Scene() = default;

    virtual ~Scene() override = default;

    constexpr const Color &background_color() const noexcept {
        return m_background_color;
    }

    inline void set_background_color(const Color &background_color) noexcept {
        m_background_color = background_color;
    }

    constexpr const PhysicsWorld &physics_world() const noexcept {
        return m_physics_world;
    }

    constexpr PhysicsWorld &physics_world() noexcept {
        return m_physics_world;
    }

    inline void set_physics_world(const PhysicsWorld &physics_world) noexcept {
        m_physics_world = physics_world;
    }

    virtual Rectangle frame() const override;

private:

    Color m_background_color;

    PhysicsWorld m_physics_world;
};
