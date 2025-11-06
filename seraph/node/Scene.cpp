#include <seraph/node/Scene.hpp>

#include <memory>

#include <seraph/core/Color.hpp>
#include <seraph/core/Rectangle.hpp>
#include <seraph/node/Node.hpp>
#include <seraph/physics/PhysicsWorld.hpp>

std::shared_ptr<Scene> Node::scene() {
    for (auto node = shared_from_this(); node; node = node->parent()) {
        if (auto scene = std::dynamic_pointer_cast<Scene>(node)) {
            return scene;
        }
    }
    return nullptr;
}

Rectangle Scene::frame() const {
    return Rectangle(position(), Size(1.0f, 1.0f));
}
