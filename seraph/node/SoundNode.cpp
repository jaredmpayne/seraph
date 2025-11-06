#include <seraph/node/SoundNode.hpp>

#include <chrono>
#include <filesystem>
#include <format>

#include <SFML/Audio.hpp>

#include <seraph/core/Exception.hpp>
#include <seraph/node/Node.hpp>

SoundNode::SoundNode(const std::filesystem::path &path) {
    try {
        m_buffer = sf::SoundBuffer(path);
        m_sound = sf::Sound(m_buffer);
    }
    catch (const sf::Exception &exception) {
        throw Exception(std::format("Unable to create SoundNode from file at path {}", path.string()));
    }
}

void SoundNode::set_position(const Point &position) {
    Node::set_position(position);
    m_sound.value().setPosition(sf::Vector3f(position.x(), position.y(), 0.0));
}
