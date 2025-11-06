#include <memory>
#include <print>

#include <seraph/core/Game.hpp>
#include <seraph/core/Input.hpp>
#include <seraph/memory/TextureManager.hpp>
#include <seraph/node/LabelNode.hpp>
#include <seraph/node/Scene.hpp>
#include <seraph/node/SpriteNode.hpp>
#include <seraph/physics/RectanglePhysicsBody.hpp>

class MyScene : public Scene {

public:

    virtual void initialize() override {
        set_physics_world(PhysicsWorld(5.0f, Vector(0.0f, 9.8f)));

        m_title = std::make_shared<LabelNode>("data/Arial.ttf", U"Gravity Demo");
        m_title->set_position(Point(12.0f, 12.0f));
        m_title->set_font_size(24);
        add_child(m_title);

        m_plane = std::make_shared<SpriteNode>("data/plane.png");
        m_plane->set_position(Point(640.0f, 100.0f));
        m_plane->set_physics_body(std::make_shared<RectanglePhysicsBody>(m_plane->frame().size()));
        m_plane->physics_body()->set_is_gravitant(true);
        m_plane->physics_body()->set_mass(1.0f);
        add_child(m_plane);
    }

private:

    std::shared_ptr<LabelNode> m_title;

    std::shared_ptr<SpriteNode> m_plane;
};

int main(int argc, const char **argv) {
    return Game(std::make_shared<MyScene>()).run();
}
