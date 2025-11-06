#pragma once

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

class Scene;

/// A node with no personal content.
class Node : public std::enable_shared_from_this<Node> {

public:

    constexpr Node() noexcept = default;

    virtual ~Node() noexcept = default;

// SECTION: Node Properties

    constexpr const std::string &name() const noexcept {
        return m_name;
    }

    inline void set_name(const std::string &name) noexcept {
        m_name = name;
    }

    constexpr const Point &position() const noexcept {
        return m_position;
    }

    virtual void set_position(const Point &position);

    constexpr float rotation() const noexcept {
        return m_rotation;
    }

    inline void set_rotation(float rotation) noexcept {
        m_rotation = rotation;
    }

    constexpr const Vector &scale() const noexcept {
        return m_scale;
    }

    inline void set_scale(const Vector &scale) noexcept {
        m_scale = scale;
    }

    constexpr float alpha() const noexcept {
        return m_alpha;
    }

    inline void set_alpha(float alpha) noexcept {
        m_alpha = std::clamp(0.0f, 1.0f, alpha);
    }

    constexpr bool is_hidden() const noexcept {
        return m_is_hidden;
    }

    inline void set_is_hidden(bool is_hidden) noexcept {
        m_is_hidden = is_hidden;
    }

    Point absolute_position() const noexcept;

    float absolute_rotation() const noexcept;

    Vector absolute_scale() const noexcept;

    float absolute_alpha() const noexcept;

// SECTION: Node Hierarchy

    inline std::shared_ptr<Node> parent() const noexcept {
        return m_parent.lock();
    }

    constexpr const std::vector<std::shared_ptr<Node>> &children() const noexcept {
        return m_children;
    }

    constexpr bool has_children() const noexcept {
        return !children().empty();
    }

    bool has_ancestor(const std::shared_ptr<Node> &node) const noexcept;

    std::shared_ptr<Node> add_child(const std::shared_ptr<Node> &node);

    std::shared_ptr<Node> remove_child(const std::shared_ptr<Node> &node);

    // NOTE: Defined in Scene.cpp
    std::shared_ptr<Scene> scene();

// SECTION: Physics

    constexpr std::shared_ptr<PhysicsBody> physics_body() const {
        return m_physics_body;
    }

    void set_physics_body(const std::shared_ptr<PhysicsBody> &physics_body);

// SECTION: Virtual Methods

    virtual Rectangle frame() const;

    virtual void initialize() { }

    virtual void update(float delta_time) { }

    virtual void fixed_update(float delta_time) { }

    virtual void on_collision(const std::shared_ptr<Node> &other) { }

    virtual void draw(Window &window) { }

private:

    inline void set_parent(const std::shared_ptr<Node> &parent) {
        m_parent = parent;
    }

private:
friend class Game;

    constexpr bool is_initialized() const {
        return m_is_initialized;
    }

    inline void set_is_initialized(bool is_initialized) {
        m_is_initialized = is_initialized;
    }

private:

    std::string m_name;

    Point m_position;

    float m_rotation;

    Vector m_scale = Vector::one();

    float m_alpha = 1.0f;

    bool m_is_hidden;

    std::weak_ptr<Node> m_parent;

    std::vector<std::shared_ptr<Node>> m_children;

    std::shared_ptr<PhysicsBody> m_physics_body;

    bool m_is_initialized;
};
