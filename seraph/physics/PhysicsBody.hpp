#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include <seraph/core/Rectangle.hpp>
#include <seraph/core/Vector.hpp>

class Node;

class PhysicsBody {

public:

    /// Constructs a default `PhysicsBody`.
    ///
    /// A default `PhysicsBody` is neutral in state, yet still potentially
    /// affectable by the `PhysicsWorld`. It has no defining categories and
    /// collides with nothing. It is not gravitant, has no applied force or
    /// velocity, and has a default mass of `1.0f`.
    constexpr PhysicsBody() noexcept = default;

    virtual ~PhysicsBody() noexcept = default;

    /// The bit mask that identifies this `PhysicsBody`'s category for collisions.
    constexpr std::uint64_t category_bit_mask() const noexcept {
        return m_category_bit_mask;
    }

    inline void set_category_bit_mask(std::uint64_t category_bit_mask) noexcept {
        m_category_bit_mask = category_bit_mask;
    }

    /// The bit mask that identifies the object categories this `PhysicsBody` can collide with. 
    constexpr std::uint64_t collision_bit_mask() const noexcept {
        return m_collision_bit_mask;
    }

    inline void set_collision_bit_mask(std::uint64_t collision_bit_mask) noexcept {
        m_collision_bit_mask = collision_bit_mask;
    }

    /// Indicates if the `PhysicsBody` is affected by gravity.
    constexpr bool is_gravitant() const noexcept {
        return m_is_gravitant;
    }

    inline void set_is_gravitant(bool is_gravitant) noexcept {
        m_is_gravitant = is_gravitant;
    }

    /// The `PhysicsBody`'s mass.
    constexpr float mass() const noexcept {
        return m_mass;
    }

    inline void set_mass(float mass) noexcept {
        m_mass = mass;
    }

    /// The force currently being applied to the `PhysicsBody`.
    constexpr const Vector &force() const noexcept {
        return m_force;
    }

    inline void set_force(const Vector &force) noexcept {
        m_force = force;
    }

    /// The `PhysicsBody`'s current velocity.
    constexpr const Vector &velocity() const {
        return m_velocity;
    }

    inline void set_velocity(const Vector &velocity) noexcept {
        m_velocity = velocity;
    }

    inline std::shared_ptr<Node> node() const noexcept {
        return m_node.lock();
    }

    inline bool can_collide(const PhysicsBody &other) const noexcept {
        return (collision_bit_mask() & other.category_bit_mask()) != std::uint64_t(0);
    }

    virtual bool is_colliding(const PhysicsBody &other) const noexcept = 0;

    // NOTE: Defined in node/Node.cpp
    std::optional<float> rotation() const noexcept;

private:
friend class Node;

    inline void set_node(const std::shared_ptr<Node> &node) noexcept {
        m_node = node;
    }

private:

// PACKED

    std::weak_ptr<Node> m_node;

    std::uint64_t m_category_bit_mask;

    std::uint64_t m_collision_bit_mask;

    Vector m_force;

    Vector m_velocity;

    float m_mass = 1.0f;

    bool m_is_gravitant = false;
};
