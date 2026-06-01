#pragma once

#include <seraph/core/ScanCode.hpp>

class AnyEvent;

class KeyReleasedEvent {

public:

    constexpr KeyReleasedEvent(ScanCode scan_code) noexcept :
        m_scan_code(scan_code) { }

    constexpr ScanCode scan_code() const noexcept {
        return m_scan_code;
    }

    // NOTE: Defined in AnyEvent.hpp
    constexpr AnyEvent erased() const noexcept;

private:

    ScanCode m_scan_code;
};
