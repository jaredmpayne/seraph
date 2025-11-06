#pragma once

namespace detail {

// Allows an overridable syntax for `std::visit` calls.
//
// Example:
//
// ```
// std::visit(
//     VisitorSet {
//         [](const T1 &) { ... },
//         [](const T2 &) { ... },
//         [](const auto &) { (default case) }
//     },
//     variant
// );
// ```
template<class... Ts>
struct VisitorSet : Ts... {
    
    using Ts::operator()...;
};

}
