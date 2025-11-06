#include <seraph/node/ShapeNode.hpp>

#include <cmath>

#include <SFML/Graphics.hpp>

#include <seraph/core/Color.hpp>
#include <seraph/core/Point.hpp>
#include <seraph/core/Rectangle.hpp>
#include <seraph/core/Vector.hpp>
#include <seraph/core/Window.hpp>
#include <seraph/node/Node.hpp>

ShapeNode::ShapeNode(float radius, unsigned int sides_count) :
    m_shape(radius, sides_count) {

    m_shape.setOrigin(sf::Vector2f(radius, radius));
    const auto fill = m_shape.getFillColor();
    const auto stroke = m_shape.getOutlineColor();
    m_fill_color = Color(fill.r, fill.g, fill.b, fill.a);
    m_stroke_color = Color(stroke.r, stroke.g, stroke.b, stroke.a);
}

Rectangle ShapeNode::frame() const {
    const auto bounds = m_shape.getGlobalBounds();
    const auto [x, y] = bounds.position;
    const auto [width, height] = bounds.size;
    return Rectangle(x, y, width, height);
}

void ShapeNode::draw(Window &window) {
    const auto [x, y] = absolute_position();
    const auto rotation = absolute_rotation();
    const auto [dx, dy] = absolute_scale();
    m_shape.setPosition(sf::Vector2f(x, y));
    m_shape.setRotation(sf::radians(rotation));
    m_shape.setScale(sf::Vector2f(dx, dy));
    window.render_window().draw(m_shape);
}
