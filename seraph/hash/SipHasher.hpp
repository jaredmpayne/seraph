#pragma once

#include <cmath>
#include <cstddef>
#include <cstdint>

/// A fast, cryptographically secure hasher.
class SipHasher {

// Read: J. Aumasson, D. Bernstein. "SipHash: a fast short-input PRF"
// https://cr.yp.to/siphash/siphash-20120918.pdf
//
// This is a SipHash-2-4 implementation.

public:

    /// Constructs a `SipHasher` with zeroed keys.
    constexpr SipHasher() noexcept :
        SipHasher(0, 0) { }

    /// Constructs a `SipHasher` with the given keys.
    constexpr SipHasher(std::uint64_t k0, std::uint64_t k1) noexcept :
        m_k0(k0),
        m_k1(k1) {
        
        reset();
    }

    /// The `SipHasher`'s current value.
    constexpr std::uint64_t value() const noexcept {
        return m_v0 ^ m_v1 ^ m_v2 ^ m_v3;
    }

    /// Hash an array of bytes.
    void write(const std::uint8_t *bytes, std::size_t count) noexcept;

    /// Hash an object as a sequence of bytes.
    template <typename T>
    inline void write(const T &object) noexcept {
        write ((std::uint8_t *)(&object), sizeof(T));
    }

    /// Resets the `SipHasher` to its initial state.
    inline void reset() noexcept {
        m_v0 = m_k0 ^ 0x736f6d6570736575;
        m_v1 = m_k1 ^ 0x646f72616e646f6d;
        m_v2 = m_k0 ^ 0x6c7967656e657261;
        m_v3 = m_k1 ^ 0x7465646279746573;
    }

private:

    void sip_round() noexcept;

    inline std::uint64_t rotate_left(std::uint64_t word, std::uint64_t count) noexcept {
        return (word << count) | (word >> (64 - count));
    }

    inline std::uint64_t rotate_right(std::uint64_t word, std::uint64_t count) noexcept {
        return (word >> count) | (word << (64 - count));
    }

    std::uint64_t m_k0;

    std::uint64_t m_k1;

    std::uint64_t m_v0;

    std::uint64_t m_v1;

    std::uint64_t m_v2;

    std::uint64_t m_v3;
};
