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

void Node::set_position(const Point &position) {
    m_position = position;
}

Point Node::absolute_position() const noexcept {
    if (const auto p = parent()) {
        return p->absolute_position() + position();
    }
    return position();
}

float Node::absolute_rotation() const noexcept {
    if (const auto the_parent = parent()) {
        return the_parent->absolute_rotation() + rotation();
    }
    return rotation();
}

Vector Node::absolute_scale() const noexcept {
    if (const auto p = parent()) {
        return p->absolute_scale() * scale();
    }
    return scale();
}

float Node::absolute_alpha() const noexcept {
    if (const auto p = parent()) {
        return p->absolute_alpha() * alpha();
    }
    return alpha();
}

bool Node::has_ancestor(const std::shared_ptr<Node> &node) const noexcept {
    for (auto ancestor = parent(); ancestor; ancestor = ancestor->parent()) {
        if (ancestor == node) {
            return true;
        }
    }
    return false;
}

std::shared_ptr<Node> Node::add_child(const std::shared_ptr<Node> &node) {
    if (!node->parent() && !has_ancestor(node)) {
        node->set_parent(shared_from_this());
        m_children.push_back(node);
        return node;
    }
    return nullptr;
}

std::shared_ptr<Node> Node::remove_child(const std::shared_ptr<Node> &node) {
    if (node->parent() == shared_from_this()) {
        m_children.erase(std::find(m_children.begin(), m_children.end(), node));
        node->set_parent(nullptr);
        return node;
    }
    return nullptr;
}

void Node::set_physics_body(const std::shared_ptr<PhysicsBody> &physics_body) {
    if (m_physics_body) {
        m_physics_body->set_node(nullptr);
    }
    if (physics_body) {
        physics_body->set_node(shared_from_this());
    }
    m_physics_body = physics_body;
}

Rectangle Node::frame() const {
    return Rectangle(position(), Size());
}

std::optional<float> PhysicsBody::rotation() const noexcept {
    if (const auto n = node()) {
        return n->rotation();
    }
    return std::nullopt;
}
