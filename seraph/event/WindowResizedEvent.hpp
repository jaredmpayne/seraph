#pragma once

#include <seraph/core/Size.hpp>

class WindowResizedEvent {

public:

    constexpr WindowResizedEvent(const Size &size) noexcept :
        m_size(size) { }

    constexpr const Size &size() const noexcept {
        return m_size;
    }

private:

    Size m_size;
};
