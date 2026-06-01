#include <seraph/core/Game.hpp>

#include <cstdlib>
#include <memory>

#include <seraph/core/Clock.hpp>
#include <seraph/event/EventSystem.hpp>
#include <seraph/node/Node.hpp>

int Game::run() {
    auto clock = Clock();
    auto time_since_last_fixed_update = 0.0f;
    while (window().is_open()) {
        EventSystem(m_input, *m_window).update();
        update(scene(), clock.time_elapsed());
        time_since_last_fixed_update += clock.restart();
        while (time_since_last_fixed_update > time_per_fixed_update()) {
            time_since_last_fixed_update -= time_per_fixed_update();
            scene()->physics_world().update(scene(), time_per_fixed_update());
            fixed_update(scene());
        }
        render();
    }
    return EXIT_SUCCESS;
}

void Game::update(const std::shared_ptr<Node> &node, float delta_time) {
    if (!node->is_initialized()) {
        node->initialize();
        node->set_is_initialized(true);
    }
    node->update(delta_time);
    for (const auto &child : node->children()) {
        update(child, delta_time);
    }
}

void Game::fixed_update(const std::shared_ptr<Node> &node) {
    node->fixed_update(time_per_fixed_update());
    for (const auto &child : node->children()) {
        fixed_update(child);
    }
}

void Game::render() {
    m_window->clear(m_scene->background_color());
    draw(m_scene.get());
    m_window->display();
}

void Game::draw(Node *node) {
    if (!node->is_hidden()) {
        node->draw(*m_window);
        for (const auto &child : node->children()) {
            draw(child.get());
        }
    }
}
