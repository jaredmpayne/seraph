#include <seraph/core/Game.hpp>

#include <cstdlib>
#include <memory>
#include <variant>

#include <seraph/core/Clock.hpp>
#include <seraph/core/Input.hpp>
#include <seraph/core/Size.hpp>
#include <seraph/core/Window.hpp>
#include <seraph/detail/VisitorSet.hpp>
#include <seraph/event/FocusGainedEvent.hpp>
#include <seraph/event/FocusLostEvent.hpp>
#include <seraph/event/KeyPressedEvent.hpp>
#include <seraph/event/KeyReleasedEvent.hpp>
#include <seraph/event/MouseMovedEvent.hpp>
#include <seraph/event/MousePressedEvent.hpp>
#include <seraph/event/MouseReleasedEvent.hpp>
#include <seraph/event/WindowClosedEvent.hpp>
#include <seraph/node/Node.hpp>
#include <seraph/node/Scene.hpp>

int Game::run() {
    auto clock = Clock();
    auto time_since_last_fixed_update = 0.0f;
    while (m_window.is_open()) {
        Input::shared().tick_next_update();
        process_events();
        update(m_scene, clock.time_elapsed());
        time_since_last_fixed_update += clock.restart();
        while (time_since_last_fixed_update > time_per_fixed_update()) {
            time_since_last_fixed_update -= time_per_fixed_update();
            m_scene->physics_world().update(m_scene, time_per_fixed_update());
            fixed_update(m_scene);
        }
        render();
    }
    return EXIT_SUCCESS;
}

void Game::process_events() {
    while (const auto event = m_window.next_event()) {
        std::visit(
            detail::VisitorSet {
                [&](const FocusGainedEvent &event) {
                    on_gain_focus();
                },
                [&](const FocusLostEvent &event) {
                    on_lose_focus();
                },
                [&](const KeyPressedEvent &event) {
                    Input::shared().set_key_down(event.key_code());
                },
                [&](const KeyReleasedEvent &event) {
                    Input::shared().set_key_up(event.key_code());
                },
                [&](const MouseMovedEvent &event) {
                    Input::shared().set_mouse_position(event.position());
                },
                [&](const MousePressedEvent &event) {
                    Input::shared().set_mouse_down(event.mouse_code());
                },
                [&](const MouseReleasedEvent &event) {
                    Input::shared().set_mouse_up(event.mouse_code());
                },
                [&](const WindowClosedEvent &event) {
                    m_window.close();
                },
                // TODO: Implement the remaining event types handled by SFML.
                [](const auto &event) { }
            },
            *event
        );
    }
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
    m_window.clear(m_scene->background_color());
    draw(m_scene);
    m_window.display();
}

void Game::draw(const std::shared_ptr<Node> &node) {
    if (!node->is_hidden()) {
        node->draw(m_window);
        for (const auto &child : node->children()) {
            draw(child);
        }
    }
}
