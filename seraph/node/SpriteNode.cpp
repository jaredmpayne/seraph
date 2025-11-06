#include <seraph/node/SpriteNode.hpp>

#include <filesystem>

#include <SFML/Graphics.hpp>

#include <seraph/core/Point.hpp>
#include <seraph/core/Rectangle.hpp>
#include <seraph/core/Vector.hpp>
#include <seraph/core/Window.hpp>
#include <seraph/memory/TextureManager.hpp>
#include <seraph/node/Node.hpp>

SpriteNode::SpriteNode(const std::filesystem::path &path) :
    m_texture(TextureManager::instance().get(path)) {
    
    // TODO: Unlike fonts, using list initialization for `sf::Sprite` right
    // after initializing `m_texture` causes the resource to drop from memory.
    m_sprite = sf::Sprite(*m_texture);
    const auto [width, height] = m_texture->getSize();
    m_sprite.value().setOrigin(sf::Vector2f(0.5f * width, 0.5f * height));
}

Rectangle SpriteNode::frame() const {
    const auto bounds = m_sprite.value().getGlobalBounds();
    const auto [x, y] = bounds.position;
    const auto [width, height] = bounds.size;
    return Rectangle(x, y, width, height);
}

void SpriteNode::draw(Window &window) {
    const auto [x, y] = absolute_position();
    const auto rotation = absolute_rotation();
    const auto [dx, dy] = absolute_scale();
    m_sprite.value().setPosition(sf::Vector2f(x, y));
    m_sprite.value().setRotation(sf::radians(rotation));
    m_sprite.value().setScale(sf::Vector2f(dx, dy));
    window.render_window().draw(m_sprite.value());
}
