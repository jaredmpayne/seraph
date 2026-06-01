#pragma once

#include <optional>

#include <seraph/core/Math.hpp>

class ScanCode;

class KeyCode {

public:

    static constexpr bool is_in_range(int value) noexcept {
        return Math::is_in_range(value, *a(), *pause());
    }

    static constexpr std::optional<KeyCode> from_value(int value) noexcept {
        if (is_in_range(value)) {
            return KeyCode(value);
        }
        return std::nullopt;
    }

    static constexpr KeyCode a() noexcept {
        return KeyCode(0);
    }

    static constexpr KeyCode b() noexcept {
        return KeyCode(1);
    }

    static constexpr KeyCode c() noexcept {
        return KeyCode(2);
    }

    static constexpr KeyCode d() noexcept {
        return KeyCode(3);
    }

    static constexpr KeyCode e() noexcept {
        return KeyCode(4);
    }

    static constexpr KeyCode f() noexcept {
        return KeyCode(5);
    }

    static constexpr KeyCode g() noexcept {
        return KeyCode(6);
    }

    static constexpr KeyCode h() noexcept {
        return KeyCode(7);
    }

    static constexpr KeyCode i() noexcept {
        return KeyCode(8);
    }

    static constexpr KeyCode j() noexcept {
        return KeyCode(9);
    }

    static constexpr KeyCode k() noexcept {
        return KeyCode(10);
    }

    static constexpr KeyCode l() noexcept {
        return KeyCode(11);
    }

    static constexpr KeyCode m() noexcept {
        return KeyCode(12);
    }

    static constexpr KeyCode n() noexcept {
        return KeyCode(13);
    }

    static constexpr KeyCode o() noexcept {
        return KeyCode(14);
    }

    static constexpr KeyCode p() noexcept {
        return KeyCode(15);
    }

    static constexpr KeyCode q() noexcept {
        return KeyCode(16);
    }

    static constexpr KeyCode r() noexcept {
        return KeyCode(17);
    }

    static constexpr KeyCode s() noexcept {
        return KeyCode(18);
    }

    static constexpr KeyCode t() noexcept {
        return KeyCode(19);
    }

    static constexpr KeyCode u() noexcept {
        return KeyCode(20);
    }

    static constexpr KeyCode v() noexcept {
        return KeyCode(21);
    }

    static constexpr KeyCode w() noexcept {
        return KeyCode(22);
    }

    static constexpr KeyCode x() noexcept {
        return KeyCode(23);
    }

    static constexpr KeyCode y() noexcept {
        return KeyCode(24);
    }

    static constexpr KeyCode z() noexcept {
        return KeyCode(25);
    }

    static constexpr KeyCode num0() noexcept {
        return KeyCode(26);
    }

    static constexpr KeyCode num1() noexcept {
        return KeyCode(27);
    }

    static constexpr KeyCode num2() noexcept {
        return KeyCode(28);
    }

    static constexpr KeyCode num3() noexcept {
        return KeyCode(29);
    }

    static constexpr KeyCode num4() noexcept {
        return KeyCode(30);
    }

    static constexpr KeyCode num5() noexcept {
        return KeyCode(31);
    }

    static constexpr KeyCode num6() noexcept {
        return KeyCode(32);
    }

    static constexpr KeyCode num7() noexcept {
        return KeyCode(33);
    }

    static constexpr KeyCode num8() noexcept {
        return KeyCode(34);
    }

    static constexpr KeyCode num9() noexcept {
        return KeyCode(35);
    }

    static constexpr KeyCode esc() noexcept {
        return KeyCode(36);
    }

    static constexpr KeyCode left_ctrl() noexcept {
        return KeyCode(37);
    }

    static constexpr KeyCode left_shift() noexcept {
        return KeyCode(38);
    }

    static constexpr KeyCode left_alt() noexcept {
        return KeyCode(39);
    }

    static constexpr KeyCode left_system() noexcept {
        return KeyCode(40);
    }

    static constexpr KeyCode right_ctrl() noexcept {
        return KeyCode(41);
    }

    static constexpr KeyCode right_shift() noexcept {
        return KeyCode(42);
    }

    static constexpr KeyCode right_alt() noexcept {
        return KeyCode(43);
    }

    static constexpr KeyCode right_system() noexcept {
        return KeyCode(44);
    }

    static constexpr KeyCode menu() noexcept {
        return KeyCode(45);
    }

    static constexpr KeyCode left_bracket() noexcept {
        return KeyCode(46);
    }

    static constexpr KeyCode right_bracket() noexcept {
        return KeyCode(47);
    }

    static constexpr KeyCode semicolon() noexcept {
        return KeyCode(48);
    }

    static constexpr KeyCode comma() noexcept {
        return KeyCode(49);
    }

    static constexpr KeyCode period() noexcept {
        return KeyCode(50);
    }

    static constexpr KeyCode apostrophe() noexcept {
        return KeyCode(51);
    }

    static constexpr KeyCode slash() noexcept {
        return KeyCode(52);
    }

    static constexpr KeyCode backslash() noexcept {
        return KeyCode(53);
    }

    static constexpr KeyCode grave() noexcept {
        return KeyCode(54);
    }

    static constexpr KeyCode equal() noexcept {
        return KeyCode(55);
    }

    static constexpr KeyCode hyphen() noexcept {
        return KeyCode(56);
    }

    static constexpr KeyCode space() noexcept {
        return KeyCode(57);
    }

    static constexpr KeyCode enter() noexcept {
        return KeyCode(58);
    }

    static constexpr KeyCode backspace() noexcept {
        return KeyCode(59);
    }

    static constexpr KeyCode tab() noexcept {
        return KeyCode(60);
    }

    static constexpr KeyCode page_up() noexcept {
        return KeyCode(61);
    }

    static constexpr KeyCode page_down() noexcept {
        return KeyCode(62);
    }

    static constexpr KeyCode end() noexcept {
        return KeyCode(63);
    }

    static constexpr KeyCode home() noexcept {
        return KeyCode(64);
    }

    static constexpr KeyCode insert() noexcept {
        return KeyCode(65);
    }

    static constexpr KeyCode del() noexcept {
        return KeyCode(66);
    }

    static constexpr KeyCode add() noexcept {
        return KeyCode(67);
    }

    static constexpr KeyCode subtract() noexcept {
        return KeyCode(68);
    }

    static constexpr KeyCode multiply() noexcept {
        return KeyCode(69);
    }

    static constexpr KeyCode divide() noexcept {
        return KeyCode(70);
    }

    static constexpr KeyCode left() noexcept {
        return KeyCode(71);
    }

    static constexpr KeyCode right() noexcept {
        return KeyCode(72);
    }

    static constexpr KeyCode up() noexcept {
        return KeyCode(73);
    }

    static constexpr KeyCode down() noexcept {
        return KeyCode(74);
    }

    static constexpr KeyCode numpad0() noexcept {
        return KeyCode(75);
    }

    static constexpr KeyCode numpad1() noexcept {
        return KeyCode(76);
    }

    static constexpr KeyCode numpad2() noexcept {
        return KeyCode(77);
    }

    static constexpr KeyCode numpad3() noexcept {
        return KeyCode(78);
    }

    static constexpr KeyCode numpad4() noexcept {
        return KeyCode(79);
    }

    static constexpr KeyCode numpad5() noexcept {
        return KeyCode(80);
    }

    static constexpr KeyCode numpad6() noexcept {
        return KeyCode(81);
    }

    static constexpr KeyCode numpad7() noexcept {
        return KeyCode(82);
    }

    static constexpr KeyCode numpad8() noexcept {
        return KeyCode(83);
    }

    static constexpr KeyCode numpad9() noexcept {
        return KeyCode(84);
    }

    static constexpr KeyCode f1() noexcept {
        return KeyCode(85);
    }

    static constexpr KeyCode f2() noexcept {
        return KeyCode(86);
    }

    static constexpr KeyCode f3() noexcept {
        return KeyCode(87);
    }

    static constexpr KeyCode f4() noexcept {
        return KeyCode(88);
    }

    static constexpr KeyCode f5() noexcept {
        return KeyCode(89);
    }

    static constexpr KeyCode f6() noexcept {
        return KeyCode(90);
    }

    static constexpr KeyCode f7() noexcept {
        return KeyCode(91);
    }

    static constexpr KeyCode f8() noexcept {
        return KeyCode(92);
    }

    static constexpr KeyCode f9() noexcept {
        return KeyCode(93);
    }

    static constexpr KeyCode f10() noexcept {
        return KeyCode(94);
    }

    static constexpr KeyCode f11() noexcept {
        return KeyCode(95);
    }

    static constexpr KeyCode f12() noexcept {
        return KeyCode(96);
    }

    static constexpr KeyCode f13() noexcept {
        return KeyCode(97);
    }

    static constexpr KeyCode f14() noexcept {
        return KeyCode(98);
    }

    static constexpr KeyCode f15() noexcept {
        return KeyCode(99);
    }

    static constexpr KeyCode pause() noexcept {
        return KeyCode(100);
    }

    constexpr auto operator<=>(const KeyCode &) const noexcept = default;

    constexpr int operator*() const noexcept {
        return value();
    }

    constexpr int value() const noexcept {
        return m_value;
    }

    // NOTE: Defined in ScanCode.hpp
    constexpr std::optional<ScanCode> delocalized() const noexcept;

private:

    constexpr KeyCode(int value) noexcept :
        m_value(value) { }

    int m_value;
};

namespace std {

    template <>
    struct hash<KeyCode> {

        size_t operator()(const KeyCode &code) const noexcept {
            return *code;
        }
    };
}
