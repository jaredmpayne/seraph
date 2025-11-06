#pragma once

#include <chrono>
#include <filesystem>

#include <SFML/Audio.hpp>

#include <seraph/core/Point.hpp>
#include <seraph/node/Node.hpp>

/// A node for playing larger audio files.
class MusicNode : public Node {

public:

    MusicNode(const std::filesystem::path &path);

    virtual void set_position(const Point &position) override;

    inline bool is_positional() const {
        return m_music.isSpatializationEnabled();
    }

    inline void set_is_positional(bool is_positional) {
        m_music.setSpatializationEnabled(is_positional);
    }

    inline bool is_looping() const {
        return m_music.isLooping();
    }

    inline void set_is_looping(bool is_looping) {
        m_music.setLooping(is_looping);
    }

    template <typename Rep, typename Period>
    inline const std::chrono::duration<Rep, Period> &loop_offset() const {
        return m_music.getLoopPoints().offset;
    }

    template <typename Rep, typename Period>
    inline void set_loop_offset(const std::chrono::duration<Rep, Period> &loop_offset) {
        m_music.setLoopPoints(sf::Music::TimeSpan(loop_offset, m_music.getLoopPoints().length));
    }

    template <typename Rep, typename Period>
    inline const std::chrono::duration<Rep, Period> &loop_length() const {
        return m_music.getLoopPoints().length;
    }

    template <typename Rep, typename Period>
    inline void set_loop_length(const std::chrono::duration<Rep, Period> &loop_length) {
        m_music.setLoopPoints(sf::Music::TimeSpan(m_music.getLoopPoints().offset, loop_length));
    }

    inline void play() {
        m_music.play();
    }

    inline void pause() {
        m_music.pause();
    }

    inline void stop() {
        m_music.stop();
    }

private:

    sf::Music m_music;
};
