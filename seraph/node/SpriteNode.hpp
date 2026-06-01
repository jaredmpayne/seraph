#pragma once

#include <filesystem>
#include <optional>

#include <SFML/Graphics.hpp>

#include <seraph/core/Point.hpp>
#include <seraph/core/Rectangle.hpp>
#include <seraph/core/Vector.hpp>
#include <seraph/core/Window.hpp>
#include <seraph/node/Node.hpp>
#include <seraph/memory/ResourceManager.hpp>

/// A node for drawing textures that should be stored in graphics memory.
class SpriteNode : public Node {

public:

    SpriteNode(const std::filesystem::path &path) :
        m_texture(texture_manager().get(path)) {

        // Using list initialization for `sf::Sprite` causes the resource to drop from memory.
        m_sprite = sf::Sprite(*m_texture);
        const auto [width, height] = m_texture->getSize();
        m_sprite->setOrigin(sf::Vector2f(0.5f * width, 0.5f * height));
    }

    virtual Rectangle frame() const override {
        const auto bounds = m_sprite->getGlobalBounds();
        const auto [x, y] = bounds.position;
        const auto [width, height] = bounds.size;
        return Rectangle(x, y, width, height);
    }

    virtual void draw(Window &window) override {
        const auto [x, y] = absolute_position();
        const auto rotation = absolute_rotation();
        const auto [dx, dy] = absolute_scale();
        m_sprite->setPosition(sf::Vector2f(x, y));
        m_sprite->setRotation(sf::radians(rotation));
        m_sprite->setScale(sf::Vector2f(dx, dy));
        window.render_window().draw(m_sprite.value());
    }

private:

    static constexpr ResourceManager<sf::Texture> &texture_manager() noexcept {
        static auto manager = ResourceManager<sf::Texture>();
        return manager;
    }

    std::optional<sf::Sprite> m_sprite;

    std::shared_ptr<sf::Texture> m_texture;
};
