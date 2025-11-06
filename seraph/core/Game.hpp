#pragma once

#include <memory>

#include <seraph/core/Input.hpp>
#include <seraph/core/Size.hpp>
#include <seraph/core/Window.hpp>
#include <seraph/node/Node.hpp>
#include <seraph/node/Scene.hpp>
#include <seraph/physics/PhysicsWorld.hpp>

class Game {

public:

    inline Game(const std::shared_ptr<Scene> &scene) noexcept :
        m_scene(scene),
        m_window(Size(1280, 720), "Window") { }

    static constexpr float time_per_fixed_update() noexcept {
        return 1.0f / 60.0f;
    }
    
    inline std::shared_ptr<Scene> scene() const {
        return m_scene;
    }

    inline void set_scene(const std::shared_ptr<Scene> &scene) {
        m_scene = scene;
    }

    inline virtual void on_gain_focus() { }

    inline virtual void on_lose_focus() { }

    int run();

private:

    void process_events();

    void update(const std::shared_ptr<Node> &node, float delta_time);

    void fixed_update(const std::shared_ptr<Node> &node);

    void render();

    void draw(const std::shared_ptr<Node> &node);

    std::shared_ptr<Scene> m_scene;

    Window m_window;
};
