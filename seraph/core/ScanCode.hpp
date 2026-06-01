#pragma once

#include <optional>

#include <SFML/Window/Keyboard.hpp>

#include <seraph/core/Math.hpp>
#include <seraph/core/KeyCode.hpp>

class ScanCode {

public:

    static constexpr bool is_in_range(int value) noexcept {
        return Math::is_in_range(value, *a(), *launch_media_select());
    }

    static constexpr std::optional<ScanCode> from_value(int value) noexcept {
        if (is_in_range(value)) {
            return ScanCode(value);
        }
        return std::nullopt;
    }

    static constexpr ScanCode a() noexcept {
        return ScanCode(0);
    }

    static constexpr ScanCode b() noexcept {
        return ScanCode(1);
    }

    static constexpr ScanCode c() noexcept {
        return ScanCode(2);
    }

    static constexpr ScanCode d() noexcept {
        return ScanCode(3);
    }

    static constexpr ScanCode e() noexcept {
        return ScanCode(4);
    }

    static constexpr ScanCode f() noexcept {
        return ScanCode(5);
    }

    static constexpr ScanCode g() noexcept {
        return ScanCode(6);
    }

    static constexpr ScanCode h() noexcept {
        return ScanCode(7);
    }

    static constexpr ScanCode i() noexcept {
        return ScanCode(8);
    }

    static constexpr ScanCode j() noexcept {
        return ScanCode(9);
    }

    static constexpr ScanCode k() noexcept {
        return ScanCode(10);
    }

    static constexpr ScanCode l() noexcept {
        return ScanCode(11);
    }

    static constexpr ScanCode m() noexcept {
        return ScanCode(12);
    }

    static constexpr ScanCode n() noexcept {
        return ScanCode(13);
    }

    static constexpr ScanCode o() noexcept {
        return ScanCode(14);
    }

    static constexpr ScanCode p() noexcept {
        return ScanCode(15);
    }

    static constexpr ScanCode q() noexcept {
        return ScanCode(16);
    }

    static constexpr ScanCode r() noexcept {
        return ScanCode(17);
    }

    static constexpr ScanCode s() noexcept {
        return ScanCode(18);
    }

    static constexpr ScanCode t() noexcept {
        return ScanCode(19);
    }

    static constexpr ScanCode u() noexcept {
        return ScanCode(20);
    }

    static constexpr ScanCode v() noexcept {
        return ScanCode(21);
    }

    static constexpr ScanCode w() noexcept {
        return ScanCode(22);
    }

    static constexpr ScanCode x() noexcept {
        return ScanCode(23);
    }

    static constexpr ScanCode y() noexcept {
        return ScanCode(24);
    }

    static constexpr ScanCode z() noexcept {
        return ScanCode(25);
    }

    static constexpr ScanCode num1() noexcept {
        return ScanCode(26);
    }

    static constexpr ScanCode num2() noexcept {
        return ScanCode(27);
    }

    static constexpr ScanCode num3() noexcept {
        return ScanCode(28);
    }

    static constexpr ScanCode num4() noexcept {
        return ScanCode(29);
    }

    static constexpr ScanCode num5() noexcept {
        return ScanCode(30);
    }

    static constexpr ScanCode num6() noexcept {
        return ScanCode(31);
    }

    static constexpr ScanCode num7() noexcept {
        return ScanCode(32);
    }

    static constexpr ScanCode num8() noexcept {
        return ScanCode(33);
    }

    static constexpr ScanCode num9() noexcept {
        return ScanCode(34);
    }

    static constexpr ScanCode num0() noexcept {
        return ScanCode(35);
    }

    static constexpr ScanCode enter() noexcept {
        return ScanCode(36);
    }

    static constexpr ScanCode esc() noexcept {
        return ScanCode(37);
    }

    static constexpr ScanCode backspace() noexcept {
        return ScanCode(38);
    }

    static constexpr ScanCode tab() noexcept {
        return ScanCode(39);
    }

    static constexpr ScanCode space() noexcept {
        return ScanCode(40);
    }

    static constexpr ScanCode hyphen() noexcept {
        return ScanCode(41);
    }

    static constexpr ScanCode equal() noexcept {
        return ScanCode(42);
    }

    static constexpr ScanCode left_bracket() noexcept {
        return ScanCode(43);
    }

    static constexpr ScanCode right_bracket() noexcept {
        return ScanCode(44);
    }

    static constexpr ScanCode backslash() noexcept {
        return ScanCode(45);
    }

    static constexpr ScanCode semicolon() noexcept {
        return ScanCode(46);
    }

    static constexpr ScanCode apostrophe() noexcept {
        return ScanCode(47);
    }

    static constexpr ScanCode grave() noexcept {
        return ScanCode(48);
    }

    static constexpr ScanCode comma() noexcept {
        return ScanCode(49);
    }

    static constexpr ScanCode period() noexcept {
        return ScanCode(50);
    }

    static constexpr ScanCode slash() noexcept {
        return ScanCode(51);
    }

    static constexpr ScanCode f1() noexcept {
        return ScanCode(52);
    }

    static constexpr ScanCode f2() noexcept {
        return ScanCode(53);
    }

    static constexpr ScanCode f3() noexcept {
        return ScanCode(54);
    }

    static constexpr ScanCode f4() noexcept {
        return ScanCode(55);
    }

    static constexpr ScanCode f5() noexcept {
        return ScanCode(56);
    }

    static constexpr ScanCode f6() noexcept {
        return ScanCode(57);
    }

    static constexpr ScanCode f7() noexcept {
        return ScanCode(58);
    }

    static constexpr ScanCode f8() noexcept {
        return ScanCode(59);
    }

    static constexpr ScanCode f9() noexcept {
        return ScanCode(60);
    }

    static constexpr ScanCode f10() noexcept {
        return ScanCode(61);
    }

    static constexpr ScanCode f11() noexcept {
        return ScanCode(62);
    }

    static constexpr ScanCode f12() noexcept {
        return ScanCode(63);
    }

    static constexpr ScanCode f13() noexcept {
        return ScanCode(64);
    }

    static constexpr ScanCode f14() noexcept {
        return ScanCode(65);
    }

    static constexpr ScanCode f15() noexcept {
        return ScanCode(66);
    }

    static constexpr ScanCode f16() noexcept {
        return ScanCode(67);
    }

    static constexpr ScanCode f17() noexcept {
        return ScanCode(68);
    }

    static constexpr ScanCode f18() noexcept {
        return ScanCode(69);
    }

    static constexpr ScanCode f19() noexcept {
        return ScanCode(70);
    }

    static constexpr ScanCode f20() noexcept {
        return ScanCode(71);
    }

    static constexpr ScanCode f21() noexcept {
        return ScanCode(72);
    }

    static constexpr ScanCode f22() noexcept {
        return ScanCode(73);
    }

    static constexpr ScanCode f23() noexcept {
        return ScanCode(74);
    }

    static constexpr ScanCode f24() noexcept {
        return ScanCode(75);
    }

    static constexpr ScanCode caps_lock() noexcept {
        return ScanCode(76);
    }

    static constexpr ScanCode print_screen() noexcept {
        return ScanCode(77);
    }

    static constexpr ScanCode scroll_lock() noexcept {
        return ScanCode(78);
    }

    static constexpr ScanCode pause() noexcept {
        return ScanCode(79);
    }

    static constexpr ScanCode insert() noexcept {
        return ScanCode(80);
    }

    static constexpr ScanCode home() noexcept {
        return ScanCode(81);
    }

    static constexpr ScanCode page_up() noexcept {
        return ScanCode(82);
    }

    static constexpr ScanCode del() noexcept {
        return ScanCode(83);
    }

    static constexpr ScanCode end() noexcept {
        return ScanCode(84);
    }

    static constexpr ScanCode page_down() noexcept {
        return ScanCode(85);
    }

    static constexpr ScanCode right() noexcept {
        return ScanCode(86);
    }

    static constexpr ScanCode left() noexcept {
        return ScanCode(87);
    }

    static constexpr ScanCode down() noexcept {
        return ScanCode(88);
    }

    static constexpr ScanCode up() noexcept {
        return ScanCode(89);
    }

    static constexpr ScanCode num_lock() noexcept {
        return ScanCode(90);
    }

    static constexpr ScanCode numpad_divide() noexcept {
        return ScanCode(91);
    }

    static constexpr ScanCode numpad_multiply() noexcept {
        return ScanCode(92);
    }

    static constexpr ScanCode numpad_minus() noexcept {
        return ScanCode(93);
    }

    static constexpr ScanCode numpad_plus() noexcept {
        return ScanCode(94);
    }

    static constexpr ScanCode numpad_equal() noexcept {
        return ScanCode(95);
    }

    static constexpr ScanCode numpad_enter() noexcept {
        return ScanCode(96);
    }

    static constexpr ScanCode numpad_decimal() noexcept {
        return ScanCode(97);
    }

    static constexpr ScanCode numpad1() noexcept {
        return ScanCode(98);
    }

    static constexpr ScanCode numpad2() noexcept {
        return ScanCode(99);
    }

    static constexpr ScanCode numpad3() noexcept {
        return ScanCode(100);
    }

    static constexpr ScanCode numpad4() noexcept {
        return ScanCode(101);
    }

    static constexpr ScanCode numpad5() noexcept {
        return ScanCode(102);
    }

    static constexpr ScanCode numpad6() noexcept {
        return ScanCode(103);
    }

    static constexpr ScanCode numpad7() noexcept {
        return ScanCode(104);
    }

    static constexpr ScanCode numpad8() noexcept {
        return ScanCode(105);
    }

    static constexpr ScanCode numpad9() noexcept {
        return ScanCode(106);
    }

    static constexpr ScanCode numpad0() noexcept {
        return ScanCode(107);
    }

    static constexpr ScanCode non_us_backslash() noexcept {
        return ScanCode(108);
    }

    static constexpr ScanCode application() noexcept {
        return ScanCode(109);
    }

    static constexpr ScanCode execute() noexcept {
        return ScanCode(110);
    }

    static constexpr ScanCode mode_change() noexcept {
        return ScanCode(111);
    }

    static constexpr ScanCode help() noexcept {
        return ScanCode(112);
    }

    static constexpr ScanCode menu() noexcept {
        return ScanCode(113);
    }

    static constexpr ScanCode select() noexcept {
        return ScanCode(114);
    }

    static constexpr ScanCode redo() noexcept {
        return ScanCode(115);
    }

    static constexpr ScanCode undo() noexcept {
        return ScanCode(116);
    }

    static constexpr ScanCode cut() noexcept {
        return ScanCode(117);
    }

    static constexpr ScanCode copy() noexcept {
        return ScanCode(118);
    }

    static constexpr ScanCode paste() noexcept {
        return ScanCode(119);
    }

    static constexpr ScanCode volume_mute() noexcept {
        return ScanCode(120);
    }

    static constexpr ScanCode volume_up() noexcept {
        return ScanCode(121);
    }

    static constexpr ScanCode volume_down() noexcept {
        return ScanCode(122);
    }

    static constexpr ScanCode media_play_pause() noexcept {
        return ScanCode(123);
    }

    static constexpr ScanCode media_stop() noexcept {
        return ScanCode(124);
    }

    static constexpr ScanCode media_next_track() noexcept {
        return ScanCode(125);
    }

    static constexpr ScanCode media_previous_track() noexcept {
        return ScanCode(126);
    }

    static constexpr ScanCode left_ctrl() noexcept {
        return ScanCode(127);
    }

    static constexpr ScanCode left_shift() noexcept {
        return ScanCode(128);
    }

    static constexpr ScanCode left_alt() noexcept {
        return ScanCode(129);
    }

    static constexpr ScanCode left_system() noexcept {
        return ScanCode(130);
    }

    static constexpr ScanCode right_ctrl() noexcept {
        return ScanCode(131);
    }

    static constexpr ScanCode right_shift() noexcept {
        return ScanCode(132);
    }

    static constexpr ScanCode right_alt() noexcept {
        return ScanCode(133);
    }

    static constexpr ScanCode right_system() noexcept {
        return ScanCode(134);
    }

    static constexpr ScanCode back() noexcept {
        return ScanCode(135);
    }

    static constexpr ScanCode forward() noexcept {
        return ScanCode(136);
    }

    static constexpr ScanCode refresh() noexcept {
        return ScanCode(137);
    }

    static constexpr ScanCode stop() noexcept {
        return ScanCode(138);
    }

    static constexpr ScanCode search() noexcept {
        return ScanCode(139);
    }

    static constexpr ScanCode favorites() noexcept {
        return ScanCode(140);
    }

    static constexpr ScanCode home_page() noexcept {
        return ScanCode(141);
    }

    static constexpr ScanCode launch_application1() noexcept {
        return ScanCode(142);
    }

    static constexpr ScanCode launch_application2() noexcept {
        return ScanCode(143);
    }

    static constexpr ScanCode launch_mail() noexcept {
        return ScanCode(144);
    }

    static constexpr ScanCode launch_media_select() noexcept {
        return ScanCode(145);
    }

    constexpr auto operator<=>(const ScanCode &) const noexcept = default;

    constexpr int operator*() const noexcept {
        return value();
    }

    constexpr int value() const noexcept {
        return m_value;
    }

    constexpr std::optional<KeyCode> localized() const noexcept {
        const auto code = sf::Keyboard::Scancode(**this);
        const auto translated = int(sf::Keyboard::localize(code));
        return KeyCode::from_value(translated);
    }

private:

    constexpr ScanCode(int value) noexcept :
        m_value(value) { }

    int m_value;
};

namespace std {

    template <>
    struct hash<ScanCode> {

        size_t operator()(const ScanCode &code) const noexcept {
            return *code;
        }
    };
}

constexpr std::optional<ScanCode> KeyCode::delocalized() const noexcept {
    const auto code = sf::Keyboard::Key(**this);
    const auto translated = int(sf::Keyboard::delocalize(code));
    return ScanCode::from_value(translated);
}
