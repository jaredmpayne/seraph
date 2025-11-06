#include <seraph/physics/PhysicsWorld.hpp>

#include <memory>
#include <ranges>
#include <vector>

#include <seraph/core/Vector.hpp>
#include <seraph/node/Node.hpp>
#include <seraph/node/Scene.hpp>
#include <seraph/physics/PhysicsBody.hpp>

void PhysicsWorld::update(const std::shared_ptr<Scene> &scene, float delta_time) const noexcept {
    const auto bodies = collect_physics_bodies(scene);
    check_collisions(bodies);
    apply_forces(bodies, delta_time);
    apply_velocity(bodies, delta_time);
}

// TODO: Rewrite this method as a view once Apple Clang catches up with their <ranges> implematation.
std::vector<std::shared_ptr<PhysicsBody>> PhysicsWorld::collect_physics_bodies(const std::shared_ptr<Node> &node) const noexcept {
    auto bodies = std::vector<std::shared_ptr<PhysicsBody>>();
    if (const auto body = node->physics_body()) {
        bodies.push_back(body);
    }
    for (const auto &child : node->children()) {
        const auto others = collect_physics_bodies(child);
        bodies.insert(bodies.end(), others.begin(), others.end());
    }
    return bodies;
}

void PhysicsWorld::check_collisions(const std::vector<std::shared_ptr<PhysicsBody>> &bodies) const noexcept {
    for (const auto &body_a : bodies) {
        for (const auto &body_b : bodies) {
            if (body_a != body_b && body_a->can_collide(*body_b)) {
                const auto node_a = body_a->node();
                const auto node_b = body_b->node();
                if (node_a && node_b && body_a->is_colliding(*body_b)) {
                    node_a->on_collision(node_b);
                }
            }
        }
    }
}

void PhysicsWorld::apply_forces(const std::vector<std::shared_ptr<PhysicsBody>> &bodies, float delta_time) const noexcept {
    for (const auto &body : bodies) {
        if (body->mass() != 0.0f) {
            const auto g = body->is_gravitant() ? gravity() : Vector();
            const auto acceleration = body->force() / body->mass() + g;
            const auto delta_velocity = acceleration * delta_time * speed();
            body->set_velocity(body->velocity() + delta_velocity);
        }
    }
}

void PhysicsWorld::apply_velocity(const std::vector<std::shared_ptr<PhysicsBody>> &bodies, float delta_time) const noexcept {
    for (const auto body : bodies) {
        if (const auto node = body->node()) {
            node->set_position(node->position() + body->velocity() * delta_time * speed());
        }
    }
}
