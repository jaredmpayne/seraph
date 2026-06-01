#pragma once

#include <filesystem>
#include <memory>
#include <optional>
#include <string>

#include <SFML/Graphics.hpp>

#include <seraph/core/Color.hpp>
#include <seraph/core/Rectangle.hpp>
#include <seraph/core/Window.hpp>
#include <seraph/memory/ResourceManager.hpp>
#include <seraph/node/Node.hpp>

/// A node for displaying fonted text.
class LabelNode : public Node {

public:

    LabelNode(const std::filesystem::path &font_path, const std::u32string &string = std::u32string()) :
        m_font(font_manager().get(font_path)) {

            // Using list initialization for `sf::Text` causes the resource to drop from memory.
            m_text = sf::Text(*m_font, sf::String(string));
        }

    virtual ~LabelNode() override = default;

    std::u32string_view string_view() const {
        return std::u32string_view(m_text->getString().getData());
    }

    void set_string(const std::u32string &string) {
        m_text->setString(sf::String(string));
        m_text->setOrigin(0.5f * m_text->getLocalBounds().size);
    }

    unsigned int font_size() const {
        return m_text->getCharacterSize();
    }

    void set_font_size(unsigned int font_size) {
        m_text->setCharacterSize(font_size);
    }

    constexpr const Color &fill_color() const {
        return m_fill_color;
    }

    void set_fill_color(const Color &fill_color) {
        m_fill_color = fill_color;
        const auto [r, g, b, a] = fill_color;
        m_text->setFillColor(sf::Color(r, g, b, a));
    }

    float stroke() const {
        return m_text->getOutlineThickness();
    }

    void set_stroke(float stroke) {
        m_text->setOutlineThickness(stroke);
    }

    constexpr const Color &stroke_color() const {
        return m_stroke_color;
    }

    void set_stroke_color(const Color &stroke_color) {
        m_stroke_color = stroke_color;
        const auto [r, g, b, a] = stroke_color;
        m_text->setOutlineColor(sf::Color(r, g, b, a));
    }

    virtual Rectangle frame() const override {
        const auto [w, h] = m_text->getLocalBounds().size;
        return Rectangle(position(), Size(w, h));
    }

    virtual void draw(Window &window) override {
        const auto [x, y] = absolute_position();
        const auto rotation = absolute_rotation();
        const auto [dx, dy] = absolute_scale();
        m_text->setPosition(sf::Vector2f(x, y));
        m_text->setRotation(sf::radians(rotation));
        m_text->setScale(sf::Vector2f(dx, dy));
        window.render_window().draw(m_text.value());
    }

private:

    static constexpr ResourceManager<sf::Font> &font_manager() noexcept {
        static auto manager = ResourceManager<sf::Font>();
        return manager;
    }

    std::optional<sf::Text> m_text;

    std::shared_ptr<sf::Font> m_font;

    Color m_fill_color;

    Color m_stroke_color;
};
