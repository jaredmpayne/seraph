#include <seraph/node/MusicNode.hpp>

#include <chrono>
#include <filesystem>
#include <format>

#include <SFML/Audio.hpp>

#include <seraph/core/Exception.hpp>
#include <seraph/node/Node.hpp>

MusicNode::MusicNode(const std::filesystem::path &path) {
    if (!m_music.openFromFile(path)) {
        throw Exception(std::format("Unable to create MusicNode from file at path {}", path.string()));
    }
}

void MusicNode::set_position(const Point &position) {
    Node::set_position(position);
    m_music.setPosition(sf::Vector3f(position.x(), position.y(), 0.0f));
}
