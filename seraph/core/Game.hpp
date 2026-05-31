#pragma once

#include <memory>

#include <seraph/core/Input.hpp>
#include <seraph/core/Size.hpp>
#include <seraph/core/Window.hpp>
#include <seraph/event/EventSystem.hpp>
#include <seraph/node/Node.hpp>
#include <seraph/node/Scene.hpp>

class Game {

public:

    static constexpr float time_per_fixed_update() noexcept {
        return 1.0f / 60.0f;
    }

    Game() noexcept = default;

    constexpr const Input &input() const noexcept {
        return m_input;
    }

    constexpr const Window &window() const noexcept {
        return m_window;
    }

    constexpr std::shared_ptr<Scene> scene() {
        return m_scene;
    }

    void set_scene(const std::shared_ptr<Scene> &scene) {
        m_scene = scene;
    }

    int run();

private:

    void update(const std::shared_ptr<Node> &node, float delta_time);

    void fixed_update(const std::shared_ptr<Node> &node);

    void render();

    void draw(Node *node);

    Input m_input;

    Window m_window = Window(Size(1280.0f, 720.0f), "");

    std::shared_ptr<Scene> m_scene;
};
