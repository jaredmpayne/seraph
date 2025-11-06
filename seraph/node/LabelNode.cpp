#include <seraph/node/LabelNode.hpp>

#include <cmath>
#include <filesystem>
#include <format>
#include <string>

#include <SFML/Graphics.hpp>

#include <seraph/core/Color.hpp>
#include <seraph/core/Exception.hpp>
#include <seraph/core/Rectangle.hpp>
#include <seraph/core/Window.hpp>
#include <seraph/memory/FontManager.hpp>
#include <seraph/node/Node.hpp>

LabelNode::LabelNode(const std::filesystem::path &font_path, const std::u32string &string) :
    m_font(FontManager::instance().get(font_path)),
    m_text(*FontManager::instance().get(font_path), sf::String(string)) { }

Rectangle LabelNode::frame() const {
    const auto [w, h] = m_text.getLocalBounds().size;
    return Rectangle(position(), Size(w, h));
}

void LabelNode::draw(Window &window) {
    const auto [x, y] = absolute_position();
    const auto rotation = absolute_rotation();
    const auto [dx, dy] = absolute_scale();
    m_text.setPosition(sf::Vector2f(x, y));
    m_text.setRotation(sf::radians(rotation));
    m_text.setScale(sf::Vector2f(dx, dy));
    window.render_window().draw(m_text);
}
