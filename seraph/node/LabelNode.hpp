#pragma once

#include <filesystem>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include <seraph/core/Color.hpp>
#include <seraph/core/Rectangle.hpp>
#include <seraph/core/Window.hpp>
#include <seraph/node/Node.hpp>

/// A node for displaying fonted text.
class LabelNode : public Node {

public:

    LabelNode(const std::filesystem::path &font_path, const std::u32string &string = std::u32string());

    virtual ~LabelNode() override = default;

    inline std::u32string_view string_view() const {
        return std::u32string_view(m_text.getString().getData());
    }

    inline void set_string(const std::u32string &string) {
        m_text.setString(sf::String(string));
        m_text.setOrigin(0.5f * m_text.getLocalBounds().size);
    }

    inline unsigned int font_size() const {
        return m_text.getCharacterSize();
    }

    inline void set_font_size(unsigned int font_size) {
        m_text.setCharacterSize(font_size);
    }

    constexpr const Color &fill_color() const {
        return m_fill_color;
    }

    inline void set_fill_color(const Color &fill_color) {
        m_fill_color = fill_color;
        const auto [r, g, b, a] = fill_color;
        m_text.setFillColor(sf::Color(r, g, b, a));
    }

    inline float stroke() const {
        return m_text.getOutlineThickness();
    }

    inline void set_stroke(float stroke) {
        m_text.setOutlineThickness(stroke);
    }

    constexpr const Color &stroke_color() const {
        return m_stroke_color;
    }

    inline void set_stroke_color(const Color &stroke_color) {
        m_stroke_color = stroke_color;
        const auto [r, g, b, a] = stroke_color;
        m_text.setOutlineColor(sf::Color(r, g, b, a));
    }

    virtual Rectangle frame() const override;

    virtual void draw(Window &window) override;

private:

    std::shared_ptr<sf::Font> m_font;

    sf::Text m_text;

    Color m_fill_color;

    Color m_stroke_color;
};
