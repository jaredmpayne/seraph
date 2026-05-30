#pragma once

#include <chrono>
#include <filesystem>
#include <optional>

#include <SFML/Audio.hpp>

#include <seraph/core/Exception.hpp>
#include <seraph/core/Point.hpp>
#include <seraph/node/Node.hpp>

/// A node for playing smaller audio files.
class SoundNode : public Node {

public:

    SoundNode(const std::filesystem::path &path) {
        try {
            m_buffer = sf::SoundBuffer(path);
            m_sound = sf::Sound(m_buffer);
        }
        catch (const sf::Exception &exception) {
            throw Exception(std::format("Unable to create SoundNode from file at path {}", path.string()));
        }
    }

    virtual void set_position(const Point &position) override {
        Node::set_position(position);
        const auto [x, y] = position;
        m_sound.value().setPosition(sf::Vector3f(x, y, 0.0f));
    }

    constexpr bool is_positional() const {
        return m_sound.value().isSpatializationEnabled();
    }

    void set_is_positional(bool is_positional) {
        m_sound.value().setSpatializationEnabled(is_positional);
    }

    constexpr bool is_looping() const {
        return m_sound.value().isLooping();
    }

    void set_is_looping(bool is_looping) {
        m_sound.value().setLooping(is_looping);
    }

    void play() {
        m_sound.value().play();
    }

    void pause() {
        m_sound.value().pause();
    }

    void stop() {
        m_sound.value().stop();
    }

private:

    sf::SoundBuffer m_buffer;

    std::optional<sf::Sound> m_sound;
};
