#pragma once

#include <memory>
#include <vector>

#include <seraph/core/Vector.hpp>
#include <seraph/node/Node.hpp>
#include <seraph/physics/PhysicsBody.hpp>

class Game;

class Scene;

class PhysicsWorld {

public:

    constexpr PhysicsWorld() noexcept = default;

    constexpr PhysicsWorld(float speed, const Vector &gravity) noexcept :
        m_speed(speed),
        m_gravity(gravity) { }

    constexpr float speed() const noexcept {
        return m_speed;
    }

    inline void set_speed(float speed) noexcept {
        m_speed = speed;
    }

    constexpr const Vector &gravity() const noexcept {
        return m_gravity;
    }

    inline void set_gravity(const Vector &gravity) noexcept {
        m_gravity = gravity;
    }

    void update(const std::shared_ptr<Scene> &scene, float delta_time) const noexcept;

private:

    std::vector<std::shared_ptr<PhysicsBody>> collect_physics_bodies(const std::shared_ptr<Node> &node) const noexcept;

    void check_collisions(const std::vector<std::shared_ptr<PhysicsBody>> &physics_bodies) const noexcept;

    void apply_forces(const std::vector<std::shared_ptr<PhysicsBody>> &physics_bodies, float delta_time) const noexcept;

    void apply_velocity(const std::vector<std::shared_ptr<PhysicsBody>> &physics_bodies, float delta_time) const noexcept;

    Vector m_gravity;

    float m_speed = 1.0f;
};
