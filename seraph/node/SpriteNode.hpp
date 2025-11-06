#pragma once

#include <filesystem>
#include <optional>

#include <SFML/Graphics.hpp>

#include <seraph/core/Point.hpp>
#include <seraph/core/Rectangle.hpp>
#include <seraph/core/Vector.hpp>
#include <seraph/core/Window.hpp>
#include <seraph/node/Node.hpp>

/// A node for drawing textures that should be stored in graphics memory.
class SpriteNode : public Node {

public:

    SpriteNode(const std::filesystem::path &path);

    virtual ~SpriteNode() override = default;

    virtual Rectangle frame() const override;

    virtual void draw(Window &window) override;

private:

    std::shared_ptr<sf::Texture> m_texture;

    std::optional<sf::Sprite> m_sprite;
};
