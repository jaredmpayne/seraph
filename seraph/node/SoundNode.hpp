#pragma once

#include <chrono>
#include <filesystem>
#include <optional>

#include <SFML/Audio.hpp>

#include <seraph/core/Point.hpp>
#include <seraph/node/Node.hpp>

/// A node for playing smaller audio files.
class SoundNode : public Node {

public:

    SoundNode(const std::filesystem::path &path);

    virtual void set_position(const Point &position) override;

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
