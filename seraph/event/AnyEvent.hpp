#pragma once

#include <variant>

#include <seraph/event/detail/AnyEventVariant.hpp>

class AnyEvent : public detail::AnyEventVariant {

public:

    using detail::AnyEventVariant::variant;
};
