#include <seraph/hash/SipHasher.hpp>

#include <cmath>
#include <cstddef>
#include <cstdint>

void SipHasher::write(const std::uint8_t *bytes, std::size_t count) noexcept {
    const auto words = std::size_t(std::ceil(count / 8));
    for (std::size_t i = 0; i < words; i += 8) {
        m_v3 ^= *(std::uint64_t *)(bytes + i);
        sip_round();
        sip_round();
        m_v0 ^= *(std::uint64_t *)(bytes + i);
    }
    m_v2 ^= 0xff;
}

void SipHasher::sip_round() noexcept {
    m_v0 += m_v1;
    m_v1 = rotate_left(m_v1, 13);
    m_v1 ^= m_v0;
    m_v0 = rotate_left(m_v0, 32);

    m_v2 += m_v3;
    m_v3 = rotate_left(m_v3, 16);
    m_v3 ^= m_v2;

    m_v0 += m_v3;
    m_v3 = rotate_left(m_v3, 21);
    m_v3 ^= m_v0;

    m_v2 += m_v1;
    m_v1 = rotate_left(m_v1, 17);
    m_v1 ^= m_v2;
    m_v2 = rotate_left(m_v2, 32);
}
